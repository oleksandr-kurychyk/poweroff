#ifndef NET_FUNC_H
#define NET_FUNC_H
#include<QtCore>



#include <stdio.h>
#include <string.h>
#include <unistd.h>
#if defined(Q_WS_WIN)


#elif defined(Q_OS_LINUX)
#include <sys/ioctl.h>
#include <net/if.h>
#include <arpa/inet.h>
#else

#endif

namespace PO {
enum Flag {All,Active };
};
QStringList getNetInterfaces( PO::Flag=PO::All )
{
    QStringList list;
#if defined(Q_WS_WIN)


#elif defined(Q_OS_LINUX)
    QStringList tmp_list;
    QFile file ("/proc/net/dev");
    if(!file.open(QIODevice::ReadOnly))
        return list;
    QTextStream in(&file);
    in.readLine();
    in.readLine();

    while(!in.atEnd())
    {
        QString str;
        in>> str;

        list<<str.left(str.size()-1);

        in.readLine();

    }
    file.close();






#else

#endif
    return list;
}
int getReceiveInf(QString name)
{
#if defined(Q_WS_WIN)
#elif defined(Q_OS_LINUX)
   int value = -1;
   QFile file ("/proc/net/dev");
    if(!file.open(QIODevice::ReadOnly))
        return value;
    QTextStream in(&file);
    QString tmp;

    in.readLine();
    in.readLine();

    while(!in.atEnd())
    {
        in>>tmp;
        tmp= tmp.left(tmp.size()-1);
        if(name == tmp)
        {
            in>>value;
             return value;
        }
        in.readLine();

    }

    return value;

#else
#endif
}
QString getNetInterfaceIP(QString name)
{
#if defined(Q_WS_WIN)


#elif defined(Q_OS_LINUX)
    struct ifreq ifr;
    memset(&ifr, 0, sizeof(ifr));
    QByteArray arr_name = name.toLocal8Bit();
    strcpy(ifr.ifr_name, arr_name.data());
    int s = socket(AF_INET, SOCK_DGRAM, 0);
    ioctl(s, SIOCGIFADDR, &ifr);
    close(s);
    struct sockaddr_in *sa = (struct sockaddr_in*)&ifr.ifr_addr;
     return  inet_ntoa(sa->sin_addr);
#else
#endif

     return QString();
}
QString getNetInterfaceMAC(QString name)
{
    QString ret_value;

#if defined(Q_WS_WIN)


#elif defined(Q_OS_LINUX)
    int s;
     ifreq buffer;
    s = socket(PF_INET, SOCK_DGRAM, 0);
    memset(&buffer, 0x00, sizeof(buffer));
    QByteArray arr_name = name.toLocal8Bit();
    strcpy(buffer.ifr_name, arr_name.data());
    ioctl(s, SIOCGIFHWADDR, &buffer);
    close(s);
    for( s = 0; s < 6; s++ )
    {
        QString tmp;
        if(((unsigned char)buffer.ifr_hwaddr.sa_data[s])<15)
        {
            tmp+='0';
        }
       tmp +=QString("%0").arg((unsigned char) buffer.ifr_hwaddr.sa_data[s],0,16);
        ret_value+=tmp;
        if(s<5)
        {
            ret_value+=':';
        }
}

#else
#endif

    return ret_value;

}
int getTransmitInf(QString name)
{
#if defined(Q_WS_WIN)
#elif defined(Q_OS_LINUX)
    int value = -1;
    QFile file ("/proc/net/dev");
     if(!file.open(QIODevice::ReadOnly))
         return value;
     QTextStream in(&file);
     QString tmp,tmp1;

     in.readLine();
     in.readLine();

     while(!in.atEnd())
     {
         in>>tmp;
         tmp= tmp.left(tmp.size()-1);
         if(name == tmp)
         {
            tmp1 = in.readLine();
            QStringList list =  tmp1.split(QRegExp("\\s+"),QString::SkipEmptyParts);
            if(list.size()>9)
            {
              value = list[8].toInt();
              return value;
            }

         }
         in.readLine();

     }

     return value;

#else
#endif

}



#endif // NET_FUNC_H
