#include <Application>
#include <Peaklist>

#include <QMessageBox>
//#include <QDockWidget>

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>

#include <listwidget.h>

#include <QSplashScreen>
#include <QWaitCondition>
#include <QMutex>

#include <QSplitter>
#include <QDebug>
#include <QPushButton>
#include <QRadioButton>

#include <QScrollArea>
#include <painter.h>

#include <QFileDialog>
#include <QInputDialog>

#include <QStringList>
#include <QDirIterator>
#include <QDateTime>

#include <qwt_plot_curve.h>
#include <qwt_plot_grid.h>
#include <qwt_scale_widget.h>

#include <tableview.h>
#include <QScrollBar>
#include <QTabWidget>

#include <QMenu>
#include <QAction>

#include <QtUiTools/QUiLoader>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QCheckBox>

//#include <fancytabwidget.h>
#include <modemanager.h>


#include <database.h>
#include <QLabel>

#include <QPicture>
#include <QPainter>
#include <QPaintEngine>

#include <QStatusBar>

#include <math.h>
#include <vector>
#include <cassert>
#include <iostream>
#include <fstream>
#include <string>

#include "Distance.h"
#include "DistanceConservative.h"
#include "DistanceEuclid.h"
#include "DistanceLiberal.h"
#include "DistancePearson.h"

extern "C" {
#include <cluster/cluster.h>
}

#include "DrawTree.h"
//#include "TreeClusterDistances.h"
#include "TreeNode.h"


//extern "C" {
//#include <cgraph.h>
//#include <Cgraph/cglobals.h>
//}

#include "pic.h"

#include "Cluster.h"
//#include "Parameter.h"
#include "Peak.h"
#include "Spectrum.h"

#include "histogram.h"

#include "qxtspanslider.h"

void calculate_distance(
        std::vector< std::vector<double> > & d,
        const std::vector<std::vector<double> >& ps,
        double sigma,
        const theplu::speclust::Distance& metric)
{
    for (unsigned int i=0; i<ps.size()-1; i++)
        for (unsigned int j=i+1; j<ps.size(); j++)
            d[ i ][ j ] = d[ j ][ i ] = metric(ps[i], ps[j], sigma);
}

typedef struct SuperSpectrum
{
    public :
        SuperSpectrum( ) : pk_list( 0 ), curve( ( QwtPlotCurve * ) NULL )
    {
    }

        void peaklist( QList < QHash < QString, QString > > peaks )
        {
            pk_list++;

            for ( int i = 0; i < peaks.size( ); i++ )
            {
                add( QPointF(
                            peaks[ i ][ "mass" ].toFloat( ),
                            peaks[ i ][ "absi" ].toFloat( )
                        ) );
            }
        }

        void show( Plot * plot, int tolerance = 2, uint presence = 60 )
        {
            fix( tolerance );

            this -> plot = plot;
            QVector < QPointF > points, points_sorted;

            points = getPeaks( presence );
            points_sorted = points;

            qSort(
                    points_sorted.begin( ),
                    points_sorted.end( ),
                    max_peak_by_absi
                 );

            for ( int i = 0; i < points.size( ); i++ )
                points[ i ].setY(
                        points[ i ].y( ) * 100
                        / points_sorted[ 0 ].y( ) * -1
                        );

            if ( curve == ( QwtPlotCurve * ) NULL )
            {
                curve = plot -> curve( points );
                curve -> attach( plot );
                plot -> setAxisScale(
                        QwtPlot :: yLeft, -100.0, 100.0
                        );
            }
        }

        void clean( )
        {
            pk_list = 0;

            if ( ! ss_points.isEmpty() )
                ss_points.clear( );

            if ( curve != ( QwtPlotCurve * ) NULL )
            {
                plot -> curve( curve );
                curve = ( QwtPlotCurve * ) NULL;
            }
        }

    private :
        int pk_list;
        QList < SuperSpectrumPoint > ss_points;

        Plot * plot;
        QwtPlotCurve * curve;

        void add( QPointF point )
        {
            SuperSpectrumPoint ssp;
            ssp.set( point );

            ss_points.append( ssp );

            qSort(
                    ss_points.begin( ),
                    ss_points.end( ),
                    sort_ss_peak_by_mass
                 );
        }

        void fix( int tolerance )
        {
            SuperSpectrumPoint ss_p1, ss_p2, ss_merged;
            QListIterator < SuperSpectrumPoint > ss_it( ss_points );

            while ( ss_it.hasNext( ) )
            {
                ss_it.next( );
                if( ss_it.hasNext( ) )
                {
                    ss_p1 = ss_it.peekPrevious( );
                    ss_p2 = ss_it.peekNext( );

                    if ( ( ss_p1.point( ).x( ) + tolerance ) > ss_p2.point( ).x( ) )
                    {
                        ss_merged.set( QPointF(
                                    ( ss_p1.point( ).x( ) + ss_p2.point( ).x( ) ) / 2,
                                    ( ss_p1.point( ).y( ) + ss_p2.point( ).y( ) ) / 2
                                      ), ss_p1.presence( ) + ss_p2.presence( ) );

                        ss_points.removeAll( ss_p1 );
                        ss_points.removeAll( ss_p2 );

                        ss_points.append( ss_merged );

                        qSort(
                                ss_points.begin( ),
                                ss_points.end( ),
                                sort_ss_peak_by_mass
                             );
                    }
                }
            }
        }

        QVector < QPointF > getPeaks( uint presence = 60 )
        {
            if ( presence > 100 )
                presence =  100;

            presence = qFloor( presence * pk_list / 100 );

            SuperSpectrumPoint ssp;
            QVector < QPointF > points;

            for ( int i = 0; i < ss_points.size( ); i++ )
            {
                ssp = ss_points.at( i );
                if ( ssp.presence( ) > presence )
                    points.append( ssp.point( ) );
            }

            return points;
        }
} SuperSpectrum;

bool sort_peak_by_mass( const QPointF & p1, const QPointF & p2 )
{
    return p1.x( ) < p2.x( );
}

bool max_peak_by_absi( const QPointF & p1, const QPointF & p2 )
{
    return p1.y( ) > p2.y( );
}

bool sort_ss_peak_by_mass( SuperSpectrumPoint & p1, SuperSpectrumPoint & p2 )
{
    return p1.point( ).x( ) < p2.point( ).x( );
}

Application :: Application( ) : MainWindow( ), modemanager( new ModeManager( this ) )
{
    QPixmap * pixmap = new QPixmap( ":/UI/IMAGES/splash.png" );

    QSplashScreen * splash = new QSplashScreen( * pixmap );
    splash -> show( );
    //splash -> showMessage( "Iniciando..." );

    //    QMutex dummy;
    //    dummy.lock( );

    //    QWaitCondition sleep;

    //    // wait a few moment
    //    sleep.wait( & dummy, 2000 );

    StyleSheet * style = new StyleSheet( this );
    style -> load( "default" );

    workpath = QDir :: homePath( ) + "/MS-Analyser";
    if ( ! workpath.exists( ) )
        workpath.mkpath( workpath.path( ) );

    createLayout( );

    //    showMaximized( );
    show( );
    splash -> finish( this );

    // INIT
    selected = 0;
    super_spectrum = new SuperSpectrum;

    db = new Database( "QSQLITE" );
    db -> setDatabaseName( "ms-info-base2" );

    if ( ! db -> open( ) )
    {
        qDebug( ) << db -> lastError( );

        //        QMessageBox :: information( 0, "", db -> lastError( ).text( ) );
    }
}

QWidget * Application :: ui( const QString & name, QWidget * parent = 0 )
{
    QUiLoader loader;

    QFile file( QString( ":/UI/%1.ui" ).arg( name ) );
    file.open( QFile :: ReadOnly );
    QWidget * widget = loader.load( & file, parent );
    file.close( );

    return widget;
}

Mode * Application :: mode( const QString & name, QWidget * content )
{
    if ( ! modes.contains( name.toLower( ) ) )
    {
        modes[ name.toLower( ) ] = modemanager -> insert(
                name,
                ( content ) ? content : new QWidget( this ),
                QIcon( ":/UI/IMAGES/mode_" + name + ".png" )
                );
    }

    return modes[ name.toLower( ) ];
}

void Application :: createLayout( )
{
    setMinimumSize( 700, 400 );

    createWelcomeLayout( );
    createProjectLayout( );
    createPeaklistLayout( );
    createAnalyzerLayout( );
    createClusterLayout( );
    createHelpLayout( );

    connect( modemanager, SIGNAL( modeChanged( int ) ), this, SLOT( modeChanged( int ) ) );

    //    QSqlError err;
    //    db = new Database( "QSQLITE" );
    //    db -> setDatabaseName( "ms-info-base" );
    //    if ( ! db -> open( ) )
    //        err = db -> lastError( );

    //    qDebug( ) << err;

    //    db -> query( "select * from Movies" );

    QSqlError err;
    QSqlDatabase db1 = QSqlDatabase :: addDatabase( "QSQLITE", "MS-INFO" );
    db1.setDatabaseName( "ms-info-base2" );
    if ( ! db1.open( ) )
    {
        err = db1.lastError( );
        qDebug( ) << err;

        db1 = QSqlDatabase( );
        QSqlDatabase :: removeDatabase( "MS-INFO" );
    }

    QSqlQuery q("", db1);

    //    q.exec( "drop table info" );
    q.exec( "CREATE TABLE info ( peaklist_id varchar(255) NULL, time int NULL, organismo_genero varchar(255) NULL, organismo_especie varchar(255) NULL, organismo_estirpe varchar(255) NULL, organismo_identificacao_taxonomica varchar(255) NULL, experimento_origem varchar(255) NULL, experimento_temperatura varchar(255) NULL, experimento_tempo_crescimento varchar(255) NULL, experimento_data varchar(255) NULL, amostra_meio_cultura varchar(255) NULL, amostra_tempo_cultivo varchar(255) NULL, amostra_temperatura_cultivo varchar(255) NULL, amostra_matriz varchar(255) NULL, amostra_processamento varchar(255) NULL )" );
    //    q.exec( "insert into info ( organismo_genero ) values( 'test2' )" );
    //    q.exec( "delete from info" );

    //    db = new Database( "QSQLITE" );
    //    db -> setDatabaseName( "ms-info-base2" );
    //    if ( ! db -> open( ) )
    //        err = db -> lastError( );

    //    qDebug( ) << err;

    //    QSqlQuery * q2 = new QSqlQuery( ( * db ) );
    //    q2 -> exec( "insert into info ( organismo_genero ) values( 'test3' )" );
    //    qDebug( ) << q2 -> lastError( );

    //    q2->prepare( "insert into info ( organismo_genero ) values( :organismo_genero )" );
    //    q2->bindValue( ":organismo_genero", "test4" );
    //    q2->exec( );
    //    qDebug( ) << q2 -> lastError( );



    //    q.exec("drop table Movies");
    //    q.exec("drop table Names");
    //    q.exec("create table Movies (id integer primary key, Title varchar, Director varchar, Rating number)");
    //    q.exec("insert into Movies values (5, 'Metropolis', 'Fritz Lang', '8.4')");
    //    q.exec("insert into Movies values (6, 'Nosferatu, eine Symphonie des Grauens', 'F.W. Murnau', '8.1')");
    //    q.exec("insert into Movies values (7, 'Bis ans Ende der Welt', 'Wim Wenders', '6.5')");
    //    q.exec("insert into Movies values (8, 'Hardware', 'Richard Stanley', '5.2')");
    //    q.exec("insert into Movies values (9, 'Mitchell', 'Andrew V. McLaglen', '2.1')");
    //    q.exec("create table Names (id integer primary key, Firstname varchar, Lastname varchar, City varchar)");
    //    q.exec("insert into Names values (0, 'Sala', 'Palmer', 'Morristown')");
    //    q.exec("insert into Names values (1, 'Christopher', 'Walker', 'Morristown')");
    //    q.exec("insert into Names values (2, 'Donald', 'Duck', 'Andeby')");
    //    q.exec("insert into Names values (3, 'Buck', 'Rogers', 'Paris')");
    //    q.exec("insert into Names values (4, 'Sherlock', 'Holmes', 'London')");

}

//void Application :: createMode( )

void Application :: createWelcomeLayout( )
{
    mode( "Welcome" ) -> enable( );
}

void Application :: createProjectLayout( )
{
    mode( "Project", ui( "settings" ) ) -> enable( );
}

void Application :: createPeaklistLayout( )
{
    QSplitter * pk_splitter = new QSplitter( Qt :: Horizontal );
    pk_splitter -> setHandleWidth( 1 );
    pk_splitter -> setSizePolicy( QSizePolicy :: Minimum, QSizePolicy :: Minimum );

    mode( "Peaklist", pk_splitter ) -> enable( );

    QWidget * list,
        * content;

    pk_splitter -> addWidget(
            ( list = ui( "peaklist_list" ) )
            );

    pk_splitter -> addWidget(
            ( content = ui( "peaklist_content" ) )
            );

    QGridLayout * list_layout = ( QGridLayout * ) list -> layout( );
    list_layout -> addWidget(
            ( pk_panel = new ListWidget( this ) ), list_layout -> rowCount( ), 0, list_layout -> rowCount( ), list_layout -> columnCount( )
            );
    //    pk_panel -> verticalScrollBar( );
    //    pk_panel -> setSizePolicy( QSizePolicy :: Expanding, QSizePolicy :: Expanding );

    tables_plots_layout = ( QGridLayout * ) ( content -> findChild< QWidget * >( "pk_tables_plots" ) ) -> layout( );
    plots_layout = ( QGridLayout * ) ( content -> findChild< QWidget * >( "pk_plots" ) ) -> layout( );
    table_layout = ( QGridLayout * ) ( content -> findChild< QWidget * >( "pk_tables" ) ) -> layout( );
    proteins_layout = ( QGridLayout * ) ( content -> findChild< QWidget * >( "pk_proteins" ) ) -> layout( );
    groups_layout = ( QGridLayout * ) ( content -> findChild< QWidget * >( "pk_groups" ) ) -> layout( );
    distance_layout = ( QGridLayout * ) ( content -> findChild< QWidget * >( "pk_distance" ) ) -> layout( );

    plotInterval = new QxtSpanSlider;
    plotInterval->setOrientation( Qt :: Horizontal );

    connect( plotInterval, SIGNAL( spanChanged( int, int ) ), this, SLOT( setPlotInterval( int, int ) ) );

    plots_layout -> addWidget( plotInterval );

    table_distance = new TableView( this );
    distance_layout -> addWidget( table_distance );

    table_protein = new TableView( this );
    proteins_layout -> addWidget( table_protein );

    table_groups = new TableView( this );
    groups_layout -> addWidget( table_groups, 0, 0, 1, 1 );

    Plot * plot_pie_groups = new Plot( this );
    plot_pie_groups -> peakWeigth( 5 );
    plot_pie_groups -> setStyleSheet( "background: #fff;" );
    //    plot_groups -> hide( );
    //    plot_groups -> curve(
    //        points, curves[ item ] -> pen( ).color( )
    //    ) -> attach( plots[ item ] );
    plot_pie_groups -> zoom( );
    plot_pie_groups -> enableAxis( QwtPlot :: yLeft, false );

    //    const QwtScaleMap yMap = plot_pie_groups->canvasMap(QwtPlot::yLeft);

    QRectF rectangle(10.0, 20.0, 80.0, 60.0);
    int startAngle = 30 * 16;
    int spanAngle = 120 * 16;

    QPainter p( plot_pie_groups );
    p.drawPie(rectangle, startAngle, spanAngle);


    groups_layout -> addWidget( plot_pie_groups, 0, 1, 1, 1 );

    histogram_groups = new HistogramPlot( this );
    //    plot_bars_groups -> peakWeigth( 5 );
    //    plot_bars_groups -> setStyleSheet( "background: #fff;" );
    //    plot_groups -> hide( );
    //    plot_groups -> curve(
    //        points, curves[ item ] -> pen( ).color( )
    //    ) -> attach( plots[ item ] );
    //    plot_bars_groups -> zoom( );
    //    plot_bars_groups -> enableAxis( QwtPlot :: yLeft, false );

    groups_layout -> addWidget( histogram_groups, 1, 0, 1, 2 );


    peaklist_info = ui( "peaklist_info" );

    ( ( QGridLayout * )
      ( content -> findChild< QWidget * >( "pk_informations" ) ) -> layout( )
    ) -> addWidget( peaklist_info );

    connect(
            ( QTabWidget * )( content -> findChild< QTabWidget * >( "pk_content_tab" ) ),
            SIGNAL( currentChanged( int ) ),
            this,
            SLOT( peaklist_infotab_changed( int ) )
           ) ;

    //    QListIterator < QLineEdit * > edit_fileds_it( peaklist_info -> findChildren< QLineEdit * >( ) );
    //    while ( edit_fileds_it.hasNext( ) )
    //        connect( edit_fileds_it.next( ), SIGNAL( editingFinished( ) ), this, SLOT( infoChanged( ) ) );

    //    QListIterator < QAbstractSpinBox * > spin_fileds_it( peaklist_info -> findChildren< QAbstractSpinBox * >( ) );
    //    while ( spin_fileds_it.hasNext( ) )
    //        connect( spin_fileds_it.next( ), SIGNAL( editingFinished( ) ), this, SLOT( infoChanged( ) ) );

    //    QListIterator < QComboBox * > cb_fileds_it( peaklist_info -> findChildren< QComboBox * >( ) );
    //    while ( cb_fileds_it.hasNext( ) )
    //        connect( cb_fileds_it.next( ), SIGNAL( currentIndexChanged(int) ), this, SLOT( infoChanged( ) ) );

    //    connect( peaklist_info -> findChild< QPushButton *>( "save_info" ), SIGNAL( clicked( ) ), this, SLOT( infoChanged( ) ) );

    //    connect( pk_panel, SIGNAL( currentTextChanged( QString ) ), this, SLOT( pk_panel_changed( QListWidgetItem * ) ) );
    connect( pk_panel, SIGNAL( itemClicked( QListWidgetItem * ) ), this, SLOT( pk_panel_clicked( QListWidgetItem * ) ) );
    connect( pk_panel, SIGNAL( customContextMenuRequested( QPoint ) ), this, SLOT( pk_context_menu( QPoint ) ) );

    connect(
            list -> findChild< QPushButton * >( "pk_bt_peaklist" ),
            SIGNAL( clicked( ) ),
            this,
            SLOT( pk_load_file( ) )
           );

    connect(
            list -> findChild< QPushButton * >( "pk_bt_replica" ),
            SIGNAL( clicked( ) ),
            this,
            SLOT( pk_load_replica( ) )
           );

    connect(
            list -> findChild< QPushButton * >( "pk_bt_analyzer_peaklist" ),
            SIGNAL( clicked( ) ),
            this,
            SLOT( pk_analyzer( ) )
           );

    QPushButton * db_button = ( list -> findChild < QPushButton * > ( "pk_bt_analyzer_peaklist" ) );

    QMenu * db_menu = new QMenu( this );
    QMenu * db_menu_add = db_menu ->  addMenu( "Add" );
    QMenu * db_menu_search = db_menu ->  addMenu( "Search" );

    db_menu_add -> setObjectName( "db_menu_add" );
    db_menu_search -> setObjectName( "db_menu_search" );

    connect( db_menu_search, SIGNAL( triggered( QAction * ) ), SLOT( searchDatabase( QAction * ) ) );
    connect( db_menu_add, SIGNAL( triggered( QAction * ) ), SLOT( addDatabase( QAction * ) ) );

    if ( ! workpath.exists( "databases" ) )
        workpath.mkdir( "databases" );

    workpath.cd( "databases" );

    QStringList databases = workpath.entryList( QDir :: Dirs | QDir::NoDotAndDotDot );
    for ( int i = 0; i < databases.size( ); i++ )
    {
        db_menu_add -> addAction( databases.at( i ) );
        db_menu_search -> addAction( databases.at( i ) );
    }

    workpath.cdUp( );

    db_menu_add -> addSeparator( );
    db_menu_add -> addAction( tr( "New Database" ) ) -> setProperty( "action", "new_database" );

    db_button -> setMenu( db_menu );
    //    db_button -> setEnabled( true );

    connect(
            list -> findChild< QPushButton * >( "pk_bt_info" ),
            SIGNAL( clicked( ) ),
            this,
            SLOT( export_files( ) )
           );

    connect(
            list -> findChild< QPushButton * >( "pk_bt_clean" ),
            SIGNAL( clicked( ) ),
            this,
            SLOT( pk_clean( ) )
           );

    //
    mode( "Peaklist" ) -> current( );
}

void Application :: export_files( void )
{
    QProcess :: startDetached( QCoreApplication::applicationDirPath() + "/zip.sh" );
    QString file = QFileDialog::getSaveFileName(this, tr("Save File"), workpath.filePath( "files.zip" ), tr("ZIP (*.zip)"));

    if ( ! file.isEmpty() )
    {
        QFile fp( workpath.filePath( "files.zip" ) );
        fp.copy( file );
        //        if( fp.copy( file ) )
        //            QMessageBox::information(this,tr(""),tr("Saved"));
    }
}


void Application :: searchDatabase( QAction * action )
{
}

void Application :: addDatabase( QAction * action )
{
    if ( action -> property( "action" ).toString( ) == "new_database" )
    {
        workpath.cd( "databases" );

        bool ok;
        QString text = QInputDialog::getText(this, tr("QInputDialog::getText()"),
                tr("User name:"), QLineEdit::Normal, "", &ok
                );

        if ( ok && ! text.isEmpty() && ! workpath.exists( text ) )
        {
            workpath.mkdir( text );

            QStringList databases;
            QMenu * menu_search = ( qFindChild< QMenu * >( this, "db_menu_search" ) );
            QMenu * menu_add = ( qFindChild< QMenu * >( this, "db_menu_add" ) );

            QList < QAction * > actions = menu_add -> actions( );
            actions.removeLast( );
            actions.removeLast( );

            databases << text;
            for ( int i = 0; i < actions.size( ); i++ )
                databases << actions.at( i ) -> text( );

            menu_add -> clear( );
            menu_search -> clear( );

            databases.sort( );

            for ( int i = 0; i < databases.size( );  i++ )
            {
                menu_add -> addAction( databases[ i ] );
                menu_search -> addAction( databases[ i ] );
            }

            menu_add -> addSeparator( );
            menu_add -> addAction( tr( "New Database" ) ) -> setProperty( "action", "new_database" );
        }

        workpath.cdUp( );
    }
    else
    {
        QMapIterator < QString, Peaklist * > pk_it( peaklists );
        int count = 0;

        while ( pk_it.hasNext( ) )
        {
            pk_it.next( );

            if ( ! pk_it.value( ) -> actived( ) )
                continue;

            count++;

            QFile::copy(
                    workpath.filePath( "peakset/" + pk_it.key( ) + ".xml" ),
                    workpath.filePath( "databases/" + action -> text( ) + "/" + pk_it.key( ) + ".xml" )
                   );
        }

        if ( count )
            QMessageBox :: information( this, "", "Spectrums were added to database '" + action -> text( ) + "'" );
    }
}

void Application :: peaklist_infotab_changed( int current )
{
    //    QMessageBox :: information( this, "", QString( "%1" ).arg( tab ) );

    static QString last_tab = "", plots_in = "", tables_in = "";
    QString current_tab;

    QTabWidget * tab = qFindChild< QTabWidget * >( this, "pk_content_tab" );

    current_tab = tab -> widget( current ) -> objectName( );

    QMapIterator < QString, Peaklist * > pk_it( peaklists );

    //    qDebug( ) << current_tab;

    while ( pk_it.hasNext( ) )
    {
        pk_it.next( );

        //        qDebug( ) << pk_it.key( );

        if ( current_tab != last_tab )
        {
            if ( current_tab == "pk_tables" )
            {
                table_layout->addWidget( tables[ pk_it.key( ) ] );
                tables_in = "tables";
            }

            if ( current_tab == "pk_plots" )
            {
                plots_layout->addWidget( plots[ pk_it.key( ) ] );
                plots_in = "plots";
            }

            if ( current_tab == "pk_tables_plots" )
            {
                //                if ( tables_in != "tables" )
                tables_plots_layout -> addWidget( plots[ pk_it.key( ) ], tables_plots_layout -> rowCount( ), 0 );

                //                if ( plots_in != "plots" )
                tables_plots_layout -> addWidget( tables[ pk_it.key( ) ], tables_plots_layout -> rowCount( ) - 1, 1 );

                tables_in = plots_in = "tables_plots";
            }

            if ( current_tab == "pk_proteins" )
            {
                distance_table( );

                break;
            }
        }
    }

    last_tab = tab -> widget( current ) -> objectName( );
}

void Application :: distance_table( )
{
    table_distance -> clear( );
    table_groups -> clear( );

    QStringList h_labels, v_labels;
    QMapIterator < QString, Peaklist * > pk_it( peaklists );

    QVector< QString > leaves;
    std::vector< std::string > leaves_;

    int count = 0;
    while ( pk_it.hasNext( ) )
    {
        pk_it.next( );

        if ( ! pk_it.value( ) -> actived( ) )
            continue;

        count++;

        //        h_labels << pk_panel_itens[ pk_it.key( ) ] -> text( );
        h_labels << QString( "%1").arg( count );
        v_labels << QString( "( %1 ) %2").arg( count ).arg( pk_panel_itens[ pk_it.key( ) ] -> text( ) );

        leaves.push_back( pk_panel_itens[ pk_it.key( ) ] -> text( ) );
        leaves_.push_back( pk_panel_itens[ pk_it.key( ) ] -> text( ).toStdString( ) );
    }

    dendogram.clear( );

    pk_it.toFront( );
    QVector < QVector < qreal > > matrix = distance( pk_it );

    // Copy distance matrix to double**
    double** distmatrix = new double*[ matrix.size( ) ];

    QFile distance_fp( workpath.filePath( "distance.txt") );
    distance_fp.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream distance_out(&distance_fp);
    distance_out << v_labels.join( "," ) << "\n";

    int i;
    for ( i = 0; i < matrix.size( ); i++ )
    {
        distmatrix[ i ] = new double[ matrix.size( ) ];

        for ( int j = 0; j < matrix.size( ); j++ )
        {
            if ( j < i )
            {
                distance_out << QString( "%1" ).arg( matrix[ i ][ j ] );
                table_distance -> setCell( i, j,
                        QString :: number(
                            QString( "%1" ).arg( matrix[ i ][ j ] ).toFloat( )
                            )
                        );
            }
            if ( j < matrix.size( ) - 2 )
                distance_out << ",";

            distmatrix[ i ][ j ]= matrix[ i ][ j ];
        }

        distance_out << "\n";
    }

    QList< QRadioButton * > clust = ( mode( "Project" ) -> content( ) -> findChildren< QRadioButton *>( QRegExp( "clust_*" ) ) );
    for ( int i = clust.size( ); i > 0; i-- )
        if ( ! clust[ i - 1 ] -> isChecked( ) )
            //        {
            clust.removeAt( i - 1 );
    //        }

    Node * nodes = treecluster(
            matrix.size( ),
            0, 0, 0, 0, 0, 0,
            clust[ 0 ]-> shortcut( ).toString( ).toLower( ).at( 0 ).toAscii( ),
            distmatrix
            );

    QFile file( workpath.filePath( "nodes.txt") );
    QFile leaf( workpath.filePath( "leaf.txt") );

    int left, right;

    qreal cutoff = ( qFindChild< QDoubleSpinBox * >( this, "cutoffSpinBox" ) )->value();

    if ( file.open(QIODevice::WriteOnly | QIODevice::Text) && leaf.open(QIODevice::WriteOnly | QIODevice::Text) )
    {
        QTextStream out(&file);
        QTextStream out_1(&leaf);

        out << "Node\tItem 1\tItem 2\tDistance\n";

        pk_it.toFront( );
        while ( pk_it.hasNext( ) )
        {
            pk_it.next( );

            if ( ! pk_it.value( ) -> actived( ) )
                continue;

            out_1 << pk_panel_itens[ pk_it.value( ) -> getInfo( )[ "spectrumid" ] ] -> text( ) << "\n";
        }

        std::vector< theplu::speclust::TreeNode > nodes_;

        //        QVector < QVector < int > > groups;
        QVector < Node > _groups;

        for ( int i = 0; i < matrix.size( ) - 1; i++ )
        {
            theplu::speclust::TreeNode tn(nodes[i].right, nodes[i].left, nodes[i].distance);
            //            std::cout << tn.distance() << " " << tn.i();
            nodes_.push_back( tn );

            //            qDebug( ) << -i-1 << '\t' << nodes[i].left << '\t' <<  nodes[i].right << '\t' << nodes[i].distance;
            out << -i-1 << '\t' << nodes[i].left << '\t' <<  nodes[i].right << '\t' << nodes[i].distance << '\n';

            _groups.append( nodes[ i ] );
        }

        QVector < QSet < int > > groups;
        QSet < int > set;
        int j;

        for ( int i = 0; i < _groups.count( ); i++ )
        {
            set.clear( );

            if ( ! ( _groups[ i ].distance < cutoff ) )
            {
                if ( ! ( _groups[ i ].left < 0 ) )
                {
                    set << _groups[ i ].left;
                    groups.append( set );
                }

                if ( ! ( _groups[ i ].right < 0 ) )
                {
                    set << _groups[ i ].right;
                    groups.append( set );
                }
            }
            else
            {
                if ( ! ( _groups[ i ].left < 0 || _groups[ i ].right < 0 ) )
                {
                    set << _groups[ i ].left << _groups[ i ].right;
                    groups.append( set );
                }
                else
                {
                    if ( _groups[ i ].left < 0 && ! ( _groups[ i ].right < 0 ) )
                    {
                        j = ( -_groups[ i ].left - 1 );
                        while ( _groups[ j ].left < 0 || _groups[ j ].right < 0 )
                        {
                            j = qMin( _groups[ j ].left, _groups[ j ].right );
                            j = -j - 1;
                        }

                        for ( int k = 0; k < groups.count( ); k++ )
                            if ( groups[ k ].contains( _groups[ j ].left ) )
                            {
                                groups[ k ].insert( _groups[ i ].right );
                            }
                    }

                    if ( _groups[ i ].right < 0 && ! ( _groups[ i ].left < 0 ) )
                    {
                        j = ( -_groups[ i ].right - 1 );
                        while ( _groups[ j ].right < 0 || _groups[ j ].left < 0 )
                        {
                            j = qMin( _groups[ j ].right, _groups[ j ].left );
                            j = -j - 1;
                        }

                        for ( int k = 0; k < groups.count( ); k++ )
                            if ( groups[ k ].contains( _groups[ j ].right ) )
                            {
                                groups[ k ].insert( _groups[ i ].left );
                            }
                    }

                    if ( _groups[ i ].left < 0 && _groups[ i ].right < 0 )
                    {
                        int j1, j2, k1, k2;

                        j1 = ( -_groups[ i ].left - 1 );
                        while ( _groups[ j1 ].left < 0 && _groups[ j1 ].right < 0 )
                        {
                            j1 = ( -_groups[ j1 ].left - 1 );
                        }

                        j2 = ( -_groups[ i ].right - 1 );
                        while ( _groups[ j2 ].left < 0 && _groups[ j2 ].right < 0 )
                        {
                            j2 = ( -_groups[ j2 ].right - 1 );
                        }

                        for ( k1 = 0; k1 < groups.count( ); k1++ )
                            if ( groups[ k1 ].contains( qMax( _groups[ j1 ].left, _groups[ j1 ].right ) ) )
                            {
                                break;
                            }

                        for ( k2 = 0; k2 < groups.count( ); k2++ )
                            if ( groups[ k2 ].contains( qMax( _groups[ j2 ].left, _groups[ j2 ].right ) ) )
                            {
                                break;
                            }

                        groups[ k1 ] += groups[ k2 ];
                        groups.remove( k2 );
                    }
                }
            }
        }

        if ( nodes_.size( ) )
        {
            theplu::speclust::DrawTree drawtree(nodes_,leaves_,*painter);
            drawtree.make_picture( "tree.ps" );
            painter -> repaint( );
        }

        QFile groups_fd( workpath.filePath( "groups.txt") );
        if ( groups_fd.open( QIODevice::WriteOnly | QIODevice::Text ) )
        {
            histogram_groups -> detachItems( );

            QStringList groups_label;
            QTextStream groups_out( & groups_fd );
            int _item;

            groups_out << "# MS-Analyser version 1.0\n" << "#\n";

            QVector < double > group;

            for ( int i = 0; i < groups.count( ); i++ )
            {
                groups_out << "group_" << i << "\t" << groups[ i ].count( ) << "\t";
                groups_label << QString( "group_%1" ).arg( i );

                _item = groups[ i ].count( );
                group.append(  _item );

                foreach ( int item, groups[ i ] )
                {
                    --_item;
                    groups_out << leaves[ item ] << ( _item ? "," : "" );
                    table_groups -> setCell( _item, i, leaves[ item ] );
                }


                groups_out << "\n";
            }

            //group.toStdVector( );
            Histogram *histogramJune = new Histogram("Summer", Qt::red);

            histogramJune -> setValues( group );
            histogramJune -> attach( histogram_groups );

            histogram_groups->setAxisScale( QwtPlot::xBottom, 0, group.count( ), 1 );

            //                group.clear( );

            table_groups->setHLabels( groups_label );
        }

        groups_fd.close( );
    }

    file.close( );
    leaf.close( );

    QProcess :: startDetached( QCoreApplication::applicationDirPath() + "/convert.sh" );

    free(nodes);

    table_distance -> resizeColumnsToContents( );

    table_distance -> setHLabels( h_labels );
    table_distance -> setVLabels( v_labels );

    using namespace theplu::speclust;

    std::vector < Spectrum * > spectra;
    pk_it.toFront( );
    while ( pk_it.hasNext( ) )
    {
        pk_it.next( );

        if ( ! pk_it.value( ) -> actived( ) )
            continue;

        Spectrum * s = new Spectrum( pk_panel_itens[ pk_it.value( ) -> getInfo( )[ "spectrumid" ] ]->text( ).toStdString( ) );

        QList < QHash < QString, QString > > mass = pk_it.value( ) -> getPeaks( );

        for ( size_t i = 0; i < mass.size( ); i++ )
        {
            Peak * p = new Peak( s, mass[ i ][ "mass" ].toFloat( ) );
            s -> push_back( p );
        }

        spectra.push_back( s );
    }

    if ( selected )
    {
        // sort spectra in name order (alphabetically).
        std::sort(spectra.begin(), spectra.end(), NameOrder());

        // pairwise must be done before consensus and peaksets
        theplu::speclust::pairwise(spectra, cutoff );
        theplu::speclust::consensus( spectra, workpath.filePath( "table.txt" ).toStdString( ) );

        QFile consensus( workpath.filePath( "table.txt" ) );

        consensus.open( QFile :: ReadOnly );
        //        if ( consensus.open( QFile :: ReadOnly ) )
        QTextStream in( & consensus );
        QList< QStringList > lists;
        QString line;

        while ( ! ( line = in.readLine( ) ).isNull( ) )
        {
            lists << line.split("\t");
        }

        table_protein -> clear( );
        table_protein -> setHLabels( lists.at( 0 ) );

        QStandardItem * cell;
        for ( int row = 1; row < lists.size(); ++row )
        {
            for ( int column = 0; column < lists[row].size(); ++column )
            {
                cell = table_protein -> setCell( row - 1, column, lists[ row ][ column ] );
                if ( column < 5 )
                    cell -> setBackground( QBrush( QColor( 200, 200, 150 ) ) );
                else
                {
                    if ( row % 2 == 1 )
                        cell -> setBackground( QBrush( QColor( 200, 200, 200 ) ) );
                    //                        else
                    //                            cell -> setBackground( QBrush( QColor( 255, 0, 0 ) ) );
                }
            }
        }

        QFile pairwise( "pairwise.txt" );
        pairwise.remove( );
    }
}

QVector < QVector < qreal > > Application :: distance( QMapIterator < QString, Peaklist * > pk_it )
{
    QMap < QString, Peaklist * > pk;

    while ( pk_it.hasNext( ) )
    {
        pk_it.next( );

        if ( ! pk_it.value( ) -> actived( ) )
            continue;

        pk[ pk_it.key( ) ] = pk_it.value( );
    }

    QVector < QVector < qreal > > _return = distance( pk );
    return _return;
}

QVector < QVector < qreal > > Application :: distance( QMap < QString, Peaklist * > pk )
{
    QList < Peaklist * > _pk;
    QList < QHash < QString, QString > > pk_1_peaks, pk_2_peaks;

    //    qreal dist = 0, dist_base = 0, min_dist = ( qreal ) NULL;
    //    int dist_x = 0, dist_y = 0;

    _pk = pk.values( );

    QVector < QVector < qreal > > matrix( _pk.size( ), QVector < qreal >( _pk.size( ), 0.0 ) );

    if ( ! pk.size( ) )
        return matrix;

    QVector < QVector < qreal > > peakset( _pk.size( ) );
    QVector < qreal > set;
    std::vector< std::vector<double> > _distance;
    _distance.resize( _pk.size( ) );

    for ( int pk_1 = 0; pk_1 < _pk.size( ); pk_1++ )
    {
        pk_1_peaks = _pk.at( pk_1 ) -> getPeaks( );

        set.resize( pk_1_peaks.size( ) );

        for ( int i = 0; i < pk_1_peaks.size( ); i++ )
        {
            set[ i ] = pk_1_peaks[ i ][ "mass" ].toFloat( );
        }

        //        qDebug( ) << set;
        peakset[ pk_1 ] = set;
    }

    theplu::speclust::Distance* metric=NULL;
    metric = new theplu::speclust::DistancePearson;

    std::vector<std::vector<double> > peaksets2;
    peaksets2.resize( _pk.size( ) );

    for ( int i = 0; i < peakset.size( ); i++ )
    {
        peaksets2[ i ] = peakset[ i ].toStdVector( );
        _distance[ i ].resize( _pk.size( ) );
    }

    assert(metric);

    qreal sigma = ( qFindChild< QSpinBox * >( this, "toleranceSpinBox" ) )->value();
    //    qDebug( ) << sigma;
    calculate_distance(_distance, peaksets2, sigma, *metric);
    delete metric;

    //    std::cout << _distance << endl;
    QVector < QVector < qreal > > distance;
    distance.resize( _distance.size( ) );

    for ( unsigned int i = 0; i < _distance.size( ); i++ )
    {
        matrix[ i ] = QVector < qreal > :: fromStdVector( _distance[ i ] );
    }

    //    qDebug( ) << distance;

    //    for ( int pk_1 = 0; pk_1 < _pk.size( ); pk_1++ )
    //    {
    //        pk_1_peaks = _pk.at( pk_1 ) -> getPeaks( );

    //        for ( int pk_2 = pk_1; pk_2 < _pk.size( ); pk_2++ )
    //        {
    //            pk_2_peaks = _pk.at( pk_2 ) -> getPeaks( );

    //            dist = 0;

    //            for ( int i = 0; i < pk_1_peaks.size( ); i++ )
    //                for ( int j = 0; j < pk_2_peaks.size( ); j++ )
    //                {
    //                    dist += sqrt(
    //                        pow( pk_1_peaks[ i ][ "mass" ].toFloat( ) - pk_2_peaks[ j ][ "mass" ].toFloat( ), 2 ) +
    //                        pow( pk_1_peaks[ i ][ "absi_rel" ].toFloat( ) - pk_2_peaks[ j ][ "absi_rel" ].toFloat( ), 2 )
    //                    );
    //                }

    //            dist /= ( pk_1_peaks.size( ) * pk_2_peaks.size( ) );

    //            if ( pk_2 == pk_1 )
    //                dist_base = dist;

    //            matrix[ pk_1 ][ pk_2 ] = matrix[ pk_2 ][ pk_1 ] = log( qFabs( dist - dist_base ) );

    //            if ( pk_2 != pk_1 )
    //            {
    //                if ( min_dist == ( qreal ) NULL )
    //                {
    //                    min_dist = matrix[ pk_1 ][ pk_2 ];
    //                    dist_x = pk_1;
    //                    dist_y = pk_2;
    //                }
    //                else
    //                {
    //                    min_dist = qMin( min_dist, matrix[ pk_1 ][ pk_2 ] );
    //                    if ( min_dist == matrix[ pk_1 ][ pk_2 ] )
    //                    {
    //                        dist_x = pk_1;
    //                        dist_y = pk_2;
    //                    }
    //                }
    //            }
    //        }
    //    }

    //    QHash<QString,QString> dng;
    //    dng[ pk.key( _pk.value( dist_x ) ) ] = pk.key( _pk.value( dist_y ) );
    //    dendogram.append( dng );

    //    switch ( pk.size( ) )
    //    {
    //        case 1 :
    //        case 2 :
    ////            qDebug( ) << dendogram;
    ////            return matrix;
    //            break;
    //        default :
    //            pk[ QString( "-%1" ).arg( dendogram.size( ) ) ] = Peaklist::New( _pk.value( dist_x ), _pk.value( dist_y ) );

    //            pk.remove( pk.key( _pk.value( dist_x ) ) );
    //            pk.remove( pk.key( _pk.value( dist_y ) ) );

    //            Peaklist * at_x = _pk.at( dist_x );
    //            Peaklist * at_y = _pk.at( dist_y );

    //            _pk.removeAll( at_x );
    //            _pk.removeAll( at_y );

    ////            if ( pk.size( ) == 1 )
    ////            {
    ////                dng.clear( );
    ////                dng[ QString( "-%1" ).arg( dendogram.size( ) ) ] = pk.key( _pk.first( ) );
    ////                dendogram.append( dng );

    ////                qDebug( ) << dendogram;
    ////                return matrix;
    ////                break;
    ////            }

    ////            pk[ QString( "-%1" ).arg( dendogram.size( ) ) ] = Peaklist::New( );

    //            distance( pk );
    //            break;
    //    }

    //    qDebug( ) << min_dist << pk.key( _pk.value( dist_x ) ) << pk.key( _pk.value( dist_y ) );

    return matrix;
}

void Application :: createAnalyzerLayout( )
{
    QSplitter * splitter = new QSplitter;
    splitter -> setHandleWidth( 1 );

    mode( "Analyzer", splitter/*plot*/ )
        -> enable( )
        -> content( );

    plot = new Plot( this );
    plot -> setStyleSheet( "background: #fff;" );
    //    plot -> hide( );

    //    plot -> axisWidget( QwtPlot :: xBottom  ) -> setTitle( "M/Z" );
    //    qDebug( ) << plot -> axisWidget( QwtPlot :: xBottom  ) ;

    //    QListView * pk_panel = new QListView;
    //    pk_panel -> setModel( this -> pk_panel -> model( ) );

    //    splitter -> addWidget( pk_panel );
    splitter -> addWidget( plot );

    //    new QLabel( "Column Weigth", plot );

    QSlider * slider = new QSlider( plot );
    slider -> setOrientation( Qt :: Horizontal );
    slider -> setRange( 1, 5 );
    slider -> setMinimumWidth( 250 );
    slider -> setTickInterval( 1 );
    slider -> setTickPosition( QSlider :: TicksBothSides );
    slider -> setToolTip( tr( "Change the peak weigth." ) );
    slider -> setSliderPosition( 2 );

    connect( slider, SIGNAL( valueChanged( int ) ), this, SLOT( plotPeakWeigth( int ) ) );

    QCheckBox * show_spectrum = new QCheckBox( "Show spectrum", plot );
    show_spectrum -> setChecked( true );
    show_spectrum -> move( ( ( int ) ( slider -> size( ).width( ) * 1.1 ) ), show_spectrum -> pos( ).y( ) );

    this -> show_spectrum = show_spectrum -> isChecked( );

    connect( show_spectrum, SIGNAL( stateChanged( int ) ), this, SLOT( plotShowSpectrum( int ) ) );
}

void Application :: createClusterLayout( )
{
    QSplitter * splitter = new QSplitter;
    splitter -> setHandleWidth( 1 );

    mode( "Cluster", splitter )
        -> enable( )
        -> content( );

    painter = new Painter;
    //    img->line( QLineF( 10.0, 80.0, 90.0, 20.0 ) );

    //    QLabel * imageLabel = new QLabel;
    //    imageLabel->setBackgroundRole(QPalette::Base);
    //    imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    //    imageLabel->setScaledContents(true);


    //    QPainter * image = new QPainter( img );
    //    image->drawLine( QLineF( 10.0, 80.0, 90.0, 20.0 ) );


    //    QPainter painter( img );
    //    painter.setPen( Qt::blue );
    //    painter.setFont( QFont("Arial",30) );
    //    painter.drawText( rect(), Qt::AlignCenter, "Qt" );


    //    QScrollArea * scrollArea = new QScrollArea;
    //    scrollArea->setBackgroundRole(QPalette::Dark);
    //    scrollArea->setWidget(image);

    splitter -> addWidget( painter );
}

void Application :: plotPeakWeigth( int value )
{
    QHashIterator < QString, QwtPlotCurve * > curves_it( curves );

    while ( curves_it.hasNext( ) )
    {
        curves_it.next( );
        QPen pen = curves_it.value( ) -> pen( );
        pen.setWidth( value );

        curves_it.value( ) -> setPen( pen );
    }

    plot -> peakWeigth( value );
}

void Application :: plotShowSpectrum( int value )
{
    show_spectrum = value && true;

    QHashIterator < QString, QwtPlotCurve * > curves_it( curves_fid );

    while ( curves_it.hasNext( ) )
    {
        curves_it.next( );

        if ( show_spectrum && peaklists[ curves_it.key( ) ] -> actived( ) )
        {
            if ( ! peaklists[ curves_it.key( ) ] -> reflex( ) )
                curves_it.value( ) -> show( );
            else
                curves_fid_reflex[ curves_it.key( ) ] -> show( );
        }
        else
        {
            curves_it.value( ) -> hide( );
            curves_fid_reflex[ curves_it.key( ) ] -> hide( );
        }
    }
}

void Application :: createHelpLayout( )
{
    mode( "Help" ) -> enable( );
}

void Application :: modeChanged( int mode )
{
    QList < int > size = ( ( QSplitter * ) pk_panel -> parentWidget( ) -> parentWidget( ) ) -> sizes( );

    if ( this -> mode( "Analyzer" ) -> index == mode )
    {
        //        QList < int > size = ( ( QSplitter * ) this -> mode( "Peaklist" ) -> content( ) ) -> sizes( );

        ( ( QSplitter * ) this -> mode( "Analyzer" ) -> content( ) )
            -> insertWidget( 0, pk_panel -> parentWidget( ) );

        ( ( QSplitter * ) pk_panel -> parentWidget( ) -> parentWidget( ) ) -> setSizes( size );

        //        QPushButton * button = ( qFindChild< QPushButton * >( this, "pk_bt_analyzer_peaklist" ) );
        //        button -> setText( tr( "Peaklist") );

        //        connect( button, SIGNAL( clicked( ) ), this, SLOT( pk_analyzer( ) ) );
    }

    if ( this -> mode( "Peaklist" ) -> index == mode )
    {
        QStatusBar * statusBar = this -> mode( "Peaklist" ) -> fancy -> statusBar( );
        //        statusBar-> showMessage( tr( "..." ) );

        //        QList < int > size = ( ( QSplitter * ) this -> mode( "Analyzer" ) -> content( ) ) -> sizes( );

        ( ( QSplitter * ) this -> mode( "Peaklist" ) -> content( ) )
            -> insertWidget( 0, pk_panel -> parentWidget( ) );

        ( ( QSplitter * ) pk_panel -> parentWidget( ) -> parentWidget( ) ) -> setSizes( size );

        //        QPushButton * button = ( qFindChild< QPushButton * >( this, "pk_bt_analyzer_peaklist" ) );
        //        button -> setText( tr( "Analyzer") );

        //        connect( button, SIGNAL( clicked( ) ), this, SLOT( pk_analyzer( ) ) );
    }

    if ( this -> mode( "Cluster" ) -> index == mode )
    {
        //        QList < int > size = ( ( QSplitter * ) this -> mode( "Analyzer" ) -> content( ) ) -> sizes( );

        ( ( QSplitter * ) this -> mode( "Cluster" ) -> content( ) )
            -> insertWidget( 0, pk_panel -> parentWidget( ) );

        ( ( QSplitter * ) pk_panel -> parentWidget( ) -> parentWidget( ) ) -> setSizes( size );

        //        QPushButton * button = ( qFindChild< QPushButton * >( this, "pk_bt_analyzer_peaklist" ) );
        //        button -> setText( tr( "Analyzer") );

        //        connect( button, SIGNAL( clicked( ) ), this, SLOT( pk_analyzer( ) ) );
    }
}

void Application :: infoChanged( )
{
    QHash < QString, QString > info;

    QListIterator < QLineEdit * > edit_fileds_it( peaklist_info -> findChildren< QLineEdit * >( ) );
    QLineEdit * edit;
    while ( edit_fileds_it.hasNext( ) )
    {
        edit = edit_fileds_it.next( );

        if ( ! edit -> objectName().startsWith( "qt_spinbox" ) )
            info.insert( edit -> objectName( ), edit -> text( ) );
        else
            info.insert( edit -> parentWidget( ) -> objectName( ), ( ( QDoubleSpinBox * ) edit -> parentWidget( ) ) -> cleanText( ) );

        //        info.insert( ( ! ( edit -> objectName().startsWith( "qt_spinbox" ) ) ?
        //                edit -> objectName( ) : edit -> parentWidget( ) -> objectName( )
        //            ),
        //            edit->text()
        //        );
    }

    QListIterator < QComboBox * > cb_fileds_it( peaklist_info -> findChildren< QComboBox * >( ) );
    QComboBox * cb;
    while ( cb_fileds_it.hasNext( ) )
    {
        cb = cb_fileds_it.next( );
        info.insert( cb->objectName( ), cb -> currentText( ) );
    }

    QHashIterator < QString, QString > info_it( info );
    QMapIterator < QString, Peaklist * > pk_it( peaklists );

    while ( pk_it.hasNext( ) )
    {
        pk_it.next( );

        if ( ! pk_it.value( ) -> actived( ) )
            continue;

        db -> prepare(
                QString( "insert into info ( peaklist_id, time, %1 ) values( :peaklist_id, :time, %2 )" )
                .arg( ( ( QStringList ) info.keys( ) ).join( ", " ) )
                .arg( QString( ":" ) + ( ( QStringList ) info.keys( ) ).join( ", :" ) )
                 );

        db -> bind( ":peaklist_id", pk_it.key( ) );
        db -> bind( ":time", QDateTime :: currentMSecsSinceEpoch( ) );

        info_it.toFront( );
        while ( info_it.hasNext( ) )
        {
            info_it.next( );
            db -> bind(
                    info_it.key( ),
                    info_it.value( )
                  );
        }

        db -> query( );
    }


    //    qDebug( ) << "-----------------------------------------------------------";
}

void Application :: createLayout( bool t )
{
    setMinimumSize( 700, 400 );

    // Layout
    QHBoxLayout * main_layout = new QHBoxLayout;//( this );
    main_layout -> setMargin( 0 );
    main_layout -> setSpacing( 0 );

    //    centralWidget( ) -> setLayout( main_layout );

    FancyTabWidget * m_modeStack = new FancyTabWidget(this);
    setCentralWidget( m_modeStack );

    //    main_layout -> addWidget( m_modeStack );

    //    mainPainel = new QWidget( this );
    //    mainPainel -> setObjectName( "MainPainel" );
    //    mainPainel -> setFixedWidth( 70 );
    //    /*mainPainel->setSizePolicy(
    //        QSizePolicy :: Maximum,
    //        QSizePolicy :: Expanding
    //    );*/

    //    //main_layout -> addWidget( mainPainel );//, 0, Qt::AlignLeft );

    //    QPushButton * load_pk = new QPushButton( mainPainel );
    //    load_pk->setIcon( QIcon( ":/UI/IMAGES/peaklist.png" ) );
    //    load_pk -> setToolTip( "Load peaklist" );
    //    load_pk->setGeometry( 20, 20, 20, 20 );

    //    connect( load_pk, SIGNAL( clicked( ) ), this, SLOT( pk_load_file( ) ) );

    //    QPushButton * load_replica = new QPushButton( mainPainel );
    //    load_replica -> setIcon( QIcon( ":/UI/IMAGES/peaklist.png" ) );
    //    load_replica -> setToolTip( "Load peaklist set" );
    //    load_replica -> setGeometry( 20, 60, 20, 20 );

    //    connect( load_replica, SIGNAL( clicked( ) ), this, SLOT( pk_load_replica( ) ) );

    //    QPushButton * super_spectrum = new QPushButton( mainPainel );
    //    super_spectrum -> setIcon( QIcon( ":/UI/IMAGES/peaklist.png" ) );
    //    super_spectrum -> setToolTip( "Create Super Spectrum" );
    //    super_spectrum -> setGeometry( 20, 220, 20, 20 );

    //    connect( super_spectrum, SIGNAL( clicked( ) ), this, SLOT( pk_super_spectrum( ) ) );

    QSplitter * main_splitter = new QSplitter( this );
    main_splitter -> setHandleWidth( 1 );

    QWidget * welcome = new QWidget( this );
    m_modeStack -> insertTab( 0,
            welcome,
            QIcon( ":/UI/IMAGES/mode_Welcome.png" ),
            "Welcome"
            );
    m_modeStack->setTabEnabled( 0, true );
    m_modeStack -> setCurrentIndex( 0 );

    QWidget * test = new QWidget( this );
    m_modeStack -> insertTab( 1,
            test,
            QIcon( ":/UI/IMAGES/mode_Project.png" ),
            "Project"
            );
    m_modeStack->setTabEnabled( 1, true );
    //    m_modeStack -> setCurrentIndex( 0 );

    m_modeStack -> insertTab( 2,
            main_splitter,
            QIcon( ":/UI/IMAGES/peaklist.png" ),
            tr("Peaklist")
            );
    m_modeStack -> setTabEnabled( 2, true );

    QWidget * analyze = new QWidget( this );
    m_modeStack -> insertTab( 3,
            analyze,
            QIcon( ":/UI/IMAGES/mode_Analyzer.png" ),
            "Analyze"
            );
    m_modeStack->setTabEnabled( 3, true );

    QWidget * help = new QWidget( this );
    m_modeStack -> insertTab( 4,
            help,
            QIcon( ":/UI/IMAGES/mode_Reference.png" ),
            "Help"
            );
    m_modeStack->setTabEnabled( 4, true );

    //main_layout -> addWidget( main_splitter );

    QWidget * aux = new QWidget( this );
    main_splitter -> addWidget( aux );

    QVBoxLayout * aux_layout = new QVBoxLayout( aux );

    aux_layout -> setMargin( 0 );
    aux_layout -> setSpacing( 0 );

    QWidget * pk_buttons = new QWidget( this );
    //    pk_buttons -> setGeometry( 0, 0, 30, 300 );
    aux_layout -> addWidget( pk_buttons );
    QHBoxLayout * bt_layout = new QHBoxLayout( pk_buttons );

    bt_layout -> setMargin( 0 );
    bt_layout -> setSpacing( 0 );

    QPushButton * load_pk = new QPushButton;
    load_pk -> setText( tr( "Single" ) );
    load_pk->setIcon( QIcon( ":/UI/IMAGES/peaklist.png" ) );
    load_pk -> setToolTip( "Load peaklist" );
    //        load_pk->setGeometry( 20, 20, 20, 20 );
    bt_layout -> addWidget( load_pk );

    connect( load_pk, SIGNAL( clicked( ) ), this, SLOT( pk_load_file( ) ) );

    QPushButton * load_replica = new QPushButton;
    load_replica -> setText( tr( "Replica" ) );
    load_replica -> setIcon( QIcon( ":/UI/IMAGES/peaklist.png" ) );
    load_replica -> setToolTip( "Load peaklist set" );
    //        load_replica -> setGeometry( 60, 20, 20, 20 );
    bt_layout -> addWidget( load_replica );

    connect( load_replica, SIGNAL( clicked( ) ), this, SLOT( pk_load_replica( ) ) );

    QPushButton * super_spectrum = new QPushButton;
    super_spectrum -> setText( tr( "Super" ) );
    super_spectrum -> setIcon( QIcon( ":/UI/IMAGES/peaklist.png" ) );
    super_spectrum -> setToolTip( "Create Super Spectrum" );
    //        super_spectrum -> setGeometry( 220, 20, 20, 20 );
    bt_layout -> addWidget( super_spectrum );

    connect( super_spectrum, SIGNAL( clicked( ) ), this, SLOT( pk_super_spectrum( ) ) );

    QPushButton * edit_info = new QPushButton;
    edit_info -> setText( tr( "Edit" ) );
    edit_info -> setIcon( QIcon( ":/UI/IMAGES/peaklist.png" ) );
    edit_info -> setToolTip( "Create Super Spectrum" );
    //        super_spectrum -> setGeometry( 220, 20, 20, 20 );
    bt_layout -> addWidget( edit_info );

    connect( super_spectrum, SIGNAL( clicked( ) ), this, SLOT( pk_super_spectrum( ) ) );


    // Sidebar tabs
    QTabWidget * sidebar_tabs = new QTabWidget;
    sidebar_tabs -> setTabPosition( QTabWidget :: West );
    sidebar_tabs -> setStyleSheet( "border: 0;" );
    sidebar_tabs -> setGeometry( 0, 30, 500, 500 );

    aux_layout -> addWidget( sidebar_tabs );

    // Sidebar
    sidebar = new QWidget;//( this );
    sidebar -> setObjectName( "SideBar" );
    //    sidebar -> setStyleSheet( "border: 1px solid #000" );

    sidebar_tabs -> addTab( sidebar, tr( "Peaklist" ) );

    QHBoxLayout * sidebar_layout = new QHBoxLayout( sidebar );
    sidebar_layout -> setMargin( 0 );
    sidebar_layout -> setSpacing( 0 );

    // PK Panel
    pk_panel = new ListWidget( this );

    //    connect( pk_panel, SIGNAL( itemClicked( QListWidgetItem * ) ), this, SLOT( pk_panel_clicked( QListWidgetItem * ) ) );
    //    connect( pk_panel, SIGNAL( customContextMenuRequested( QPoint ) ), this, SLOT( pk_context_menu( QPoint ) ) );

    sidebar_layout -> addWidget( pk_panel );

    // Sidebar Settings
    settings = new QWidget;

    sidebar_tabs->addTab( settings, tr( "Settings" ) );

    createSettingsLayout( settings );

    // Content
    /*QVBoxLayout * */content_layout = new QVBoxLayout( main_splitter );
    content_layout -> setMargin( 0 );
    content_layout -> setSpacing( 0 );

    QSplitter * content_splitter = new QSplitter( Qt :: Vertical, this );
    content_splitter -> setHandleWidth( 1 );

    content_layout -> addWidget( content_splitter );

    // Plot
    QHBoxLayout * plot_layout = new QHBoxLayout( analyze );
    plot_layout -> setMargin( 0 );
    plot_layout -> setSpacing( 0 );

    QSplitter * plot_splitter = new QSplitter( this );
    plot_splitter -> setHandleWidth( 1 );

    plot_layout -> addWidget( plot_splitter );

    QWidget * plot_area = new QWidget( this );
    plot_area -> setStyleSheet( "background: #fff;" );

    plot = new Plot( plot_area );
    plot -> setAxisScale( QwtPlot :: yLeft, 0.0, 110.0 );

    QGridLayout * plot_area_layout = new QGridLayout( plot_area );
    plot_area_layout -> addWidget( plot );

    QWidget * plot_tools = new QWidget( this );
    plot_tools -> setStyleSheet( "background: #fff; border-left: black;" );
    plot_tools -> hide( );

    plot_aux = new Plot( plot_tools );
    plot_aux -> setAxisScale( QwtPlot :: yLeft, 0.0, 110.0 );

    QGridLayout * plot_aux_area_layout = new QGridLayout( plot_tools );
    plot_aux_area_layout -> addWidget( plot_aux );

    plot_splitter -> addWidget( plot_area );
    plot_splitter -> addWidget( plot_tools );


    // Table
    QWidget * table_area = new QWidget( this );
    table_area->setMinimumHeight( 200 );
    //    table_area->hide();

    content_splitter -> addWidget( table_area );

    //    table_layout = new QVBoxLayout( table_area );

    //    content_area = new QWidget;
    //    content_area -> setObjectName( "ContentArea" );
    //    content_area -> setMinimumWidth( 300 );

    //    QVBoxLayout * content_area_layout = new QVBoxLayout( content_area );
    //    content_area_layout -> setMargin( 0 );
    //    content_area_layout -> setSpacing( 0 );

    //    splitter -> addWidget( content_area );

    //    m_layout -> addWidget( splitter );

    //    splitter -> setHandleWidth( 1 );

    //    QPushButton * load_pk = new QPushButton( mainPainel );
    //    load_pk->setIcon( QIcon( ":/UI/IMAGES/peaklist.png" ) );
    //    load_pk -> setToolTip( "Load peaklist" );
    //    load_pk->setGeometry( 20, 20, 20, 20 );

    //    connect( load_pk, SIGNAL( clicked( ) ), this, SLOT( pk_file( ) ) );

    //    QPushButton * load_replica = new QPushButton( mainPainel );
    //    load_replica -> setIcon( QIcon( ":/UI/IMAGES/peaklist.png" ) );
    //    load_replica -> setToolTip("Load peaklist set");
    //    load_replica -> setGeometry( 20, 60, 20, 20 );

    //    connect( load_replica, SIGNAL( clicked( ) ), this, SLOT( pk_replica( ) ) );

    //    pk_panel = new QListWidget;

    //    sidebar_layout -> addWidget( pk_panel );

    //    connect( pk_panel, SIGNAL( itemChanged( QListWidgetItem * ) ), this, SLOT( handler( QListWidgetItem * ) ) );

    //    content_area_splitter = new QSplitter( this );
    //    content_area_splitter -> setOrientation( Qt :: Vertical );



    //    QWidget * plot_area = new QWidget( this );
    //    plot_area->setStyleSheet("background:green;");

    //    content_area_splitter -> addWidget( plot_area );

    //    QVBoxLayout * plot_area_layout = new QVBoxLayout;//( plot_area );
    //    plot_area_layout -> setMargin( 0 );
    //    plot_area_layout -> setSpacing( 0 );


    //    new Plot( plot_area );

    //    QWidget * table_area = new QWidget( this );
    //    table_area->setStyleSheet("background:yellow;");

    //    content_area_splitter -> addWidget(table_area);

    //    content_area_layout -> addWidget( content_area_splitter );

    //    content_area_splitter -> setHandleWidth( 1 );
}

void Application :: createSettingsLayout( QWidget * settings )
{
    ui( "settings", settings );

    //    QVBoxLayout *layout = new QVBoxLayout;
    //    layout->addWidget(myWidget);
    //    settings -> setLayout(layout);

    //    qDebug( ) << settings->findChild<QSpinBox *>( "toleranceSpinBox" )->value();
}

void Application :: createCurve( QString item )
{
    static int plotLowerBound = ( int ) NULL, plotUpperBound = ( int ) NULL;

    QList < QHash < QString, QString > > peaks;
    peaks = peaklists[ item ] -> getPeaks( );

    QVector < QPointF > points;
    QVector < QPointF > points_fid;
    QVector < QPointF > points_reflex;
    QVector < QPointF > points_fid_reflex;
    QVector < QPointF > points_sorted;

    for ( int i = 0; i < peaks.size( ); i++ )
    {
        points.append( QPointF(
                    ( peaks[ i ].contains( "ind" ) ? peaks[ i ][ "ind" ].toFloat( ) : peaks[ i ][ "mass" ].toFloat( ) ),
                    peaks[ i ][ "absi_rel" ].toFloat( )
                      ) );
    }

    points_sorted = points;
    qSort( points_sorted.begin( ), points_sorted.end( ), max_peak_by_absi );

    for ( int i = 0; i < peaks.size( ); i++ )
    {
        points_reflex.append( points.at( i ) );
        points_reflex[ i ].setY( points_reflex[ i ].y( ) * -1 );
    }

    points_fid = peaklists[ item ] -> getFid( );
    for ( int i = 0; i < points_fid.size( ); i++ )
    {
        points_fid_reflex.append( points_fid.at( i ) );
        points_fid_reflex[ i ].setY( points_fid_reflex[ i ].y( ) * -1 );
    }

    curves[ item ] = plot -> curve( points );
    curves[ item ] -> hide( );

    QPen pen = curves[ item ] -> pen( );
    pen.setWidth( 1 );

    curves_reflex[ item ] = plot -> curve( points_reflex, curves[ item ] -> pen( ).color( ) );
    curves_reflex[ item ] -> hide( );

    curves_fid[ item ] = plot -> curve( points_fid, curves[ item ] -> pen( ).color( ) );
    curves_fid[ item ] -> hide( );
    curves_fid[ item ] -> setStyle( QwtPlotCurve :: Lines );
    curves_fid[ item ] -> setPen( pen );

    curves_fid_reflex[ item ] = plot -> curve( points_fid_reflex, curves[ item ] -> pen( ).color( ) );
    curves_fid_reflex[ item ] -> hide( );
    curves_fid_reflex[ item ] -> setStyle( QwtPlotCurve :: Lines );
    curves_fid_reflex[ item ] -> setPen( pen );

    curves[ item ] -> attach( plot );
    curves_fid[ item ] -> attach( plot );
    curves_reflex[ item ] -> attach( plot );
    curves_fid_reflex[ item ] -> attach( plot );

    for ( int i = 0; i < peaks.size( ); i++ )
        points[ i ].setY( 100 );

    plots[ item ] = new Plot( this );
    plots[ item ] -> peakWeigth( 5 );
    plots[ item ] -> setStyleSheet( "background: #fff;" );
    plots[ item ] -> hide( );
    plots[ item ] -> curve(
            points, curves[ item ] -> pen( ).color( )
            ) -> attach( plots[ item ] );
    plots[ item ] -> zoom( );

    plots[ item ] -> enableAxis( QwtPlot :: yLeft, false );
    plots[ item ] -> setAxisScale( QwtPlot :: yLeft, 0, 130.0 );

    QwtPlotMarker * marker = new QwtPlotMarker( );
    marker ->setValue( 0.0, 110.0 );
    marker ->  setLineStyle( QwtPlotMarker :: HLine );
    marker -> setLabelAlignment( Qt::AlignRight | Qt::AlignBottom );
    marker -> setLinePen( QPen( Qt::green, 0, Qt :: DashDotLine ) );
    marker -> attach( plots[ item ] );

    QwtText text( pk_panel_itens[ item ] -> data( Qt :: DisplayRole ).toString( ) );
    text.setFont( QFont( "Helvetica", 10, QFont::Bold ) );
    text.setColor( QColor( 200, 150, 0 ) );

    marker->setLabel(text);

    //    plots[ item ] -> text( pk_panel_itens[ item ] -> data( Qt :: DisplayRole ).toString( ) );

    if ( plotLowerBound == ( int ) NULL )
    {
        plotLowerBound = ( int ) plots[ item ] -> axisScaleDiv( QwtPlot :: xBottom ) -> lowerBound( );
        plotUpperBound = ( int ) plots[ item ] -> axisScaleDiv( QwtPlot :: xBottom ) -> upperBound( );
    }
    else
    {
        plotLowerBound = qMin( plotLowerBound, ( int ) plots[ item ] -> axisScaleDiv( QwtPlot :: xBottom ) -> lowerBound( ) );
        plotUpperBound = qMax( plotUpperBound, ( int ) plots[ item ] -> axisScaleDiv( QwtPlot :: xBottom ) -> upperBound( ) );
    }

    plot -> scale( plotLowerBound, plotUpperBound );

    plots[ item ] -> enableAxis( QwtPlot :: yLeft, false );
    plots[ item ] -> grid( ) -> enableY( false );

    QFont font = plots[ item ] -> axisFont( QwtPlot :: xBottom );
    font.setPointSize( 6 );

    plots[ item ] -> setAxisFont( QwtPlot :: xBottom, font );

    QHashIterator < QString, Plot * > plots_it( plots );
    while( plots_it.hasNext( ) )
    {
        plots_it.next( );
        plots_it.value( ) -> scale( plotLowerBound, plotUpperBound );
    }

    plotInterval -> setRange( plotLowerBound, plotUpperBound );
    plotInterval -> setLowerPosition( plotLowerBound );
    plotInterval -> setUpperPosition( plotUpperBound );

    //    plots_layout->addWidget( plots[ item ] );
}

void Application :: createTable( QString item )//QPen pen )
{
    TableView * table = new TableView( this );

    QList < QHash < QString, QString > > peaks;
    QVector < QPointF > points;
    QVector < QPointF > points_sorted;

    peaks = peaklists[ item ] -> getPeaks( );

    qreal mean = 0;

    for ( int column = 0; column < peaks.size( ); ++column )
    {
        table -> setCell( 0, column + 1, QString :: number( peaks[ column ][ "mass" ].toFloat( ) ) );
        table -> setCell( 1, column + 1, QString :: number( peaks[ column ][ "absi" ].toFloat( ) ) );

        mean += peaks[ column ][ "mass" ].toFloat( );

        points.append( QPointF(
                    peaks[ column ][ "mass" ].toFloat( ),
                    peaks[ column ][ "absi" ].toFloat( )
                      ) );
    }

    mean /= peaks.size( );

    //        table -> setCell( 0, 0, QString( "%1" ).arg( mean ) );

    points_sorted = points;
    qSort( points_sorted.begin( ), points_sorted.end( ), max_peak_by_absi );

    table -> resizeRowsToContents( );
    table -> resizeColumnsToContents( );

    //        table -> setMinimumHeight(/*
    //            table -> horizontalHeader( ) -> height( )
    //                + ( 2 * table -> rowHeight( 1 ) )
    //                + table -> horizontalScrollBar( ) -> height( )
    //        */100);

    //        table -> setSizePolicy( QSizePolicy :: Expanding, QSizePolicy :: Expanding );

    QStringList h_labels, v_labels;
    qreal variance = 0;

    h_labels << QString( "Mean" );

    for ( int i = 0; i < peaks.size( ); i++ )
    {
        h_labels << QString( "%1%" ).arg(
                peaks[ i ][ "absi_rel" ].toFloat( ), 0, 'f', 2
                );

        variance += pow( points[ i ].x( ) - mean, 2 );
    }

    //        qreal inrec = 0;
    //        for ( int i = 0; i < peaks.size( ); i++ )
    //        {
    //            if ( inrec )
    //                inrec = sinh( log( sqrt( inrec * points[ i ].x( ) )) );
    //            else
    //                inrec = sinh( log( sqrt( points[ i ].x( ) ) ) );

    //            qDebug( ) << peaks[ i ][ "mass" ].toFloat( ) << " :: "
    //                      << log( peaks[ i ][ "mass" ].toFloat( ) ) << " :: "
    //                      << log10( peaks[ i ][ "mass" ].toFloat( ) ) << " :: "
    //                      << pow( peaks[ i ][ "mass" ].toFloat( ), 0.1 ) << " :: "
    //                      << sqrt( peaks[ i ][ "mass" ].toFloat( ) ) << " :: "
    //                      << log( sqrt( peaks[ i ][ "mass" ].toFloat( ) ) ) << " :: "
    //                      << sqrt( log( peaks[ i ][ "mass" ].toFloat( ) ) ) << " :: "
    //                      << log( log( peaks[ i ][ "mass" ].toFloat( ) ) );

    //            qDebug( ) << peaks[ i ][ "mass" ].toFloat( ) << " :: "
    //                      << pow( peaks[ i ][ "mass" ].toFloat( ), 0.1 ) << " :: "
    //                      << log( pow( peaks[ i ][ "mass" ].toFloat( ), 0.1 ) ) << " :: "
    //                      << log10( pow( peaks[ i ][ "mass" ].toFloat( ), 0.1 ) ) << " :: "
    //                      << sinh( log10( pow( peaks[ i ][ "mass" ].toFloat( ), 0.1 ) ) );

    //            if ( inrec )
    //                inrec = sinh( log( pow( inrec * peaks[ i ][ "mass" ].toFloat( ), 0.1 ) ) );
    //            else
    //                inrec = sinh( log( pow( peaks[ i ][ "mass" ].toFloat( ), 0.1 ) ) );


    //            qDebug( ) << inrec;
    //        }

    //        table -> setCell( 1, 0, QString( "%1" ).arg( sqrt( variance / peaks.size( ) ) ) );

    //        qreal inrec = 0;

    //        for ( int i = peaks.size( ); i > 0; i++ )
    //        {
    //            if ( ! inrec )
    //                inrec = sinh( points[ i - 1 ].x( ) );
    //            else
    //                inrec *= sinh( points[ i - 1 ].x( ) );
    //        }

    //        table -> setCell( 1, 0, QString( "%1" ).arg( inrec ) );

    v_labels << "mass" << "absi";

    table -> setHLabels( h_labels );
    table -> setVLabels( v_labels );

    QwtPlotMarker * marker = new QwtPlotMarker;

    marker -> setLineStyle( QwtPlotMarker :: HLine );
    //    marker -> setLabelAlignment( Qt :: AlignRight | Qt :: AlignBottom );
    marker -> setLinePen( QPen( curves[ item ] -> pen( ).brush( ), 0, Qt :: DashLine ) );
    marker -> setSymbol( new QwtSymbol(
                QwtSymbol :: Diamond,
                curves[ item ] -> pen( ).brush( ),
                curves[ item ] -> pen( ),
                QSize( 7,7 )
                ) );
    marker -> attach( plot );
    //        marker -> hide( );

    table -> setMarker( marker );
    //        table -> setSizePolicy( QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding );
    table -> hide( );

    tables[ item ] = table;

    tables_plots_layout -> addWidget( plots[ item ], tables_plots_layout -> rowCount( ), 0 );
    tables_plots_layout -> addWidget( tables[ item ], tables_plots_layout -> rowCount( ) - 1, 1 );

    //        qDebug( ) << tables_plots_layout -> rowMinimumHeight( tables_plots_layout -> rowCount( ) );
    //        qDebug( ) << tables_plots_layout -> rowMinimumHeight( tables_plots_layout -> rowCount( ) - 1 );
    //        qDebug( ) << "--------------";

    //        tables_plots_layout -> setRowMinimumHeight( tables_plots_layout -> rowCount( ) - 1, 100 );
    //        tables_plots_layout -> setRowMinimumHeight( tables_plots_layout -> rowCount( ) - 1, 100 );
}

void Application :: pk_load( )
{
    if ( ! files.count( ) )
        QMessageBox :: information( this, tr( "Load Peaklist" ),
                tr( "The peaklist files are not found." )
                );
    else
    {
        QListIterator < QString > file( files );
        Peaklist * pk_list;

        QHash < QString, QString > info;

        //        QDateTime date;
        QListWidgetItem * item;

        //        QFile leaf("leaf.txt");

        //        leaf.open(QIODevice::WriteOnly | QIODevice::Text);
        //        QTextStream out(&leaf);

        while ( file.hasNext( ) )
        {
            if ( ( pk_list = Peaklist :: New( file.next( ) ) ) )
            {
                info = pk_list -> getInfo( );

                //                date = QDateTime :: fromString( info[ "date" ], Qt :: ISODate );
                item = new QListWidgetItem( tr( "%1" )
                        .arg( ( info.contains( "name" ) ) ? info[ "name" ] : info[ "spectrumid" ] )
                        );

                item->setData( Qt :: UserRole, info[ "spectrumid" ] );

                //                item -> setFlags( Qt :: ItemIsEditable );

                if ( peaklists.contains( item -> data( Qt :: UserRole ).toString( ) ) )
                    delete item;
                else
                {
                    pk_panel_itens[ item -> data( Qt :: UserRole ).toString( ) ] = item;
                    pk_panel -> addItem( item );

                    item -> setFlags( item -> flags( ) | Qt :: ItemIsUserCheckable | Qt :: ItemIsSelectable | Qt :: ItemIsEditable );
                    item -> setCheckState( Qt::Unchecked );

                    //                    qDebug( ) << item -> text( );

                    peaklists[ item -> data( Qt :: UserRole ).toString( ) ] = pk_list;

                    createCurve( item -> data( Qt :: UserRole ).toString( ) );
                    item -> setForeground(
                            curves[ item -> data( Qt :: UserRole ).toString( ) ] -> pen( ).brush( )
                            );
                    createTable( item -> data( Qt :: UserRole ).toString( ) );
                    tables[ item -> data( Qt :: UserRole ).toString( ) ] -> setStyleSheet(
                            tables[ item -> data( Qt :: UserRole ).toString( ) ] -> styleSheet( )
                            + "QHeaderView::section:checked{background-color:"
                            + curves[ item -> data( Qt :: UserRole ).toString( ) ] -> pen( ).brush( ).color().name()
                            + ";}"
                            );

                    ( qFindChild< QPushButton * >( this, "pk_bt_clean" ) ) -> setEnabled( true );

                    //                    if ( ! pk_list -> getFid( ).empty( ) )
                    //                    qDebug( ) << pk_list -> getFid( ).last();
                }
            }

            files.pop_front( );
        }

        //        leaf.close( );
        files.clear( );

        modemanager -> statusBar( QString( "Available: %1 | Selected: %2" ).arg( peaklists.size( ) ).arg( selected ) );
    }
}

void Application :: pk_load_file( )
{
    files << QFileDialog :: getOpenFileName( this, tr( "Open Directory" ),
            QDir :: homePath(), tr("Bruker Peaklist (peaklist.xml *.peaks)")
            );

    pk_load( );
}

void Application :: pk_load_replica( )
{
    QString path = QFileDialog::getExistingDirectory( this, tr( "Open Directory" ),
            QDir :: homePath() /*+ "/Documents/MESTRADO/MS"*/, QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks
            );

    if ( ! path.isEmpty( ) )
    {
        QDir currentDir = QDir( path );
        currentDir.setFilter(  QDir::Files | QDir::NoSymLinks | QDir :: NoDotAndDotDot );

        QDirIterator it( currentDir, QDirIterator::Subdirectories );

        while ( it.hasNext( ) )
        {
            it.next( );

            if ( it.fileInfo( ).suffix( ) == "xml" /*&& it.fileName( ).contains( "peaklist" )*/ )
                files << it.filePath( );

            if ( it.fileInfo( ).suffix( ) == "peaks" /*&& it.fileName( ).contains( "ceae" )*/ )
                files << it.filePath( );
        }

        pk_load( );
    }
}

void Application :: setPlotInterval( int lower, int upper )
{
    //    qDebug( ) << "Lower: " << lower << " | Upper: " << upper;

    QHashIterator < QString, Plot * > plots_it( plots );
    while( plots_it.hasNext( ) )
    {
        plots_it.next( );
        plots_it.value( ) -> scale( lower, upper );
    }
}

void Application :: pk_super_spectrum( )
{
    QMapIterator < QString, Peaklist * > pk_it( peaklists );
    bool show = false;

    super_spectrum -> clean( );

    while ( pk_it.hasNext( ) )
    {
        pk_it.next( );

        if ( ! pk_it.value( ) -> actived( ) )
            continue;

        show = true;

        super_spectrum -> peaklist(
                pk_it.value( ) -> getPeaks( )
                );
    }

    if ( show )
    {
        super_spectrum -> show( plot,
                settings -> findChild< QSpinBox * >( "toleranceSpinBox" ) -> value( ),
                settings -> findChild< QSpinBox * >( "presenceSpinBox" ) -> value( )
                );
    }
}

void Application :: pk_analyzer( )
{
    mode( "Analyzer" )
        -> enable( )
        -> current( );
}

void Application :: pk_clean( )
{
    ( qFindChild< QPushButton * >( this, "pk_bt_clean" ) ) -> setEnabled( false );

    for ( int row = 0; row < pk_panel -> count(); row++ )
        if ( pk_panel -> item( row ) -> checkState( ) == Qt::Checked )
            pk_panel_clicked( pk_panel -> item( row ) );

    pk_panel -> clear( );

    peaklists.clear( );
    tables.clear( );
    curves.clear( );

    modemanager -> statusBar( "" );
}

void Application :: pk_buttons( bool enable )
{
    ( qFindChild< QPushButton * >( this, "pk_bt_info" ) ) -> setEnabled( enable );
    ( qFindChild< QPushButton * >( this, "pk_bt_clean" ) ) -> setEnabled( enable );
}

void Application :: pk_context_menu( const QPoint & pos )
{
    QListWidgetItem * item = pk_panel -> itemAt( pos );

    if ( item )
    {
        //        if ( item -> checkState( ) != Qt :: Checked )
        //            pk_panel_clicked( item );

        //        QMessageBox :: information( this, "", "show" );

        QMenu menu( pk_panel );

        QAction * info = new QAction( tr( "Informations" ), pk_panel );
        QAction * reflex = new QAction( tr( "Reflex" ), pk_panel );
        QAction * remove = new QAction( tr( "Remove" ), pk_panel );
        QAction * merge = new QAction( tr( "Merge" ), pk_panel );
        QAction * edit= new QAction( tr( "Edit" ), pk_panel );

        menu.addAction( info );
        menu.addAction( reflex );
        menu.addAction( remove );
        menu.addAction( merge );
        menu.addAction( edit );

        connect( reflex, SIGNAL( triggered( ) ), SLOT( pk_panel_clicked_reflex( ) ) );
        connect( info, SIGNAL( triggered( ) ), SLOT( pk_edit_info( ) ) );
        connect( merge, SIGNAL( triggered( ) ), SLOT( pk_merge( ) ) );

        connect( edit, SIGNAL( triggered( ) ), SLOT( pk_panel_item_edit( ) ) );

        menu.exec( pk_panel -> mapToGlobal( pos ) );
    }
}

void Application :: pk_merge( )
{
    QMapIterator < QString, Peaklist * > pk_it( peaklists );

    while ( pk_it.hasNext( ) )
    {
        pk_it.next( );

        if ( ! pk_it.value( ) -> actived( ) )
            continue;
    }
}

void Application :: pk_panel_item_edit( void )
{
    QListWidgetItem * item = pk_panel -> currentItem( );
    pk_panel -> editItem( item );
}

void Application :: pk_panel_item_edited( QWidget * test )
{
    //    QMessageBox::information(this,tr(""),tr("Edited"));
//    qDebug( ) << ">>" << ( ( QLineEdit * ) test ) -> objectName( );
    //    plots[ ( ( QLineEdit * ) test ) -> objectName( ) ] -> text( );
}

void Application :: pk_panel_changed( QListWidgetItem * item )
{
    if ( item == pk_panel -> currentItem( ) )
    {
        //        qDebug( ) << item->text();
        item->checkState();
    }
}

void Application :: pk_panel_clicked( QListWidgetItem * item )
{
    pk_panel_clicked( item, false );
}

void Application :: pk_panel_clicked( QListWidgetItem * item, bool reflex = false )
{
    if ( ! item )
        return;

    //    QMessageBox :: information( this, "", "show" );

    if ( item -> checkState( ) == Qt :: Unchecked )
    {
        selected++;
    }

    item -> setCheckState(
            ( item -> checkState( ) == Qt::Checked && ! reflex ) ?
            Qt :: Unchecked : Qt :: Checked
            );

    peaklists[ item -> data( Qt :: UserRole ).toString( ) ] -> actived(
            item -> checkState( ) == Qt::Checked
            );

    peaklists[ item -> data( Qt :: UserRole ).toString( ) ] -> reflex( reflex );

    //    distance_table( );

    tables[ item -> data( Qt :: UserRole ).toString( ) ] -> visible(
            item -> checkState( ) == Qt::Checked, reflex
            );

    super_spectrum -> clean( );

    if ( item -> checkState( ) == Qt::Checked )
    {
        //        selected++;
        plots[ item -> data( Qt :: UserRole ).toString( ) ] -> show( );

        tables[ item -> data( Qt :: UserRole ).toString( ) ] -> show( );
        tables[ item -> data( Qt :: UserRole ).toString( ) ] -> select( 0, 0 );

        if ( ! reflex )
        {
            curves_reflex[ item -> data( Qt :: UserRole ).toString( ) ] -> hide( );
            curves_fid_reflex[ item -> data( Qt :: UserRole ).toString( ) ] -> hide( );
            curves[ item -> data( Qt :: UserRole ).toString( ) ] -> show( );

            if ( show_spectrum )
                curves_fid[ item -> data( Qt :: UserRole ).toString( ) ] -> show( );
        }
        else
        {
            plot -> setAxisScale( QwtPlot :: yLeft, -110.0, 130.0 );

            curves[ item -> data( Qt :: UserRole ).toString( ) ] -> hide( );
            curves_fid[ item -> data( Qt :: UserRole ).toString( ) ] -> hide( );
            curves_reflex[ item -> data( Qt :: UserRole ).toString( ) ] -> show( );

            if ( show_spectrum )
                curves_fid_reflex[ item -> data( Qt :: UserRole ).toString( ) ] -> show( );
        }

        db -> prepare( "select * from info where peaklist_id in ( :peaklist_id )" );
        db -> bind( ":peaklist_id", item -> data( Qt :: UserRole ).toString( ) );

        QSqlQuery * query = db -> query( );

        QSqlRecord rec = query -> record( );
        if ( query -> last( ) )
        {
            //            for ( int i = 0; i < rec.count( ); i++ )
            //                qDebug( ) << rec.fieldName( i ) << query -> value( i ).toString( );

            QListIterator < QLineEdit * > edit_fileds_it( peaklist_info -> findChildren< QLineEdit * >( ) );
            QLineEdit * edit;
            while ( edit_fileds_it.hasNext( ) )
            {
                edit = edit_fileds_it.next( );

                int column = rec.indexOf( (
                            ( ! edit -> objectName().startsWith( "qt_spinbox" ) ) ?
                            edit : edit -> parentWidget( )
                            ) -> objectName( )
                        );

                edit -> setText( query -> value( column ).toString( ) );
            }

            QListIterator < QComboBox * > cb_fileds_it( peaklist_info -> findChildren< QComboBox * >( ) );
            QComboBox * cb;
            while ( cb_fileds_it.hasNext( ) )
            {
                cb = cb_fileds_it.next( );
                //                info.insert( cb->objectName( ), cb -> currentText( ) );

                cb -> setCurrentIndex(
                        cb -> findText(
                            query -> value(
                                rec.indexOf( cb->objectName( ) )
                                ).toString( )
                            )
                        );
            }
        }
    }
    else
    {
        selected--;
        plots[ item -> data( Qt :: UserRole ).toString( ) ] -> hide( );

        tables[ item -> data( Qt :: UserRole ).toString( ) ] -> hide( );

        curves[ item -> data( Qt :: UserRole ).toString( ) ] -> hide( );
        curves_fid[ item -> data( Qt :: UserRole ).toString( ) ] -> hide( );
        curves_reflex[ item -> data( Qt :: UserRole ).toString( ) ] -> hide( );
        curves_fid_reflex[ item -> data( Qt :: UserRole ).toString( ) ] -> hide( );

        //        plot -> replot( );
    }


    distance_table( );

    plot -> zoom( );

    //    qDebug( ) << plot -> rect().x() << " - " << plot -> canvas() -> rect().width() << " - " << plot -> canvas() -> rect().x();

    QMapIterator < QString, Peaklist * > pk_it( peaklists );
    //    int selected = 0;
    //    while ( pk_it.hasNext( ) )
    //    {
    //        pk_it.next( );

    //        if ( pk_it.value( ) -> actived( ) )
    //            selected++;
    //    }

    modemanager -> statusBar( QString( "Available: %1 | Selected: %2" ).arg( peaklists.size( ) ).arg( selected ) );

    switch ( selected )
    {
        case 0 :
            ( qFindChild< QPushButton * >( this, "pk_bt_analyzer_peaklist" ) ) -> setEnabled( false );
            ( qFindChild< QPushButton * >( this, "pk_bt_info" ) ) -> setEnabled( false );
            ( qFindChild< QWidget * >( this, "pk_informations" ) ) -> setEnabled( false );
            mode( "Analyzer") -> enable( false );
            break;
        case 1 :
            ( qFindChild< QPushButton * >( this, "pk_bt_analyzer_peaklist" ) ) -> setEnabled( true );
            ( qFindChild< QPushButton * >( this, "pk_bt_info" ) ) -> setEnabled( true );
            ( qFindChild< QWidget * >( this, "pk_informations" ) ) -> setEnabled( true );
            mode( "Analyzer") -> enable( );
            break;
    }

    bool rescale_plot = true;
    QHashIterator < QString, QwtPlotCurve * > i( curves_reflex );
    while ( i.hasNext( ) )
    {
        i.next( );

        if ( i.value( ) -> isVisible( ) )
        {
            rescale_plot = false;
            break;
        }
    }

    if ( rescale_plot )
        plot -> setAxisScale( QwtPlot :: yLeft, 0.0, 110.0 );
}

void Application :: pk_panel_clicked_reflex( )
{
    QListWidgetItem * item = pk_panel -> currentItem();
    pk_panel_clicked( item, true );
}

void Application :: pk_edit_info( )
{
    QTabWidget * tab = qFindChild< QTabWidget * >( this, "pk_content_tab" );
    tab -> setCurrentIndex( tab -> indexOf(
                qFindChild< QWidget * >( this, "pk_informations" ) )
            );
}

void Application :: resizeEvent( QResizeEvent * event )
{
}

void Application :: showEvent( QShowEvent * event )
{
    //    QMessageBox :: information( this, "", "show" );
}
