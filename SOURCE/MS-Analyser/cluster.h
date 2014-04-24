#ifndef CLUSTER_H
#define CLUSTER_H

#include <QWidget>

class ClusterPainter : public QWidget
{
    Q_OBJECT
public:
    explicit ClusterPainter(QWidget *parent = 0);
    void paintEvent( QPaintEvent * event );
    
signals:

public slots:
    
};

#endif // CLUSTER_H
