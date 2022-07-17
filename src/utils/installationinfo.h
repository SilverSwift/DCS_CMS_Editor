#ifndef INSTALLATIONINFO_H
#define INSTALLATIONINFO_H

#include <QObject>

class InstallationInfo : public QObject
{
    Q_OBJECT
public:
    explicit InstallationInfo(QObject *parent = nullptr);
    ~InstallationInfo();

    Q_PROPERTY(bool isFirstRun
               READ isFirstRun
               NOTIFY isFirstRunChanged)

    Q_PROPERTY(bool isSettingsValid
               READ isSettingsValid
               NOTIFY isSettingsValidChanged)

    Q_PROPERTY(QString dcsRootDir
               READ dcsRootDir
               WRITE setDcsRootDir
               NOTIFY dcsRootDirChanged)

    Q_PROPERTY(QString dcsSavesDir
               READ dcsSavesDir
               WRITE setDcsSavesDir
               NOTIFY dcsSavesDirChanged)

    Q_PROPERTY(QStringList instaledModules
               READ instaledModules
               NOTIFY instaledModulesChanged)


    bool isFirstRun() const;
    bool isSettingsValid() const;
    QString dcsRootDir() const;
    QString dcsSavesDir() const;
    QStringList instaledModules() const;

    void setDcsRootDir(QString value);
    void setDcsSavesDir(QString value);

    bool validate();

signals:
    void isFirstRunChanged(bool value);
    void isSettingsValidChanged(bool value);
    void dcsRootDirChanged(QString value);
    void dcsSavesDirChanged(QString value);
    void instaledModulesChanged(QStringList value);

    void error(QString );

private:
    const bool mFirstRun;
};

#endif // INSTALLATIONINFO_H
