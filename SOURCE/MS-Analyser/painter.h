#ifndef PAINTER_H
#define PAINTER_H

#include <QPainter>
#include <QPainterPath>
#include <QWidget>
#include <QLineF>

class Painter : public QWidget
{
    public:
        explicit Painter(QWidget *parent = 0);
        void line( QLineF );
        void line( qreal x, qreal y );
        void move( qreal x, qreal y );
        void text( qreal x, qreal y, QString name );

    private :
        QVector< QLineF > lines;
        QPainter painter;
        QPainterPath * path;
        QPainterPath * pathtext;

    signals:

    public slots:
        void paintEvent( QPaintEvent * event );

};

#endif // PAINTER_H
