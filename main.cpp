#include "mainwindow.h"
#include "widgetpowerexec.h"
#include <QApplication>
#include "widgetcurinf.h"
#include "widgettimerlist.h"
#include "widgettimercpu.h"
#include "widgetnetworktimer.h"
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MainWindow w;
	w.show();

	
	//WidgetTimerCpu wtc;wtc.show(); 
	//WidgetPowerExec wpe;
	//wpe.show();
	//wpe.ExecTimer(" 11","sds",3535);
	return a.exec();
}
