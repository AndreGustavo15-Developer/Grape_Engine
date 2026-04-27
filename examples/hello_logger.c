#include "logger/logger.h"

// Backend console prototype
void backend_console_init(void);

int main(void) {
    // 1. Start the logger
    logger_init(DYNORA_LEVEL_DEBUG, DYNORA_LOG_ALL);

    // 2. Starts the console backend
    backend_console_init();

    // 3. Test logs
    DYNORA_LOG_DEBUG(DYNORA_LOG_RENDER, "Shader carregado com sucesso!");
    DYNORA_LOG_INFO(DYNORA_LOG_AUDIO, "Audio system iniciado");
    DYNORA_LOG_WARNING(DYNORA_LOG_PHYSICS, "Objeto fora do mundo físico");
    DYNORA_LOG_ERROR(DYNORA_LOG_ECS, "Falha ao criar entidade");
    DYNORA_LOG_FATAL(DYNORA_LOG_GENERAL, "Falha ao iniciar a gameplay");
    DYNORA_LOG_FATAL(DYNORA_LOG_IO,
        "Erro crítico: não foi possível salvar o arquivo");

    return 0;
}
