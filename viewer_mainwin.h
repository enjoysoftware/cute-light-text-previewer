#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QFile>
#include <QFileInfo>
#include "aboutdialog.h"
#include "gtranslatedialog.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class viewer_mainwin : public QMainWindow
{
    Q_OBJECT

public:
    viewer_mainwin(QWidget *parent = nullptr);
    QString currentPath;
    ~viewer_mainwin();
public slots:
    void fileOpen(const QString &fname = "");
private:
    void iconSetup();
    void actionSetup();
    void dragEnterEvent(QDragEnterEvent *);
    void dropEvent(QDropEvent *);
    QString loadFile(QString);
    QByteArray detectEncoding(const QByteArray &text);
    Ui::MainWindow *ui;
    AboutDialog *about_;
    GTranslateDialog *trdlg;
    bool is_empty;
    bool is_opened;
private slots:
    void filePrint();
    void showabout();
    void setData();
    void trDlgOpen();
};
#endif // MAINWINDOW_H
