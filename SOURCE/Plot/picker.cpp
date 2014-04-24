#include "picker.h"

Picker :: Picker( int xAxis, int yAxis, RubberBand rubberBand, DisplayMode trackerMode, QwtPlotCanvas * canvas ) : QwtPlotPicker( xAxis, yAxis, rubberBand, trackerMode, canvas )
{
}

void Picker :: begin( )
{
    QwtPlotPicker :: begin( );
}
