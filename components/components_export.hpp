
#ifndef COMPONENTS_EXPORT_H
#define COMPONENTS_EXPORT_H

#ifdef COMPONENTS_BUILT_AS_STATIC
#  define COMPONENTS_EXPORT
#  define COMPONENTS_NO_EXPORT
#else
#  ifndef COMPONENTS_EXPORT
#    ifdef components_EXPORTS
        /* We are building this library */
#      define COMPONENTS_EXPORT __declspec(dllexport)
#    else
        /* We are using this library */
#      define COMPONENTS_EXPORT __declspec(dllimport)
#    endif
#  endif

#  ifndef COMPONENTS_NO_EXPORT
#    define COMPONENTS_NO_EXPORT 
#  endif
#endif

#ifndef COMPONENTS_DEPRECATED
#  define COMPONENTS_DEPRECATED __declspec(deprecated)
#endif

#ifndef COMPONENTS_DEPRECATED_EXPORT
#  define COMPONENTS_DEPRECATED_EXPORT COMPONENTS_EXPORT COMPONENTS_DEPRECATED
#endif

#ifndef COMPONENTS_DEPRECATED_NO_EXPORT
#  define COMPONENTS_DEPRECATED_NO_EXPORT COMPONENTS_NO_EXPORT COMPONENTS_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef COMPONENTS_NO_DEPRECATED
#    define COMPONENTS_NO_DEPRECATED
#  endif
#endif

#endif /* COMPONENTS_EXPORT_H */
