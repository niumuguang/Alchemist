#ifndef DEALER_GLOBAL_H
#define DEALER_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(DEALER_LIBRARY)
#  define DEALERSHARED_EXPORT Q_DECL_EXPORT
#else
#  define DEALERSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // DEALER_GLOBAL_H
