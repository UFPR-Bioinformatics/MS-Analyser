#include "listwidget.h"
#include <QMouseEvent>
#include <QDebug>

#include <QMenu>

#include <variantdelegate.h>


ListWidget :: ListWidget( QWidget * parent )
{
    this -> parent = parent;
    setContextMenuPolicy( Qt :: CustomContextMenu );
    setSortingEnabled( true );

    setItemDelegate( new VariantDelegate( parent ) );
}

void ListWidget :: mousePressEvent( QMouseEvent * e )
{
    setCurrentItem( itemAt( e->pos( ) ) );

//    if ( e -> button( ) == Qt::LeftButton )
    if ( ! ( e -> buttons( ) & Qt::RightButton ) )
        emit itemClicked( itemAt( e->pos( ) ) );

    e -> ignore( );
}

void ListWidget :: mouseReleaseEvent( QMouseEvent * e )
{
    e -> ignore( );
}

void ListWidget :: customContextMenuRequested( const QPoint & )
{
//    qDebug( ) << "customContextMenuRequested";
}

void ListWidget :: contextMenuEvent( QContextMenuEvent * e )
{
//    qDebug( ) << "contextMenuEvent";

//    QListWidgetItem * item = itemAt( e -> pos( ) );

//    if ( item )
//    {
////        if ( item -> checkState( ) != Qt :: Checked )
////            pk_panel_clicked( item );

////        QMessageBox :: information( this, "", "show" );

//        QMenu menu( this );

//        QAction * info = new QAction( tr( "Informations" ), this );
//        QAction * reflex = new QAction( tr( "Reflex" ), this );
//        QAction * remove = new QAction( tr( "Remove" ), this );
//        QAction * merge = new QAction( tr( "Merge" ), this );
//        QAction * edit= new QAction( tr( "Edit" ), this );

//        menu.addAction( info );
//        menu.addAction( reflex );
//        menu.addAction( remove );
//        menu.addAction( merge );
//        menu.addAction( edit );

//        connect( reflex, SIGNAL( triggered( ) ), parent, SLOT( pk_panel_clicked_reflex( ) ) );
//        connect( info, SIGNAL( triggered( ) ), parent, SLOT( pk_edit_info( ) ) );
//        connect( merge, SIGNAL( triggered( ) ), parent, SLOT( pk_merge( ) ) );
//        connect( edit, SIGNAL( triggered( ) ), parent, SLOT( pk_panel_item_edit( ) ) );

//        menu.exec( e -> globalPos( ) );
//    }
}
