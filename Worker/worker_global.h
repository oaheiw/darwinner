#ifndef WORKER_GLOBAL_H
#define WORKER_GLOBAL_H

#include <Qt/qglobal.h>

#ifdef WORKER_LIB
# define WORKER_EXPORT Q_DECL_EXPORT
#else
# define WORKER_EXPORT Q_DECL_IMPORT
#endif

#endif // WORKER_GLOBAL_H
