/*
 * File:   newForm.cpp
 * Author: andre
 *
 * Created on September 23, 2012, 11:09 PM
 */

#include "MainWindow.h"

MainWindow::MainWindow()
{
    widget.setupUi(this);
    customSetupUi();
}

MainWindow::~MainWindow()
{
}

void MainWindow::customSetupUi()
{   
    // Adds marble widget
    marbleWidget = new CustomMarbleWidget();
    marbleWidget->setMapThemeId("earth/plain/plain.dgml");
    marbleWidget->goHome();
    widget.middleVerticalLayout->addWidget(marbleWidget);

    // setup signals/slots hooks
    connect(widget.searchButton, SIGNAL(clicked()),
            this, SLOT(geoCodeIp()));
}

GeoIPRecord* MainWindow::get_ip_record(const std::string& ip)
{
    GeoIP * gi;
    // TODO: handle if the file doesn't exit
    gi = GeoIP_open("/usr/share/GeoIP/GeoLiteCity.dat", GEOIP_STANDARD);
    GeoIPRecord* geoIPRecord = GeoIP_record_by_addr(gi, ip.c_str());
    GeoIP_delete(gi);
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
        marbleWidget->centerOn(longitude, latitude, true);
        marbleWidget->zoomView(1500, Linear);
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
        GeoIPRecord_delete(geoIPRecord);
    }
}