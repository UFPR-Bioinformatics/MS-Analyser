#include "database.h"

#include <QMessageBox>

Database :: Database( ) : QSqlDatabase( )
{
}

Database :: Database( const QString & type ) : QSqlDatabase( type )
{
}

Database :: Database( QSqlDriver * driver ) : QSqlDatabase( driver )
{
}

void Database :: prepare( const QString & query )
{
    q = new QSqlQuery( ( * this ) );
    q -> prepare( query );

//    int field_title = q -> record( ).indexOf( "title" );

//    while ( q -> next( ) )
//    {
//        qDebug( ) << q -> value( field_title ).toString( );
//    }
}

void Database :: bind( const QString & placeholder, const QVariant & val )
{
    q -> bindValue( placeholder, val );
//    qDebug( ) << q -> lastError( );
}

QSqlQuery * Database :: query( )
{
//    qDebug( ) << q -> lastQuery( );
//    qDebug( ) << q -> boundValues( );

//    QMessageBox :: information( 0, "", "query" );
//    QMessageBox :: information( 0, "", q -> lastQuery( ) );

    bool exec = q -> exec( );


//    rec = q -> record( );

//    if ( q -> isSelect( ) )
//    {
//        while ( q -> next( ) )
//        {
//            qDebug( ) << ">> " << q -> value( 0 ).toString( );
//        }
//    }

    if ( ! exec )
    {
//        qDebug( ) << q -> lastError( );

//        QMessageBox :: information( 0, "", q -> lastError( ).text( ) );
    }

    return q;
}

QSqlRecord Database :: record( )
{
//    qDebug( ) << q -> executedQuery( );
    return rec;
}
