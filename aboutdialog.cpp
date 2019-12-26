#include "aboutdialog.h"
#include "ui_aboutdialog.h"
QString const extern APP_NAME;
QString const extern VERSION;
AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutDialog)
{
    ui->setupUi(this);
    this->setWindowTitle(tr("About %1").arg(APP_NAME));
    ui->version->setText(VERSION);
    ui->appname->setText(tr("<html><head/""><body><p><span style=\" font-size:18pt;\">"
                            "%1</span></p></body></html>")
                         .arg(APP_NAME));
}

AboutDialog::~AboutDialog()
{
    delete ui;
}
