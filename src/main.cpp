#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QIcon>

#include "appfacade.h"
#include "cmsmodel.h"
#include "installationinfo.h"
#include "abstractparser.h"

int main(int argc, char** argv)
{   
    QGuiApplication app(argc, argv);
    app.setApplicationName("DCS_Preset_Editor");
    app.setOrganizationDomain("github.com");
    app.setOrganizationName(QStringLiteral("SilverSwift"));
    app.setWindowIcon(QIcon(":/img/win_icon.png"));

    qmlRegisterType<AppFacade>("SilverSwift.Model", 0, 1, "Facade");
    qmlRegisterType<parsing::AbstractParser>("SilverSwift.Model", 0, 1, "Parser");
    qmlRegisterType<model::CMSModel>("SilverSwift.Model", 0, 1, "CMSModel");
    qmlRegisterType<InstallationInfo>("SilverSwift.Model", 0, 1, "InstallInfo");

    QQmlApplicationEngine engine;
    QUrl url(QStringLiteral("qrc:/qml/Main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
                              if (!obj && url == objUrl)
                                  qApp->quit();

                          }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
