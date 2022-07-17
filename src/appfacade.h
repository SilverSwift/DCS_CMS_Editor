#ifndef APPFACADE_H
#define APPFACADE_H

#include <QObject>

#include "cmsmodel.h"
#include "installationinfo.h"

namespace model{
    class AbstractValidator;
}
namespace parsing {
    class AbstractParser;
}

class GameFilesManager;

class AppFacade : public QObject{
    Q_OBJECT
public:
    explicit AppFacade(QObject *parent = nullptr) ;

    Q_PROPERTY(model::CMSModel* model READ model NOTIFY modelChanged);
    Q_PROPERTY(InstallationInfo* installInfo READ installInfo NOTIFY installInfoChanged);

    inline model::CMSModel* model() const {return pModel;}
    inline InstallationInfo* installInfo() const {return pInstallationInfo;}

    Q_INVOKABLE void onAircraftClicked(QString text);
    Q_INVOKABLE void apply();
    Q_INVOKABLE void restore(const QString text);
    Q_INVOKABLE void validateSettings();
    Q_INVOKABLE void doForcedBackup();
    Q_INVOKABLE void onCompletedSlot();

signals:
    void modelChanged(model::CMSModel* model);
    void installInfoChanged(InstallationInfo* info);
    void error(QString );
    void info(QString );
    void showSettings();

private:
    parsing::AbstractParser* pParser = nullptr;
    QSharedPointer<model::AbstractValidator> pValidator;
    model::CMSModel* pModel = nullptr;
    InstallationInfo* pInstallationInfo = nullptr;
    GameFilesManager* pGameFilesManager = nullptr;
};

#endif // APPFACADE_H
