#ifndef WIDGETTIMERCPU_H
#define WIDGETTIMERCPU_H

#include <QWidget>
#include <QtWidgets>
#include "headers.h"

 
class WidgetTimerCpu : public QWidget
{
	Q_OBJECT

public:
	WidgetTimerCpu(QWidget *parent=0);
	~WidgetTimerCpu();

private:
	void InitUI();
	QGroupBox * groupbox;
	QLabel * labelTimeCapacity;
		QLabel * labelTimeCpuInf;
		QSpinBox *spinbox;
		QTimeEdit * teCpu;
		QCheckBox * checkboxCpu;
		QProgressBar * progbar;
		QGridLayout * layout_1;
		QGridLayout * layout_2;
		QTimer * timer;
		

int cpu ,time_counter ;
////////////////// win_os
#if defined (Q_WS_WIN)
bool sp1,sp2;
int idletime1,idletime2,kerneltime1, kerneltime2, userTime1,userTime2,
FILETIME lpIdleTime1, lpKernelTime,lpUserTime;



#elif defined (Q_OS_LINUX)
QList<float> list_proc;
float sum_proc;

#else
#endif




private slots:
	void slotTimerCpuExec();
	void slotTimerCpuCounter();
	void slotRadioCheck(int);
	void slotTeTimeChanged(QTime);

	signals:
		void execTimer (QString,QString,int);

	
};

#endif // WIDGETTIMERCPU_H
