#include "databaseinterface.h"

#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>

DatabaseInterface::DatabaseInterface(const QString &path, QObject *parent)
    : QObject(parent)
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(path);

    qDebug() << "Opening database " << path;

    // TODO check and create lockfile?

    if (!m_db.open())
    {
        qDebug() << "Error: connection with database fail";
        m_db_valid = false;
    }
    else
    {
        qDebug() << "Database: connection ok";
         m_db_valid = true;
    }
}

DatabaseInterface::~DatabaseInterface()
{
    if (m_db.isOpen())
        m_db.close();
        // TODO release lockfile?
}

QStringList DatabaseInterface::listRecipies(void)
{
    qDebug() << "Prompting all recipes...";

    QSqlQuery query("SELECT title FROM recipes;");

    QStringList retval;
    query.first();
    do {
        QString title = query.value(0).toString();
        qDebug() << title;
        retval.append(title);
    } while (query.next());

    return retval;
}

QMap<QString, int> DatabaseInterface::listFridgeContents(void)
{

}

Recipe* DatabaseInterface::loadRecipe(QString name)
{

}

