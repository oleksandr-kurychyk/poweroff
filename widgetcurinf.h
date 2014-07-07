#ifndef WIDGETCURINF_H
#define WIDGETCURINF_H

#include "headers.h"
#include <QWidget>
#include <QLabel>
#include <QtWidgets/QFrame>
#include <QGridLayout>
#include <QGroupBox>
#include <QDate>
#include <QTimer>

class WidgetCurInf : public QWidget
{
	Q_OBJECT

public:
	WidgetCurInf(QWidget *parent = 0);
	~WidgetCurInf();

private:
	void InitUI();
	QFrame * line;
	QLabel * labelCurentTime;
	QLabel * labelCurentTimeData;
	QLabel * labelCurentDate;
	QLabel * labelCurentDateData;
	QLabel * labelCurentDay;
	QLabel * labelCurentDayData;
	QLabel * labelUser;
	QLabel * labelUserData;
	QLabel * labelTimer;
	QLabel * labelTimerData;
	QGroupBox * groupInf;
	QGridLayout *layout_1;
	QGridLayout *layout_2;
	QTimer * timer;
	private slots:
		void slotTimerEvent();

};

#endif // WIDGETCURINF_H
