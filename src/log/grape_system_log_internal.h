#ifndef GRAPE_SYSTEM_LOG_INTERNAL_H
#define GRAPE_SYSTEM_LOG_INTERNAL_H
#include "log/grape_system_log_types.h"

void grape_log_dispatch(GrapeLogCategory category,
    enum GrapeLogLevel level,
    const char* file,
    uint32_t line,
    const char* function,
    const char* fmt,
    ...);

#endif /* GRAPE_SYSTEM_LOG_INTERNAL_H */
