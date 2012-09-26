/*
 * File:   newForm.cpp
 * Author: andre
 *
 * Created on September 23, 2012, 11:09 PM
 */

#include "MainWindow.h"
#include "PreferencesForm.h"
#include <QFile>
#include <QMessageBox>
#include <QSettings>
#include <marble/GeoPainter.h>
#include <qt4/QtCore/qcoreapplication.h>


const string MainWindow::geoIpDefaultPath =
        "/usr/share/GeoIP/GeoLiteCity.dat";

MainWindow::MainWindow()
{
    widget.setupUi(this);
    customSetupUi();
}

MainWindow::~MainWindow()
{
    if (preferencesForm != NULL)
    {
        delete preferencesForm;
    }
}

void MainWindow::customSetupUi()
{
    QApplication::setApplicationName(applicationName);
    updateZoomTimer = new QTimer(this);

    // adds marble widget
    marbleWidget = new CustomMarbleWidget();
    marbleWidget->setMapThemeId("earth/plain/plain.dgml");
    marbleWidget->setAnimationsEnabled(true);
    marbleWidget->goHome();
    widget.middleVerticalLayout->addWidget(marbleWidget);

    preferencesForm = NULL;

    // setups signals/slots hooks
    connect(widget.searchButton, SIGNAL(clicked()),
            this, SLOT(geoCodeIp()));
    connect(widget.actionPreferences, SIGNAL(triggered()),
            this, SLOT(openSettings()));
    connect(updateZoomTimer, SIGNAL(timeout()),
            this, SLOT(updateZoom()));
}

void MainWindow::openSettings()
{
    if(preferencesForm == NULL)
    {
        preferencesForm = new PreferencesForm();
    }
    preferencesForm->exec();
}

GeoIPRecord* MainWindow::get_ip_record(const std::string& ip)
{
    GeoIP * gi;
    GeoIPRecord* geoIPRecord;
    QSettings settings;
    QString geoLiteCityPath;

    geoLiteCityPath = settings.value(
            "geoLiteCityPath",
            QString::fromStdString(MainWindow::geoIpDefaultPath)).toString();

    if (QFile(geoLiteCityPath).exists())
    {
        gi = GeoIP_open(geoLiteCityPath.toStdString().c_str(), GEOIP_STANDARD);
        geoIPRecord = GeoIP_record_by_addr(gi, ip.c_str());
        GeoIP_delete(gi);
    }
    else
    {
        geoIPRecord = NULL;
        QMessageBox msgBox;
        msgBox.setText("File not found: " + geoLiteCityPath);
        msgBox.exec();
    }
    return geoIPRecord;
}

void MainWindow::update_labels_from_record(
        const GeoIPRecord* record_by_addr)
{
    QString defaultValue("Unknown");
    QString city(defaultValue);
    QString region_name(defaultValue);
    QString country_name(defaultValue);
    QString latitude(defaultValue);
    QString longitude(defaultValue);

    if (record_by_addr != NULL)
    {
        latitude = QString::number(record_by_addr->latitude);
        longitude = QString::number(record_by_addr->longitude);
        city = record_by_addr->city;
        region_name = record_by_addr->region;
        country_name = record_by_addr->country_name;
    }
    // setting labels
    widget.cityLabel->setText(city);
    widget.regionLabel->setText(region_name);
    widget.countryLabel->setText(country_name);
    widget.longitudeLabel->setText(longitude);
    widget.latitudeLabel->setText(latitude);
}

void MainWindow::update_map_from_record(
        GeoIPRecord* record_by_addr, const std::string& ip)
{
    if (record_by_addr != NULL)
    {
        float longitude = record_by_addr->longitude;
        float latitude = record_by_addr->latitude;
        Marker marker;
        marker.latitude = latitude;
        marker.longitude = longitude;
        marker.text = ip;
        marbleWidget->addMarker(marker);
        GeoDataCoordinates geoDataCoordinates(
        longitude, latitude, defaultZoom, GeoDataCoordinates::Degree);
        // marbleWidget->centerOn(longitude, latitude, true);
        marbleWidget->centerOn(geoDataCoordinates, true);
        // marbleWidget->zoomView(defaultZoom, Jump);
    }
}

/**
 * This is a workaround to make zoom working after map centering
 */
void MainWindow::updateZoom()
{
    updateZoomTimer->stop();
    if(marbleWidget->zoom() != defaultZoom)
    {
        marbleWidget->zoomView(defaultZoom, Jump);
    }
}

void MainWindow::geoCodeIp()
{
    std::string ip = widget.ipLineEdit->text().toStdString();
    GeoIPRecord* geoIPRecord = get_ip_record(ip);
    update_labels_from_record(geoIPRecord);
    update_map_from_record(geoIPRecord, ip);
    if(geoIPRecord != NULL)
    {
        if(marbleWidget->zoom() != defaultZoom)
        {
            updateZoomTimer->start(1000);
        }
        GeoIPRecord_delete(geoIPRecord);
    }
}