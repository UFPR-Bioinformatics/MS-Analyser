#ifndef MSANALYSER_H
#define MSANALYSER_H

#include <MainWindow>
//#include <Peaklist>
class Peaklist;

#include <QWidget>
#include <QDir>
#include <QFileDialog>
#include <QDirIterator>
#include <QMessageBox>

#include <QDomDocument>
#include <QTableView>

#include "plot.h"
#include "tableview.h"

class MSAnalyser : public QWidget
{
    Q_OBJECT

    public:
        explicit MSAnalyser( QWidget * parent = 0 );

    signals:

    public slots:
        void loadReplica( );
        void loadSingle( );
        void selectionChanged( int, int );

    private :
        QStringList files;

        QList < Peaklist * > peaklist;

        void findFiles( QDir & );
        void load( );
};

#endif // MSANALYSER_H
