#ifndef EXPORT_GLOBAL_H
#define EXPORT_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(EXPORT_LIBRARY)
#  define DCOGNI_EXPORT Q_DECL_EXPORT
#else
#  define DCOGNI_EXPORT Q_DECL_IMPORT
#endif

#endif // EXPORT_GLOBAL_H
