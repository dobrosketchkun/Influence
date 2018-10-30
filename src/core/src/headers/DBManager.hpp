#pragma once

#include <QObject>
#include <QtSql>

class DBManager : public QObject
{
    Q_OBJECT
    public:
        explicit DBManager(QObject *parent = nullptr);

    private:
        QSqlDatabase db;
};
