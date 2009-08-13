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

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
};

#endif // MAINWINDOW_H
