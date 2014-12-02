#ifndef ACTOR_GLOBAL_H
#define ACTOR_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(ACTOR_LIBRARY)
#  define ACTORSHARED_EXPORT Q_DECL_EXPORT
#else
#  define ACTORSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // ACTOR_GLOBAL_H
