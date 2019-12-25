#include "viewer_mainwin.h"

#include <QApplication>
#include <QTranslator>
#include <QLibraryInfo>
QString const extern APP_NAME=QObject::tr("Cute Light Text Previewer");
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTranslator qtTranslator;
    qtTranslator.load("qt_" + QLocale::system().name(),QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    QTranslator translator;
    translator.load("text-previewer_" + QLocale::system().name(), ":/translations");
    a.installTranslator(&translator);
    a.installTranslator(&qtTranslator);
    viewer_mainwin w;
    w.show();
    return a.exec();
}
