#ifndef TABLEVIEW_H
#define TABLEVIEW_H

#include <QTableView>
#include <QHeaderView>

#include <QStandardItemModel>
#include <QStandardItem>
#include <QMouseEvent>

#include <qwt_plot_marker.h>

//#include <Peaklist>
//class MSAnalyser;
class Peaklist;

class TableView : public QTableView
{
    public:
        TableView( QWidget * parent );
        QStandardItem * setCell( int, int, QString );
        void setHLabels( QStringList );
        void setVLabels( QStringList );
        void setMarker( QwtPlotMarker * );
        void visible( bool, bool );
        void select( int, int );
        void clear( void );

    protected :
        void mousePressEvent( QMouseEvent * );
        void mouseMoveEvent( QMouseEvent * );
        void mouseReleaseEvent( QMouseEvent * );
        void selectionChanged( const QItemSelection & selected, const QItemSelection & deselected );

    private :
        bool reflex;
        QPoint mouseStartPosition;

        QStandardItemModel * model;
        QWidget * parent;

        QwtPlotMarker * marker;
};

#endif // TABLEVIEW_H
