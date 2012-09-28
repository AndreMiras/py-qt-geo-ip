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
    QSettings settings(MainWindow::getSettingsFilename());
    int mapThemeComboBoxIndex;

    QString geoLiteCityPath = settings.value(
            "geoLiteCityPath",
            QString::fromStdString(MainWindow::defaultGeoIpPath)).toString();
    widget.geoLiteCityPathLineEdit->setText(geoLiteCityPath);
    QString mapTheme = settings.value(
            "mapTheme", 0).toString();
    mapThemeComboBoxIndex = widget.mapThemeComboBox->findText(mapTheme);

    // if the mapTheme doesn't exist set the index to the first (default)
    if(mapThemeComboBoxIndex == -1)
    {
        mapThemeComboBoxIndex = 0;
    }
    widget.mapThemeComboBox->setCurrentIndex(mapThemeComboBoxIndex);
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

QString PreferencesForm::getMapTheme()
{
    return widget.mapThemeComboBox->currentText();
}

void PreferencesForm::saveSettings()
{
    QSettings settings(MainWindow::getSettingsFilename());

    settings.setValue(
            "geoLiteCityPath", widget.geoLiteCityPathLineEdit->text());
    settings.setValue(
            "mapTheme", widget.mapThemeComboBox->currentText());
}