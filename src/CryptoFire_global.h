#ifndef CRYPTOFIRE_GLOBAL_H
#define CRYPTOFIRE_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(CRYPTOFIRE_LIBRARY)
#  define CRYPTOFIRE_EXPORT Q_DECL_EXPORT
#else
#  define CRYPTOFIRE_EXPORT Q_DECL_IMPORT
#endif

#endif // CRYPTOFIRE_GLOBAL_H