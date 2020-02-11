#include "gtranslatedialog.h"
#include "ui_gtranslatedialog.h"
#include "gtranslator.h"
#include "ui_viewer_mainwin.h"
#include <QLocale>
#include <QDebug>
#include <QMessageBox>
GTranslateDialog::GTranslateDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GTranslateDialog)
{
    ui->setupUi(this);
    QString locale=QLocale::system().name();
    qDebug() << "Guess language...";
    if(locale.length() >= 2){
    language=locale.mid(0,2);
    }else if(locale == "C"){
        language="en";
    }else {
        language=locale;
    }
    ui->targetLangBox->setText(language);
//    GTranslator tra(language,"en","Please type here",this);
//    ui->translatedText->setText(tra.translate());
//    qDebug() << "Language :" << language;
}

GTranslateDialog::~GTranslateDialog()
{
    delete ui;
}
void GTranslateDialog::setText(QString tmptext){
    text = tmptext; return;
}
void GTranslateDialog::showEvent(QShowEvent *){
    ui->translatedText->setText(text);
}
