#ifndef LISTWIDGET_H
#define LISTWIDGET_H

#include <QListWidget>

class ListWidget : public QListWidget
{
    public:
        ListWidget( QWidget * );

    protected :
        void mousePressEvent( QMouseEvent * );
        void mouseReleaseEvent( QMouseEvent * );
        void customContextMenuRequested( const QPoint & );
        void contextMenuEvent( QContextMenuEvent * );

    private :
        QWidget * parent;
};

#endif // LISTWIDGET_H
