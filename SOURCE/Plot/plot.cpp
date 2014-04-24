#include "plot.h"

#include <QDebug>
#include <qwt_plot_zoomer.h>
#include <qwt_plot_grid.h>
#include <QSlider>

#include <QTime>

class PlotZoomer: public QwtPlotZoomer
{
    public:
        PlotZoomer( QwtPlotCanvas * canvas ) : QwtPlotZoomer( canvas )
        {
//            setTrackerMode(QwtPicker::AlwaysOff);
//            setRubberBand(QwtPicker::NoRubberBand);

        //    zoomer->setRubberBandPen( QColor( Qt::black ) );
        //    zoomer->setTrackerPen( QColor( Qt::black ) );
        //    zoomer->setMousePattern(
        //        QwtEventPattern::MouseSelect2,
        //        Qt::RightButton,
        //        Qt::ControlModifier
        //    );
        //    zoomer->setMousePattern(
        //        QwtEventPattern::MouseSelect3,
        //        Qt::RightButton
        //    );
            // RightButton: zoom out by 1
            // Ctrl+RightButton: zoom out to full size

            setMousePattern(QwtEventPattern::MouseSelect2,
                Qt::RightButton, Qt::ControlModifier);
            setMousePattern(QwtEventPattern::MouseSelect3,
                Qt::RightButton);
        }
        QRectF scaleRect( )
        {
            return QwtPlotZoomer :: scaleRect( );
        }
};


Plot :: Plot( QWidget * parent ): QwtPlot( parent ), peak_weigth( 1 )
{
    setGeometry( 0, 0, 700, 150 );

    setAutoFillBackground( true );
    setPalette( QPalette( QColor( 165, 193, 228 ) ) );

    setVisible( true );

    // axes
    //setAxisTitle( xBottom, "mass" );
    //setAxisScale( xBottom, 0.0, 10.0 );

    //setAxisTitle( yLeft, "absi" );
    setAxisScale( yLeft, 0.0, 100.0 );

    // canvas
    canvas( ) -> setLineWidth( 0 );

    //picker
//    picker = new Picker(
//        QwtPlot :: xBottom,
//        QwtPlot :: yLeft,
//        QwtPlotPicker :: CrossRubberBand,
//        QwtPicker :: AlwaysOn,
//        canvas( )
//    );

//    picker -> setStateMachine( new QwtPickerDragPointMachine( ) );
//    picker -> setRubberBandPen( QColor( Qt :: white ) );
//    picker -> setRubberBand( QwtPicker :: CrossRubberBand );
//    picker -> setTrackerPen( QColor( Qt :: white ) );
//    //picker -> setTrackerMode( QwtPicker :: ActiveOnly );

//    //qDebug( ) << picker -> isActive();

//    picker -> begin();

    zoomer = new PlotZoomer( canvas() );
//    zoomer->setRubberBandPen( QColor( Qt::black ) );
//    zoomer->setTrackerPen( QColor( Qt::black ) );
//    zoomer->setMousePattern(
//        QwtEventPattern::MouseSelect2,
//        Qt::RightButton,
//        Qt::ControlModifier
//    );
//    zoomer->setMousePattern(
//        QwtEventPattern::MouseSelect3,
//        Qt::RightButton
//    );

    //qDebug( ) << picker -> isActive();

    //replot( );


    //show();

    setAutoReplot( true );

    //    setTitle("Frequency Response of a Second-Order System");

    //    setCanvasBackground( QColor( Qt :: darkBlue ) );

    // legend
    //    QwtLegend * legend = new QwtLegend;
    //    insertLegend( legend, QwtPlot :: BottomLegend );

    // grid
        plot_grid = new QwtPlotGrid;
        plot_grid -> enableX( false );
//        grid -> enableYMin( true );
        plot_grid -> setMajPen( QPen( Qt :: gray, 0, Qt :: DotLine ) );
//        grid -> setMinPen( QPen( Qt :: white, 0 , Qt :: DotLine ) );
        plot_grid -> attach( this );



        // marker
        QwtPlotMarker * marker = new QwtPlotMarker;
        marker -> setLineStyle( QwtPlotMarker :: HLine );
        marker -> setLinePen( QPen( Qt :: red, 0, Qt :: SolidLine ) );
        marker -> attach( this );


    // axes
    //    enableAxis( QwtPlot :: yRight );
    //    setAxisTitle( QwtPlot :: xBottom, "Normalized Frequency" );
    //    setAxisTitle( QwtPlot :: yLeft, "Amplitude [dB]" );
    //    setAxisTitle( QwtPlot :: yRight, "Phase [deg]" );

    //    setAxisMaxMajor( QwtPlot :: xBottom, 60 );
    //    setAxisMaxMinor( QwtPlot :: xBottom, 100 );
    //    setAxisScaleEngine( QwtPlot :: xBottom, new QwtLog10ScaleEngine );

    // curves
    //    d_curve1 = new QwtPlotCurve( "Amplitude" );
    //    d_curve1 -> setRenderHint( QwtPlotItem :: RenderAntialiased );
    //    d_curve1 -> setPen( QPen( Qt :: yellow ) );
    //    d_curve1 -> setLegendAttribute( QwtPlotCurve :: LegendShowLine );
    //    d_curve1 -> setYAxis( QwtPlot :: yLeft );
    //    d_curve1 -> attach( this );

    //    d_curve2 = new QwtPlotCurve( "Phase" );
    //    d_curve2->setRenderHint( QwtPlotItem :: RenderAntialiased );
    //    d_curve2->setPen( QPen( Qt :: cyan ) );
    //    d_curve2->setLegendAttribute( QwtPlotCurve :: LegendShowLine );
    //    d_curve2->setYAxis( QwtPlot :: yRight );
    //    d_curve2->attach( this );

    // marker
    //d_marker1 = new QwtPlotMarker( );
    //d_marker1->setValue( 0.0, 0.0);
    //d_marker1->setLineStyle( QwtPlotMarker :: VLine );
    //d_marker1->setLabelAlignment(Qt::AlignRight | Qt::AlignBottom);
    //d_marker1->setLinePen(QPen(Qt::green, 0, Qt::DashDotLine));
    //d_marker1->attach(this);

    //d_marker2 = new QwtPlotMarker();
    //    d_marker2->setLineStyle(QwtPlotMarker::HLine);
    //    d_marker2->setLabelAlignment(Qt::AlignRight | Qt::AlignBottom);
    //    d_marker2->setLinePen(QPen(QColor(200,150,0), 0, Qt::DashDotLine));
    //    d_marker2->setSymbol( new QwtSymbol(QwtSymbol::Diamond,
    //        QColor(Qt::yellow), QColor(Qt::green), QSize(7,7)));
    //    d_marker2->attach(this);

    //    setDamp(0.0);

    //    setAutoReplot(true);
}

QwtPlotGrid * Plot :: grid( )
{
    return plot_grid;
}

void Plot :: peakWeigth( int value )
{
    peak_weigth = value;
}

void Plot :: zoom( )
{
//    zoomer -> zoom( zoomer -> scaleRect( ) );
//    zoomer -> setZoomBase( false );
//    zoomer -> setZoomBase( zoomer -> canvas() -> rect() );
    zoomer -> setZoomBase( zoomer -> zoomBase( ) );

//    qDebug( ) << zoomer -> zoomBase( );

//    QStack< QRectF> stack;
//    stack.push( zoomer->plot()->rect());

//    zoomer->rescale();

//    qDebug( ) << zoomer->plot()-> ;
//    qDebug( ) << zoomer -> scaleRect( );
}

void Plot :: scale( qreal min, qreal max )
{
    setAxisScale( QwtPlot :: xBottom, min, max );

    zoomer -> setZoomBase( zoomer -> scaleRect( ) );

    zoom( );
}

void Plot :: curve( QwtPlotCurve * curve )
{
    curve -> hide( );
    curve -> detach( );
//    qDebug( ) << "# " << curves.removeAll( curve );
    delete curve;
}

QwtPlotCurve * Plot :: curve( QVector < QPointF > points )
{

    return curve( points, QColor( ) );
}

QwtPlotCurve * Plot :: curve( QVector < QPointF > points, QColor color = QColor( ) )
{
//    if ( curves.size( ) > 9 )
//    {
//        QMessageBox :: information( this, "Peak List", "There are many curves in the plot, to draw this remove one before." );
//        return ( QwtPlotCurve * ) NULL;
//    }

//    QwtPlotCurve * curves = new QwtPlotCurve;
    curves << new QwtPlotCurve;

    curves.last()->setSamples( points );
//    curves.last( ) -> attach( this );
//    curves.last( ) -> setPen(
//        QPen( ( color.isValid( ) ) ? color : ( ( Qt :: GlobalColor ) ( curves.size( ) + 3 ) ) )
//    );

//    curves.last( ) -> setPen(
//        QPen( ( color.isValid( ) ) ? color : QColor( ( ( Qt :: GlobalColor ) ( (int)( curves.size( ) / 2 ) + 6 ) ) ) )
//    );

    QPen pen = QPen( ( color.isValid( ) ) ?
        color : QColor( qrand( ) % 200, qrand( ) % 200, qrand( ) % 200 )
    );
    pen.setWidth( peak_weigth );

    curves.last( ) -> setPen( pen );

    curves.last( ) -> setStyle( QwtPlotCurve :: Sticks );
    //curve1 -> setSymbol(
    //    new QwtSymbol( QwtSymbol :: Ellipse, Qt :: yellow, QPen( Qt :: blue ), QSize( 5, 5 ) )
    //);

//    replot( );

//    setAxisScale( yLeft, floor( curves.last( ) -> minYValue( ) ), ceil( curves.last( ) -> maxYValue( ) ) );
//    setAxisScale( xBottom, floor( curves.last( ) -> minXValue( ) ), ceil( curves.last( ) -> maxXValue( ) ) );

    return curves.last();
}

void Plot :: mousePressEvent( QMouseEvent * e )
{
//    qDebug( ) << e;
//    e -> ignore( );
}

void Plot :: mouseReleaseEvent( QMouseEvent * e )
{
//    qDebug( ) << e;
//    e -> ignore( );
}

void Plot :: mouseMoveEvent( QMouseEvent * e )
{
//    qDebug( ) << e;
//    e -> ignore( );
}

void Plot :: replot( )
{
    QwtPlot::replot( );

}
