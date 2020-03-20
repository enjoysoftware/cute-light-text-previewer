#include "viewer_mainwin.h"
#include "ui_viewer_mainwin.h"
#include <QIcon>
#include <QFileDialog>
#include <QDebug>
#include <QDir>
#include <QTextStream>
#include <QPrintDialog>
#include <QMessageBox>
#include <QMimeData>
#include "defines.h"
QString const extern APP_NAME;
viewer_mainwin::viewer_mainwin(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , trdlg(new GTranslateDialog)
{
    ui->setupUi(this);
    setAcceptDrops(true);
    is_opened = false;
    is_empty = false;
    actionSetup();
    iconSetup();
    currentPath = QDir::homePath();
    ui->actionAbout->setText(tr("&About %1").arg(APP_NAME));
}

viewer_mainwin::~viewer_mainwin()
{
    delete trdlg;
    delete ui;
}
void viewer_mainwin::actionSetup(){
    qDebug() << "MSG:" << tr("Connecting actions...");
    connect(ui->actionOpen_O,SIGNAL(triggered()),this,SLOT(fileOpen()));
    connect(ui->action_Print,SIGNAL(triggered()),this,SLOT(filePrint()));
    connect(ui->action_Translate,SIGNAL(triggered()),this,SLOT(trDlgOpen()));
    connect(ui->actionAbout,SIGNAL(triggered()),this,SLOT(showabout()));
    connect(ui->actionExit,SIGNAL(triggered()),this,SLOT(close()));
    connect(ui->textEdit,SIGNAL(textChanged()),this,SLOT(setData()));
    qDebug() << "MSG:" << tr("Done");
    this->setContextMenuPolicy(Qt::NoContextMenu);
    about_=new AboutDialog();
    ui->action_Print->setEnabled(is_opened);
}
void viewer_mainwin::iconSetup(){
    qDebug() << "MSG:" << tr("Setting up icons");
    ui->actionOpen_O->setIcon(ICON_OPEN);
    ui->action_Print->setIcon(ICON_PRINT);
    ui->actionExit->setIcon(ICON_EXIT);
    ui->action_Translate->setIcon(ICON_TRANSLATE);
    qDebug() << "MSG:" << tr("Done");
}
void viewer_mainwin::fileOpen(const QString &fname){
    QString name;
    if(fname.isEmpty())
    {
        QFileDialog filed;
        name = filed.getOpenFileName(this,tr("Open file"),currentPath,tr("Text files(*.txt);;"
                                                                                       "HTML document(*.html *.htm);;"
                                                                                       "Markdown document(*.md *.markdown);;"
                                                                                       "C/C++ Source code and Header(*.c *.cpp *.cc *.h *.cxx);;"
                                                                                       "JavaScript(*.js);;"
                                                                                       "All files(*.* *)"));
    }else{
        name = fname;
    }
    if (name.isEmpty()){
        return;
    }
    QString content=loadFile(name);
    ui->textEdit->setPlainText(content);
    QFileInfo forpath(name);
    currentPath = forpath.absolutePath();
}
void viewer_mainwin::filePrint(){
    QPrintDialog pdlg;
    if(is_empty){
        if(QMessageBox::question(this,tr("Question"),tr("This file is empty.\nDo you want to continue?")) == QMessageBox::No) {
            return;
        }
    }
    qDebug() << "Execute the print dialog.";
    int res=pdlg.exec();
    if(res == QPrintDialog::Accepted){
        qDebug() << "Accepted.Sent a job.";
        ui->textEdit->print((QPagedPaintDevice*)pdlg.printer());
}
}
QString viewer_mainwin::loadFile(QString filename){
    QFile qfilename(filename);
    if (!qfilename.open(QIODevice::ReadOnly)) {
        QString errMsg = qfilename.errorString();
        QMessageBox::critical(this,tr("Error"),tr("Can't open %1:\n%2").arg(qfilename.fileName(),errMsg));
        return tr("Error:\n%1").arg(errMsg);
    }
    QTextStream in(&qfilename);
    QString line;
    int lines;
    lines=0;
    while (!in.atEnd()){
        lines++;
        line +=in.readLine()+"\n";
    }
    ui->statusbar->showMessage(tr("Opened \"%1\" :%2 lines").arg(filename,QString::number(lines)));
    is_opened = true;
    return line;
}
void viewer_mainwin::showabout(){
    about_->show();
}
void viewer_mainwin::setData(){
    trdlg->setText(ui->textEdit->toPlainText());
    ui->action_Print->setEnabled(is_opened);
    if (is_opened){
    if(ui->textEdit->toPlainText() == ""){
        is_empty = true;
        qDebug() << "Changed status:textEdit is empty";
    }else{
        is_empty  = false;
        qDebug() << "textEdit is not empty";
    }
    }
}
void viewer_mainwin::trDlgOpen(){
    if(trdlg->exec() == QDialog::Rejected){
        qWarning() << "Dialog closed unexpectedly: Rejected.";
    }
}
void viewer_mainwin::dragEnterEvent(QDragEnterEvent *e){
    if(e->mimeData()->hasUrls())
    {e->acceptProposedAction();}
}
void viewer_mainwin::dropEvent(QDropEvent *e){
   if(e->mimeData()->urls().size() >= 2){
       QMessageBox::critical(this,tr("Error"),tr("%1 files have been dragged at the same time. Even multiple files do not support reading.").arg(e->mimeData()->urls().size() ));
   }else
   {
       QString draggedfile = e->mimeData()->urls().first().toLocalFile();
       qDebug() << "Load:" << draggedfile;
       fileOpen(draggedfile);
   }
}
