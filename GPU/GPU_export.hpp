
#ifndef GPU_EXPORT_H
#define GPU_EXPORT_H

#ifdef GPU_BUILT_AS_STATIC
#  define GPU_EXPORT
#  define GPU_NO_EXPORT
#else
#  ifndef GPU_EXPORT
#    ifdef GPU_EXPORTS
        /* We are building this library */
#      define GPU_EXPORT __declspec(dllexport)
#    else
        /* We are using this library */
#      define GPU_EXPORT __declspec(dllimport)
#    endif
#  endif

#  ifndef GPU_NO_EXPORT
#    define GPU_NO_EXPORT 
#  endif
#endif

#ifndef GPU_DEPRECATED
#  define GPU_DEPRECATED __declspec(deprecated)
#endif

#ifndef GPU_DEPRECATED_EXPORT
#  define GPU_DEPRECATED_EXPORT GPU_EXPORT GPU_DEPRECATED
#endif

#ifndef GPU_DEPRECATED_NO_EXPORT
#  define GPU_DEPRECATED_NO_EXPORT GPU_NO_EXPORT GPU_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef GPU_NO_DEPRECATED
#    define GPU_NO_DEPRECATED
#  endif
#endif

#endif /* GPU_EXPORT_H */
