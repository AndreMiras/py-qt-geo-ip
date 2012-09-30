/*
 * File:   MapInstallerForm.cpp
 * Author: andre
 *
 * Created on September 30, 2012, 1:36 PM
 */

#include "MapInstallerForm.h"

MapInstallerForm::MapInstallerForm()
{
    widget.setupUi(this);
    customSetupUi();
    setupSignalsSlots();
}

MapInstallerForm::~MapInstallerForm()
{
}

void MapInstallerForm::customSetupUi()
{
    // TODO: adding two items for testing
    MapItemModel mapItemModel1("Map 1");
    MapItemModel mapItemModel2("Map 2");
    addInstallMapItem(new InstallMapItemWidget(&mapItemModel1));
    addInstallMapItem(new InstallMapItemWidget(&mapItemModel2));
}

void MapInstallerForm::setupSignalsSlots()
{
    
}

void MapInstallerForm::addInstallMapItem(
        InstallMapItemWidget* installMapItemWidget)
{
    QListWidgetItem *item = new QListWidgetItem();
    widget.mapsListWidget->addItem(item);
    widget.mapsListWidget->setItemWidget(item, installMapItemWidget);
    item->setSizeHint(installMapItemWidget->sizeHint());
}
