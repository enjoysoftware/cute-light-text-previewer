#include "viewer_mainwin.h"

#include <QApplication>
#include <QTranslator>
#include <QLibraryInfo>
#include <QTextStream>
#include <QCommandLineParser>
#include <QCommandLineOption>
#include <QDebug>
#include <QFileInfo>
QString const extern APP_NAME=QObject::tr("Cute Light Text Previewer");
QString const extern VERSION="1.0";
QString const extern ORG_NAME="EnjoySoftware";
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTranslator qtTranslator;
    qtTranslator.load("qt_" + QLocale::system().name(),QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    QTranslator translator;
    translator.load("text-previewer_" + QLocale::system().name(), ":/translations");
    a.installTranslator(&translator);
    a.installTranslator(&qtTranslator);
    QCoreApplication::setApplicationName(APP_NAME);
    QCoreApplication::setApplicationVersion(VERSION);
    QCoreApplication::setOrganizationName(ORG_NAME);
    QCommandLineParser parser;
    parser.addHelpOption();
    parser.addVersionOption();
    parser.setApplicationDescription(QObject::tr("This application loads, and translates file."));
    parser.addPositionalArgument(QObject::tr("file"),QObject::tr("The file to open."));
    parser.process(a);
    viewer_mainwin w;
    if(!parser.positionalArguments().isEmpty()){
        qDebug() << "Load:" << parser.positionalArguments().first();
        w.fileOpen(parser.positionalArguments().first());
    }
#ifdef WITH_DARKSTYLE
    QFile stylefile(":/QDarkStyleSheet/qdarkstyle/style.qss");
    if (!stylefile.exists())
    {
    qDebug() << w.tr("Unable to set stylesheet, file not found\n");
    }
else
{
    if(stylefile.open(QFile::ReadOnly | QFile::Text)){
    QTextStream ts(&stylefile);
    a.setStyleSheet(ts.readAll());
    }else{
        qDebug() << w.tr("Unable to set stylesheet:\n%1").arg(stylefile.errorString());
    }
}
#endif
    w.show();
    return a.exec();
}
