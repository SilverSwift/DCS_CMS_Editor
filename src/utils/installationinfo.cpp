#include "installationinfo.h"

#include <QDir>
#include <QFileInfo>
#include <QSettings>

namespace {
    const QString aircrafsDir = QStringLiteral("Mods/aircraft");
    const QString firstRunKey = QStringLiteral("firstRun");
    const QString dcsRootDirKey = QStringLiteral("dcsRootDir");
    const QString dcsSavesDirKey = QStringLiteral("dcsSavesDir");
}

InstallationInfo::InstallationInfo(QObject *parent)
    : QObject{parent}
    , mFirstRun (QSettings{}.value(::firstRunKey, true).toBool())
{

}

InstallationInfo::~InstallationInfo()
{
    QSettings {}.setValue(::firstRunKey, false);
}

bool InstallationInfo::isFirstRun() const
{
    return mFirstRun;
}

bool InstallationInfo::isSettingsValid() const
{
    return QFileInfo::exists(dcsRootDir()) &&
           QFileInfo::exists(dcsSavesDir());
}

QString InstallationInfo::dcsRootDir() const
{
    return QSettings{}.value(::dcsRootDirKey).toString();
}

QString InstallationInfo::dcsSavesDir() const
{
    return QSettings{}.value(::dcsSavesDirKey).toString();
}

QStringList InstallationInfo::instaledModules() const
{
    QStringList modules;
    QDir root(dcsRootDir());
    root.cd(::aircrafsDir);
    if (!root.exists() || !root.isAbsolute())
        return modules;
    auto subdirs = root.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot);

    for (const auto& subdir : subdirs)
        modules<<subdir.fileName();

    return modules;
}

void InstallationInfo::setDcsRootDir(QString value)
{
    QSettings().setValue(::dcsRootDirKey, value);
}

void InstallationInfo::setDcsSavesDir(QString value)
{
    QSettings().setValue(::dcsSavesDirKey, value);
}

void InstallationInfo::validate()
{
    if (!QFileInfo::exists(dcsRootDir() + "/bin/DCS.exe"))
        emit error(tr("Incorrect root dir"));

    emit instaledModulesChanged(instaledModules());
}
