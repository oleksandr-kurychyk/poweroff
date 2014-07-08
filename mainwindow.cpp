#include "mainwindow.h"
#include "comandsdialog.h"


MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	
    main_menu = this->menuBar();
    this->file_menu = new QMenu(tr("Файл"));
    this->about_menu = new QMenu(tr("Про"));
    main_menu->addMenu(file_menu);
    main_menu->addMenu(about_menu);
    this->action_comands = new QAction("Команди",this);
    this->action_exit = new QAction("Виход",this);
    this->action_about = new QAction("Про",this);
    file_menu->addAction(action_comands);
     file_menu->addAction(action_exit);
    about_menu->addAction(action_about);
    tray_icon  = new QSystemTrayIcon(QIcon(":/tray_icon.png"),this);
    action_show_hide =new QAction("Свернуть",this);
    tray_menu = new QMenu("Меню");
    tray_menu->addAction(action_show_hide);
    tray_menu->addAction(action_exit);

    tray_icon->setContextMenu(tray_menu);
    tray_icon->show();
    connect(action_comands,&QAction::triggered,this,&MainWindow::on_action_comands);
    connect(action_exit,&QAction::triggered,this,&MainWindow::on_action_exit);
    connect(action_about,&QAction::triggered,this,&MainWindow::on_action_about);
    connect(action_show_hide,&QAction::triggered,this,&MainWindow::on_action_show_hide);






	this->root = new QWidget(this);
	this->setCentralWidget(root);
    this->layout = new QGridLayout();
	this->layout->setContentsMargins(1,1,1,1);
	this->layout->setVerticalSpacing(1);
	root->setLayout(layout);
	this->cur_inf = new WidgetCurInf(this);
	this->layout->addWidget(cur_inf,1,1);
	this->power_exec = new WidgetPowerExec(this);
	this->layout->addWidget(power_exec,2,1);
    this->timer_list = new WidgetTimerList(this);
    this->layout->addWidget(timer_list,3,1);
	this->timer_cpu = new WidgetTimerCpu();
	this->layout->addWidget(timer_cpu,1,2);
    this->net_timer = new WidgetNetworkTimer(this);
    this->layout->addWidget(net_timer,2,2,2,1);


    connect(timer_cpu,&WidgetTimerCpu::execTimer,power_exec,&WidgetPowerExec::ExecTimer);
    connect(timer_list,&WidgetTimerList::execTimer,power_exec,&WidgetPowerExec::ExecTimer);
    connect(net_timer,&WidgetNetworkTimer::execTimer,power_exec,&WidgetPowerExec::ExecTimer);





}

MainWindow::~MainWindow()
{

}
void MainWindow::on_action_comands()
{
ComandsDialog Dlg;Dlg.exec();
}
void MainWindow::on_action_exit()
{
    qApp->exit();

}
void MainWindow::on_action_about()
{

   QMessageBox::about(this,"PowerOff","Програму создал Курильчик Олександр\nemail:oleksandr.kurylchyk@gmail.com  ");
}
 void MainWindow::on_action_show_hide()
 {
     if(this->isVisible()==false)
     {
         action_show_hide->setText("Свернуть");
         this->setVisible(1);
     }
     else
     {
         action_show_hide->setText("Развернуть");
         this->setVisible(0);

     }

 }
  void MainWindow::closeEvent(QCloseEvent * ev)
  {
      ev->ignore();
      action_show_hide->setText("Развернуть");
      this->setVisible(0);

  }
