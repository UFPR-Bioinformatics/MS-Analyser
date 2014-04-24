#ifndef MODEMANAGER_H
#define MODEMANAGER_H

class Application;
class QWidget;

#include <fancytabwidget.h>
#include <QString>
#include <QIcon>

typedef struct Mode
{
    FancyTabWidget * fancy;
    int index;
    QWidget * container;

    Mode( FancyTabWidget * fancy, int index, const QString & name, QWidget * content, const QIcon & icon ) :
        fancy( fancy ), index( index ), container( content )
    {
        fancy -> insertTab( index, content, icon, name );
    }

    Mode * enable( bool enabled = true )
    {
        fancy -> setTabEnabled( index, enabled );

        return this;
    }

    Mode * current( )
    {
        fancy -> setCurrentIndex( index );

        return this;
    }

    QWidget * content( )
    {
        return container;
    }
} Mode;

class ModeManager : public QObject
{
    Q_OBJECT

    public:
        ModeManager( Application * );
        Mode * insert( const QString &, QWidget *, const QIcon & );
        Mode * current( void );
        void statusBar( QString );

    public slots :
        void currentChanged( int );

    signals :
        void modeChanged( int mode );

    private :
        FancyTabWidget * fancy;
        int index;
        int _current;

        QVector < Mode * > mode;
};

#endif // MODEMANAGER_H
