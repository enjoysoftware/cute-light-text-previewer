#ifndef GTRANSLATEDIALOG_H
#define GTRANSLATEDIALOG_H

#include <QDialog>
#include <QShowEvent>
namespace Ui {
class GTranslateDialog;
}

class GTranslateDialog : public QDialog
{
    Q_OBJECT

public:
    explicit GTranslateDialog(QWidget *parent = nullptr);
    void setText(QString);
    ~GTranslateDialog();
private:
    QString text;
    Ui::GTranslateDialog *ui;
    QString language;
private slots:
    void boxCheck();
protected:
    virtual void showEvent(QShowEvent *);
};

#endif // GTRANSLATEDIALOG_H
