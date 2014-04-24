#include <Peaklist>

#include <QDebug>
#include <QScrollBar>
//#include <QModelIndex>

#include <QCryptographicHash>

#include <tableview.h>

bool max_fid_peak_by_absi( const QPointF & p1, const QPointF & p2 )
{
    return p1.y( ) > p2.y( );
}

bool sort_peaks( const QHash < QString, QString > p1, const QHash < QString, QString > p2)
{
    return p1[ "mass" ].toFloat( ) < p2[ "mass" ].toFloat( );
}


Peaklist :: Peaklist( QList < QHash < QString, QString > > peaks, QHash < QString, QString > info )
{
    this -> peaks = peaks;
    this -> info = info;
    this -> fid = ( QVector < QPointF > ) NULL;

    fix( );
}

Peaklist :: Peaklist( QList < QHash < QString, QString > > peaks, QHash < QString, QString > info, QVector < QPointF > fid = ( QVector < QPointF > ) NULL )
{
    this -> peaks = peaks;
    this -> info = info;
    this -> fid = fid;

    fix( );
}

Peaklist :: Peaklist( QList < QHash < QString, QString > > peaks )
{
    this -> peaks = peaks;

    fix( );
}

void Peaklist :: fix( void )
{
    qreal max_absi = 0;
    for ( int i = 0; i < peaks.size( ); i++ )
        max_absi = qMax( max_absi, ( qreal ) peaks[ i ][ "absi" ].toFloat( ) );

    for ( int i = 0; i < peaks.size( ); i++ )
        if ( peaks[ i ][ "absi" ].toFloat( ) > 0 )
            peaks[ i ][ "absi_rel" ] = QString( "%1" ).arg(
                peaks[ i ][ "absi" ].toFloat( ) * 100 / max_absi
            );
        else
            peaks[ i ][ "absi_rel" ] = "1";

    fid = fid.mid( 0, ( int ) peaks.last( ).value( "rind" ).toFloat( ) ).mid( ( int ) peaks.first( ).value( "lind" ).toFloat( ) );

    max_absi = 0;
    for ( int i = 0; i < fid.size( ); i++ )
        max_absi = qMax( max_absi, ( qreal ) fid[ i ].y( ) );

    for ( int i = 0; i < fid.size( ); i++ )
    {
//        fid[ i ].setX( fid[ i ].x( ) - ( ( int ) peaks.first( ).value( "ind" ).toFloat( ) - ( int ) peaks.first( ).value( "mass" ).toFloat( )) );

        if ( fid[ i ].y( ) > 0 )
            fid[ i ].setY( fid[ i ].y( ) * 100 / max_absi );
    }

    isActive = false;
}

Peaklist * Peaklist :: New( Peaklist * pk_1, Peaklist * pk_2 )
{
    QList < QHash < QString, QString > > peaks;

    peaks.append( pk_1 -> getPeaks( ) );
    peaks.append( pk_2 -> getPeaks( ) );

    qSort( peaks.begin( ), peaks.end( ), sort_peaks );

    bool merge = true;
    int i = 0;

    while ( merge )
    {
        if ( i < ( peaks.size( ) - 1 ) )
        {
            if ( peaks[ i + 1 ][ "mass" ].toFloat( ) - peaks[ i ][ "mass" ].toFloat( ) < 5 )
            {
                peaks[ i ][ "mass" ] = QString( "%1" ).arg( (
                        peaks[ i ][ "mass" ].toFloat( ) /** peaks[ i ][ "absi" ].toFloat( )*/ +
                        peaks[ i + 1 ][ "mass" ].toFloat( ) /** peaks[ i + 1 ][ "absi" ].toFloat( )*/
                    ) / (
                        2/*peaks[ i ][ "absi" ].toFloat( ) + peaks[ i + 1 ][ "absi" ].toFloat( )*/
                ) );

                peaks[ i ][ "absi" ] = QString( "%1" ).arg(
                    ( peaks[ i ][ "absi" ].toFloat( ) + peaks[ i + 1 ][ "absi" ].toFloat( ) ) / 2
                );

                peaks.removeAt( i + 1 );
            }
            else
            {
                i++;
                if ( i > peaks.size( ) - 3 )
                    merge = false;
            }
        }
        else
        {
            merge = false;
        }
    }

    return new Peaklist( peaks );
}

Peaklist * Peaklist :: New( const QString file )
{
    QFile fp( file );

    if ( ! fp.open( QFile :: ReadOnly | QFile :: Text ) )
    {
        //QMessageBox::warning( this, tr( "Load Peaklist" ),
        //  tr( "Cannot read file %1:\n%2." )
        //  .arg( xml.fileName( ) )
        //  .arg( xml.errorString( ) )
        //);
        return ( Peaklist * ) NULL;
    }

    QList < QHash < QString, QString > > peaks;
    QHash < QString, QString > info;
    QHash < QString, QString > fields;
    QVector < QPointF > fid_data;

    QFileInfo fp_info( fp );

    QDir workpath = QDir :: homePath( ) + "/MS-Analyser/peakset";
    if ( ! workpath.exists( ) )
        workpath.mkpath( workpath.path( ) );

    if ( fp_info.suffix( ) == "peaks" )
    {
        QTextStream in( & fp );
        QString spectrumid = QString( QCryptographicHash::hash( in.readAll( ).toStdString().c_str(), QCryptographicHash :: Md5 ).toHex( ) );
        QString file = workpath.filePath( spectrumid + ".xml" );

//        qDebug( ) << file << " :: " << fp.exists( file );

        if ( ! fp.exists( file ) )
        {
            in.seek( 0 );

            QDomDocument * dom = new QDomDocument;
            QDomElement root = dom -> createElement( "pklist" );

            root.setAttribute( "spectrumid", spectrumid );
            if ( ! fp_info.baseName( ).isEmpty( ) )
                root.setAttribute( "name", fp_info.baseName( ) );

            dom -> appendChild( root );

            QString line;

            while ( ! ( line = in.readLine( ) ).isNull( ) )
            {
                QDomElement pk = dom -> createElement( "pk" );
                root.appendChild( pk );

                QDomElement absi = dom -> createElement( "absi" );
                ( pk.appendChild( absi ) ).appendChild( dom -> createTextNode( "1.0" ) );

                QDomElement mass = dom -> createElement( "mass" );
                ( pk.appendChild( mass ) ).appendChild( dom -> createTextNode( line ) );
            }

            fp.close( );

            fp.setFileName( file );

            if ( ! fp.open( QIODevice::WriteOnly | QIODevice::Truncate ) )
                return ( Peaklist * ) NULL;

            QTextStream out( & fp );
            dom -> save( out, 0 );

            fp.copy( workpath.filePath( spectrumid + ".ms-analyser" ) );
        }

        fp.close( );

        fp.setFileName( file );

        if ( ! fp.open( QFile :: ReadOnly | QFile :: Text ) )
            return ( Peaklist * ) NULL;

        fp_info.setFile( fp );
    }

    if ( fp_info.suffix( ) == "xml" )
    {
        QDomDocument * dom = new QDomDocument;
        QString errorStr;
        int errorLine;
        int errorColumn;

        if ( ! ( dom -> setContent( & fp, true, & errorStr, & errorLine, & errorColumn ) ) )
        {
            return ( Peaklist * ) NULL;
        }

        QDomNode node, subNode;
        node = dom -> documentElement( );

        if ( node.nodeName( ) != "pklist" )
            return ( Peaklist * ) NULL;

        if ( ! node.hasChildNodes( ) )
            return ( Peaklist * ) NULL;

        node = node.firstChild( );

        while ( ! node.isNull( ) )
        {
            subNode = node.firstChild( );

            while( ! subNode.isNull( ) )
            {
                fields[ subNode.nodeName( ) ] = subNode.firstChild( ).nodeValue( );
                subNode = subNode.nextSibling( );
            }

            peaks << fields;

            node = node.nextSibling( );
        }

        QDomNamedNodeMap attrs = dom -> documentElement( ).attributes( );

        for ( uint i = 0; i < attrs.length( ); i++ )
            info[ attrs.item( i ).nodeName( ) ] = attrs.item( i ).nodeValue( );

        if ( info.contains( "spectrumid" ) )
        {
//            QDir workpath = QDir :: homePath( ) + "/MS-Analyser/peakset";
//            if ( ! workpath.exists( ) )
//                workpath.mkpath( workpath.path( ) );

            if ( ! fp.exists( workpath.filePath( info[ "spectrumid" ] + ".xml" ) ) )
            {
                fp.copy( workpath.filePath( info[ "spectrumid" ] + ".xml" ) );
//                fp.copy( workpath.filePath( info[ "spectrumid" ] + ".ms-analyser" ) );
            }
            else
            {
                //QFile fp( workpath.filePath( info[ "spectrumid" ] + ".ms-analyser" ) );
                if ( fp.exists( workpath.filePath( info[ "spectrumid" ] + ".ms-analyser" ) ) )
                {
                    fp.close( );
                    fp.setFileName( workpath.filePath( info[ "spectrumid" ] + ".ms-analyser" ) );
                    if ( fp.open( QFile :: ReadOnly | QFile :: Text ) )
                    {
                        if ( dom -> setContent( & fp, true, & errorStr, & errorLine, & errorColumn ) )
                        {
                            QDomElement root = dom -> documentElement( );
                            if ( root.hasAttribute( "name") )
                            {
                                info[ "name" ] = root.attribute( "name" );
                            }
                        }
                    }
                }
            }

            fp.close( );
            return new Peaklist( peaks, info, fid_data );
        }

        return ( Peaklist * ) NULL;
    }

//    if ( fp_info.suffix( ) == "peaks" )
//    {
//        QTextStream in( & fp );

//        QString line;
//        while ( ! ( line = in.readLine( ) ).isNull( ) )
//        {
//            fields[ "mass" ] = line;
//            fields[ "absi" ] = "1";

//            peaks << fields;
//        }

//        info[ "spectrumid" ] = fp_info.baseName( );
//        info[ "date" ] = "";

////        qDebug( ) << peaks;
//        return new Peaklist( peaks, info );

////        return ( Peaklist * ) NULL;
//    }
}

QHash < QString, QString > Peaklist :: getInfo( )
{
    return info;
}

QList < QHash < QString, QString > > Peaklist :: getPeaks( void )
{
    return peaks;
}

QVector < QPointF > Peaklist :: getFid( void )
{
    return fid;
}

//QVector < QPointF > Peaklist :: getPeaks( void )
//{
//    QVector < QPointF > points;

//    for ( int i = 0; i < peaks.size( ); i++ )
//    {
//        points.append( QPointF(
//            peaks[ i ][ "mass" ].toFloat( ),
//            peaks[ i ][ "absi" ].toFloat( )
//        ) );
//    }

//    return points;
//}

void Peaklist :: show( void )
{
//    QWidget :: show( );
}

void Peaklist :: actived( bool isActive )
{
    this -> isActive = isActive;
}

bool Peaklist :: actived( )
{
    return isActive;
}

void Peaklist :: reflex( bool isReflex )
{
    this -> isReflex = isReflex;
}

bool Peaklist :: reflex( )
{
    return isReflex;
}

void Peaklist :: createPlot( )
{
//    QVector < QPointF > points;

//    for ( int i = 0; i < peaks.size( ); i++ )
//    {
////        qDebug( ) << peaks[ i ][ "mass" ] << " # " << peaks[ i ][ "mass" ].toFloat( );
//        points.append( QPointF(
//            peaks[ i ][ "mass" ].toFloat( ),
//            peaks[ i ][ "absi" ].toFloat( )
//        ) );
//    }

//    plot = new Plot( this );

//    createTable( plot -> curve( points ) );
}

void Peaklist :: createTable( QPen pen )
{
//    table = new TableView( this );

//    for ( int column = 0; column < peaks.length( ); ++column )
//    {
//        table -> setCell( 0, column, peaks.at( column )[ "mass" ] );
//        table -> setCell( 1, column, peaks.at( column )[ "absi" ] );
//    }

//    table -> resizeRowsToContents( );
//    table -> resizeColumnsToContents( );

//    table -> setGeometry(
//        0,
//        plot -> size( ).height( ),
//        plot -> size( ).width( ),
//        table -> horizontalHeader( ) -> height( )
//            + ( 2 * table -> rowHeight( 1 ) )
//            + table -> horizontalScrollBar( ) -> height( )
//    );

//    QStringList labels;
//    labels << "mass" << "absi";

//    table -> setVLabels( labels );

//    marker = new QwtPlotMarker;

//    marker -> setLineStyle( QwtPlotMarker :: HLine );
//    //    marker -> setLabelAlignment( Qt :: AlignRight | Qt :: AlignBottom );
//    marker -> setLinePen( QPen( Qt :: yellow, 0, Qt :: DashLine ) );
//    marker -> setSymbol( new QwtSymbol(
//        QwtSymbol :: Diamond,
//        QColor( Qt :: yellow ),
//        QColor( Qt :: green ),
//        QSize( 7,7 )
//    ) );
//    marker -> attach( plot );

//    table -> setMarker( marker );

//    table -> select( 0, 0 );
}

void Peaklist :: mousePressEvent( QMouseEvent * e )
{
//    mouseStartPosition = e -> pos( );

//    raise( );
}

void Peaklist :: mouseReleaseEvent( QMouseEvent * e )
{
//    mouseStartPosition = QPoint( 0, 0 );
}

void Peaklist :: mouseMoveEvent( QMouseEvent * e )
{/*
    if ( e -> buttons( ) & Qt :: LeftButton )
    {
        QPoint pos = geometry( ).topLeft( ) + ( e -> pos( ) - mouseStartPosition );

        if ( pos.x( ) < 0 )
            pos.setX( 0 );

        if ( pos.y( ) < 0 )
            pos.setY( 0 );

        move( pos );
    }

    if ( ! ( e -> buttons( ) & Qt :: LeftButton ) )
    {
        QSize size = geometry( ).size( );

        QPoint pos = ( e -> pos( ) - mouseStartPosition );

        size.setWidth( size.width( ) + pos.x( ) );
        size.setHeight( size.height( ) + pos.y( ) );

        if ( size.height( ) < table -> height( ) + 100 )
            size.setHeight( table -> height( ) + 100 );

        mouseStartPosition = e -> pos( );

        resize( size );

        size.setHeight(
            size.height( ) - table -> size( ).height( )
        );

        plot -> resize( size );

        table -> move( 0, plot -> size( ).height( ) );

        size.setHeight( table -> size( ).height( ) );

        table -> resize( size );
    }*/
}

void Peaklist :: selectionChanged( int row, int column )
{
//    parent -> selectionChanged( row, column );
}

void Peaklist :: select( int row, int column )
{
//    table -> select( row, column );
}

//void Peaklist :: point( const QModelIndex & current, const QModelIndex & previous )
//{
//    marker -> setValue(
//        current.sibling( 0, current.column( ) ).data( ).toFloat( ),
//        current.sibling( 1, current.column( ) ).data( ).toFloat( )
//    );

//    plot -> replot( );
//}
