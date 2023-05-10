#ifndef CLOCK_H
#define CLOCK_H

#include <QWidget>

namespace Ui {
class Clock;
}

class Clock : public QWidget
{
    Q_OBJECT
    
public:
    explicit Clock(QWidget *parent = 0);
    void paintEvent(QPaintEvent * );
    void drawBase(QPainter &paint); // метод отрисовки циферблата
    void drawHours(QPainter &paint, double alpha); // метод отрисовки часовой стрелки
    void drawMinutes(QPainter &paint, double alpha); // ... минутной стрелки
    void drawSeconds(QPainter &paint, double alpha); // .. секундной стрелки
    void drawCenter(QPainter &paint); // отрисовка точки в центре
    void clear(QPainter &paint); // метод очистки экрана
    void initTime(); // метод инициализации времени и углов отклонения стрелок
    void recountTime(); // метод пересчета вермени
    QPair<double, double> getPoint(double nowX, double nowY, double alpha);
    ~Clock();
    
private:
    Ui::Clock *ui;
    int seconds,minutes,hours;
    int Ox,Oy; // координаты центра
    double upX,upY; // координаты верха
    double alphaSec,alphaMin,alphaHours; // углы отклонения стрелок
    bool first;
public slots:
 void OnTimer();

};

#endif // CLOCK_H
