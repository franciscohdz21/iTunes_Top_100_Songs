#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QUrl>
#include "trackviewmodel.h"
#include "xmlparser.h"
#include "guifeatures.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    //Set context properties
    QQmlContext* trackViewModelCtx = engine.rootContext();
    trackViewModelCtx->setContextProperty("trackviewmodel", &TrackViewModel::Instance());

    QQmlContext* xmlPArserCtx = engine.rootContext();
    xmlPArserCtx->setContextProperty("xmlparser", &XMLParser::Instance());

    QQmlContext* guiFeaturesCtx = engine.rootContext();
    guiFeaturesCtx->setContextProperty("guifeatures", &GUIFeatures::Instance());

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
