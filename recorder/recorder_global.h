#ifndef RECORDER_GLOBAL_H
#define RECORDER_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(RECORDER_LIBRARY)
#  define RECORDERSHARED_EXPORT Q_DECL_EXPORT
#else
#  define RECORDERSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // RECORDER_GLOBAL_H
