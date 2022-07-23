#ifndef GAMEFILESMANAGER_H
#define GAMEFILESMANAGER_H

#include <QObject>
#include <QHash>

class GameFilesManager : public QObject
{
    Q_OBJECT
public:
    explicit GameFilesManager(QObject *parent = nullptr);

    void backup(QStringList modules);
    QString backupPathForAircraft(const QString aircaft);
    QString fullPathForAircraft(const QString aircaft);

    bool validate();

signals:
    void error(QString);

private:
    const QHash<QString, QString> mPathsByModDir {
        {"A-10C", "/Mods/aircraft/A-10C/Cockpit/Scripts/AN_ALE40V/device/AN_ALE40V_params.lua"},
        {"A-10C_2", "/Mods/aircraft/A-10C_2/Cockpit/Scripts/AN_ALE40V/device/AN_ALE40V_params.lua"},
        {"FA-18C", "/Mods/aircraft/FA-18C/Cockpit/Scripts/TEWS/device/CMDS_ALE47.lua"},
        {"F-16C", "/Mods/aircraft/F-16C/Cockpit/Scripts/EWS/CMDS/device/CMDS_ALE47.lua"},
        {"AV8BNA", "/Mods/aircraft/AV8BNA/Cockpit/Scripts/EWS/EW_Dispensers_init.lua"},
        {"M-2000C", "/Mods/aircraft/M-2000C/Cockpit/Scripts/SPIRALE.lua"},
        {"JF-17", "/Config/options.lua"},
    };
};

#endif // GAMEFILESMANAGER_H
