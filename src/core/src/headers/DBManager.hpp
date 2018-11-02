#pragma once

#include <QObject>
#include <QJsonObject>
#include <QJsonArray>
#include <QtSql>

class DBManager : public QObject
{
    Q_OBJECT

    public:
        explicit DBManager(QObject *parent = nullptr);
    protected:
        QSqlDatabase db;
        virtual void createDB() = 0;
        QJsonArray executeSelectQuery(QString query);
        bool executeInsertQuery(QString queryString);
};
