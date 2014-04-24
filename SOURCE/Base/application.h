#ifndef APPLICATION_H
#define APPLICATION_H

#include <MainWindow>
#include <StyleSheet>
#include <MSAnalyser>

#include <QWidget>
#include <QResizeEvent>
#include <QPushButton>
#include <QLineEdit>
#include <QListWidgetItem>

#include "plot.h"
#include <painter.h>

class QStringList;
class QSplitter;
class QVBoxLayout;
class QGridLayout;
class TableView;
class ListWidget;

class FancyTabWidget;
class ModeManager;

class Database;

class QSqlDatabase;

struct SuperSpectrumPoint;
struct SuperSpectrum;

class HistogramPlot;

class QxtSpanSlider;

struct Mode;

bool sort_peak_by_mass( const QPointF & p1, const QPointF & p2 );
bool max_peak_by_absi( const QPointF & p1, const QPointF & p2 );
bool sort_ss_peak_by_mass( SuperSpectrumPoint & p1, SuperSpectrumPoint & p2 );

typedef struct SuperSpectrumPoint
{
    public :
        void set( QPointF point, uint presence = 1 )
        {
            _point = point;
            _presence = presence;
        }

        QPointF point( )
        {
            return _point;
        }

        uint presence( )
        {
            return _presence;
        }

        bool operator ==( SuperSpectrumPoint p )
        {
            return ( p.point( ).x( ) == _point.x( ) );
        }

    private :
        QPointF _point;
        uint _presence;
} SuperSpectrumPoint;

class Application : public MainWindow
{
    Q_OBJECT

    public :
        Application( );

        void resizeEvent( QResizeEvent * );
        void showEvent( QShowEvent * event );

    private :
        MSAnalyser * ms;
        Plot * plot, * plot_aux;
        SuperSpectrum * super_spectrum;

        FancyTabWidget * m_modeStack;
        ModeManager * modemanager;

        QWidget * mainPainel;
        QWidget * sidebar;
        QWidget * content_area;
        QSplitter * content_area_splitter;
        QWidget * settings;

        ListWidget * pk_panel;
        QHash < QString, QListWidgetItem * > pk_panel_itens;

        QStringList files;
        QMap < QString, Peaklist * > peaklists;
        QHash < QString, QwtPlotCurve * > curves;
        QHash < QString, QwtPlotCurve * > curves_fid;
        QHash < QString, QwtPlotCurve * > curves_reflex;
        QHash < QString, QwtPlotCurve * > curves_fid_reflex;
        QHash < QString, TableView * > tables;
        QHash < QString, Plot * > plots;

        bool show_spectrum;

        int selected;

        QDir workpath;

        Painter * painter;

        QVBoxLayout * content_layout;
        QGridLayout * plots_layout;
        QGridLayout * tables_plots_layout;
        QGridLayout * table_layout;
        QGridLayout * proteins_layout;
        QGridLayout * groups_layout;
        QGridLayout * distance_layout;

        TableView * table_protein;
        TableView * table_distance;
        TableView * table_groups;

        HistogramPlot * histogram_groups;

        QWidget * peaklist_info;

        QWidget * ui( const QString &, QWidget * );

        QHash < QString, Mode * > modes;

        QxtSpanSlider * plotInterval;

        Mode * mode( const QString & name, QWidget * content = 0 );

        Database * db;

        QVector < QHash < QString, QString > > dendogram;

        void createLayout( void );
        void createWelcomeLayout( void );
        void createProjectLayout( void );
        void createPeaklistLayout( void );
        void createAnalyzerLayout( void );
        void createClusterLayout( void );
        void createHelpLayout( void );

        void createLayout( bool );

        void createSettingsLayout( QWidget * );

        void pk_load( void );

        void createCurve( QString );
        void createTable( QString );

        QVector < QVector < qreal > > distance( QMap < QString, Peaklist * > );
        QVector < QVector < qreal > > distance( QMapIterator < QString, Peaklist * > );
        void distance_table( void );

    public slots :
        void pk_load_file( );
        void pk_load_replica( );

        void pk_super_spectrum( );

        void pk_analyzer( void );
        void pk_buttons( bool );
        void pk_context_menu( const QPoint & );
        void pk_panel_changed( QListWidgetItem * );
        void pk_panel_clicked( QListWidgetItem * );
        void pk_panel_clicked( QListWidgetItem *, bool );
        void pk_panel_clicked_reflex( );

        void pk_edit_info( void );
        void pk_clean( void );
        void pk_merge( void );
        void pk_panel_item_edit( void );
        void pk_panel_item_edited( QWidget * );

        void export_files( void );
        void addDatabase( QAction * );
        void searchDatabase( QAction * );

        void setPlotInterval( int, int );
        void infoChanged( void );
        void modeChanged( int );

        void plotPeakWeigth( int );
        void plotShowSpectrum( int );
        void peaklist_infotab_changed( int );
};

#endif // APPLICATION_H
