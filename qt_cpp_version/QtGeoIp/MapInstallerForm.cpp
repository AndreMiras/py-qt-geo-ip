/*
 * File:   MapInstallerForm.cpp
 * Author: andre
 *
 * Created on September 30, 2012, 1:36 PM
 */

#include "MapInstallerForm.h"
#include <QFile>
#include <QTimer>

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
    MapItemModel* mapItemModel1 = new MapItemModel("Map 1");
    mapItemModel1->setDownloadLink(
    "http://www-ftp.lip6.fr/pub/X11/kde-applicationdata/marble/newstuff/maps/naturalearth-marblemap-4.5.zip");
    MapItemModel* mapItemModel2 = new MapItemModel("Map 2");
    addInstallMapItem(new InstallMapItemWidget(mapItemModel1));
    addInstallMapItem(new InstallMapItemWidget(mapItemModel2));
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

    connect(installMapItemWidget, SIGNAL(installButtonClicked(const MapItemModel&)),
                this, SLOT(installMap(const MapItemModel&)));
}

// FIXME[deprecated]: everything is now managed inside the InstallMapItemWidget
void MapInstallerForm::installMap(const MapItemModel& mapItemModel)
{
    /*
    // QUrl url(mapItemModel.getDownloadLink());
    QString url(mapItemModel.getDownloadLink());
    url = "http://leanonymous.free.fr/Linux/ScreenRC";
    QList<QUrl> urls;
    urls.append(url);
    DownloadManager downloadManager(urls);
    // downloadManager.doDownload(url);
    // QTimer::singleShot(0, &downloadManager, SLOT(execute()));
    downloadManager.doDownload(url);
    */
}