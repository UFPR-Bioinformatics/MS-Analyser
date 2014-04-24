#include "painter.h"
#include <QPaintEvent>

#include <QDebug>

Painter::Painter(QWidget *parent) : QWidget(parent)
{
//    QPainter p( this );
//    painter = new QPainter;//( this );

    path = new QPainterPath;
    path->addRect( rect( ) );

    pathtext = new QPainterPath;
    pathtext->addRect( rect( ) );
}

void Painter :: line( QLineF line )
{
//    lines.append( line );

//    painter.eraseRect( rect( ) );
//    update( rect( ) );
}

void Painter :: line( qreal x, qreal y )
{
//    qDebug( ) << "line( " << x << ", " << y << ")";
    path->lineTo( y/* + 20*/, x/* + 700*/ );
}

void Painter :: move( qreal x, qreal y )
{
//    qDebug( ) << "move( " << x << ", " << y << ")";
    path->moveTo( y/* + 20*/, x/* + 700*/ );
}

void Painter :: text( qreal x, qreal y, QString name )
{
//    qDebug( ) << "text( " << x << ", " << y << ")";
//    QFont font("Times", 10, QFont::Bold);;
//    font.setPointSize( 8 );
//    font.setWeight( QFont::Normal );
    pathtext -> addText( 0/* - 200*/, x + 3, QFont("Arial", 8 ), name );
}

void Painter :: paintEvent( QPaintEvent * event )
{
    painter.begin( this );
//    painter.drawRect( rect( ) );
//    painter.setBrush( QBrush( QColor( 255, 255, 255 ) ) );
//    painter.setPen( QPen( QBrush( QColor( 0, 0, 0 ) ) ) );
    painter.scale( 2, 2 );
//    painter.setPen( QColor( 255, 0, 0 ) );
    painter.drawPath( * pathtext );
    qDebug( ) << "height : " << rect( );
//    painter.rotate( 90 );
//    painter.translate( 0, height( ) * -1 + 20 );
    painter.drawPath( * path );
    painter.end( );

    delete path;
    delete pathtext;

    path = new QPainterPath;
    path->addRect( rect( ) );

    pathtext = new QPainterPath;
    pathtext->addRect( rect( ) );
}
