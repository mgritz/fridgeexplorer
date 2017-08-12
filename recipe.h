#ifndef RECIPE_H
#define RECIPE_H

#include <QObject>
#include <QSet>
#include <QString>
#include <QMap>

#include "recipemanager.h"

typedef enum{
    SERVE_DESSERT = 0x10,
    SERVE_TAKE = 0x08,
    SERVE_DINNER = 0x04,
    SERVE_LUNCH = 0x02,
    SERVE_BREAKFAST = 0x01
} serving_options_type;

typedef enum{
    EFFORT_DIFFICULT = 0x02,
    EFFORT_WAITING = 0x01
} effort_options_type;

class Recipe : public QObject
{
    Q_OBJECT
public:
    /** defines Recipe from arguments */
    explicit Recipe(const QString& name,
                    const QString& location,
                    const QSet<serving_options_type> serving,
                    const QSet<effort_options_type> effort,
                    QObject *parent = nullptr);

    bool registerIngredient(const QString& ingredient, const int amount);

    void fillOutUi(Ui::RecipeManager *ui);

private:
    int m_id;
   QString m_title;
   QString m_location;
   int m_requiredTime;
   QSet<serving_options_type> m_serving;
   QSet<effort_options_type> m_effort;

   QMap<QString, int> m_ingredients;
};

#endif // RECIPE_H
