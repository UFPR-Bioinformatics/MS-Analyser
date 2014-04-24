#ifndef PEAKLIST_H
#define PEAKLIST_H

#include <QFile>
#include <QHash>
#include <QList>
#include <QDomDocument>
#include <QWidget>

#include <plot.h>

#include <QVector>
#include <QPointF>

#include <tableview.h>

#include <MSAnalyser>
class TableView;

class QString;

class Peaklist// : public QDomDocument//, public QWidget
{
    public:
        static Peaklist * New( const QString );
        static Peaklist * New( Peaklist * pk_1, Peaklist * pk_2 );

        QList < QHash < QString, QString > > getPeaks( void );

        void show( void );
        void selectionChanged( int, int );
        void select( int, int );

        void actived( bool );
        bool actived( void );

        void reflex( bool );
        bool reflex( void );

        QHash < QString, QString > getInfo( void );
        QVector < QPointF > getFid( void );

        void mousePressEvent( QMouseEvent * );
        void mouseMoveEvent( QMouseEvent * );
        void mouseReleaseEvent( QMouseEvent * );

//    public slots :
//        void point( const QModelIndex &, const QModelIndex & );

    private :
        Peaklist( QList < QHash < QString, QString > >, QHash < QString, QString >, QVector < QPointF > );
        Peaklist( QList < QHash < QString, QString > >, QHash < QString, QString > );
        Peaklist( QList < QHash < QString, QString > > );

        QHash < QString, QString > info;
        QVector < QPointF > fid;

        QList < QHash < QString, QString > > peaks;
        MSAnalyser * parent;
        QWidget * container;
        QPoint mouseStartPosition;

        QwtPlotMarker * marker;

        Plot * plot;
        TableView * table;

        bool isActive;
        bool isReflex;

        void createPlot( void );
        void createTable( QPen );

        void fix( void );

};

#endif // PEAKLIST_H
