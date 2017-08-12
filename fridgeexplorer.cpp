#include "fridgeexplorer.h"
#include "ui_fridgeexplorer.h"

#include "globalsettings.h"

#include <QDebug>
#include <QTime>

Fridgeexplorer::Fridgeexplorer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Fridgeexplorer)
{
    m_productHandler = new ProductHandling(this);
    m_recipeManager = new RecipeManager(this);

    if (globalSettings == NULL)
    {
        globalSettings = new QSettings(QSettings::IniFormat,
                                       QSettings::UserScope,
                                       "openNom", "fridgeexplorer");
        qDebug() << "Using INI file form " << globalSettings->fileName();
    } else {
        qWarning() << "INI file already installed.";
    }

    startTimer(1000);
    ui->setupUi(this);
    // Controls for product handler window
    QObject::connect(ui->button_add, &QPushButton::clicked, this, &Fridgeexplorer::showProductHandling_add);
    QObject::connect(ui->button_remove, &QPushButton::clicked, this, &Fridgeexplorer::showProductHandling_rem);
    // Controls for recipe management window
    QObject::connect(ui->actionmanage_recipes, &QAction::triggered , this, &Fridgeexplorer::showRecipeManager);
}

Fridgeexplorer::~Fridgeexplorer()
{
    m_productHandler->close();
    delete m_productHandler;
    m_productHandler = NULL;

    m_recipeManager->close();
    delete m_recipeManager;
    m_recipeManager = NULL;

    if (globalSettings != NULL)
    {
        globalSettings->sync();
        delete globalSettings;
    }

    delete ui;
}

void Fridgeexplorer::timerEvent(QTimerEvent * event)
{
    ui->label_time->setText(QTime::currentTime().toString("hh:mm:ss t"));
}

void Fridgeexplorer::showProductHandling_add()
{
    m_productHandler->setMode(true);
    m_productHandler->show();
}

void Fridgeexplorer::showProductHandling_rem()
{
    m_productHandler->setMode(false);
    m_productHandler->show();
}

void Fridgeexplorer::showRecipeManager()
{
    // TODO Initialize the class correctly.
    m_recipeManager->show();
}
