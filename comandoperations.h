#ifndef COMANDOPERATIONS_H
#define COMANDOPERATIONS_H
#include <QtCore>








class ComandOperations
{
private:
  ComandOperations();
~ComandOperations();
  QSettings *settings;
  static ComandOperations * instance ;
public:
static ComandOperations * getInstance();
void execComandSD();
void execComandRB();
void execComandHib();
void execComandSb();
void execComandLO();
void execComandLock();
void execComandNM();
void execComandRPO();


void setComandSD(QString str);
void setComandRB(QString str);
void setComandHib(QString str);
void setComandSb(QString str);
void setComandLO(QString str);
void setComandLock(QString str);
void setComandNM(QString str);
void setComandRPO(QString str);


/////////////////////////////
QString getComandSD();
QString getComandRB();
QString getComandHib();
QString getComandSb();
QString getComandLO();
QString getComandLock();
QString getComandNM();
QString getComandRPO();

};


#endif // COMANDOPERATIONS_H
