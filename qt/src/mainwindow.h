//
//  mainwindow.h
//  QtCelerityViewer
//
//  Created by Jari Bakken on 2009-08-13.
//  Copyright 2009 Jari Bakken. All rights reserved.
//


#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QWebView>
#include <QLineEdit>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QWebView *view;

public slots:
    void setLocation(QString location);

private:
    QLineEdit *locationEdit;
    void createLocationEdit();
    void createToolBar();
    void createWebView();
};

#endif // MAINWINDOW_H
