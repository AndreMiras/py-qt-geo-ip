/* 
 * File:   newForm.h
 * Author: andre
 *
 * Created on September 23, 2012, 11:09 PM
 */

#ifndef _MAINWINDOW_H
#define	_MAINWINDOW_H

#include "ui_main_window_ui.h"
#include "CustomMarbleWidget.h"
#include "PreferencesForm.h"
#include <GeoIPCity.h>
#include <QTimer>
#include <QString>

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
private:
    Ui::MainWindow widget;
    CustomMarbleWidget* marbleWidget;
    QTimer* updateZoomTimer;
    PreferencesForm* preferencesForm;
    static QString settingsFilename;

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
