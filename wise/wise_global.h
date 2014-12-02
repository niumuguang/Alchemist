#ifndef WISE_GLOBAL_H
#define WISE_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(WISE_LIBRARY)
#  define WISESHARED_EXPORT Q_DECL_EXPORT
#else
#  define WISESHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // WISE_GLOBAL_H
