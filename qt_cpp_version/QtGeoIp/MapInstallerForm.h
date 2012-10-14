/* 
 * File:   MapInstallerForm.h
 * Author: andre
 *
 * Created on September 30, 2012, 1:36 PM
 */
/*
 * TODO:
 *      - add consts keywords
 */

#ifndef _MAPINSTALLERFORM_H
#define	_MAPINSTALLERFORM_H

#include "ui_MapInstallerForm.h"
#include "InstallMapItemWidget.h"
#include <QNetworkAccessManager>
#include <QWebPage>
#include <QMap>

class MapInstallerForm : public QDialog {
    Q_OBJECT
public:
    MapInstallerForm();
    virtual ~MapInstallerForm();
    void addInstallMapItem(InstallMapItemWidget* installMapItemWidget);

private slots:
    void mapsIndexReplyFinished(QNetworkReply*);

    /**
     * Parses the remote meta file and extracts relevant map meta data
     * @param pReply, QNetworkReply object of the finished meta data download
     */
    void mapMetaReplyFinished(QNetworkReply* pReply);

    /**
     * Creates the MapItemModel object from the given map information dictionary
     * @param dict with the given keys
     *  - "name": the map name
     *  - "summary_text": the map description
     *  - "payload_url": the map (tar.gz or zip) archive url
     *  - "preview_url": the map preview image
     */
    void addMapItemModelFromDict(const QMap<QString, QString> dict);

private:
    static const QString maps_url;
    Ui::MapInstallerForm widget;
    QNetworkAccessManager* mapsIndexManager;
    QNetworkAccessManager* mapsMetaManager;
    // QWebPage page;
    QWebPage mapsMetaPage;
    void customSetupUi();
    void setupSignalsSlots();
    void getRemoteMapsMeta();
    QMap<QString, QString> getMetaDictFromMetaContent(const QString&) const;

    /**
     * Downloads maps meta info from url list
     * @param metaUrls
     */
    void processMapsMeta(QStringList metaUrls);
};

#endif	/* _MAPINSTALLERFORM_H */
