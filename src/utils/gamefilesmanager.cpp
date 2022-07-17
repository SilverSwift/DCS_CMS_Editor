#include "gamefilesmanager.h"
#include "installationinfo.h"

#include <QDir>
#include <QFileInfo>
#include <QFile>

namespace {
    static const QString cmsDirName = QStringLiteral("/Cms_Editor");
}

GameFilesManager::GameFilesManager(QObject *parent)
    : QObject{parent}
{

}

void GameFilesManager::backup(QStringList modules)
{
    InstallationInfo info;
    QString fromPath = info.dcsRootDir();
    QString toPath = info.dcsSavesDir();

    toPath.append(::cmsDirName);
    for (const auto& module : modules){
        if (!mPathsByModDir.contains(module)){
            qDebug()<<"skipped unsupported module:"<<module;
            continue;
        }

        QString src (fromPath + mPathsByModDir.value(module));
        QFileInfo srcInfo(src);
        QFileInfo dstInfo(toPath + mPathsByModDir.value(module));
        QDir{}.mkpath(dstInfo.absolutePath());

        if (dstInfo.exists() &&
            !QFile::remove(dstInfo.absoluteFilePath())){
            emit error(tr("Failed to update file: %1").
                       arg(dstInfo.absoluteFilePath()));
            continue;
        }

        if (!QFile::copy(srcInfo.absoluteFilePath(), dstInfo.absoluteFilePath()))
            emit error(tr("Failed to copy file: %1").
                       arg(dstInfo.absoluteFilePath()));
    }
}

QString GameFilesManager::pathForAircraft(const QString aircaft)
{
    return mPathsByModDir.value(aircaft);
}

void GameFilesManager::validate()
{
    for (const auto& module : InstallationInfo{}.instaledModules()){
        if (!QFileInfo::exists(backupPathForAircraft(module))){
            emit error(tr("Backup files weren't found"));
            break;
        }
    }
}

QString GameFilesManager::backupPathForAircraft(const QString aircaft)
{
    return  InstallationInfo{}.dcsSavesDir() +
            ::cmsDirName +
            mPathsByModDir.value(aircaft);
}

QString GameFilesManager::fullPathForAircraft(const QString aircaft)
{
    return  InstallationInfo{}.dcsRootDir() +
            mPathsByModDir.value(aircaft);
}
