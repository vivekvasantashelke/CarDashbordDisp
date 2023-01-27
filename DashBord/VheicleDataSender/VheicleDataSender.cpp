#include "VheicleDataSender.h"
static int speed=-50;
static int RPM=-50;
static int PETROL=250;
static int Digitalspeed;
static int totalETs;
static int totalETm;
static int totalETh;
int z=-50,k=0,par=0,ri=0,li=0,ab=0,d=0;
VheicleDataSender::VheicleDataSender(QObject *parent) :QObject(parent)
  ,m_check("345")
{

    forDialmain->start(30);
    connect(forDialmain,&QTimer::timeout,this,&VheicleDataSender::notifyDialsugnal);
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

    RPM=RPM+1;
QString s=QString::number(RPM);
if(PETROL<=110)
{

     RPM=RPM-1;
    QString r=QString::number(RPM);
    emit rpm(QVariant(r));

     if(RPM==-50)
      speedRMP->stop();

}
else if(RPM>=235|RPM==-50)
{
     qDebug()<<"stoped rpm";
     speedRMP->stop();
}
else
    emit rpm(QVariant(s));
}

void VheicleDataSender::notifyPetrol()
{

    PETROL=PETROL-1;
    QString s=QString::number(PETROL);

    if(PETROL==100|PETROL<110)
    {
       // ab=1;
        qDebug()<<ab;
        speedTime->start(50);
       speedRMP->start(50);
        SpeedDigital->start(50);
          speedPetrol->start(30);
              Digitalspeed=Digitalspeed-1;
              RPM=RPM-1;
              speed=speed-1;
               QString sp=QString::number(speed);
             QString r=QString::number(RPM);
        QString s=QString::number(Digitalspeed);
        emit send(QVariant(sp));
         emit speedDigitalmeter(QVariant(s));
        emit rpm(QVariant(r));

        if(speed==-50)
              speedTime->stop();
         if(RPM==-50)
          speedRMP->stop();
        if(Digitalspeed<=0)
        speedPetrol->stop();

    }

   else
        emit petrolSend(QVariant(s));

}

void VheicleDataSender::notifyDigitalMeter()
{
Digitalspeed=Digitalspeed+1;
QString h="285";
QString s=QString::number(Digitalspeed);
if(PETROL<=109)
{
    //  qDebug()<<"petrol dital";
    Digitalspeed=Digitalspeed-1;
    QString s=QString::number(Digitalspeed);
     emit speedDigitalmeter(QVariant(s));
 if(Digitalspeed<=0)
    SpeedDigital->stop();
}
else if(Digitalspeed>284){
  emit speedDigitalmeter(QVariant(h));
    qDebug()<<" dital stopespped";
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

void VheicleDataSender::notifyDialsugnal()
{
    if(d==100)
    {
        forDialmain->stop();
    }
    else
    {
    emit forrunDialsignal(int (d++));
    //qDebug()<<d;
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
   speedPetrol->start(200);
   SpeedDigital->start(500);
   TotalETime->start(1000);
}

void VheicleDataSender::absstoppedcar()
{
    qDebug()<<"called";

//    disconnect(speedTime,&QTimer::timeout,this,&VheicleDataSender::NotifySignalSpeedslots);
//    disconnect(speedRMP,&QTimer::timeout,this,&VheicleDataSender::notifyrpm);
//    disconnect(speedPetrol,&QTimer::timeout,this,&VheicleDataSender::notifyPetrol);
//    disconnect(SpeedDigital,&QTimer::timeout,this,&VheicleDataSender::notifyDigitalMeter);
//     speed=-50;
//       Digitalspeed=0;
//        RPM=-50;



    if(ab==0)
    {
       ab=1;
       // qDebug()<<ab;
                     QString sp=QString::number(-50);
             QString r=QString::number(-50);
        QString s=QString::number(0);
        emit send(QVariant(sp));
         emit speedDigitalmeter(QVariant(s));
        emit rpm(QVariant(r));

        speedRMP->stop();
        speedPetrol->stop();
         SpeedDigital->stop();
          speedTime->stop();

    }





}

void VheicleDataSender::setpar()
{
    par=0;
}

void VheicleDataSender::fillpetroll()
{
PETROL=250;
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
