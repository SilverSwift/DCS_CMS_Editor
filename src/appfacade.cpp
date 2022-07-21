#include "appfacade.h"
#include "a10cparser.h"
#include "a10cvalidator.h"
#include "fa18cparcer.h"
#include "fa18cvalidator.h"
#include "m2000cparser.h"
#include "m2000cvalidator.h"
#include "f16cparser.h"
#include "f16cvalidator.h"
#include "av8bparser.h"
#include "av8bvalidator.h"
#include "gamefilesmanager.h"

AppFacade::AppFacade(QObject *parent)
    : QObject(parent)
    , pInstallationInfo(new InstallationInfo(this))
    , pGameFilesManager(new GameFilesManager(this))
{
    connect (pGameFilesManager, &GameFilesManager::error,
             this, &AppFacade::error);
    connect(pInstallationInfo, &InstallationInfo::error,
            this, &AppFacade::error);

    connect(this, &AppFacade::modelErrorWorkaround,
            this, &AppFacade::modelError,
            Qt::QueuedConnection);

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
    else if (text == QStringLiteral("M-2000C")){
        pParser = new parsing::M2000CParser(this);
        pValidator = QSharedPointer<model::M2000CValidator>::create();
    }
    else if (text == QStringLiteral("F-16C")){
        pParser = new parsing::F16CParser(this);
        pValidator = QSharedPointer<model::F16CValidator>::create();
    }
    else if (text == QStringLiteral("AV8BNA")){
        pParser = new parsing::AV8BParser(this);
        pValidator = QSharedPointer<model::AV8BValidator>::create();
    }
    else{
        //JF-17
        Q_ASSERT_X(false, Q_FUNC_INFO, text.toStdString().c_str());
        return;
    }

    if (pModel)
        pModel->deleteLater();
    pModel = new model::CMSModel(pParser, pValidator.data(), this);
    connect(pParser, &parsing::AbstractParser::dataUpdated,
            pModel, &model::CMSModel::onDataChanged);
    connect(pParser, &parsing::AbstractParser::errorOccured,
            this, [this](parsing::Error err){emit error(err.errorMsg);});
    connect(pModel, &model::CMSModel::info,
            this, &AppFacade::info);

    if (!pParser->readFromFile(pGameFilesManager->fullPathForAircraft(text)))
        emit modelErrorWorkaround(QPrivateSignal());

    emit modelChanged(pModel);
}

void AppFacade::reset(QString text)
{
    pParser->initFromDefaults(text);
    pParser->writeToFile(pGameFilesManager->fullPathForAircraft(text));
    pParser->readFromFile(pGameFilesManager->fullPathForAircraft(text));
    emit modelChanged(pModel);
}

void AppFacade::apply(QString text)
{
    pModel->save();
    pParser->writeToFile(pGameFilesManager->backupPathForAircraft(text));
    pParser->readFromFile(pGameFilesManager->fullPathForAircraft(text));
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

    mIsValid = (pInstallationInfo->validate() &&
                pGameFilesManager->validate());
    emit isValidChanged(mIsValid);
}

void AppFacade::doForcedBackup()
{
    if (pInstallationInfo->validate()){
        pGameFilesManager->backup(pInstallationInfo->instaledModules());
        emit info(tr("Force backup finished"));
    }
}

void AppFacade::onCompletedSlot()
{
    if (pInstallationInfo->isFirstRun())
        emit showSettings();
    else
        validateSettings();
}

