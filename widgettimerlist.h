#ifndef WIDGETTIMERLIST_H
#define WIDGETTIMERLIST_H

#include <QWidget>
#include <QTimeEdit>
#include <QDateEdit>
#include <QCheckBox>
#include <QGroupBox>
#include <QGridLayout>
#include <QLabel>
#include <QTimer>
#include <qmessagebox.h>


class WidgetTimerList : public QWidget
{
	Q_OBJECT

public:
	WidgetTimerList(QWidget *parent = 0);
	~WidgetTimerList();

private:
	void initUI();
	QCheckBox * checkTimeOp;
	QCheckBox * checkDate;
	QCheckBox * checkCountdown;
	
	QTimeEdit * teTimeOp;
	QDateEdit * deDate;
	QTimeEdit * teCountdown;
	
	QLabel * label_t1;
	QLabel * label_t2;
	QGridLayout*layout_1;
	QGridLayout*layout_2;
	QTimer * timer_1;
	QTimer * timer_2;
	int count_countdown;
	

	QGroupBox  * groupbox;
	
	void slotCheckTimeOp(int );
	void slotCheckDate(int );
	void slotCheckCountdown(int );
	
	void slotTOTimer_one();
	void slotTOTimer_two();
	void slotTimeChanged(QTime);
signals:
	void execTimer (QString,QString,int);
	
	
	
};


#endif // WIDGETTIMERLIST_H
