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
    bool storeRecipe(Recipe* newRecipe);

private:

    static QMap<serving_options_type, int> servigToBits;
    static QMap<effort_options_type, int> effortToBits;

    static QMap<serving_options_type, int> populateServing(void);
    static QMap<effort_options_type, int> populateEffort(void);

    QSet<serving_options_type> decodeServing(int servingField);
    int encodeServing(QSet<serving_options_type> servigOptions);
    QSet<effort_options_type> decodeEffort(int effortField);
    int encodeEffort(QSet<effort_options_type> effortOptions);

    QSqlDatabase m_db;
    bool m_db_valid;
};

#endif // DATABASEINTERFACE_H
