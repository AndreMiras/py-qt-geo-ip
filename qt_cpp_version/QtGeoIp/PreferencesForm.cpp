/*
 * File:   PreferencesForm.cpp
 * Author: andre
 *
 * Created on September 25, 2012, 2:09 PM
 */

#include "PreferencesForm.h"
#include "MainWindow.h"
#include <QCoreApplication>
#include <QSettings>
#include <QFileDialog>

PreferencesForm::PreferencesForm()
{
    widget.setupUi(this);
    customSetupUi();
    setupSignalsSlots();
}

PreferencesForm::~PreferencesForm()
{
}

void PreferencesForm::setupSignalsSlots()
{
    connect(widget.okCancelButtonBox, SIGNAL(accepted()),
            this, SLOT(saveSettings()));
    connect(widget.browsePushButton, SIGNAL(clicked()),
            this, SLOT(browse()));
    
}

void PreferencesForm::customSetupUi()
{
    QSettings settings;

    QString geoLiteCityPath = settings.value(
            "geoLiteCityPath",
            QString::fromStdString(MainWindow::geoIpDefaultPath)).toString();
    widget.geoLiteCityPathLineEdit->setText(geoLiteCityPath);
}

void PreferencesForm::browse()
{
    // FIXME: hardcoded default path
    QString fileName = QFileDialog::getOpenFileName(
            this, tr("Open Database"), "/", tr("Database Files (*.dat)"));

    if (!fileName.isEmpty())
    {
        widget.geoLiteCityPathLineEdit->setText(fileName);
    }
}


void PreferencesForm::saveSettings()
{
    QSettings settings;

    settings.setValue(
            "geoLiteCityPath", widget.geoLiteCityPathLineEdit->text());
}