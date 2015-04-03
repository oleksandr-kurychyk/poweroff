#include "widgettimerlist.h"

bool equalTime(const QTime  &t1,const QTime & t2)
{
	if(t1.minute() == t2.minute() && t1.hour() ==t2.hour() && t1.second() == t2.second())
	{
		return true;
	}
	return false;
}
bool equalDateTime(const QDateTime &d1,const QDateTime & d2)
{ 

	if(equalTime(d1.time(),d2.time())&&d1.date()==d2.date())
	{
		return true;
	}
	return false;
}


WidgetTimerList::WidgetTimerList(QWidget *parent)
	: QWidget(parent)
{
	initUI();
	this->timer_1 = new QTimer(this);
	this->timer_2 = new QTimer(this);

	connect(timer_1, &QTimer::timeout, this,&WidgetTimerList::slotTOTimer_one);
	connect(timer_2, &QTimer::timeout, this, &WidgetTimerList::slotTOTimer_two);


}

WidgetTimerList::~WidgetTimerList()
{

}
void WidgetTimerList::initUI()
{
	this->groupbox = new QGroupBox();
    this->groupbox->setStyleSheet( "QGroupBox { background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,stop: 0 #E0E0E0, stop: 1 #FFFFFF);"
                                   "border: 2px solid gray;border-radius: 5px;margin-top: 1ex;}   "
                               "QGroupBox::title {subcontrol-origin: margin;subcontrol-position: top center; padding: 0 3px;"
                                   "background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #E0E0E0, stop: 1 #FFFFFF); }");
	this->layout_1 = new QGridLayout();
	this->layout_2 = new QGridLayout();
    this->checkTimeOp = new QCheckBox(tr("Время "));
    this->checkDate = new QCheckBox(tr("Дата"));
	this->checkDate->setEnabled(0);
    this->checkCountdown = new QCheckBox(tr("Таймер"));

    this->teTimeOp = new QTimeEdit();
    this->teTimeOp->setDisplayFormat("hh:mm:ss");

	this->deDate = new QDateEdit();
    this->deDate->setMinimumDate(QDate::currentDate());
	this->teCountdown = new QTimeEdit();
    this->teCountdown->setMinimumTime(QTime(0,0,10));
    this->teCountdown->setDisplayFormat("hh:mm:ss");
;

    this->label_t1 = new QLabel(tr("Время истечет"));
	this->label_t2 = new QLabel();
	this->setLayout(this->layout_1);
	this->layout_1->addWidget(groupbox);
	this->groupbox->setLayout(layout_2);
	this->layout_2->addWidget(checkTimeOp,1,1);
	this->layout_2->addWidget(teTimeOp,1,2);
	this->layout_2->addWidget(checkDate,2,1);
	this->layout_2->addWidget(deDate,2,2);
	this->layout_2->addWidget(checkCountdown,3,1);
	this->layout_2->addWidget(teCountdown,3,2);

	this->layout_2->addWidget(label_t1,4,1);
	this->layout_2->addWidget(label_t2,4,2);
	connect(checkTimeOp,&QCheckBox::stateChanged,this,&WidgetTimerList::slotCheckTimeOp);
	connect(checkDate,&QCheckBox::stateChanged,this,&WidgetTimerList::slotCheckDate);
	connect(checkCountdown ,&QCheckBox::stateChanged,this,&WidgetTimerList::slotCheckCountdown);
	connect(teCountdown,&QTimeEdit::timeChanged,this,&WidgetTimerList::slotTimeChanged);
}
void WidgetTimerList::slotCheckTimeOp(int state )
{
	switch(state)
	{
	case Qt::Checked:
		{
			this->checkDate->setEnabled(1);
			this->deDate->setEnabled(1);
            this->timer_1->start(500);
		}
		break;
	case Qt::Unchecked:
		{		
			this->timer_1->stop();
			this->checkDate->setEnabled(0);
			this->deDate->setEnabled(0);
		}
		break;

	}
}
void WidgetTimerList::slotCheckDate(int )
{
}
void WidgetTimerList::slotCheckCountdown(int state)
{
	switch(state)
	{
	case Qt::Checked:
		{
            this->timer_2->start(1000);
			this->count_countdown =  (teCountdown->time().hour()*3600)+(teCountdown->time().minute()*60)+teCountdown->time().second();

		}
		break;
	case Qt::Unchecked:
		{		
			this->timer_2->stop();
			this->label_t2->setText("");
		}
		break;

	}

}
void WidgetTimerList::slotTOTimer_two()
{
    if(count_countdown<=0)
	{
		emit execTimer("countdown","countdown",0);
		this->timer_2->stop();
		this->checkCountdown->setChecked(0);
        this->label_t2->setText("Сейчас");
		return;
	}
	else
	{
		count_countdown--;
        QTime tmp_time(count_countdown/3600,(count_countdown/60)%24,count_countdown%60);
        this->label_t2->setText(tmp_time.toString("hh:mm:ss"));

	}

}
void WidgetTimerList::slotTOTimer_one()
{
	if(checkDate->isChecked())
	{
		QDateTime date(deDate->date(),teTimeOp->time())  ;
		if(equalDateTime(QDateTime::currentDateTime(),date ))
		{
			this->checkTimeOp->setChecked(0);
			emit execTimer("countdown","countdown",0);

			return;
		}

	}
	else
	{
		if(equalTime(QTime::currentTime(),this->teTimeOp->time()))
		{
			

			this->checkTimeOp->setChecked(0);
			emit execTimer("countdown","countdown",0);

			return;
		}

	}

}
void WidgetTimerList::slotTimeChanged(QTime time)
{
	this->count_countdown =  (time.hour()*3600)+(time.minute()*60)+time.second();
}
