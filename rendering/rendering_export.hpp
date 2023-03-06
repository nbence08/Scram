
#ifndef RENDERING_EXPORT_H
#define RENDERING_EXPORT_H

#ifdef RENDERING_BUILT_AS_STATIC
#  define RENDERING_EXPORT
#  define RENDERING_NO_EXPORT
#else
#  ifndef RENDERING_EXPORT
#    ifdef rendering_EXPORTS
        /* We are building this library */
#      define RENDERING_EXPORT __declspec(dllexport)
#    else
        /* We are using this library */
#      define RENDERING_EXPORT __declspec(dllimport)
#    endif
#  endif

#  ifndef RENDERING_NO_EXPORT
#    define RENDERING_NO_EXPORT 
#  endif
#endif

#ifndef RENDERING_DEPRECATED
#  define RENDERING_DEPRECATED __declspec(deprecated)
#endif

#ifndef RENDERING_DEPRECATED_EXPORT
#  define RENDERING_DEPRECATED_EXPORT RENDERING_EXPORT RENDERING_DEPRECATED
#endif

#ifndef RENDERING_DEPRECATED_NO_EXPORT
#  define RENDERING_DEPRECATED_NO_EXPORT RENDERING_NO_EXPORT RENDERING_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef RENDERING_NO_DEPRECATED
#    define RENDERING_NO_DEPRECATED
#  endif
#endif

#endif /* RENDERING_EXPORT_H */
