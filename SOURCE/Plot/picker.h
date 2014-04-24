#ifndef PICKER_H
#define PICKER_H

#include <qwt_plot_picker.h>
class QwtPlotCanvas;

class Picker : public QwtPlotPicker
{
    public:
        explicit Picker( int xAxis, int yAxis, RubberBand rubberBand, DisplayMode trackerMode, QwtPlotCanvas * );

        void begin( );

    signals:

    public slots:

};

#endif // PICKER_H
