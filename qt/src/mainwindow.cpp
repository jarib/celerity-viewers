//
//  mainwindow.cpp
//  QtCelerityViewer
//
//  Created by Jari Bakken on 2009-08-13.
//  Copyright 2009 Jari Bakken. All rights reserved.
//


#include "mainwindow.h"
#include <QToolBar>
#include <QMenuBar>
#include <QStyle>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("CelerityViewer");

    createLocationEdit();
    createWebView();
    createToolBar();

    setCentralWidget(view);
}

MainWindow::~MainWindow()
{

}

void MainWindow::setLocation(QString location)
{
    locationEdit->setText(location);
}

void MainWindow::createLocationEdit()
{
    locationEdit = new QLineEdit(this);
    locationEdit->setSizePolicy(QSizePolicy::MinimumExpanding, locationEdit->sizePolicy().verticalPolicy());
    locationEdit->setReadOnly(true);

    QFont font = locationEdit->font();
    font.setPixelSize(11);
    locationEdit->setFont(font);
 }

void MainWindow::createToolBar()
{
    QToolBar *toolBar = addToolBar(tr("Navigation"));
    toolBar->setMinimumHeight(50);
    toolBar->addWidget(locationEdit);
    toolBar->addAction(view->pageAction(QWebPage::InspectElement));
 }

void MainWindow::createWebView()
{
    QString initialUrl = "http://celerity.rubyforge.org/";


    view = new QWebView(this);
    view->setHtml("<p style=\"font-size: 12px\">Loading QtCelerityViewer...</pre>");
    view->load(initialUrl);
    setLocation(initialUrl);
}

