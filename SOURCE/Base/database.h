#ifndef DATABASE_H
#define DATABASE_H

#include <QtSql>

class Database : public QSqlDatabase
{
    public:
        explicit Database( );
        explicit Database( const QString & type );
        explicit Database( QSqlDriver * driver );

        QSqlQuery * q;
        QSqlRecord rec;

        void prepare( const QString & query );
        void bind( const QString &, const QVariant & );
        QSqlQuery * query( );

        QSqlRecord record( );

    signals:

    public slots:

};

#endif // DATABASE_H
