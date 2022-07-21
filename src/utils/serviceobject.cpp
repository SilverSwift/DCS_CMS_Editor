#include "serviceobject.h"

#include <QGuiApplication>
#include <QDebug>

#include "gamefilesmanager.h"
//#include "installationinfo.h"

#include "a10cparser.h"
#include "av8bparser.h"
#include "f16cparser.h"
#include "fa18cparcer.h"
#include "m2000cparser.h"


ServiceObject::ServiceObject(QObject *parent)
    : QObject{parent}
{

}

#ifdef QT_DEBUG
void ServiceObject::generateDefaults(QString outputDir)
{
    if (outputDir.isEmpty())
        outputDir = qApp->applicationDirPath();


    qDebug()<<"output dir is:"<<outputDir;

    auto gameFiles = new GameFilesManager(this);

    qDebug()<<"serializing A-10C";
    auto a10c = new parsing::A10CParser(this);
    a10c->readFromFile(gameFiles->fullPathForAircraft(QStringLiteral("A-10C")));
    a10c->serialize(outputDir + "/A-10C");
    a10c->serialize(outputDir + "/A-10C_2");

    qDebug()<<"serializing AV-8B";
    auto av8b = new parsing::AV8BParser(this);
    av8b->readFromFile(gameFiles->fullPathForAircraft(QStringLiteral("AV8BNA")));
    av8b->serialize(outputDir + "/AV8BNA");

    qDebug()<<"serializing F-16C";
    auto f16c = new parsing::F16CParser(this);
    f16c->readFromFile(gameFiles->fullPathForAircraft(QStringLiteral("F-16C")));
    f16c->serialize(outputDir + "/F-16C");

    qDebug()<<"serializing FA-18C";
    auto fa18c = new parsing::FA18CParcer(this);
    fa18c->readFromFile(gameFiles->fullPathForAircraft(QStringLiteral("FA-18C")));
    fa18c->serialize(outputDir + "/FA-18C");

    qDebug()<<"serializing M-2000C";
    auto m2000c = new parsing::M2000CParser(this);
    m2000c->readFromFile(gameFiles->fullPathForAircraft(QStringLiteral("M-2000C")));
    m2000c->serialize(outputDir + "/M-2000C");

}

#endif
