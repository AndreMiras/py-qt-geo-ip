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
 
    /*
    // Create a Marble QWidget without a parent
    MarbleWidget *mapWidget = new MarbleWidget();
 
    // Load the OpenStreetMap map
    mapWidget->setMapThemeId("earth/openstreetmap/openstreetmap.dgml");
 
    mapWidget->show();
    */

    MainWindow form;
    form.show();
 
    return app.exec();
}


int mainDisabled(int argc, char *argv[])
{
    // initialize resources, if needed
    // Q_INIT_RESOURCE(resfile);

    QApplication app(argc, argv);

    // create and show your widgets here

    return app.exec();
}
