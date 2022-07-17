#include "appfacade.h"
#include "a10cparser.h"
#include "a10cvalidator.h"
#include "fa18cparcer.h"
#include "fa18cvalidator.h"
#include "mockparser.h"
#include "gamefilesmanager.h"

#include <QTimer>

AppFacade::AppFacade(QObject *parent)
    : QObject(parent)
    , pInstallationInfo(new InstallationInfo(this))
    , pGameFilesManager(new GameFilesManager(this))
{
    connect (pGameFilesManager, &GameFilesManager::error,
             this, &AppFacade::error);
    connect(pInstallationInfo, &InstallationInfo::error,
            this, &AppFacade::error);

    if (pInstallationInfo->isFirstRun())
        QTimer::singleShot(1, this,[this](){emit showSettings();});
}

void AppFacade::onAircraftClicked(QString text)
{
    if (text == QStringLiteral("A-10C")){
        pParser = new parsing::A10CParser(this);
        pValidator = QSharedPointer<model::A10CValidator>::create();
    }
    else if (text == QStringLiteral("A-10C_2")){
        pParser = new parsing::A10CParser(this);
        pValidator = QSharedPointer<model::A10CValidator>::create();
    }
    else if (text == QStringLiteral("FA-18C")){
        pParser = new parsing::FA18CParcer(this);
        pValidator = QSharedPointer<model::FA18CValidator>::create();
    }
    else{
//        "F-16C"
//        "M-2000C"
//        "AV8BNA"
        Q_ASSERT(false);
        return;
    }

    if (pModel)
        pModel->deleteLater();
    pModel = new model::CMSModel(pParser, pValidator.data(), this);
    connect(pParser, &parsing::AbstractParser::dataUpdated,
            pModel, &model::CMSModel::onDataChanged);
    connect(pParser, &parsing::AbstractParser::errorOccured,
            this, [this](parsing::Error err){emit error(err.errorMsg);});

    pParser->readFromFile(pGameFilesManager->fullPathForAircraft(text));

    emit modelChanged(pModel);
}

void AppFacade::apply()
{
    pModel->save();
    emit info(tr("Chages saved!"));
}

void AppFacade::restore(const QString text)
{
    pParser->readFromFile(pGameFilesManager->backupPathForAircraft(text));
    pParser->writeToFile(pGameFilesManager->fullPathForAircraft(text));
    pParser->readFromFile(pGameFilesManager->fullPathForAircraft(text));
    emit modelChanged(pModel);
}

void AppFacade::validateSettings()
{
    if (pInstallationInfo->isFirstRun())
        pGameFilesManager->backup(pInstallationInfo->instaledModules());
    pInstallationInfo->validate();
    pGameFilesManager->validate();
}

void AppFacade::doForcedBackup()
{
    pGameFilesManager->backup(pInstallationInfo->instaledModules());
}

