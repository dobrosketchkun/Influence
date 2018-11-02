#include "../headers/DBManager.hpp"

DBManager::DBManager(QObject *parent) : QObject(parent)
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("database.db");
}

QJsonArray DBManager::executeSelectQuery(QString queryString)
{
    QJsonArray jsonArray;
    QSqlQuery query(queryString, db);
    while(query.next())
      {
         QJsonObject recordObject;
         for(int i = 0; i < query.record().count(); i++)
         {
            recordObject.insert(query.record().fieldName(i), QJsonValue::fromVariant(query.value(i)));
         }
         jsonArray.push_back(recordObject);
      }

    return jsonArray;
}

bool DBManager::executeInsertQuery(QString queryString)
{
    QSqlQuery query;
    if(!query.exec(queryString))
    {
        return false;
    }

    return true;
}
