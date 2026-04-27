#ifndef LOGGER_BACKEND_H
#define LOGGER_BACKEND_H
#include "logger/logger_types.h"

void logger_add_backend(void (*write)(const DynoraLogEvent*, void*),
    void* user_data);

#endif /* LOGGER_BACKEND_H */
