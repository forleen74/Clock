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
    void drawBase(QPainter &paint); // ����� ��������� ����������
    void drawHours(QPainter &paint, double alpha); // ����� ��������� ������� �������
    void drawMinutes(QPainter &paint, double alpha); // ... �������� �������
    void drawSeconds(QPainter &paint, double alpha); // .. ��������� �������
    void drawCenter(QPainter &paint); // ��������� ����� � ������
    void clear(QPainter &paint); // ����� ������� ������
    void initTime(); // ����� ������������� ������� � ����� ���������� �������
    void recountTime(); // ����� ��������� �������
    QPair<double, double> getPoint(double nowX, double nowY, double alpha);
    ~Clock();
    
private:
    Ui::Clock *ui;
    int seconds,minutes,hours;
    int Ox,Oy; // ���������� ������
    double upX,upY; // ���������� �����
    double alphaSec,alphaMin,alphaHours; // ���� ���������� �������
    bool first;
public slots:
 void OnTimer();

};

#endif // CLOCK_H
