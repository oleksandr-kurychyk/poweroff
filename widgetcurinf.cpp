#include "widgetcurinf.h"

WidgetCurInf::WidgetCurInf(QWidget *parent)
	: QWidget(parent)
{
	
	InitUI();


	this->timer = new QTimer(this);
	timer->start(1000);
	connect(timer,&QTimer::timeout,this,&WidgetCurInf::slotTimerEvent);

}

WidgetCurInf::~WidgetCurInf()
{

}
void WidgetCurInf::InitUI()
{
	this->layout_1 = new QGridLayout();
	this->setLayout(layout_1);
    this->groupInf = new QGroupBox(tr("Информация"));
    groupInf->setStyleSheet( "QGroupBox { background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,stop: 0 #E0E0E0, stop: 1 #FFFFFF);"
                             "border: 2px solid gray;border-radius: 5px;margin-top: 1ex;}   "
                         "QGroupBox::title {subcontrol-origin: margin;subcontrol-position: top left; padding: 0 3px;"
                             "background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #E0E0E0, stop: 1 #FFFFFF); }");

	this->layout_1->addWidget(groupInf);
	this->layout_2 = new QGridLayout();
	this->groupInf->setLayout(layout_2);
	///create label
    this->labelCurentTime = new QLabel(tr("Время"));
	this->labelCurentTimeData = new QLabel();
    this->labelCurentDate = new QLabel(tr("Дата"));
	this->labelCurentDateData = new QLabel();
    this->labelCurentDay = new QLabel(tr("Деннь"));
	this->labelCurentDayData = new QLabel();
    this->labelTimer = new QLabel(tr("  "));
	this->labelTimerData = new QLabel();
    this->labelUser = new QLabel(tr("Пользователь"));
	this->labelUserData = new QLabel(QString("null"));
	
	//////////////////////////
	this->line = new QFrame();
	this->line->setFrameShape(QFrame::HLine);
    this->line->setFrameShadow(QFrame::Sunken);
	///////////////////////////////
	this->layout_2->addWidget(labelCurentTime,1,1);
	this->layout_2->addWidget(labelCurentTimeData,1,2);
	this->layout_2->addWidget(labelCurentDate,2,1);
	this->layout_2->addWidget(labelCurentDateData,2,2);
	this->layout_2->addWidget(labelCurentDay,3,1);
	this->layout_2->addWidget(labelCurentDayData,3,2);
	this->layout_2->addWidget(labelUser,4,1);
	this->layout_2->addWidget(labelUserData,4,2);
	this->layout_2->addWidget(line,5,1,1,2);
	this->layout_2->addWidget(labelTimer,6,1);
	this->layout_2->addWidget(labelTimerData,6,2);
	///////////////////////////////////////

	

	
	this->labelUserData->setText(QString(getenv("USERNAME")));
	

	
#if defined(Q_WS_WIN)
#elif defined(Q_OS_LINUX)



#else
#endif




};
void WidgetCurInf::slotTimerEvent()
{
	labelCurentTimeData->setText(QTime::currentTime().toString("hh:mm:ss"));
	labelCurentDateData->setText(QDate::currentDate().toString("d MMMM"));
	labelCurentDayData->setText(QDate::currentDate().toString("dddd"));


}
