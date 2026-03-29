#ifndef GRAPE_SYSTEM_LOG_TYPES_H
#define GRAPE_SYSTEM_LOG_TYPES_H
#include <stdint.h>

/* ===== LEVEL ===== */
enum GrapeLogLevel {
    GRAPE_LEVEL_DEBUG,
    GRAPE_LEVEL_INFO,
    GRAPE_LEVEL_WARNING,
    GRAPE_LEVEL_ERROR,
    GRAPE_LEVEL_FATAL,
};

/* ===== TYPES ===== */
typedef uint32_t GrapeLogCategory;

typedef struct GrapeLogEvent {
    uint64_t timestamp;   // Momento do log
    const char* file;     // Arquivo onde ocorreu
    const char* function; // Função onde ocorreu
    uint32_t line;        // Linha do código
    uint32_t category;    // Categoria (bitmask)
    uint8_t level;        // Nível do log
    const char* message;  // Ponteiro para a mensagem formatada
    void* user_data;      // Opcional para backends avançados
} GrapeLogEvent;

// Move defines category to grape_system_log_h after adding new system
// backends
/* ===== CATEGORY ===== */
#define GRAPE_LOG_RENDER ((GrapeLogCategory)(1u << 0))
#define GRAPE_LOG_AUDIO ((GrapeLogCategory)(1u << 1))
#define GRAPE_LOG_PHYSICS ((GrapeLogCategory)(1u << 2))
#define GRAPE_LOG_ECS ((GrapeLogCategory)(1u << 3))
#define GRAPE_LOG_IO ((GrapeLogCategory)(1u << 4))
#define GRAPE_LOG_GENERAL ((GrapeLogCategory)(1u << 5))

// Use just on function grape_log_init()
#define GRAPE_LOG_NONE ((GrapeLogCategory)0)
#define GRAPE_LOG_ALL                                                     \
    (GRAPE_LOG_RENDER | GRAPE_LOG_AUDIO | GRAPE_LOG_PHYSICS |             \
        GRAPE_LOG_ECS | GRAPE_LOG_IO | GRAPE_LOG_GENERAL)

#endif /* GRAPE_SYSTEM_LOG_TYPES_H */
