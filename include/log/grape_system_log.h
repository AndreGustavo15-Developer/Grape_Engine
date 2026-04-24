#ifndef GRAPE_SYSTEM_LOG_H
#define GRAPE_SYSTEM_LOG_H
#include "log/grape_system_log_types.h"

/* ===== API ===== */
void grape_log_init(enum GrapeLogLevel level, GrapeLogCategory category);
void grape_log_set_level(enum GrapeLogLevel level);
void grape_log_set_category_mask(GrapeLogCategory category);

enum GrapeLogLevel grape_log_get_level(void);
GrapeLogCategory grape_log_get_category_mask(void);

// IMPORTANT:
// grape_log_dispatch MUST NOT be called directly by user code.
// Use GRAPE_LOG macros instead.
void grape_log_dispatch(GrapeLogCategory category,
    enum GrapeLogLevel level,
    const char* file,
    uint32_t line,
    const char* function,
    const char* fmt,
    ...);

/* ===== MACROS ===== */
#define GRAPE_LOG(cat, level, fmt, ...)                                   \
    do {                                                                  \
        if ((cat & grape_log_get_category_mask()) &&                      \
            (level) >= grape_log_get_level())                             \
            grape_log_dispatch(cat,                                       \
                level,                                                    \
                __FILE__,                                                 \
                __LINE__,                                                 \
                __func__,                                                 \
                fmt __VA_OPT__(,) __VA_ARGS__);                          \
    } while (0)

#define GRAPE_LOG_DEBUG(cat, fmt, ...)                                    \
    GRAPE_LOG(cat, GRAPE_LEVEL_DEBUG, fmt __VA_OPT__(,) __VA_ARGS__)

#define GRAPE_LOG_INFO(cat, fmt, ...)                                     \
    GRAPE_LOG(cat, GRAPE_LEVEL_INFO, fmt __VA_OPT__(,) __VA_ARGS__)

#define GRAPE_LOG_WARNING(cat, fmt, ...)                                  \
    GRAPE_LOG(cat, GRAPE_LEVEL_WARNING, fmt __VA_OPT__(,) __VA_ARGS__)

#define GRAPE_LOG_ERROR(cat, fmt, ...)                                    \
    GRAPE_LOG(cat, GRAPE_LEVEL_ERROR, fmt __VA_OPT__(,) __VA_ARGS__)

#define GRAPE_LOG_FATAL(cat, fmt, ...)                                    \
    GRAPE_LOG(cat, GRAPE_LEVEL_FATAL, fmt __VA_OPT__(,) __VA_ARGS__)

#endif /* GRAPE_SYSTEM_LOG_H */
