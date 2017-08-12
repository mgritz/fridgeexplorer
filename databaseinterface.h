#ifndef DATABASEINTERFACE_H
#define DATABASEINTERFACE_H

#include <QObject>
#include <QMap>
#include <QSqlDatabase>
#include <QStringList>

#include "recipe.h"

class DatabaseInterface : public QObject
{
    Q_OBJECT
public:
    explicit DatabaseInterface(const QString& path, QObject *parent = nullptr);
    ~DatabaseInterface();

    bool isValid() {return m_db_valid; }
    QStringList listRecipies(void);
    QMap<QString, int> listFridgeContents(void);
    Recipe* loadRecipe(QString name);

private:
    QSqlDatabase m_db;
    bool m_db_valid;
};

#endif // DATABASEINTERFACE_H
