#include "comandsdialog.h"
#include "ui_comandsdialog.h"
#include "comandoperations.h"


ComandsDialog::ComandsDialog(QWidget *parent) :
    QDialog(parent=0),
    ui(new Ui::ComandsDialog)
{
    ui->setupUi(this);
    this->com = ComandOperations::getInstance();
    ui->lineEdit_sd->setText(com->getComandSD());
    ui->lineEdit_rb->setText(com->getComandRB());
    ui->lineEdit_hib->setText(com->getComandHib());
    ui->lineEdit_sb->setText(com->getComandSb() );
    ui->lineEdit_lo->setText(com->getComandLO());
    ui->lineEdit_lock->setText(com->getComandLock());
    ui->lineEdit_nm->setText(com->getComandNM());
    ui->lineEdit_rpo->setText(com->getComandRPO());




}

ComandsDialog::~ComandsDialog()
{
    delete ui;
}

void ComandsDialog::on_pushButton_2_clicked()
{

    com->setComandSD(ui->lineEdit_sd->text());
    com->setComandRB(ui->lineEdit_rb->text());
    com->setComandHib(ui->lineEdit_hib->text());
    com->setComandSb(ui->lineEdit_sb->text());
    com->setComandLO(ui->lineEdit_lo->text());
    com->setComandLock(ui->lineEdit_lock->text());
    com->setComandNM(ui->lineEdit_nm->text());
    com->setComandRPO(ui->lineEdit_rpo->text());
    this->close();
    this->setResult(1);

}

void ComandsDialog::on_pushButton_clicked()
{
    this->close();
    this->setResult(0);
}

void ComandsDialog::on_pushButton_default_clicked()
{
    ui->lineEdit_sd->setText("dbus-send --system --print-reply --dest=\"org.freedesktop.ConsoleKit\" /org/freedesktop/ConsoleKit/Manager org.freedesktop.ConsoleKit.Manager.Stop");
    ui->lineEdit_rb->setText("dbus-send --system --print-reply --dest=\"org.freedesktop.ConsoleKit\" /org/freedesktop/ConsoleKit/Manager org.freedesktop.ConsoleKit.Manager.Restart");
    ui->lineEdit_hib->setText("dbus-send --system --print-reply --dest=\"org.freedesktop.UPower\" /org/freedesktop/UPower org.freedesktop.UPower.Hibernate");
    ui->lineEdit_sb->setText("dbus-send --system --print-reply --dest=\"org.freedesktop.UPower\" /org/freedesktop/UPower org.freedesktop.UPower.Suspend");
    ui->lineEdit_lo->setText("");
    ui->lineEdit_lock->setText("");
    ui->lineEdit_nm->setText("");
    ui->lineEdit_rpo->setText("");




}
