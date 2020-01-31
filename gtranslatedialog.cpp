#include "gtranslatedialog.h"
#include "ui_gtranslatedialog.h"
#include "gtranslator.h"
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
    GTranslator tra(language,"en","Value arrays — A container structure to maintain an array of generic values",this);
    ui->translatedText->setText(tra.translate());
    qDebug() << "Language :" << language;
}

GTranslateDialog::~GTranslateDialog()
{
    delete ui;
}
