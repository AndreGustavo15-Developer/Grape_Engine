#include "grape_system_log_internal.h"
#include <time.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#define GRAPE_LOGGER_MAX_BACKENDS 16

/* ===== BACKEND ===== */
typedef struct Backend {
    void (*write)(const GrapeLogEvent* event, void* user_data);
    void* user_data;
} Backend;

/* ===== LOGGER STATE ===== */
typedef struct GrapeLoggerState {
    enum GrapeLogLevel level;
    Backend backends[GRAPE_LOGGER_MAX_BACKENDS];
    uint32_t backend_count;
    GrapeLogCategory category_mask;
} GrapeLoggerState;

// não é thread-safe
static GrapeLoggerState g_logger;

/* ===== DISPATCH ===== */
void grape_log_dispatch(GrapeLogCategory category,
    enum GrapeLogLevel level,
    const char* file,
    uint32_t line,
    const char* function,
    const char* fmt,
    ...) {

    if (level < g_logger.level)
        return;
    if (!(g_logger.category_mask & category))
        return;
    if (g_logger.backend_count == 0)
        return;

    GrapeLogEvent event;
    event.timestamp = (uint64_t)time(NULL);
    event.file = file;
    event.function = function;
    event.line = line;
    event.category = category;
    event.level = (uint8_t)level;

    va_list args;
    va_start(args, fmt);
    vsnprintf(event.message, GRAPE_LOG_MESSAGE_MAX, fmt, args);
    va_end(args);
    event.user_data = NULL;

    for (uint32_t i = 0; i < g_logger.backend_count; i++) {
        Backend* backend = &g_logger.backends[i];
        if (backend->write)
            backend->write(&event, backend->user_data);
    }
}

/* ===== INIT ===== */
void grape_log_init(enum GrapeLogLevel level, GrapeLogCategory category) {
    g_logger.level = level;
    g_logger.backend_count = 0;
    g_logger.category_mask = category;
}

/* ===== GET LEVEL ===== */
enum GrapeLogLevel grape_log_get_level(void) { return g_logger.level; }

/* ===== GET CATEGORY ===== */
GrapeLogCategory grape_log_get_category_mask(void) {
    return g_logger.category_mask;
}

/* ===== ADD BACKEND ===== */
void grape_log_add_backend(void (*write)(const GrapeLogEvent*, void*),
    void* user_data) {

    if (!write || g_logger.backend_count >= 16)
        return;

    Backend backend = {.write = write, .user_data = user_data};
    g_logger.backends[g_logger.backend_count++] = backend;
}