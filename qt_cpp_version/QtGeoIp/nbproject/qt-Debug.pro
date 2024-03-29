# This file is generated automatically. Do not edit.
# Use project properties -> Build -> Qt -> Expert -> Custom Definitions.
TEMPLATE = app
DESTDIR = dist/Debug/GNU-Linux-x86
TARGET = QtGeoIp
VERSION = 1.0.0
CONFIG -= debug_and_release app_bundle lib_bundle
CONFIG += debug 
PKGCONFIG +=
QT = core gui network xml webkit
SOURCES += InstallMapItemWidget.cpp MainWindow.cpp main.cpp PreferencesForm.cpp CustomMarbleWidget.cpp MapInstallerForm.cpp MapItemModel.cpp
HEADERS += PreferencesForm.h CustomMarbleWidget.h MapItemModel.h InstallMapItemWidget.h MapInstallerForm.h MainWindow.h
FORMS += MapInstallerForm.ui main_window_ui.ui InstallMapItemWidget.ui PreferencesForm.ui
RESOURCES +=
TRANSLATIONS +=
OBJECTS_DIR = build/Debug/GNU-Linux-x86
MOC_DIR = 
RCC_DIR = 
UI_DIR = 
QMAKE_CC = gcc
QMAKE_CXX = g++
DEFINES += 
INCLUDEPATH += 
LIBS += -lmarblewidget -lGeoIP -lquazip  
