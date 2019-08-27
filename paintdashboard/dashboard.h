#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <QWidget>
#include <QPainter>
#include <QTimer>

class DashBoard : public QWidget
{
    Q_OBJECT

public:
    DashBoard(QWidget *parent = 0);
    ~DashBoard();

protected:
    void paintEvent(QPaintEvent *);

    void drawCrown(QPainter *painter); // 画表盘边框
//    void drawBackground(QPainter *painter);
    void drawScaleNum(QPainter *painter); //画刻度数值
    void drawScale(QPainter *painter); // 画刻度线
    void drawTitle(QPainter *painter);  //绘制标题
    void drawIndicator(QPainter *painter);  //画表针
    void drawNumericValue(QPainter *painter);  //画单位，与数值

public slots:
    void updateAngle();

private:
    QColor m_background;
    QColor m_foreground;

    int m_maxValue; //刻度最大值
    int m_minValue; //刻度最小值
    int m_startAngle;
    int m_endAngle;

    int m_scaleMajor;   //大刻度数
    int m_scaleMinor;   //大刻度分成小刻度数
    double m_value;
    int m_precision;
    QTimer *m_updateTimer;
    QString m_units;
    QString m_title;
};

#endif // DASHBOARD_H
