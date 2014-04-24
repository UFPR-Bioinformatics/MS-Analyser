#ifndef _PLOT_H_
#define _PLOT_H_

#include <QMessageBox>

#include <qwt_plot.h>
#include <qwt_plot_canvas.h>
#include <qwt_plot.h>
#include <qwt_plot_canvas.h>
//#include <qwt_plot_picker.h>
#include <qwt_picker_machine.h>

#include <qwt_plot_curve.h>
#include <qwt_symbol.h>
#include <qwt_plot_marker.h>

#include <qwt_scale_div.h>


#include <QMouseEvent>

#include "picker.h"

#include <QModelIndex>

class QwtPlotGrid;
//#include <qwt_plot_zoomer.h>

class PlotZoomer;

class Plot: public QwtPlot
{
    Q_OBJECT

    public :
        Plot( QWidget * parent );
        QwtPlotCurve * curve( QVector < QPointF > );
        QwtPlotCurve * curve( QVector < QPointF >, QColor );
        void curve( QwtPlotCurve * );
        void zoom( );
        void scale( qreal, qreal );
        void peakWeigth( int );
        QwtPlotGrid * grid( );

    protected :
        Picker * picker ;

        void mousePressEvent( QMouseEvent * e );
        void mouseMoveEvent( QMouseEvent * e );
        void mouseReleaseEvent( QMouseEvent * );

        void replot( );

    private :
        QList < QwtPlotCurve * > curves;
        QPoint dragStartPosition;

        QwtPlotGrid * plot_grid;

        PlotZoomer * zoomer;

        int peak_weigth;
};

#endif
