/*
 * File:   InstallMapItemWidget.cpp
 * Author: andre
 *
 * Created on September 30, 2012, 1:45 PM
 */

#include "InstallMapItemWidget.h"
#include <quazip/JlCompress.h>
#include <QDesktopServices>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QMessageBox>
#include <QFileInfo>
#include <QDir>
#include <QUrl>

InstallMapItemWidget::InstallMapItemWidget(MapItemModel* mapItemModel)
{
    widget.setupUi(this);
    customSetupUi();
    setupSignalsSlots();
    setMapItemModel(mapItemModel);

    progressDialog = new QProgressDialog(this);
    connect(widget.installPushButton, SIGNAL(clicked()),
            this, SLOT(downloadButtonPressed()));
}

InstallMapItemWidget::~InstallMapItemWidget()
{
}

void InstallMapItemWidget::customSetupUi()
{

}

void InstallMapItemWidget::setupSignalsSlots()
{
    connect(widget.installPushButton, SIGNAL(clicked()),
            this, SLOT(emitInstallButtonClicked()));
    connect(widget.usePushButton, SIGNAL(clicked()),
            this, SLOT(emitUseButtonClicked()));
    connect(widget.usePushButton, SIGNAL(clicked()),
            this, SLOT(unZipFile()));
}

void InstallMapItemWidget::downloadButtonPressed()
{
    QUrl url(mapItemModel->getDownloadLink());
    QString downloadDir =
            QDesktopServices::storageLocation(QDesktopServices::DataLocation);
    QString filename = QFileInfo(url.path()).fileName();
    QString filenameFullPath = downloadDir + "/" + filename;

    // create the application data folder if it doesn't exist
    if (!QDir(downloadDir).exists())
    {
        QDir().mkpath(downloadDir);
    }

    // popup a message if the file exists
    if (QFile::exists(filenameFullPath))
    {
        if (QMessageBox::question(this, tr("Downloader"),
                                  tr(
                                     "There already exists a file called %1 in "
                                     "the current directory. Overwrite?"
                                     ).arg(filenameFullPath),
                                  QMessageBox::Yes | QMessageBox::No,
                                  QMessageBox::No)
                == QMessageBox::No)
            return;
        QFile::remove(filenameFullPath);
    }

    file = new QFile(filenameFullPath);
    if (!file->open(QIODevice::WriteOnly))
    {
        QMessageBox::information(this, "Downloader",
                                 tr("Unable to save the file %1: %2.")
                                 .arg(filenameFullPath).arg(file->errorString()));
        delete file;
        file = NULL;
        return;
    }

    downloadRequestAborted = false;
    reply = manager.get(QNetworkRequest(url));

    connect(reply, SIGNAL(finished()),
            this, SLOT(downloadFinished()));
    /*
    connect(reply, SIGNAL(finished()),
            this, SLOT(unZipFile()));
     */
    connect(reply, SIGNAL(readyRead()),
            this, SLOT(downloadReadyRead()));
    connect(reply, SIGNAL(downloadProgress(qint64, qint64)),
            this, SLOT(downloadProgress(qint64, qint64)));
    connect(progressDialog, SIGNAL(canceled()),
            this, SLOT(cancelDownload()));

    progressDialog->setLabelText(tr("Downloading %1...").arg(filename));
    widget.installPushButton->setEnabled(false);
    progressDialog->exec();
}

void InstallMapItemWidget::downloadProgress(qint64 bytesReceived, qint64 bytesTotal)
{
    if (downloadRequestAborted)
        return;
    progressDialog->setMaximum(bytesTotal);
    progressDialog->setValue(bytesReceived);
}

void InstallMapItemWidget::downloadReadyRead()
{
    if (file)
    {
        file->write(reply->readAll());
    }
}

void InstallMapItemWidget::cancelDownload()
{
    downloadRequestAborted = true;
    reply->abort();
    widget.installPushButton->setEnabled(true);
}

void InstallMapItemWidget::downloadFinished()
{
    if (downloadRequestAborted)
    {
        if (file)
        {
            file->close();
            file->remove();
            delete file;
            file = NULL;
        }
        reply->deleteLater();
        progressDialog->hide();
        widget.installPushButton->setEnabled(true);
        return;
    }

    downloadReadyRead();
    progressDialog->hide();
    widget.installPushButton->setEnabled(true);
    file->flush();
    file->close();

    if (reply->error())
    {
        //Download failed
        QMessageBox::information(
                                 this, "Download failed",
                                 tr("Failed: %1").arg(reply->errorString()));
    }

    reply->deleteLater();
    reply = NULL;
    delete file;
    file = NULL;

    unZipFile();
}

/**
 * TODO: handle if the file doesn't exist (e.g. couldn't be downloaded)
 */
void InstallMapItemWidget::unZipFile()
{
    QUrl url(mapItemModel->getDownloadLink());
    QString downloadDir =
            QDesktopServices::storageLocation(QDesktopServices::DataLocation);
    QString filename = QFileInfo(url.path()).fileName();
    QString filenameFullPath = downloadDir + "/" + filename;
    unZipFile(filenameFullPath, downloadDir);
    /*
    QString outFileName(filenameFullPath);
    // takes the zip out
    outFileName.chop(QString(".zip").size());
    unZipFile(filenameFullPath, outFileName);
     */
}

/*
 * TODO: add some progress bar
 */
void InstallMapItemWidget::unZipFile(
        const QString& zipfilename, const QString& extDirPath)
{
    // QStringList list =
    JlCompress::extractDir(
                           zipfilename, extDirPath);
    /*
    for (int i=0,n=list.count();i<n;i++)
    {
        qDebug("%2i : %s",i,qPrintable(list.at(i)));
    }
     */
}

void InstallMapItemWidget::updateWidget()
{
    if (mapItemModel != NULL)
    {
        widget.mapTitleLabel->setText(mapItemModel->getName());
        widget.mapDescriptionLabel->setText(mapItemModel->getDescription());
    }
}

MapItemModel* InstallMapItemWidget::getMapItemModel()
{
    return mapItemModel;
}

void InstallMapItemWidget::setMapItemModel(MapItemModel* mapItemModel)
{
    this->mapItemModel = mapItemModel;
    updateWidget();
}

void InstallMapItemWidget::emitInstallButtonClicked()
{
    emit installButtonClicked(*mapItemModel);
}

void InstallMapItemWidget::emitUseButtonClicked()
{
    emit useButtonClicked(*mapItemModel);
}