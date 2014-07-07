#include "comandoperations.h"

  ComandOperations::ComandOperations()
  {
       settings  = new QSettings("Kurylchyk Oleksandr","PowerOff",0);
  }
ComandOperations::~ComandOperations(){delete settings;}


 ComandOperations* ComandOperations::getInstance()
{
    if(instance == 0)
    {
        instance = new ComandOperations();

    }
    return instance;

}
void  ComandOperations::execComandSD()
{
   QProcess::startDetached(settings->value("/comands/ShutDown").toString());
}
void  ComandOperations::execComandRB()
{
     QProcess::startDetached(settings->value("/comands/Reboot").toString() );
}
void  ComandOperations::execComandHib()
{
     QProcess::startDetached(settings->value("/comands/Hibernate").toString() );
}
void  ComandOperations::execComandSb()
{
     QProcess::startDetached(settings->value("/comands/Standby").toString() );
}
void  ComandOperations::execComandLO()
{
     QProcess::startDetached(settings->value("/comands/Logout").toString() );
}
void  ComandOperations::execComandLock()
{
     QProcess::startDetached(settings->value("/comands/Lock").toString());
}
void  ComandOperations::execComandNM()
{
     QProcess::startDetached(settings->value("/comands/Network_Message").toString() );
}
void  ComandOperations::execComandRPO()
{
     QProcess::startDetached(settings->value("/comands/Remote_PO").toString() );
}


void  ComandOperations::setComandSD(QString str)
{
    settings->setValue("/comands/ShutDown",str);

}
void  ComandOperations::setComandRB(QString str)
{
    settings->setValue("/comands/Reboot",str);
}
void  ComandOperations::setComandHib(QString str)
{
    settings->setValue("/comands/Hibernate",str);

}
void  ComandOperations::setComandSb(QString str)
{
    settings->setValue("/comands/Standby",str);

}
void  ComandOperations::setComandLO(QString str)
{
    settings->setValue("/comands/Logout",str);

}
void  ComandOperations::setComandLock(QString str)
{
    settings->setValue("/comands/Lock",str);

}
void  ComandOperations::setComandNM(QString str)
{
    settings->setValue("/comands/Network_Message",str);

}
void  ComandOperations::setComandRPO(QString str)
{
    settings->setValue("/comands/Remote_PO",str);

}


QString  ComandOperations::getComandSD()
{
   return settings->value("/comands/ShutDown").toString();

}
QString  ComandOperations::getComandRB()
{
   return settings->value("/comands/Reboot").toString();
}
QString  ComandOperations::getComandHib()
{
   return settings->value("/comands/Hibernate").toString();

}
QString  ComandOperations::getComandSb()
{
   return settings->value("/comands/Standby").toString();

}
QString  ComandOperations::getComandLO()
{
  return  settings->value("/comands/Logout").toString();

}
QString  ComandOperations::getComandLock()
{
  return  settings->value("/comands/Lock").toString();

}
QString  ComandOperations::getComandNM()
{
   return settings->value("/comands/Network_Message").toString();

}
QString  ComandOperations::getComandRPO()
{
  return  settings->value("/comands/Remote_PO").toString();

}



ComandOperations * ComandOperations::instance = 0;
