#include "widgetnetworktimer.h"
#include "net_func.h"



WidgetNetworkTimer::WidgetNetworkTimer(QWidget *parent)
    : QWidget(parent)
{
    InitUI();
    timer=new QTimer(this);
    timer_count=new QTimer(this);
    connect(timer,&QTimer::timeout,this,&WidgetNetworkTimer::TimerNetExec );
    connect(timer_count,&QTimer::timeout,this,&WidgetNetworkTimer::TimerCountExec);
    connect(checkbox_get_inf,&QCheckBox::stateChanged,this,&WidgetNetworkTimer::slot_check_inf);
    connect(checkbox_count,&QCheckBox::stateChanged,this,&WidgetNetworkTimer::slot_check_count);
    connect(combo_net_count,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_cnc_index_changed(int)));
    connect(combo_net_power,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_cnp_index_changed(int)));
    connect(te_count,SIGNAL(timeChanged(QTime)),this,SLOT(slot_tepow_timechanged(QTime )));
    connect(spin_net_va,SIGNAL(valueChanged(int)),this,SLOT(slot_sinpow_changed(int)));
    connect(button_update,SIGNAL(clicked()),this,SLOT(slot_button_update_click()));
    net_manager->updateConfigurations();
    this->setStyleSheet( "QGroupBox { background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,stop: 0 #E0E0E0, stop: 1 #FFFFFF);"
                         "border: 2px solid gray;border-radius: 5px;margin-top: 1ex;}   "
                         "QGroupBox::title {subcontrol-origin: margin;subcontrol-position: top left; padding: 0 3px;"
                         "background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #E0E0E0, stop: 1 #FFFFFF); }");

    this->current_receive_value=0;
    this->current_transmit_value=0;
    checkbox_count->stateChanged(0);
    checkbox_count->setTristate(0);
    checkbox_get_inf->stateChanged(0);
    checkbox_get_inf->setTristate(0);
}

WidgetNetworkTimer::~WidgetNetworkTimer()
{

}
void WidgetNetworkTimer::InitUI()
{
    this->layout_1 = new QGridLayout();
    this->groupbox = new QGroupBox(tr("Сетевой таймер"));
    this->layout_2 = new QGridLayout();


    this->checkbox_get_inf = new QCheckBox("Получить статистику активного соединения");
    this->button_update = new QPushButton("Обновить");
    ////
     QHBoxLayout * hblayout_1 = new QHBoxLayout();
    hblayout_1->addWidget(checkbox_get_inf);
    hblayout_1->addWidget(button_update);
    ///////////////
    this->combo_net_in = new QComboBox();
    for(int i=0;i<12;i++)
    {
        this->arrlabel_net_inf[i] = new QLabel(QString("%0").arg(i));
        this->layout_2->addWidget(arrlabel_net_inf[i],(i/2)+2,i%2);
    }
    arrlabel_net_inf[0]->setText(tr("IP адреса"));
    arrlabel_net_inf[2]->setText(tr("МАС адрес"));
    arrlabel_net_inf[4]->setText(tr("Входящий трафик"));
    arrlabel_net_inf[6]->setText(tr("Входяща скорость"));
    arrlabel_net_inf[8]->setText(tr("Исходящий  трафик"));
    arrlabel_net_inf[10]->setText(tr("Исходяща скорость"));
    this->label_1 = new QLabel(tr("       "));
    this->label_2 = new QLabel(tr("Учитивать скорость в течении"));
    this->label_3 = new QLabel();
    this->line = new QFrame();
    this->line->setLineWidth(2);
    this->line->setFrameShape(QFrame::HLine);
    this->checkbox_count  = new QCheckBox(tr("Учитивать"));
    this->combo_net_count = new QComboBox();
    this->combo_net_count->addItem(tr("Скорость входящого трафика"));
    this->combo_net_count->addItem(tr("Скорость исходящого трафика"));
    this->combo_net_count->addItem(tr("Обьем входящого трафика"));
    this->combo_net_count->addItem(tr("Обьем исхдящого трафика "));
    this->combo_net_count->addItem(tr("Сумарний обьем трафика"));
    this->spin_net_va = new QSpinBox();
    spin_net_va->setMinimum(1);
    spin_net_va->setMaximum(10000);
    this->combo_net_power = new QComboBox();
    combo_net_power->addItem("Kb");
    combo_net_power->addItem("Mb");
    combo_net_power->addItem("Gb");
    this->te_count = new QTimeEdit();
    te_count->setMinimumTime(QTime(0,0,3));
    te_count->setDisplayFormat("hh:mm:ss");
    this->setLayout(layout_1);
    this->layout_1->addWidget(groupbox);
    this->groupbox->setLayout(layout_2);
    /*
    this->layout_2->addWidget(checkbox_get_inf,0,0);
    this->layout_2->addWidget(button_update,0,1);
    */
    this->layout_2->addLayout(hblayout_1,0,0,1,3);

    this->layout_2->addWidget(combo_net_in,1,0,1,3);
    this->layout_2->addWidget(line,9,0,1,3);
    this->layout_2->addWidget(checkbox_count,10,0);
    this->layout_2->addWidget(combo_net_count,10,1,1,2);
    this->layout_2->addWidget(label_1,11,0);
    this->layout_2->addWidget(spin_net_va,11,1);
    this->layout_2->addWidget(combo_net_power,11,2);
    this->layout_2->addWidget(label_2,12,0,1,2);
    this->layout_2->addWidget(te_count,12,2);
    this->layout_2->addWidget(label_3,13,0,1,3);

}
void WidgetNetworkTimer::TimerNetExec()
{    
    int tmp_res,tmp_trans;
    tmp_res = getReceiveInf(combo_net_in->currentText());
    tmp_trans = getTransmitInf(combo_net_in->currentText());
    if(tmp_res==-1||tmp_trans==-1)
    {
        UpdateNIList();
        checkbox_count->stateChanged(0);
        checkbox_count->setEnabled(0);
        return;
    }
    net_speed_down = tmp_res - this->current_receive_value;
    net_speed_up = tmp_trans - this->current_transmit_value;
    arrlabel_net_inf[1]->setText(getNetInterfaceIP(combo_net_in->currentText()));
    arrlabel_net_inf[3]->setText(getNetInterfaceMAC(combo_net_in->currentText())) ;
    arrlabel_net_inf[5]->setText(transFormNetUnit(current_receive_value));
    arrlabel_net_inf[7]->setText(transFormNetUnit(net_speed_down)+tr("\\s"));
    arrlabel_net_inf[9]->setText(transFormNetUnit(current_transmit_value));
    arrlabel_net_inf[11]->setText(transFormNetUnit(net_speed_up)+tr("\\s"));
    this->current_receive_value = tmp_res;
    this->current_transmit_value =tmp_trans;
}
void WidgetNetworkTimer::slot_button_update_click()
{
    UpdateNIList();
    checkbox_count->stateChanged(0);;
    checkbox_count->setEnabled(0);
}

QString WidgetNetworkTimer::transFormNetUnit(int value)
{
    QString ret_value;
    if(value<1024)
    {
        ret_value=(QString("%0 B").arg( value));
    }
    else if(value>1024&&value<1024*1024)
    {
        ret_value=(QString("%0 kB").arg((float) value/1024,0,'f',2));
    }
    else if(value>1024*1024)
    {
        ret_value=(QString("%0 mB").arg((float) value/(1024*1024),0,'f',2));
    }
    return ret_value;
}

void WidgetNetworkTimer::UpdateNIList()
{
    combo_net_in->clear();
    QStringList tmplist = getNetInterfaces();
    if(tmplist.count()==0)
    {
        checkbox_get_inf->stateChanged(0);;
    }
    combo_net_in->addItems(tmplist);
}
void WidgetNetworkTimer::slot_check_inf(int state )
{
    switch (state) {
    case Qt::Checked:
    {
        timer->start(1000);
        UpdateNIList();
       this->current_receive_value == getReceiveInf(combo_net_in->currentText());
        this->current_transmit_value =getTransmitInf(combo_net_in->currentText());
        SetEnableWidgetNetInf(1);
    }
        break;
    case Qt::Unchecked:
    {
        this->combo_net_in->clear();
        timer->stop();
        for(int i =1;i<12;i+=2)
        {
            arrlabel_net_inf[i]->setText("              ");
        }

        SetEnableWidgetNetInf(0);
    }
        break;
    default:
        break;
    }
}
void WidgetNetworkTimer::TimerCountExec()
{
    (this->*p_Count_func)();

}
void WidgetNetworkTimer::slot_check_count(int state)
{
    switch (state) {
    case Qt::Checked:
    {
        StartCountTraffic();
        SetEnableWidgetNetCount(1);
    }
        break;
    case Qt::Unchecked:
    {
        StopCountTraffic();
        SetEnableWidgetNetCount(0);
    }
        break;
    default:
        break;
    }
}
void WidgetNetworkTimer::SetEnableWidgetNetInf(bool flag)
{
    for(int i=0;i<12;i++)
    {
        this->arrlabel_net_inf[i]->setEnabled(flag);
    }
    combo_net_in->setEnabled(flag);
    this->button_update->setEnabled(flag);
    checkbox_count->stateChanged(0);;
    checkbox_count->setEnabled(flag);
}
void WidgetNetworkTimer::SetEnableWidgetNetCount(bool flag )
{
    this->combo_net_count->setEnabled(flag);
    this->combo_net_count->setEnabled(flag);
    this->spin_net_va-> setEnabled(flag);
    this->combo_net_power-> setEnabled(flag);
    this->te_count-> setEnabled(flag);
    label_1->setEnabled(flag);
    label_2->setEnabled(flag);
    label_3->setEnabled(flag);
};
void WidgetNetworkTimer::StartCountTraffic()
{
    current_count_traffic=0;
    current_count_limit =spin_net_va->value() * pow(10, (combo_net_power->currentIndex()+1)*3);
    QTime tmp_time= te_count->time();
    current_count_time_limit = tmp_time.hour()*3600+tmp_time.minute()*60+tmp_time.second();
    current_count_time = 0;
    this->te_count-> setEnabled(1);
    switch( combo_net_count->currentIndex() )
    {
    case 0:
    {
        p_Count_func = &WidgetNetworkTimer::CountInputSpeedTraffic;
    }
        break;
    case 1:
    {
        p_Count_func = &WidgetNetworkTimer::CountOutputSpeedTraffic;

    }
        break;
    case 2:
    {
        p_Count_func = &WidgetNetworkTimer::CountInputVolumeTraffic;
        this->te_count-> setEnabled(0);
    }
        break;
    case 3:
    {
        p_Count_func = &WidgetNetworkTimer::CountOutputVolumeTraffic;
        this->te_count-> setEnabled(0);
    }
        break;
    case 4:
    {
        p_Count_func = &WidgetNetworkTimer::CountSummaryVolumeTraffic;
        this->te_count-> setEnabled(0);

    }
        break;
    }
    timer_count->start(1000);
}
void WidgetNetworkTimer::StopCountTraffic()
{
    timer_count->stop();
    label_3->setText("");
}
void WidgetNetworkTimer::RestartCountTraffic()
{
    StopCountTraffic();
    StartCountTraffic();
}
void WidgetNetworkTimer::slot_cnc_index_changed(int index)
{   RestartCountTraffic();

};
void WidgetNetworkTimer::slot_cnp_index_changed(int)
{
    RestartCountTraffic();
}
void WidgetNetworkTimer::CounterTraficExec(QString s1="",QString s2="",int flag=0)
{
    checkbox_count->setChecked(0);
    label_3->setText("");
    emit execTimer(s1,s2,flag);
}
void WidgetNetworkTimer::slot_sinpow_changed(int)
{
    RestartCountTraffic();
}
void WidgetNetworkTimer::slot_tepow_timechanged(QTime )
{
    RestartCountTraffic();
}

void WidgetNetworkTimer::CountSummaryVolumeTraffic()
{
    current_count_traffic+= net_speed_down +net_speed_up;
    if(current_count_traffic>=current_count_limit)
    {
        CounterTraficExec("Сетевий таймер","Сумарний обьем ",0);

    }
    label_3->setText(tr("Сумарний обьем ")+ transFormNetUnit(current_count_traffic));
}
void WidgetNetworkTimer::CountInputVolumeTraffic()
{
    current_count_traffic+= net_speed_down ;
    if(current_count_traffic>=current_count_limit)
    {
        CounterTraficExec("Сетевий таймер","Обьем входящого трафика",0);
    }
    label_3->setText(tr("Обьем входящого трафика ")+ transFormNetUnit(current_count_traffic));
}
void WidgetNetworkTimer::CountOutputVolumeTraffic()
{
    current_count_traffic+= net_speed_up;
    if(current_count_traffic>=current_count_limit)
    {
        CounterTraficExec("Сетевий таймер","Обьем исходящого трафика",0);
    }
    label_3->setText(tr("Обьем исходящого трафика")+ transFormNetUnit(current_count_traffic));
}
void WidgetNetworkTimer::CountInputSpeedTraffic()
{
    if(current_count_limit<=net_speed_down)
        current_count_time++;
    else
    {
        current_count_time=0;
    }
    if (current_count_time>=current_count_time_limit)
    {
        CounterTraficExec("Сетевий таймер","Скорость входящого трафика",0);
    }
    QTime tmp_time(current_count_time/3600,(current_count_time/60)%24,current_count_time%60);

    label_3->setText(tmp_time.toString("hh:mm:ss"));
}
void WidgetNetworkTimer::CountOutputSpeedTraffic()
{
    if(current_count_limit<=net_speed_up)
        current_count_time++;
    else
    {
        current_count_time=0;
    }
    if (current_count_time>=current_count_time_limit)
    {
        CounterTraficExec("Сетевий таймер","Скорость исходящого трафика",0);
    }
    QTime tmp_time(current_count_time/3600,(current_count_time/60)%24,current_count_time%60);
    label_3->setText(tmp_time.toString("hh:mm:ss"));
}


