#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "appfacade.h"
#include "cmsmodel.h"
#include "installationinfo.h"
#include "AbstractParser.h"

int main(int argc, char** argv)
{
    QGuiApplication app(argc, argv);
    app.setApplicationName("DCS_CMS_Editor");
    app.setOrganizationDomain("github.com");
    app.setOrganizationName(QStringLiteral("SilverSwift"));

    qmlRegisterType<AppFacade>("SilverSwift.Model", 0, 1, "Facade");
    qmlRegisterType<parsing::AbstractParser>("SilverSwift.Model", 0, 1, "Parser");
    qmlRegisterType<model::CMSModel>("SilverSwift.Model", 0, 1, "CMSModel");
    qmlRegisterType<InstallationInfo>("SilverSwift.Model", 0, 1, "InstallInfo");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));

    return app.exec();
}
