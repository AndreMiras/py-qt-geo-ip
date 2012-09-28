/*
 * File:   main.cpp
 * Author: andre
 *
 * Created on September 23, 2012, 11:08 PM
 */
#include <QtGui/QApplication>
#include <marble/MarbleWidget.h>
#include "MainWindow.h"

using namespace Marble;
 
int main(int argc, char** argv)
{
    QApplication app(argc,argv);

    app.setApplicationName("QtGeoIp");

    MainWindow form;
    form.show();
 
    return app.exec();
}
