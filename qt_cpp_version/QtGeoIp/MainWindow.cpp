/*
 * File:   MainWindow.cpp
 * Author: andre
 *
 * Created on September 23, 2012, 11:09 PM
 */

#include "MainWindow.h"
#include <iostream>
#include "PreferencesForm.h"
#include <QUrl>
#include <QFile>
#include <QSettings>
#include <QMessageBox>
#include <QDesktopServices>
#include <QDirIterator>
#include <QStack>
#include <marble/GeoPainter.h>
#include <marble/MapThemeManager.h>
#include <marble/MarbleDirs.h>
#include <qt4/QtCore/qglobal.h>


const string MainWindow::defaultGeoIpPath =
        "/usr/share/GeoIP/GeoLiteCity.dat";
const string MainWindow::defaultMapTheme = "earth/plain/plain.dgml";
QString MainWindow::settingsFilename;
QDir MainWindow::localMarbleDir;
QDir MainWindow::systemMarbleDir;
// TODO: ~/.local/share/data/QtGeoIp != ~/.local/share/QtGeoIp/data
QDir MainWindow::runningAppDataDir;

MainWindow::MainWindow()
{
    widget.setupUi(this);
    customSetupUi();
    setupSignalsSlots();
}

MainWindow::~MainWindow()
{
    if (preferencesForm != NULL)
    {
        delete preferencesForm;
    }
    if (mapInstallerForm != NULL)
    {
        delete mapInstallerForm;
    }
}

void MainWindow::setupSignalsSlots()
{
    // setups signals/slots hooks
    connect(widget.searchButton, SIGNAL(clicked()),
            this, SLOT(geoCodeIp()));
    connect(widget.actionPreferences, SIGNAL(triggered()),
            this, SLOT(openSettings()));
    connect(widget.actionDownloadMaps, SIGNAL(triggered()),
            this, SLOT(openDownloadMap()));
    connect(widget.actionDownloadGeoCityLite, SIGNAL(triggered()),
            this, SLOT(openDownloadGeoLite()));
    connect(updateZoomTimer, SIGNAL(timeout()),
            this, SLOT(updateZoom()));
}

void MainWindow::customSetupUi()
{
    /* setup globals */
    settingsFilename = QCoreApplication::applicationName();
    localMarbleDir = QDir::cleanPath(MarbleDirs::localPath());
    systemMarbleDir = QDir::cleanPath(MarbleDirs::systemPath());
    runningAppDataDir = QDir::cleanPath(
        QDesktopServices::storageLocation(QDesktopServices::DataLocation));

    updateZoomTimer = new QTimer(this);
    preferencesForm = NULL;
    mapInstallerForm = NULL;

    // adds marble widget
    marbleWidget = new CustomMarbleWidget();
    updateMapTheme();
    marbleWidget->setShowGrid(false);
    marbleWidget->setAnimationsEnabled(true);
    marbleWidget->goHome();
    widget.middleVerticalLayout->addWidget(marbleWidget);
}

QString MainWindow::getSettingsFilename()
{
    return settingsFilename;
}

void MainWindow::openSettings()
{
    if(preferencesForm == NULL)
    {
        preferencesForm = new PreferencesForm();
        connect(preferencesForm, SIGNAL(accepted()),
                this, SLOT(updateMapTheme()));
        connect(preferencesForm, SIGNAL(moreMapsClicked()),
                this, SLOT(openDownloadMap()));
    }
    preferencesForm->exec();
}

void MainWindow::openMapInstaller()
{
    if(mapInstallerForm == NULL)
    {
        mapInstallerForm = new MapInstallerForm();
    }
    /*
     * if the preference form was already opened,
     * updates its maps combobox after the new map was installed
     */
    if (preferencesForm != NULL)
    {
        connect(mapInstallerForm, SIGNAL(newMapInstalled()),
                preferencesForm, SLOT(updateMapThemesComboBox()));
    }
    mapInstallerForm->exec();
}

void MainWindow::openDownloadMap()
{
    openMapInstaller();
    /*
    QUrl url("http://edu.kde.org/marble/maps.php");
    QDesktopServices::openUrl(url);
    */
}

void MainWindow::openDownloadGeoLite()
{
    QUrl url("http://www.maxmind.com/en/geolite");
    QDesktopServices::openUrl(url);
}

QString MainWindow::getMapTheme()
{
    QString mapTheme;
    QSettings settings(settingsFilename);

    // if the preference form was opened to update the map theme
    if (preferencesForm != NULL)
    {
        mapTheme = preferencesForm->getMapTheme();
    }
    // otherwise get it from saved settings
    else
    {
        mapTheme = settings.value(
            "mapTheme",
            QString::fromStdString(MainWindow::defaultMapTheme)).toString();
    }

    return mapTheme;
}

GeoIPRecord* MainWindow::get_ip_record(const std::string& ip)
{
    GeoIP * gi;
    GeoIPRecord* geoIPRecord;
    QSettings settings(settingsFilename);
    QString geoLiteCityPath;

    geoLiteCityPath = settings.value(
            "geoLiteCityPath",
            QString::fromStdString(MainWindow::defaultGeoIpPath)).toString();
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

void MainWindow::updateMapTheme()
{
    QString mapTheme = getMapTheme();
    // MarbleDirs::setMarbleDataPath(runningAppMapDataDir);
    // MarbleDirs::path(runningAppMapDataDir);

    /*
     * using "MarbleDirs::setMarbleDataPath(const QString&)" will overwrite
     * "systemPath" while "MarbleDirs::path(const QString&)" doesn't seem
     * to have any effect. Is this a Marble (KDE 4.8.5 SC) bug?
     */
    // marble bug workaround
    QString themeDirectory = getDirFromTheme(mapTheme);
    MarbleDirs::setMarbleDataPath(themeDirectory); // marble bug workaround
    qDebug("themeDirectory: %s", qPrintable(themeDirectory));
    /*
    qDebug("localPath: %s", qPrint12.04able(MarbleDirs::localPath()));
    qDebug("systemPath: %s", qPrintable(MarbleDirs::systemPath()));
    qDebug("marbleDataPath: %s", qPrintable(MarbleDirs::marbleDataPath()));
     */

    if (marbleWidget->mapThemeId() != mapTheme)
    {
        marbleWidget->setMapThemeId(mapTheme);
        // for some reasons showGrid state is lost after setting map theme
        marbleWidget->setShowGrid(false);
    }
}


// TODO: DRY
QString MainWindow::getDirFromTheme(QString theme)
{
    if (getAllThemesIn(getLocalMarbleMapDir()).contains(theme))
    {
        return localMarbleDir.path();
    }
    if (getAllThemesIn(getSystemMarbleMapDir()).contains(theme))
    {
        return systemMarbleDir.path();
    }
    if (getAllThemesIn(getRunningAppMapDataDir()).contains(theme))
    {
        return runningAppDataDir.path();
    }
    return QString();
}

QList<QString> MainWindow::getAllThemes()
{
    QStringList dgmlFiles;

    dgmlFiles += getAllThemesIn(getLocalMarbleMapDir());
    dgmlFiles += getAllThemesIn(getSystemMarbleMapDir());
    dgmlFiles += getAllThemesIn(getRunningAppMapDataDir());

    return dgmlFiles;
}

QList<QString> MainWindow::getAllThemesIn(const QDir& directory)
{
    QStringList dgmlFiles;
    QStack<QString> stack;

    QDir directoryCleaned(QDir::cleanPath(directory.absolutePath()));
    stack.push(directoryCleaned.absolutePath());
    while (!stack.isEmpty())
    {
        QString sSubdir = stack.pop();
        QDir subdir(sSubdir);

        // Check for the files.
        QStringList entries = subdir.entryList(QStringList() << "*.dgml", QDir::Files);
        for (int i = 0; i < entries.size(); i++)
        {
            // tries to extract the Marble style relative theme path
            int relativePathSize =
                subdir.path().size() - directoryCleaned.path().size() - 1;
            QString mapRelativeDir = sSubdir.right(relativePathSize);
            QString mapRelativePathmapRelativeDir =
                    mapRelativeDir + "/" + entries[i];
            dgmlFiles += QDir::cleanPath(mapRelativePathmapRelativeDir);
        }

        QFileInfoList infoEntries = subdir.entryInfoList(
                QStringList(),
                QDir::AllDirs | QDir::NoSymLinks | QDir::NoDotAndDotDot);
        for (int i = 0; i < infoEntries.size(); i++)
        {
            QFileInfo& item = infoEntries[i];
            stack.push(item.absoluteFilePath());
        }
    }

    return dgmlFiles;
}

QString MainWindow::getLocalMarbleMapDir()
{
    return QDir::cleanPath(localMarbleDir.path() + "/maps/");
}

QString MainWindow::getSystemMarbleMapDir()
{
    return QDir::cleanPath(systemMarbleDir.path() + "/maps/");
}

QString MainWindow::getRunningAppMapDataDir()
{
    return QDir::cleanPath(runningAppDataDir.path() + "/maps/");
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
