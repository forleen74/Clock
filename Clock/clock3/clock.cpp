#include "clock.h"
#include "ui_clock.h"
#include "stdio.h"
#include <QTime>
#include <QTimer>
#include <QPainter>
#include <QPair>
#include "math.h"

Clock::Clock(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Clock)
{
    ui->setupUi(this);
    resize(300,300);
    Ox=150; Oy=150;
    upX=150; upY=5;
    first=true;
    initTime();
    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL (timeout()),this, SLOT(OnTimer()));
    timer->start(1000);
}
void Clock::initTime()
{

 QTime time=QTime::currentTime();
 seconds=time.second();
 minutes=time.minute();
 hours=time.hour();
 alphaSec=6.0*seconds;
 alphaMin=6.0*minutes;
 alphaHours=30.0*hours+minutes*0.5+0.025*seconds/3;
}
void Clock::recountTime()
{

 seconds++;
 minutes += (seconds/60);
 seconds %= 60;
 hours += (minutes/60);
 minutes %= 60;
 alphaSec += 6.0;
 if(alphaSec == 360.0)
 alphaSec = 0.0;
 if(first!=true){
 if(seconds%60 == 0) {
 alphaMin += 6.0;
 alphaHours += 0.5;
 }
 if(alphaMin == 360.0)
 alphaMin = 0.0;
 if(alphaHours == 360.0)
 alphaHours = 0.0;
 }
 else
 first = false;
}

Clock::~Clock()
{
    delete ui;
}

void Clock::OnTimer()
{
    recountTime();
     char time[10];
     sprintf(time,"%d:%d:%d",hours,minutes,seconds);
     ui->label->setText(time);
     update();
    }
    QPair<double,double> Clock::getPoint(double nowX, double nowY, double alpha)
    {


     double retX=(nowX-Ox)*cos(alpha*M_PI/180.0)-(nowY-Oy)*sin(alpha*M_PI/180.0)+Ox;
     double retY=(nowY-Oy)*cos(alpha*M_PI/180.0)+(nowX-Ox)*sin(alpha*M_PI/180.0)+Oy;
     if(abs(retX)<1e-9)
     retX=0;
     if(abs(retY)<1e-9)
     retY=0;
     if(retX<0)
     retX=300+retX;
     if(retY<0)
     retY=300+retY;
     return QPair<double,double>(retX,retY);
    }
    void Clock::paintEvent(QPaintEvent *)
    {
     QPainter paint(this);
     clear(paint);
     drawBase(paint);
     drawHours(paint,alphaHours);
     drawMinutes(paint,alphaMin);
     drawSeconds(paint,alphaSec);
     drawCenter(paint);
    }
    void Clock::drawBase(QPainter &paint)
    {

     paint.setPen(QPen(Qt::black,3,Qt::SolidLine));
     paint.setRenderHint(QPainter::Antialiasing, true);
     paint.drawEllipse(5,5,290,290);
     paint.setPen(QPen(Qt::black,3,Qt::SolidLine,Qt::RoundCap));
     double nowUpX=295,nowUpY=150,nowDownX=280,nowDownY=150;
     paint.drawLine(nowUpX,nowUpY,nowDownX,nowDownY);

     nowUpX=150; nowUpY=295; nowDownX=150; nowDownY=280;
     paint.drawLine(nowUpX,nowUpY,nowDownX,nowDownY);
     nowUpX=5; nowUpY=150; nowDownX=20; nowDownY=150;
     paint.drawLine(nowUpX,nowUpY,nowDownX,nowDownY);
     nowUpX=150; nowUpY=5; nowDownX=150; nowDownY=20;
     paint.drawLine(nowUpX,nowUpY,nowDownX,nowDownY);

     nowDownY=12;
     for(int i=1;i<=12;++i){
     QPair<double,double> tmp=getPoint(nowUpX,nowUpY,30.0);
     nowUpX=tmp.first; nowUpY=tmp.second;
     tmp=getPoint(nowDownX,nowDownY,30.0);
      nowDownX=tmp.first; nowDownY=tmp.second;
      if(i==12)
      continue;
      paint.drawLine(nowUpX,nowUpY,nowDownX,nowDownY);
      }

      nowDownY=7;
      for(int i=1;i<=60;++i){
      QPair<double,double> tmp = getPoint(nowUpX,nowUpY,6.0);
      nowUpX = tmp.first; nowUpY = tmp.second;
      tmp = getPoint(nowDownX,nowDownY,6.0);
      nowDownX = tmp.first; nowDownY = tmp.second;
      paint.drawLine(nowUpX,nowUpY,nowDownX,nowDownY);
      }
     }
     void Clock::drawSeconds(QPainter &paint, double alpha)
     {
      // узнаем координаты конца стрелки после отклонения
      QPair<double,double> tmp=getPoint(upX,upY+15,alpha);
      paint.setPen(QPen(Qt::darkBlue,1,Qt::SolidLine));
      paint.setRenderHint(QPainter::Antialiasing, true);
      paint.drawLine(Ox,Oy,tmp.first,tmp.second);
      tmp=getPoint(upX,100+20,alpha+180.0);
      paint.drawLine(Ox,Oy,tmp.first,tmp.second);
     }
     void Clock::drawMinutes(QPainter &paint, double alpha)
     {

      QPair<double,double> tmp=getPoint(upX,upY+15,alpha);
      paint.setPen(QPen(Qt::cyan,2,Qt::SolidLine));
      paint.setRenderHint(QPainter::Antialiasing, true);
      paint.drawLine(Ox,Oy,tmp.first,tmp.second);
     }
     void Clock::drawHours(QPainter &paint, double alpha)
     {

      QPair<double,double> tmp = getPoint(upX,upY+50,alpha);
      paint.setPen(QPen(Qt::blue,2,Qt::SolidLine));
      paint.setRenderHint(QPainter::Antialiasing, true);
      paint.drawLine(Ox,Oy,tmp.first,tmp.second);
     }
     void Clock::drawCenter(QPainter &paint)
     {
      // рисуем точку в центре
      paint.setPen(QPen(Qt::black,6,Qt::SolidLine,Qt::RoundCap));
      paint.setRenderHint(QPainter::Antialiasing, true);
      paint.drawPoint(150,150);
     }
     void Clock::clear(QPainter &paint)
     {

      paint.eraseRect(0,0,300,300);
     }
