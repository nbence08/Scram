
#ifndef IO_EXPORT_H
#define IO_EXPORT_H

#ifdef IO_BUILT_AS_STATIC
#  define IO_EXPORT
#  define IO_NO_EXPORT
#else
#  ifndef IO_EXPORT
#    ifdef IO_EXPORTS
        /* We are building this library */
#      define IO_EXPORT __declspec(dllexport)
#    else
        /* We are using this library */
#      define IO_EXPORT __declspec(dllimport)
#    endif
#  endif

#  ifndef IO_NO_EXPORT
#    define IO_NO_EXPORT 
#  endif
#endif

#ifndef IO_DEPRECATED
#  define IO_DEPRECATED __declspec(deprecated)
#endif

#ifndef IO_DEPRECATED_EXPORT
#  define IO_DEPRECATED_EXPORT IO_EXPORT IO_DEPRECATED
#endif

#ifndef IO_DEPRECATED_NO_EXPORT
#  define IO_DEPRECATED_NO_EXPORT IO_NO_EXPORT IO_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef IO_NO_DEPRECATED
#    define IO_NO_DEPRECATED
#  endif
#endif

#endif /* IO_EXPORT_H */
