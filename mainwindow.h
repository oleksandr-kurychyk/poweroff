#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QGroupBox>
#include "widgetpowerexec.h"
#include "widgetcurinf.h"
#include "widgettimerlist.h"
#include "widgettimercpu.h"
#include "widgetnetworktimer.h"
#include <QtGui>


class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = 0);
	~MainWindow();

private:

    QMenuBar * main_menu;
    QMenu * file_menu;
    QMenu * about_menu;
    QAction * action_comands;
     QAction * action_exit;
    QAction * action_about;
    QSystemTrayIcon * tray_icon;
    QAction * action_show_hide;
    QMenu * tray_menu;

	WidgetCurInf * cur_inf;
	WidgetPowerExec * power_exec;
    WidgetTimerList * timer_list;
	WidgetTimerCpu * timer_cpu;
	WidgetNetworkTimer * net_timer;
	QWidget * root;
	QGridLayout *layout;
    void closeEvent(QCloseEvent *);
private slots:
    void on_action_comands();
    void on_action_exit();
    void on_action_about();
    void on_action_show_hide();


};



#endif // MAINWINDOW_H
