#include "viewer_mainwin.h"

#include <QApplication>
#include <QTranslator>
#include <QLibraryInfo>
#include <QTextStream>
QString const extern APP_NAME=QObject::tr("Cute Light Text Previewer");
QString const extern VERSION="0.1";
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTranslator qtTranslator;
    qtTranslator.load("qt_" + QLocale::system().name(),QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    QTranslator translator;
    translator.load("text-previewer_" + QLocale::system().name(), ":/translations");
    a.installTranslator(&translator);
    a.installTranslator(&qtTranslator);
    QFile stylefile("QDarkStyleSheet/qdarkstyle/style.qss");
    if (!stylefile.exists())
    {
    printf("Unable to set stylesheet, file not found\n");
    }
else
{
    stylefile.open(QFile::ReadOnly | QFile::Text);
    QTextStream ts(&stylefile);
    a.setStyleSheet(ts.readAll());
}
    viewer_mainwin w;
    w.show();
    return a.exec();
}
