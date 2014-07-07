#ifndef COMANDSDIALOG_H
#define COMANDSDIALOG_H

#include <QDialog>
class ComandOperations;
namespace Ui {
class ComandsDialog;
}

class ComandsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ComandsDialog(QWidget *parent = 0);
    ~ComandsDialog();
     ComandOperations * com;

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::ComandsDialog *ui;
};

#endif // COMANDSDIALOG_H
