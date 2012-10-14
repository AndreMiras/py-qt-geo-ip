/* 
 * File:   InstallMapItemWidget.h
 * Author: andre
 *
 * Created on September 30, 2012, 1:45 PM
 */

#ifndef _INSTALLMAPITEMWIDGET_H
#define	_INSTALLMAPITEMWIDGET_H

#include "ui_InstallMapItemWidget.h"
#include "MapItemModel.h"
#include <QNetworkAccessManager>
#include <QProgressDialog>
#include <QFile>

class InstallMapItemWidget : public QWidget
{
    Q_OBJECT
public:
    InstallMapItemWidget(MapItemModel* mapItemModel);
    virtual ~InstallMapItemWidget();
    MapItemModel* getMapItemModel();
    void setMapItemModel(MapItemModel* mapItemModel);

signals:
       /*
       void installButtonClicked(const MapItemModel& mapItemModel);
       void useButtonClicked(const MapItemModel& mapItemModel);
        */
        /**
         * Signal released when a new map was successfully installed.
         */
        void newMapInstalled();

private slots:
    /*
    void emitInstallButtonClicked();
    void emitUseButtonClicked();
     */

    void downloadButtonPressed();
    void downloadProgress(qint64 bytesReceived, qint64 bytesTotal);
    /**
     * Performs some clean-up
     */
    void downloadFinished();
    void mapImageReplyFinished(QNetworkReply* pReply);
    void unZipFile();
    void downloadReadyRead();
    void cancelDownload();

private:
    Ui::InstallMapItemWidget widget;
    MapItemModel* mapItemModel;
    QString downloadDir;
    QNetworkAccessManager* mapImageManager;
    void setupSignalsSlots();
    void customSetupUi();
    void updateWidget();
    void unZipFile(const QString& zipfilename, const QString& extDirPath);

    QNetworkAccessManager manager;
    QFile *file;
    QProgressDialog *progressDialog;
    QNetworkReply *reply;
    bool downloadRequestAborted;
};

#endif	/* _INSTALLMAPITEMWIDGET_H */
