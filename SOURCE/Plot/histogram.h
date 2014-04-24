//#ifndef _TV_PLOT_H_

#include <stdlib.h>
#include <qpen.h>
#include <qwt_plot_layout.h>
#include <qwt_legend.h>
#include <qwt_legend_item.h>
#include <qwt_plot_grid.h>
#include <qwt_plot_histogram.h>
#include <qwt_column_symbol.h>
#include <qwt_series_data.h>

#include <qwt_plot.h>

class Histogram: public QwtPlotHistogram
{
    public:
        Histogram( const QString &, const QColor & );

        void setColor( const QColor & );
        void setValues( QVector < double > );
};


class HistogramPlot: public QwtPlot
{
    Q_OBJECT

public:
    HistogramPlot(QWidget * = NULL);

//private:
    void populate();

private Q_SLOTS:
    void showItem(QwtPlotItem *, bool on);
};

//#endif
