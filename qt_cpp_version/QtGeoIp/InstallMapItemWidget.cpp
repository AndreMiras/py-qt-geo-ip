/*
 * File:   InstallMapItemWidget.cpp
 * Author: andre
 *
 * Created on September 30, 2012, 1:45 PM
 * TODO: verify the directory doesn't already exists before unziping
 * prompt a warning message if it does
 */

#include "InstallMapItemWidget.h"
#include "MainWindow.h"
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
}

InstallMapItemWidget::~InstallMapItemWidget()
{
}

void InstallMapItemWidget::customSetupUi()
{
    // MarbleWidget doesn't seem to look into runningAppMapData directory but
    // cheating with MarbleDirs::setMarbleDataPath(getRunningAppMapDataDir())
    // did the trick
    downloadDir = MainWindow::getRunningAppMapDataDir();
    // doing it in the designer (4.8.2) breaks the layout
    widget.mapDescriptionLabel->setWordWrap(true);
}

void InstallMapItemWidget::setupSignalsSlots()
{
    /*
    connect(widget.installPushButton, SIGNAL(clicked()),
            this, SLOT(emitInstallButtonClicked()));
    connect(widget.usePushButton, SIGNAL(clicked()),
            this, SLOT(emitUseButtonClicked()));
     */
    connect(widget.installPushButton, SIGNAL(clicked()),
            this, SLOT(downloadButtonPressed()));
}

void InstallMapItemWidget::downloadButtonPressed()
{
    QUrl url(mapItemModel->getDownloadLink());
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
    QString filename = QFileInfo(url.path()).fileName();
    QString filenameFullPath = downloadDir + "/" + filename;

    // create the application data folder if it doesn't exist
    if (!QDir(downloadDir).exists())
    {
        QDir().mkpath(downloadDir);
    }

    unZipFile(filenameFullPath, downloadDir);
}

/*
 * TODO:
 *      - add some progress bar
 *      - add file exists warning
 */
void InstallMapItemWidget::unZipFile(
        const QString& zipfilename, const QString& extDirPath)
{
    // TODO: verify nothing will be overwrited, popup a message if this is
    // the case
    /*
    if (QFile::exists(filenameFullPath))
    {
        if (QMessageBox::question(this, tr("Downloader"),
                                  tr(
                                     "There already exists a file called %1 in "
                                     "Overwrite?"
                                     ).arg(filenameFullPath),
                                  QMessageBox::Yes | QMessageBox::No,
                                  QMessageBox::No)
                == QMessageBox::No)
            return;
        QFile::remove(filenameFullPath);
    }
     */

    JlCompress::extractDir(zipfilename, extDirPath);
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

/*
void InstallMapItemWidget::emitInstallButtonClicked()
{
    emit installButtonClicked(*mapItemModel);
}

void InstallMapItemWidget::emitUseButtonClicked()
{
    emit useButtonClicked(*mapItemModel);
}
 */