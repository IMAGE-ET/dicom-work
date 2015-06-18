#include "Gauge.h"
#include <QColor>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QWidget>
#include <QPen>
#include <QBrush>
#include <QLinearGradient>
#include <QRectF>

Gauge::Gauge(QDeclarativeItem *parent) : QDeclarativeItem(parent), smallThreshold(0.33), mediumThreshold(0.66) {
    setFlag(QDeclarativeItem::ItemHasContents, true);

    smallColor = QColor(Qt::red);
    mediumColor = QColor(Qt::yellow);
    largeColor = QColor(Qt::green);
    _value = 0.3;
    qDebug("Constructor");
}

double Gauge::value() const {
    return _value;
}

void Gauge::paint(QPainter *painter) {
/*    QPen pen(QColor(Qt::green), 10);
    painter->setPen(pen);
    painter->drawRect(boundingRect());
*/
    QRectF rect = boundingRect();
    qreal y = rect.center().y();
    qreal x1 = rect.left();
    qreal x2 = rect.right();
    QLinearGradient gradient(QPointF(x1, y), QPointF(x2, y));
    gradient.setColorAt(0, smallColor);
    gradient.setColorAt(smallThreshold, mediumColor);
    gradient.setColorAt(mediumThreshold, largeColor);
    QRectF rect1(rect.topLeft(), QPointF(rect.left() + rect.width()*_value, rect.bottom()));
    painter->fillRect(rect1, gradient);

}

void Gauge::updateValue(const double &v) {
    if (v > 1) {
        _value = 1;
    }
    else if (v < 0) {
        _value = 0;
    }
    else {
        _value = v;
    }
    update();
    emit valueChanged();
}
