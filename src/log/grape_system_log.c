#include "grape_system_log_internal.h"
#include <stdarg.h>
#include <stdio.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <time.h>
#endif

#define GRAPE_LOGGER_MAX_BACKENDS 16

/* ===== BACKEND ===== */
typedef struct Backend {
    void (*write)(const GrapeLogEvent* event, void* user_data);
    void* user_data;
} Backend;

/* ===== LOGGER STATE ===== */
typedef struct GrapeLoggerState {
    uint64_t counter;
    enum GrapeLogLevel level;
    Backend backends[GRAPE_LOGGER_MAX_BACKENDS];
    uint32_t backend_count;
    GrapeLogCategory category_mask;
} GrapeLoggerState;

// não é thread-safe
static GrapeLoggerState g_log_state;

/* ===== TIME ===== */
#ifdef _WIN32
static inline uint64_t grape_time_now_ns(void) {
    static LARGE_INTEGER freq = {0};

    if (freq.QuadPart == 0) {
        QueryPerformanceFrequency(&freq);
    }

    LARGE_INTEGER now;
    QueryPerformanceCounter(&now);

    return (uint64_t)((now.QuadPart * 1000000000ULL) / freq.QuadPart);
}
#else
static inline uint64_t grape_time_now_ns(void) {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (uint64_t)ts.tv_sec * 1000000000ULL + (uint64_t)ts.tv_nsec;
}
#endif

/* ===== DISPATCH ===== */
void grape_log_dispatch(GrapeLogCategory category,
    enum GrapeLogLevel level,
    const char* file,
    uint32_t line,
    const char* function,
    const char* fmt,
    ...) {

    if (g_log_state.backend_count == 0)
        return;

    GrapeLogEvent event;
    event.timestamp = grape_time_now_ns();
    event.sequence = g_log_state.counter++;
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

    // WARNING:
    // Event memory is only valid during backend write call.
    // Backends must NOT store pointers to event fields.
    // If persistence is required, data must be copied.
    for (uint32_t i = 0; i < g_log_state.backend_count; i++) {
        const Backend* backend = &g_log_state.backends[i];
        if (backend->write)
            backend->write(&event, backend->user_data);
    }
}

/* ===== API ===== */
void grape_log_init(enum GrapeLogLevel level, GrapeLogCategory category) {
    g_log_state.level = level;
    g_log_state.backend_count = 0;
    g_log_state.category_mask = category;
    g_log_state.counter = 0;
}

void grape_log_set_level(enum GrapeLogLevel level) {
    g_log_state.level = level;
}

void grape_log_set_category_mask(GrapeLogCategory category) {
    g_log_state.category_mask = category;
}

/* ===== GET LEVEL ===== */
enum GrapeLogLevel grape_log_get_level(void) { return g_log_state.level; }

/* ===== GET CATEGORY ===== */
GrapeLogCategory grape_log_get_category_mask(void) {
    return g_log_state.category_mask;
}

/* ===== ADD BACKEND ===== */
void grape_log_add_backend(void (*write)(const GrapeLogEvent*, void*),
    void* user_data) {

    if (!write || g_log_state.backend_count >= GRAPE_LOGGER_MAX_BACKENDS)
        return;

    Backend backend = {.write = write, .user_data = user_data};
    g_log_state.backends[g_log_state.backend_count++] = backend;
}