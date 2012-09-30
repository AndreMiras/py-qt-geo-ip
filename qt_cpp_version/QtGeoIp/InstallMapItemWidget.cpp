/*
 * File:   InstallMapItemWidget.cpp
 * Author: andre
 *
 * Created on September 30, 2012, 1:45 PM
 */

#include "InstallMapItemWidget.h"
#include <quazip/quazipfile.h>
#include <quazip/quazip.h>
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
// static bool extract(const QString & filePath, const QString & extDirPath, const QString & singleFileName = QString("")) {

    QuaZip zip(zipfilename);

    if (!zip.open(QuaZip::mdUnzip))
    {
        qWarning("testRead(): zip.open(): %d", zip.getZipError());
        return; // false;
    }

    zip.setFileNameCodec("IBM866");

    qWarning("%d entries\n", zip.getEntriesCount());
    qWarning("Global comment: %s\n", zip.getComment().toLocal8Bit().constData());

    QuaZipFileInfo info;

    QuaZipFile file(&zip);

    QFile out;
    QString name;
    char c;
    // TODO: code readability
    for (bool more = zip.goToFirstFile(); more; more = zip.goToNextFile())
    {

        if (!zip.getCurrentFileInfo(&info))
        {
            qWarning("testRead(): getCurrentFileInfo(): %d\n", zip.getZipError());
            return; // false;
        }
        /*
        if (!singleFileName.isEmpty())
            if (!info.name.contains(singleFileName))
                continue;
         */
        if (!file.open(QIODevice::ReadOnly))
        {
            qWarning("testRead(): file.open(): %d", file.getZipError());
            return; // false;
        }

        name = QString("%1/%2").arg(extDirPath).arg(file.getActualFileName());

        if (file.getZipError() != UNZ_OK)
        {
            qWarning("testRead(): file.getFileName(): %d", file.getZipError());
            return; // false;
        }

        //out.setFileName("out/" + name);
        out.setFileName(name);

        // this will fail if "name" contains subdirectories, but we don't mind that
        out.open(QIODevice::WriteOnly);
        // Slow like hell (on GNU/Linux at least), but it is not my fault.
        // Not ZIP/UNZIP package's fault either.
        // The slowest thing here is out.putChar(c).
        while (file.getChar(&c)) out.putChar(c);

        out.close();

        if (file.getZipError() != UNZ_OK)
        {
            qWarning("testRead(): file.getFileName(): %d", file.getZipError());
            return; // false;
        }

        if (!file.atEnd())
        {
            qWarning("testRead(): read all but not EOF");
            return; // false;
        }

        file.close();

        if (file.getZipError() != UNZ_OK)
        {
            qWarning("testRead(): file.close(): %d", file.getZipError());
            return; // false;
        }
    }

    zip.close();

    if (zip.getZipError() != UNZ_OK)
    {
        qWarning("testRead(): zip.close(): %d", zip.getZipError());
        return; // false;
    }

    return; // true;
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