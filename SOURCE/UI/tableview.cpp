#include "tableview.h"

#include <QMessageBox>
#include <QDebug>

#include <Peaklist>

TableView :: TableView( QWidget * parent ) : QTableView( parent )
{
    this -> parent = parent;
    model = new QStandardItemModel;

    setSelectionMode( QAbstractItemView :: SingleSelection );

    setStyleSheet(
        "QTableView { border: none;"
//        "background-color: #8EDE21;"
        "selection-background-color: #999}"
        "QHeaderView::section {"
        "background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
        "stop:0 #616161, stop: 0.5 #505050,"
        "stop: 0.6 #434343, stop:1 #656565);"
        "color: white;"
        "padding-left: 4px;"
        "border: 1px solid #6c6c6c;"
        "}"
    );

    reflex = false;
}

//void TableView :: setHeader( int row, int column, QString value )
//{
//    QHeaderView
//}

QStandardItem * TableView :: setCell( int row, int column, QString value )
{
//    model -> setItem( row, column, new QStandardItem( QString :: number( value.toFloat( ) ) ) );
    QStandardItem * cell = new QStandardItem( value );
    model -> setItem( row, column, cell );

    setModel( model );

    return cell;
}

void TableView :: clear( )
{
    model -> clear( );
}

void TableView :: select( int row, int column )
{
    if ( ! model -> index( row, column, QModelIndex( ) ).isValid( ) )
        return;

    if ( selectionModel( ) -> hasSelection( ) )
        selectionModel( ) -> clearSelection( );

    selectionModel( ) -> select(
        QItemSelection(
            model -> index( row, column, QModelIndex( ) ),
            model -> index( row, column, QModelIndex( ) )
        ), QItemSelectionModel :: Select
    );

    setFocus( );

//    parent -> selectionChanged( row, column );
}

void TableView :: setHLabels( QStringList labels )
{
    model -> setHorizontalHeaderLabels( labels );
}

void TableView :: setVLabels( QStringList labels )
{
    model -> setVerticalHeaderLabels( labels );
}

void TableView :: setMarker( QwtPlotMarker * marker )
{
    this -> marker = marker;
    marker -> hide( );
}

void TableView :: visible( bool visible = false, bool reflex = false )
{
    this -> reflex = reflex;

    if ( visible )
        marker -> show( );
    else
        marker -> hide( );
}

void TableView :: mousePressEvent( QMouseEvent * e )
{
    e -> ignore( );
}

void TableView :: mouseReleaseEvent( QMouseEvent * e )
{
    e -> ignore( );
}

void TableView :: mouseMoveEvent( QMouseEvent * e )
{
    e -> ignore( );
}

void TableView :: selectionChanged( const QItemSelection & selected, const QItemSelection & deselected )
{
    if ( selected.isEmpty( ) )
        return;

    QModelIndex current = selected.indexes( ).last( );

    marker -> setValue(
        current.sibling( 0, current.column( ) ).data( ).toFloat( ),
        QString(
            model -> headerData( current.column( ), Qt::Horizontal ).toString( ).split("%")[0]
        ).toFloat( ) * ( ( reflex ) ? -1 : 1 )
    );

//    QString label;
//    label.sprintf( "%f (%f)",
//        current.sibling( 0, current.column( ) ).data( ).toFloat( ),
//        current.sibling( 1, current.column( ) ).data( ).toFloat( )
//    );

//    QwtText text( label );
//    text.setFont( QFont( "Helvetica", 10, QFont :: Bold ) );
//    text.setColor( QColor( 200, 150, 0 ) );

//    marker -> setLabelAlignment( Qt :: AlignRight | Qt :: AlignTop );
//    marker -> setLabel( text );

//    marker -> show( );

    QTableView :: selectionChanged( selected, deselected );
}
