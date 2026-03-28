#ifndef GRAPE_SYSTEM_LOG_BACKEND_H
#define GRAPE_SYSTEM_LOG_BACKEND_H
#include "log/grape_system_log_types.h"

void grape_log_add_backend(void (*write)(const GrapeLogEvent*, void*),
    void* user_data);

#endif /* GRAPE_SYSTEM_LOG_BACKEND_H */