#ifndef WIDGETPOWEREXEC_H
#define WIDGETPOWEREXEC_H
#include <QWidget>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QRadioButton>
#include <QPushButton>
#include <QGroupBox>
#include <qmessagebox.h>
class WidgetPowerExec :	public QWidget
{
	Q_OBJECT
public:
	WidgetPowerExec(QWidget *parent = 0);
	~WidgetPowerExec();
public slots:
	void ExecTimer(QString msg_1,QString msg_2,int code);

private:
	int state;
	void InitUI(); 

	QHBoxLayout * hblayout_1;
	QGridLayout * gridlayout_1;
	QPushButton * buton_exec;
	QGroupBox   * groupbox_item;
	QRadioButton *radiobutton_shutdown;
	QRadioButton *radiobutton_restart;
	QRadioButton *radiobutton_hibernation;
	QRadioButton *radiobutton_standby;
	QRadioButton *radiobutton_logout;
	QRadioButton *radiobutton_lock;
	QRadioButton *radiobutton_nm;
	QRadioButton *radiobutton_rpo;
    QRadioButton ** arr_button;

private slots:
		void slotRadioSelected(); 
        void slotPushButtonClick();

	


};
#endif // WIDGETPOWEREXEC_H

