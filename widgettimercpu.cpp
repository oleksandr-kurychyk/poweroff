#include "widgettimercpu.h"
#include "headers.h"
QList<float> readCpuStats();
WidgetTimerCpu::WidgetTimerCpu(QWidget *parent)
	: QWidget(parent)
{
	
	InitUI();
	this->timer=new QTimer(this);
    timer->start(1000);
	connect(timer,&QTimer::timeout,this,&WidgetTimerCpu::slotTimerCpuExec);
	connect(this->checkboxCpu,&QCheckBox::stateChanged,this,&WidgetTimerCpu::slotRadioCheck);
	connect(this->teCpu,&QTimeEdit::timeChanged,this,&WidgetTimerCpu::slotTeTimeChanged);

#if defined(Q_WS_WIN)
	this->idletime1=0;
	this->idletime2=0;
	this->kerneltime1=0;
	this->kerneltime2=0;
	this->userTime1=0;
	this->userTime2=0;
	this->time_counter = -1;
    #elif defined(Q_OS_LINUX)

    list_proc=readCpuStats();
    sum_proc=1;

#else

#endif


}

WidgetTimerCpu::~WidgetTimerCpu()
{

}
void WidgetTimerCpu::InitUI()
{
	this->layout_1 = new QGridLayout();
	this->layout_2 = new QGridLayout();
    this->groupbox = new QGroupBox("CPU таймер");
    this->groupbox->setStyleSheet( "QGroupBox { background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,stop: 0 #E0E0E0, stop: 1 #FFFFFF);"
                                   "border: 2px solid gray;border-radius: 5px;margin-top: 1ex;}   "
                               "QGroupBox::title {subcontrol-origin: margin;subcontrol-position: top center; padding: 0 3px;"
                                   "background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #E0E0E0, stop: 1 #FFFFFF); }");
    this->labelTimeCapacity = new QLabel(tr("Время загрузки СРU"));
	this->labelTimeCpuInf = new QLabel();
	this->labelTimeCpuInf->setVisible(0);
	this->spinbox = new QSpinBox();
    spinbox->setMinimum(1);
    spinbox->setMaximum(100);
	this->teCpu = new QTimeEdit();
    teCpu->setDisplayFormat("hh:mm:ss");
	this->teCpu->setMinimumTime(QTime(0,0,3)); 
    this->checkboxCpu = new QCheckBox(tr("Минимальна загрузка CPU"));
	this->checkboxCpu->setCheckState(Qt::Unchecked);
	this->progbar = new QProgressBar();
	this->progbar->setMaximum(100);
	this->progbar->setMinimum(0);
	//this->progbar->setTextVisible(0);
	this->progbar->setAlignment(Qt::AlignCenter);;
	/**/
	this->progbar->setValue(12);
	/**/
	this->setLayout(this->layout_1);
	this->layout_1->addWidget(this->groupbox);
	this->groupbox->setLayout(this->layout_2);
	this->layout_2->addWidget(checkboxCpu,1,1);
	this->layout_2->addWidget(spinbox,1,2);
	this->layout_2->addWidget(labelTimeCapacity,2,1);
	this->layout_2->addWidget(teCpu,2,2);
	
	this->layout_2->addWidget(labelTimeCpuInf,3,1,1,2);
	this->layout_2->addWidget(progbar,4,1,1,2);
	this->teCpu->setEnabled(0);
	this->spinbox->setEnabled(0);



}
void WidgetTimerCpu::slotTimerCpuExec()
{
	
#if defined(Q_WS_WIN)
	int usr,kerl,idl,sys; 
	bool bb= GetSystemTimes(&lpIdleTime1, &lpKernelTime, &lpUserTime);
	idletime1 = lpIdleTime1.dwLowDateTime;
	kerneltime1 = lpKernelTime.dwLowDateTime;
	userTime1 = lpUserTime.dwLowDateTime;

	usr = userTime1 - userTime2;
	kerl = kerneltime1 - kerneltime2;
	idl = idletime1 - idletime2;
	sys = kerl + usr;
	cpu = int( (sys - idl) *100 / sys );
	progbar->setValue(cpu);
	userTime2 = userTime1;
	kerneltime2 = kerneltime1;
	idletime2 = idletime1;



#elif defined( Q_OS_LINUX)
   QList<float> tmp_list = readCpuStats();
    //if(tmp_list.size()==list_proc.size()||tmp_list.size()==4)
    {
        float v1 =tmp_list[0]- list_proc[0];
         float v2 = tmp_list[1]- list_proc[1];
          float v3 =tmp_list[2]- list_proc[2];
           float v4 = tmp_list[3]- list_proc[3];
           cpu=(100*(v1+v2+v3)/(v1+v2+v3+v4));
           progbar->setValue(cpu);
list_proc=tmp_list;

    }
#else
#endif
}

void WidgetTimerCpu::slotRadioCheck(int state)
{
	switch(state)
	{

	case Qt::Unchecked:
		{
			this->teCpu->setEnabled(0);
			this->spinbox->setEnabled(0);
			this->labelTimeCpuInf->setVisible(0);
			disconnect(timer,&QTimer::timeout,this,&WidgetTimerCpu::slotTimerCpuCounter);
		}
		break;
	case Qt::Checked:
		{
			this->teCpu->setEnabled(1);
			this->spinbox->setEnabled(1);
			this->labelTimeCpuInf->setVisible(1);
			connect(timer,&QTimer::timeout,this,&WidgetTimerCpu::slotTimerCpuCounter);
			this->time_counter = (teCpu->time().hour()*3600)+(teCpu->time().minute()*60)+teCpu->time().second();		
		}
		break;	
	}
}
void WidgetTimerCpu::slotTimerCpuCounter()
{
    if(cpu>spinbox->value())
	{
		this->time_counter--;
		if(time_counter ==0)
		{
			emit execTimer("Cpu timer exec","procesor",0); 
			this->checkboxCpu->setChecked(0);
		}
		
	}
    else if(cpu<spinbox->value())
	{
	this->time_counter = (teCpu->time().hour()*3600)+(teCpu->time().minute()*60)+teCpu->time().second();

	}
    QTime tmp_time(time_counter/3600,(time_counter/60)%24,time_counter%60);

    this->labelTimeCpuInf->setText(tmp_time.toString("hh:mm:ss"));
	

}
void WidgetTimerCpu::slotTeTimeChanged(QTime time)
{
	this->time_counter = (time.hour()*3600)+(time.minute()*60)+time.second();
}
QList<float> readCpuStats()
{
    QList<float> tmp_list;
    QFile file("/proc/stat");
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return tmp_list;
     }
     QTextStream in(&file);
    QString tmp;
    in>>tmp;
    for(int i=0;i<4;i++ )
    {
        float value = 0;
        in>>value;
        tmp_list.append(value);

    }
    file.close();
    return tmp_list;
}

