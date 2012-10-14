/*
 * File:   MapInstallerForm.cpp
 * Author: andre
 *
 * Created on September 30, 2012, 1:36 PM
 */

#include "MapInstallerForm.h"
#include "qdom.h"
#include <QFile>
#include <QTimer>
#include <QUrl>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QWebPage>
#include <QWebFrame>
#include <QWebElement>
#include <QWebElementCollection>


const QString MapInstallerForm::maps_url =
    "http://www-ftp.lip6.fr/pub/X11/kde-applicationdata/marble/newstuff/maps/";


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
    mapsIndexManager = new QNetworkAccessManager(this);
    mapsMetaManager = new QNetworkAccessManager(this);
    getRemoteMapsMeta();
}

void MapInstallerForm::setupSignalsSlots()
{
    connect(mapsIndexManager, SIGNAL(finished(QNetworkReply*)),
         this, SLOT(mapsIndexReplyFinished(QNetworkReply*)));
    connect(mapsMetaManager, SIGNAL(finished(QNetworkReply*)),
         this, SLOT(mapMetaReplyFinished(QNetworkReply*)));
}

void MapInstallerForm::addInstallMapItem(
        InstallMapItemWidget* installMapItemWidget)
{
    QListWidgetItem *item = new QListWidgetItem();
    widget.mapsListWidget->addItem(item);
    widget.mapsListWidget->setItemWidget(item, installMapItemWidget);
    item->setSizeHint(installMapItemWidget->sizeHint());
}

void MapInstallerForm::getRemoteMapsMeta()
{
    mapsIndexManager->get(QNetworkRequest(QUrl(maps_url)));
}

// TODO: give a more relevant name to this method
void MapInstallerForm::processMapsMeta(QStringList metaUrls)
{
    for (int i = 0; i < metaUrls.count(); i++)
    {
        QString url = metaUrls.at(i);
        mapsMetaManager->get(QNetworkRequest(url));
    }
}

void MapInstallerForm::mapMetaReplyFinished(QNetworkReply* pReply)
{
    QByteArray data = pReply->readAll();
    QString html(data);
    QMap<QString, QString> dict = getMetaDictFromMetaContent(html);
    addMapItemModelFromDict(dict);
}

void MapInstallerForm::addMapItemModelFromDict(
    const QMap<QString, QString> dict)
{
    MapItemModel* mapItemModel = new MapItemModel(dict["name"]);
    mapItemModel->setDownloadLink(maps_url + dict["payload_url"]);
    mapItemModel->setDescription(dict["summary_text"]);
    addInstallMapItem(new InstallMapItemWidget(mapItemModel));
}

QMap<QString, QString> MapInstallerForm::getMetaDictFromMetaContent(
        const QString& metaContent) const
{
    QMap<QString, QString> dict;
    QDomDocument doc("mydocument");
    if (doc.setContent(metaContent))
    {
        QDomElement docElem = doc.documentElement();
        dict["name"] =
                docElem.elementsByTagName("name").at(0).toElement().text();
        dict["payload_url"] =
                docElem.elementsByTagName("payload").at(0).toElement().text();
        /*
         * workaround for using the zip file rather than the tar.gz
         * I don't mind using tar.gz files, but I don't have the code setup yet
         */
        dict["payload_url"].replace(".tar.gz", ".zip");
        dict["preview_url"] =
                docElem.elementsByTagName("preview").at(0).toElement().text();
        dict["summary_text"] =
                docElem.elementsByTagName("summary").at(0).toElement().text();
    }

    return dict;
}

void MapInstallerForm::mapsIndexReplyFinished(QNetworkReply* pReply)
{
    QStringList metaUrls;
    QByteArray data=pReply->readAll();
    QString html(data);
    QWebPage page;
    page.mainFrame()->setHtml(html);
    QUrl baseUrl = pReply->url();
    QWebElementCollection collection = page.mainFrame()->findAllElements("a");
    foreach (QWebElement element, collection)
    {
        QString href = element.attribute("href");
        if (href.endsWith(".meta"))
        {
            QUrl relativeUrl(href);
            QUrl absoluteUrl = baseUrl.resolved(relativeUrl);
            metaUrls.append(absoluteUrl.toString());
        }
    }
    processMapsMeta(metaUrls);
}