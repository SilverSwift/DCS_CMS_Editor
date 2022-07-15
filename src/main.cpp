#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "appobject.h"
#include "cmsmodel.h"
#include "AbstractParser.h"

int main(int argc, char** argv)
{

    QGuiApplication app(argc, argv);

    qmlRegisterType<AppObject>("SilverSwift.Application", 0, 1, "Instance");
    qmlRegisterType<CMSModel>("SilverSwift.Model", 0, 1, "CMSModel");
    qmlRegisterType<parsing::AbstractParser>("SilverSwift.Model", 0, 1, "Parser");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));


    return app.exec();
}
