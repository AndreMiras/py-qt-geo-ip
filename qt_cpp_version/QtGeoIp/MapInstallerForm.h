/* 
 * File:   MapInstallerForm.h
 * Author: andre
 *
 * Created on September 30, 2012, 1:36 PM
 */

#ifndef _MAPINSTALLERFORM_H
#define	_MAPINSTALLERFORM_H

#include "ui_MapInstallerForm.h"
#include "InstallMapItemWidget.h"

class MapInstallerForm : public QDialog {
    Q_OBJECT
public:
    MapInstallerForm();
    virtual ~MapInstallerForm();
    void addInstallMapItem(InstallMapItemWidget* installMapItemWidget);

private slots:
    void installMap(const MapItemModel& mapItemModel);

private:
    Ui::MapInstallerForm widget;
    void customSetupUi();
    void setupSignalsSlots();
};

#endif	/* _MAPINSTALLERFORM_H */
