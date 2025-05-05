#ifndef SOEM_EXPORT_H
#define SOEM_EXPORT_H

#ifdef SOEM_STATIC_DEFINE
#define SOEM_EXPORT
#define SOEM_NO_EXPORT
#else
#ifndef SOEM_EXPORT
#ifdef soem_EXPORTS
/* We are building this library */
#define SOEM_EXPORT __attribute__((visibility("default")))
#else
/* We are using this library */
#define SOEM_EXPORT __attribute__((visibility("default")))
#endif
#endif

#ifndef SOEM_NO_EXPORT
#define SOEM_NO_EXPORT __attribute__((visibility("hidden")))
#endif
#endif

#ifndef SOEM_DEPRECATED
#define SOEM_DEPRECATED __attribute__((__deprecated__))
#endif

#ifndef SOEM_DEPRECATED_EXPORT
#define SOEM_DEPRECATED_EXPORT SOEM_EXPORT SOEM_DEPRECATED
#endif

#ifndef SOEM_DEPRECATED_NO_EXPORT
#define SOEM_DEPRECATED_NO_EXPORT SOEM_NO_EXPORT SOEM_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#ifndef SOEM_NO_DEPRECATED
#define SOEM_NO_DEPRECATED
#endif
#endif

#endif /* SOEM_EXPORT_H */
