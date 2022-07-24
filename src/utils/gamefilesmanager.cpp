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
    for (const auto& module : modules){
        if (!mPathsByModDir.contains(module)){
            qDebug()<<"skipped unsupported module:"<<module;
            continue;
        }

        QFileInfo srcInfo(fullPathForAircraft(module));
        QFileInfo dstInfo(backupPathForAircraft(module));
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

bool GameFilesManager::validate()
{
    bool ok = true;
    for (const auto& module : InstallationInfo{}.instaledModules()){
        if (!QFileInfo::exists(backupPathForAircraft(module))){
            emit error(tr("Backup files weren't found"));
            ok = false;
            break;
        }
    }

    return ok;
}

QString GameFilesManager::backupPathForAircraft(const QString aircaft)
{
    InstallationInfo info;
    if (aircaft == QStringLiteral("JF-17"))
        return info.dcsSavesDir() +
                ::cmsDirName +
                mPathsByModDir.value(aircaft);
    else
        return  info.dcsSavesDir() +
                ::cmsDirName +
                mPathsByModDir.value(aircaft);
}

QString GameFilesManager::fullPathForAircraft(const QString aircaft)
{
    InstallationInfo info;
    if (aircaft == QStringLiteral("JF-17"))
        return info.dcsSavesDir() + mPathsByModDir.value(aircaft);
    else
        return  InstallationInfo{}.dcsRootDir() +
                mPathsByModDir.value(aircaft);
}
