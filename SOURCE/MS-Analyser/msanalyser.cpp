#include <MSAnalyser>
#include <Peaklist>

#include <QVector>
#include <QPointF>
#include <QPen>

#include <QStandardItemModel>
#include <QStandardItem>

#include <QListIterator>

#include <QLabel>
#include <QList>

#include "tableview.h"

MSAnalyser :: MSAnalyser( QWidget * parent ) : QWidget( parent )
{
//    plot = new Plot( parent );

//    QVector <QPointF> points;

//    points.append( QPointF( 20, 50 ) );
//    points.append( QPointF( 120, 350 ) );
//    points.append( QPointF( 220, 250 ) );
//    points.append( QPointF( 270, 50 ) );
//    points.append( QPointF( 320, 150 ) );
//    points.append( QPointF( 620, 150 ) );
//    points.append( QPointF( 720, 50 ) );
//    points.append( QPointF( 920, 650 ) );

//    QwtPlotCurve * curve1 = new QwtPlotCurve;
//    curve1 -> setSamples( points );
//    curve1 -> attach( plot );
//    curve1 -> setPen( QPen( Qt :: yellow ) );
//    curve1 -> setStyle( QwtPlotCurve :: Sticks );
////    curve1 -> setSymbol(
////        new QwtSymbol( QwtSymbol :: Ellipse, Qt :: yellow, QPen( Qt :: blue ), QSize( 5, 5 ) )
////    );

//    QwtPlotMarker * marker = new QwtPlotMarker;
//    marker -> setLineStyle( QwtPlotMarker :: HLine );
////    marker -> setLabelAlignment( Qt :: AlignRight | Qt :: AlignBottom );
//    marker -> setLinePen( QPen( Qt :: yellow, 0, Qt :: DashLine ) );
//    marker -> setSymbol( new QwtSymbol(
//        QwtSymbol :: Diamond, QColor( Qt :: yellow ), QColor( Qt :: green ), QSize( 7,7 )
//    ) );
//    marker -> attach( plot );
//    marker -> setValue( 320, 150 );

//    peaklist_table = new QTableView( parent );

//parentWidget( ) -> findChild< QWidget * >( "sidePanel" ) -> findChild< QWidget * >( "pk_container" );

//    QList<QWidget *> pk_container = parentWidget() -> findChildren< QWidget * >("sidePanel");
//    QLabel * tst = new QLabel( pk_container );
//    tst-> setText("first line\nsecond line");
//    tst->setAlignment(Qt::AlignBottom | Qt::AlignRight);
//    tst -> show( );
}

void MSAnalyser :: findFiles( QDir & currentDir )
{
//    QStringList foundFiles;
    QDirIterator it( currentDir, QDirIterator::Subdirectories );

    while ( it.hasNext( ) )
    {
        it.next( );

        if ( it.fileInfo( ).suffix( ) == "xml" && it.fileName( ).contains( "peaklist" ) )
            files << it.filePath( );
    }
}

void MSAnalyser :: load( )
{
    if ( ! files.count( ) )
        QMessageBox :: information( this, tr( "Load Peaklist" ),
            tr( "The peaklist files are not found." )
        );
    else
    {
        QListIterator < QString > file( files );

        while ( file.hasNext( ) )
        {
            file.next( );
//            peaklist << new Peaklist( file.next( ), this );

//            files.pop_front( );

//            peaklist.last( ) -> show( );

//            peaklist.last( ) -> move(
//                20 * peaklist.length( ),
//                30 + 20 * peaklist.length( )
//            );
        }
        files.clear( );
    }
}

void MSAnalyser :: loadReplica( )
{
    QString path = QFileDialog::getExistingDirectory( this, tr( "Open Directory" ),
        QDir :: homePath(), QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks
    );

    if ( ! path.isEmpty( ) )
    {
        QDir currentDir = QDir( path );
        currentDir.setFilter(  QDir::Files | QDir::NoSymLinks | QDir :: NoDotAndDotDot );

        findFiles( currentDir );

        load( );
    }
}

void MSAnalyser :: loadSingle( )
{
    files << QFileDialog :: getOpenFileName( this, tr( "Open Directory" ),
        QDir :: homePath(), tr("Bruker Peaklist (peaklist*.xml)")
    );

    load( );
}

void MSAnalyser :: selectionChanged( int row, int column )
{
    Peaklist * pk;
    foreach ( pk, peaklist )
    {
        pk -> select( row, column );
    }
}
