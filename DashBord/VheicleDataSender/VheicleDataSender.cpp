#include "VheicleDataSender.h"
static int speed=-50;
static int RPM=-50;
static int PETROL=250;
static int Digitalspeed;
static int totalETs;
static int totalETm;
static int totalETh;
int z=-50,k=0,par=0,ri=0,li=0;
VheicleDataSender::VheicleDataSender(QObject *parent) :QObject(parent)
  ,m_check("345")
{
   //speedTime->setInterval(50);
// speedTime->start(500);
//speedRMP->start(500);
//speedPetrol->start(2000);
//SpeedDigital->start(500);
//TotalETime->start(1000);

  // connect(speedTime,SIGNAL(timeout()),this,SLOT(NotifySignalSpeedslots()));
  connect(speedTime,&QTimer::timeout,this,&VheicleDataSender::NotifySignalSpeedslots);
   connect(speedRMP,&QTimer::timeout,this,&VheicleDataSender::notifyrpm);
   connect(speedPetrol,&QTimer::timeout,this,&VheicleDataSender::notifyPetrol);
   connect(SpeedDigital,&QTimer::timeout,this,&VheicleDataSender::notifyDigitalMeter);
connect(TotalETime,&QTimer::timeout,this,&VheicleDataSender::notifyTotalEnginTime);
connect(emptytimer,&QTimer::timeout,this,&VheicleDataSender::notifyemptypetrooltank);
connect(Parkingtimer,&QTimer::timeout,this,&VheicleDataSender::notifyParkingsignal);

connect(rightindicatortimer,&QTimer::timeout,this,&VheicleDataSender::notifyindicatorsignal);

connect(letRightind,&QTimer::timeout,this,&VheicleDataSender::notifyletRightIndicatorsignal);
connect(letLeftIND,&QTimer::timeout,this,&VheicleDataSender::notifyltLeftINdicatorsignal);

}

void VheicleDataSender::NotifySignalSpeedslots()
{
    QString p=QString::number(z);
    speed=speed+1;
    QString s=QString::number(speed);
if(PETROL<110)
{
     speed=speed-1;
      QString s=QString::number(speed);
     emit send(QVariant(s));
    speedTime->stop();
}
else if(speed>=235)
{
    speedTime->stop();
}
else
    emit send(QVariant(s));
  //  qDebug()<<"calls";
}

void VheicleDataSender::notifyrpm()
{
  //  qDebug()<<"called rpm";
    RPM=RPM+1;
    QString s=QString::number(RPM);
if(PETROL<110)
{
     RPM=RPM-1;
   // QString p=QString::number(z);
  //  QString s=QString::number(RPM);
     // QString s=QString::number(speed);
     emit rpm(QVariant(s));

}
else if(RPM>=235)
{
     speedRMP->stop();
}
else
    emit rpm(QVariant(s));
}

void VheicleDataSender::notifyPetrol()
{
   // qDebug()<<"petrol";
    PETROL=PETROL-0.5;
    QString s=QString::number(PETROL);

//qDebug()<<"petrol->"<<PETROL;
    if(PETROL==0|PETROL<110)
    {
        speedPetrol->stop();

    }
    else
     emit petrolSend(QVariant(s));

}

void VheicleDataSender::notifyDigitalMeter()
{
Digitalspeed=Digitalspeed+1;
QString h="285";
//QString l="0";
QString s=QString::number(Digitalspeed);
if(PETROL<=110)
{
    Digitalspeed=Digitalspeed-1;
    QString s=QString::number(Digitalspeed);
  //  QString p=QString::number(k);
    emit speedDigitalmeter(QVariant(s));

    SpeedDigital->stop();
}
else if(Digitalspeed>284){
  emit speedDigitalmeter(QVariant(h));
SpeedDigital->stop();
}
    else
    emit speedDigitalmeter(QVariant(s));
}

void VheicleDataSender::notifyTotalEnginTime()
{
    if(totalETs==60)
    {
        totalETm++;
        if(totalETm==60)
        {
            totalETh++;
            totalETm=0;
        }
        if(totalETh==12)
        {
            totalETh=0;
        }
        totalETs=0;
    }
    else
        totalETs++;

    QString s=QString::number(totalETs);
    emit totalEnginTime(QVariant(s));

}

void VheicleDataSender::notifyemptypetrooltank()
{
    if(PETROL<=110)
    {
        RPM=RPM-1;
     QString s=QString::number(RPM);
         emit emptypetrolatank(QVariant(s));
    }
if(RPM<=-50)
{
    emptytimer->stop();
}
}

void VheicleDataSender::notifyParkingsignal()
{

    if(par<50)
    {
          //QString s=QString::number(par);
    emit parkingsignal(QVariant("2"));
          par++;
    }
    else if(par>50)
    {
         Parkingtimer->stop();
       // emit parkingsignal(QVariant("1"));
    par=0;

    }
    else if(par>50)
    {
          Parkingtimer->stop();
          par=0;
    }
}

void VheicleDataSender::notifyindicatorsignal()
{
emit indicatorsignal(int(par));

    if(par>50)
    {
        Parkingtimer->stop();
        rightindicatortimer->stop();
        emptytimer->stop();
    }
}

void VheicleDataSender::notifyletRightIndicatorsignal()
{
    emit letRightIndicatorsignal(int (ri));
    ri++;
    if(ri>50)
    {
        letRightind->stop();
    }
}

void VheicleDataSender::notifyltLeftINdicatorsignal()
{
    emit ltLeftINdicatorsignal(int(li));
    li++;
    if(li>50)
    {
        letLeftIND->stop();
    }
}

void VheicleDataSender::starttimer()
{
    qDebug()<<"caleed";
rightindicatortimer->start(500);
    Parkingtimer->start(500);

}

void VheicleDataSender::startRigtindicator()
{
 rightindicatortimer->start(500);
 //emptytimer->start(500);
}

void VheicleDataSender::letstartRightindicator()
{
    letRightind->start(500);

}

void VheicleDataSender::letstoprigtindicator()
{
    ri=0;
}

void VheicleDataSender::letstratLeftindicator()
{
    letLeftIND->start(500);
}

void VheicleDataSender::letStopLeftindicator()
{
    li=0;
}

void VheicleDataSender::mainclikedbuttonTIMERSSTARTING()
{
    speedTime->start(500);
   speedRMP->start(500);
   speedPetrol->start(2000);
   SpeedDigital->start(500);
   TotalETime->start(1000);
}

void VheicleDataSender::setpar()
{
    par=0;
}
QString VheicleDataSender::check() const
{
    return m_check;
}

void VheicleDataSender::setcheck(const QString &newCheck)
{
    if (m_check == newCheck)
        return;
    m_check = newCheck;
    emit checkChanged();
}
