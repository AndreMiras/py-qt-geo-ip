/* 
 * File:   MainWindow.h
 * Author: andre
 *
 * Created on September 23, 2012, 11:09 PM
 */

#ifndef _MAINWINDOW_H
#define	_MAINWINDOW_H

#include "ui_main_window_ui.h"
#include "CustomMarbleWidget.h"
#include "PreferencesForm.h"
#include "MapInstallerForm.h"
#include <GeoIPCity.h>
#include <QTimer>
#include <QString>
#include <QList>
#include <QDir>

using namespace Marble;
using namespace std;


const int defaultZoom = 1500;

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    static const string defaultGeoIpPath;
    static const string defaultMapTheme;
    MainWindow();
    virtual ~MainWindow();
    static QString getSettingsFilename();
    static QString getLocalMarbleMapDir();
    static QString getSystemMarbleMapDir();
    static QString getRunningAppMapDataDir();

    /**
     * Retrieves map themes files by looking in three locations:
     *  - running application dedicated map data directory
     *  - local Marble map data directory
     *  - system Marble map data directory
     * @return List of map theme relative paths
     */
    static QList<QString> getAllThemes();

    /**
     * Retrieves the directory where is stored the given theme
     * @param theme
     * @return a directory string
     */
    static QString getDirFromTheme(QString theme);
private slots:
    /**
     * Geocodes IP:
     *  - retrieves IP information
     *  - places map marker from ip lat/long
     */
    void geoCodeIp();
    void updateZoom();
    void updateMapTheme();
    void openSettings();
    void openMapInstaller();
    void openDownloadMap();
    void openDownloadGeoLite();

private:
    Ui::MainWindow widget;
    CustomMarbleWidget* marbleWidget;
    QTimer* updateZoomTimer;
    PreferencesForm* preferencesForm;
    MapInstallerForm* mapInstallerForm;
    static QString settingsFilename;
    static QDir localMarbleDir;
    static QDir systemMarbleDir;
    static QDir runningAppDataDir;

    void setupSignalsSlots();
    /**
     * Setups marble widget
     */
    void customSetupUi();
    /**
     * Returns the ip information dictionary from ip.
     * @param ip
     * @return 
     */
    GeoIPRecord* get_ip_record(const string& ip);

    QString getMapTheme();

    /**
     * Searches for *.dgml files in all sub directories
     * @param directory, directory to search from
     * @return a list of found map theme relative paths
     */
    static QList<QString> getAllThemesIn(const QDir& directory);

    /**
     * Updates the IP information box labels.
     * @param record_by_addr
     */
    void update_labels_from_record(
        const GeoIPRecord* record_by_addr);
    /**
     * Adds map marker from ip dictionary information (lat, long).
     * @param record_by_addr
     * @param ip
     */
    void update_map_from_record(
    GeoIPRecord* record_by_addr, const std::string& ip);
};

#endif	/* _MAINWINDOW_H */
