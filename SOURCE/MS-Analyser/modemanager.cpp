#include "modemanager.h"

#include <Application>
#include "fancytabwidget.h"

#include <QString>
#include <QWidget>
#include <QIcon>

#include <QMessageBox>
#include <QStatusBar>

ModeManager :: ModeManager( Application * parent ) : QObject( parent ), index( 0 )
{
    fancy = new FancyTabWidget( parent );
    fancy -> statusBar( ) -> setSizeGripEnabled( false );
    parent -> setCentralWidget( fancy );

    connect( fancy, SIGNAL( currentChanged(int) ), this, SLOT( currentChanged( int ) ) );
}

Mode * ModeManager :: insert( const QString & name, QWidget * content, const QIcon & icon )
{
    Mode * mode = new Mode( fancy, index++, name, content, icon );
//    fancy -> insertTab( index, content, icon, name );

    this -> mode.append( mode );

    return mode;
}

void ModeManager :: currentChanged( int mode )
{
//    QMessageBox :: information( 0, "", QString( "#1 - Mode changed (%1)." ).arg( mode ) );

    _current = mode;
    emit modeChanged( mode );
}

Mode * ModeManager :: current( )
{
    return mode.at( _current );
}

void ModeManager :: statusBar( QString status )
{
    if ( status.size( ) )
        current( ) -> fancy -> statusBar( ) -> showMessage( status );
    else
        current( ) -> fancy -> statusBar( ) -> clearMessage( );
}
