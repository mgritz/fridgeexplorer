#ifndef GLOBALSETTINGS_H
#define GLOBALSETTINGS_H

#include <QSettings>

/** INI contents:
 *
 * database/
 *  path : Full path to database file including filename.
 */
extern QSettings* globalSettings;

#endif // GLOBALSETTINGS_H
