#include "../headers/DBManager.hpp"

DBManager::DBManager(QObject *parent) : QObject(parent)
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("InfluenceDB.sqlite");

    if(!db.open())
    {
        //TODO
    }
}
