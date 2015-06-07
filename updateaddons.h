﻿#ifndef UPDATEADDONS_H
#define UPDATEADDONS_H

// httpDownload
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

#include <QCryptographicHash>

#include <QTime>
#include <QTimer>
#include <QFileInfo>
#include <QProcess>
#include <QFile>
#include <QDir>

#include <QObject>

#include "deleteotherfiles.h"

class updateAddons : public QObject {
    Q_OBJECT
public:
    explicit updateAddons(QWidget *parent = 0);
    ~updateAddons();
    // Установка репозитория
    void setRepository(Repository repo);
signals:
    // Сигналы основного класса
    void started(const Repository repository, const QList< QMap<QString, QString> > addonsList, const QStringList modsList);
    void finished();

    // Проверка аддонов
    void checkAddonsFinished(int type, const QList< QMap<QString, QString> > otherFiles, const QList< QMap<QString, QString> > newFiles,
                             const QList< QMap<QString, QString> > correctFiles, const QList< QMap<QString, QString> > notCorrectFiles);
    void checkAddonsProgressUI(int index, const QList< QMap<QString, QString> > existsFiles);

    // Скачивание аддонов
    void downloadAddonStarted(const QList< QMap<QString, QString> > downloadFiles, int index);
    void downloadAddonFinished();
    void downloadAddonsFinished(bool success);

    // Сигналы скачивания файлов
    void downloadFile_UI(QString fileName);
    void updateDownloadProgress_UI(qint64 bytesRead, qint64 totalBytes, QString speed);
    void downloadFinished(bool success);

    // Сигналы удаления лишних файлов
    void deleteOtherFiles(const QList< QMap<QString, QString> > otherFiles, QString addonsPath);

    // Сигналы unzipa
    void unzipStart(QString fileName);
    void unzipFinished(QString fileName);

public slots:
    // Запуск апдейтера
    void start();
    void startFinished(bool success);
    void updaterUIStarted(QStringList folders);

    // Завершение апдейтера
    void finish();

    // Слоты UI
    void checkAddons(QString path);
    void downloadUpdate(QList<int> fileID);
    void delOtherFiles();
    void stopUpdater();

    // Слоты обновления файлов
    void downloadAddonStart();
    void downloadAddonFinish(bool succ);
    void downloadAddonsFinish();

    // Слоты загрузки
    void httpReadyRead();
    void httpDownloadFinished();
    void updateDownloadProgress(qint64, qint64);

private:

    // Работа с httpDownload
    //..время для расчета промежутка обновления загрузки
    qint64 downloadTime;
    //..кол-во байт на момент прошлого обновления
    qint64 bytesBefore;
    //..урл загрузки файла
    QUrl url;
    //..менеджер послания запроса на загрузку
    QNetworkAccessManager *manager;
    //..сокет получения ответа
    QNetworkReply *reply;
    //..расположение загружаемого файла
    QFile *filePath;
    //..разрыв соеденения загрузки
    bool httpRequestAborted;
    //..загрузка началась
    bool downloadStart;
    int triger;

    // Скачивание файла
    void downloadFile(QString fileUrl, QString path);
    // Запуск запроса на скачивание
    void startRequest(QUrl url);
    // Распаковка архива
    bool unzipArchive(QString archive, QString extracting);
    // Получаем проверочную сумму файла по пути
    QString getChecksum(QString filePath, QCryptographicHash::Algorithm alg);
    //
    void getAllFilesInDir(const QString path, QList< QMap<QString, QString> > &allFiles);
    //
    void parseYomaInformation(QString path, QString fileName);
    void parseSyncInformation(QString path);

    // Репозиторий
    Repository repository;
    // Данные конфига репозитория
    QList< QMap<QString, QString> > addonsList;
    QStringList modsList;
    QStringList addonsFolders;
    QString addonsPath;

    //
    QList< QMap<QString, QString> > otherFiles;
    QList< QMap<QString, QString> > newFiles;
    QList< QMap<QString, QString> > correctFiles;
    QList< QMap<QString, QString> > notCorrectFiles;
    QList< QMap<QString, QString> > downloadFiles;
    bool downloadAddonsInProgress;
    bool downloadAddonsAbort;
    QString pathUrl;
    int downloadFilesIndex;

    QList<YomaFileInfo> yomaFileInfo;
    QList<SyncFileInfo> syncFileInfo;

    void saveTempFileInfo();

};

#endif // UPDATEADDONS_H
