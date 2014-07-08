#include "widgetpowerexec.h"
#include "comandoperations.h"


WidgetPowerExec::WidgetPowerExec(QWidget *parent )
{
	InitUI();

}
void WidgetPowerExec::InitUI()
{
	this->hblayout_1 = new QHBoxLayout();
	this->buton_exec = new QPushButton();
	this->buton_exec->setMinimumSize (60,60);
    buton_exec->setIconSize(QSize(50,50));
    this->groupbox_item = new QGroupBox("Команди");
    this->groupbox_item->setStyleSheet( "QGroupBox { background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,stop: 0 #E0E0E0, stop: 1 #FFFFFF);"
                                        "border: 2px solid gray;border-radius: 5px;margin-top: 1ex;}   "
                                    "QGroupBox::title {subcontrol-origin: margin;subcontrol-position: top center; padding: 0 3px;"
                                        "background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #E0E0E0, stop: 1 #FFFFFF); }");
	this->gridlayout_1 = new QGridLayout();
	/////////////
	this->setLayout(hblayout_1); 
	this->hblayout_1->addWidget(this->buton_exec,1);
	this->hblayout_1->addWidget(this->groupbox_item,3);	
	this->groupbox_item->setLayout(gridlayout_1);

	//radiobuttons
	this->radiobutton_shutdown = new QRadioButton(tr("Power Off"));
	this->radiobutton_restart = new QRadioButton(tr("Reboot"));
	this->radiobutton_logout = new QRadioButton(tr("Logout"));
	this->radiobutton_lock = new QRadioButton(tr("Lock"));
	this->radiobutton_hibernation = new QRadioButton(tr("Hibernate"));
	this->radiobutton_standby = new QRadioButton(tr("Standby"));
	this->radiobutton_nm = new QRadioButton(tr("Network message"));
	this->radiobutton_rpo = new QRadioButton(tr("Remote Power Off"));
	//radiobuttons insert into layout
	this->gridlayout_1->addWidget(radiobutton_shutdown ,1,1);		
	this->gridlayout_1->addWidget(radiobutton_restart,2,1);
	this->gridlayout_1->addWidget(radiobutton_hibernation,3,1);
	this->gridlayout_1->addWidget(radiobutton_standby,4,1);
	this->gridlayout_1->addWidget(radiobutton_logout,1,2);
	this->gridlayout_1->addWidget(radiobutton_lock,2,2);
	this->gridlayout_1->addWidget(radiobutton_nm,3,2);
	this->gridlayout_1->addWidget(radiobutton_rpo,4,2);

	//radiobuttons connect slots
	connect( radiobutton_shutdown,&QRadioButton::clicked,this,&WidgetPowerExec::slotRadioSelected);
	connect( radiobutton_restart,&QRadioButton::clicked,this,&WidgetPowerExec::slotRadioSelected);
	connect( radiobutton_hibernation,&QRadioButton::clicked,this,&WidgetPowerExec::slotRadioSelected);
	connect( radiobutton_standby,&QRadioButton::clicked,this,&WidgetPowerExec::slotRadioSelected);
	connect( radiobutton_logout,&QRadioButton::clicked,this,&WidgetPowerExec::slotRadioSelected);
	connect( radiobutton_lock,&QRadioButton::clicked,this,&WidgetPowerExec::slotRadioSelected);
	connect( radiobutton_nm,&QRadioButton::clicked,this,&WidgetPowerExec::slotRadioSelected);
	connect( radiobutton_rpo,&QRadioButton::clicked,this,&WidgetPowerExec::slotRadioSelected);
    connect( buton_exec,&QPushButton::clicked,this,&WidgetPowerExec::slotPushButtonClick);
    radiobutton_shutdown->click();

}
WidgetPowerExec::~WidgetPowerExec()
{
}
void WidgetPowerExec:: ExecTimer(QString msg_1,QString msg_2,int code)
{
    //QMessageBox::information(this,msg_1,msg_1);
	if(this->radiobutton_shutdown->isChecked())
	{
       ComandOperations::getInstance()->execComandSD();
	}
    else if(this->radiobutton_restart->isChecked())
	{
        ComandOperations::getInstance()->execComandRB();
	}
	else if(this->radiobutton_hibernation->isChecked())
	{
        ComandOperations::getInstance()->execComandHib();
	}
	else if(this->radiobutton_standby->isChecked())
	{
        ComandOperations::getInstance()->execComandSb();
	}
	else if(this->radiobutton_logout->isChecked())
	{
        ComandOperations::getInstance()->execComandLO();
	}
	else if(this->radiobutton_lock->isChecked())
	{
        ComandOperations::getInstance()->execComandLock();
	}
	else if(this->radiobutton_nm->isChecked())
	{
        ComandOperations::getInstance()->execComandNM();
	}
	else if(this->radiobutton_rpo->isChecked())
	{
        ComandOperations::getInstance()->execComandRPO();
	}
}
void WidgetPowerExec:: slotRadioSelected()
{

	QRadioButton * p_sender = 	(QRadioButton * )sender();

	if(p_sender==radiobutton_shutdown)
	{
        buton_exec->setIcon(QIcon(":/shutdown.png"));
	}
	else if(p_sender==radiobutton_restart)
	{
         buton_exec->setIcon(QIcon(":/restart.png"));
    }
	else if(p_sender==radiobutton_hibernation  )
	{
         buton_exec->setIcon(QIcon(":/hibernate.png"));
	}
	else if(p_sender==radiobutton_standby)
	{
         buton_exec->setIcon(QIcon(":/standby.png"));
	}
	else if(p_sender==radiobutton_logout)
	{
         buton_exec->setIcon(QIcon(":/logout.png"));
	}
	else if(p_sender==radiobutton_lock)
	{
         buton_exec->setIcon(QIcon(":/lock.png"));
	}
	else if(p_sender==radiobutton_nm)
	{
         buton_exec->setIcon(QIcon(":/network_message.png"));
	}
	else if(p_sender==radiobutton_rpo)
	{
         buton_exec->setIcon(QIcon(":/remote_po.png"));
	}
}

  void WidgetPowerExec::slotPushButtonClick()
  {
      ExecTimer("Кнопка","Немедленое виключение",0);


  }

