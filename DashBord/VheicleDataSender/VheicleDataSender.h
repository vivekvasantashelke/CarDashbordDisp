
//#ifndef VHEICLEDATASENDER_H
//#define VHEICLEDATASENDER_H
#pragma once
#include <QObject>
#include <QTimer>
#include <QVariant>
#include <QDebug>

class VheicleDataSender:public QObject
{
Q_OBJECT
    Q_PROPERTY(QString check READ check WRITE setCheck NOTIFY checkChanged)
public:

    explicit VheicleDataSender(QObject *parent = nullptr);


    QString check() const;
    void setcheck(const QString &newCheck);

signals:
    void send(QVariant data);

   void rpm(QVariant data2);

   void checkChanged();

   void petrolSend(QVariant Data3);
   void speedDigitalmeter(QVariant DigitalData);
   void totalEnginTime(QVariant enginTime);

   void emptypetrolatank(QVariant emptytankthen);

   void parkingsignal(QVariant park);
   void indicatorsignal(int ind);

    void letRightIndicatorsignal(int rightind);

    void ltLeftINdicatorsignal(int leftind);

private slots:

    void NotifySignalSpeedslots();
    void notifyrpm();
    void notifyPetrol();
    void notifyDigitalMeter();
    void notifyTotalEnginTime();

    void notifyemptypetrooltank();
    void notifyParkingsignal();

    void notifyindicatorsignal();
  void notifyletRightIndicatorsignal();

  void notifyltLeftINdicatorsignal();

public slots:
    void stopedtimer();

    void starttimer();
    void startRigtindicator();

    void letstartRightindicator();
    void letstoprigtindicator();

void letstratLeftindicator();
 void letStopLeftindicator();

 void mainclikedbuttonTIMERSSTARTING();

 void setpar();


private :
    QTimer *speedTime=new QTimer(this);
     QTimer *speedRMP=new QTimer(this);
      QTimer *speedPetrol=new QTimer(this);
      QTimer *SpeedDigital=new QTimer(this);
      QTimer *TotalETime=new QTimer(this);
      QTimer *emptytimer=new QTimer(this);
      QTimer *Parkingtimer=new QTimer(this);

      QTimer *rightindicatortimer=new QTimer(this);

    QTimer *letRightind=new QTimer(this);
    QTimer *letLeftIND=new QTimer(this);

    QString m_check;
};






//#endif
