#ifndef WIDGETNETWORKTIMER_H
#define WIDGETNETWORKTIMER_H

#include <QWidget>
#include <QCheckBox>
#include <QGridLayout>
#include <QComboBox>
#include <QPushButton>
#include <QTimeEdit>
#include <QLabel>
#include <QSpinBox>
#include <QGroupBox>
#include <QFrame>
#include <QTimer>
#include <QtNetwork>
#include <QMessageBox>


class WidgetNetworkTimer : public QWidget
{
	Q_OBJECT

public:
	WidgetNetworkTimer(QWidget *parent = 0);
	~WidgetNetworkTimer();
private:
	QGridLayout *layout_1;
	QGridLayout *layout_2;
	QCheckBox * checkbox_get_inf;
	QCheckBox * checkbox_count;	 
	QLabel * arrlabel_net_inf[12];
	QLabel * label_1;
	QLabel *label_2;
    QLabel *label_3;
	QComboBox * combo_net_in;
	QComboBox * combo_net_count;
	QSpinBox * spin_net_va;
	QComboBox * combo_net_power;
	QTimeEdit * te_count;
	QGroupBox * groupbox;
    QPushButton * button_update;
	QFrame *line;
	QNetworkConfigurationManager * net_manager;
	QList<QNetworkConfiguration>  list_net_inter;

    int net_speed_up ;
    int net_speed_down;
	QTimer * timer;

    QTimer  * timer_count;
	void InitUI();

	void UpdateNIList();

    int current_receive_value;
    int current_transmit_value;
    int current_count_traffic;
    int current_count_time;
    int current_count_time_limit;
    int current_count_limit;
    QString transFormNetUnit(int);
    void SetEnableWidgetNetInf(bool);
    void SetEnableWidgetNetCount(bool);

    void (WidgetNetworkTimer::*p_Count_func)(void);

    void CountSummaryVolumeTraffic();
    void CountInputVolumeTraffic();
    void CountOutputVolumeTraffic();
    void CountInputSpeedTraffic();
    void CountOutputSpeedTraffic();

    void StartCountTraffic();
    void StopCountTraffic();
    void RestartCountTraffic();
    void CounterTraficExec(QString,QString,int);

private slots:
    void slot_check_inf(int );
    void slot_check_count(int);
    void slot_cnc_index_changed(int);
    void slot_cnp_index_changed(int);
    void slot_sinpow_changed(int);
    void slot_tepow_timechanged(QTime );
    void slot_button_update_click();
    void TimerNetExec();
    void TimerCountExec();
signals:
void execTimer (QString,QString,int);

	
};

#endif // WIDGETNETWORKTIMER_H
