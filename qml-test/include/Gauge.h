#ifndef __GAUGE_H__
#define __GAUGE_H__
#ifdef QT5
    #include <QQuickPaintedItem>
    typedef QQuickPaintedItem QDeclarativeItem;
#else
    #include <QDeclarativeItem>
#endif

#include <QPainter>
#include <QWidget>
#include <QColor>
#include <QStyleOptionGraphicsItem>

class Gauge : public QDeclarativeItem {
    Q_OBJECT
    Q_PROPERTY(double value READ value)
public:
    Gauge(QDeclarativeItem *parent = 0);
    double value() const;
    void paint(QPainter *painter);
public slots:
    void updateValue(const double &v);
signals:
    void valueChanged();
private:
    QColor largeColor;
    QColor mediumColor;
    QColor smallColor;
    double smallThreshold;
    double mediumThreshold;
    double _value;
};
#endif
