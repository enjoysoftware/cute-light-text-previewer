#include "viewer_mainwin.h"

#include <QApplication>
#include <QTranslator>
#include <QLibraryInfo>
#include <QTextStream>
#include <QDebug>
QString const extern APP_NAME=QObject::tr("Cute Light Text Previewer");
QString const extern VERSION="1.0";
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
    w.show();
    return a.exec();
}
