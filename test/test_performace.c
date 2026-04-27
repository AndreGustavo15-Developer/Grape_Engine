#include "log/grape_system_log.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// backend
void grape_backend_console_init(void);

#define TEST_ITERATIONS 10000000

static const char* random_string(void) {
    static const char* messages[] = {
        "Shader carregado",
        "Erro ao compilar shader",
        "Player spawnado",
        "Colisão detectada",
        "Falha na física",
        "Arquivo não encontrado",
        "Rede desconectada",
        "Som reproduzido",
        "IA atualizada",
        "Frame renderizado"
    };

    return messages[rand() % 10];
}

static GrapeLogCategory random_category(void) {
    GrapeLogCategory cats[] = {
        GRAPE_LOG_RENDER,
        GRAPE_LOG_AUDIO,
        GRAPE_LOG_PHYSICS,
        GRAPE_LOG_ECS,
        GRAPE_LOG_IO
    };
    return cats[rand() % 5];
}

static enum GrapeLogLevel random_level(void) {
    return rand() % 5;
}

int main(void) {
    srand((unsigned int)time(NULL));

    printf("=== Grape Log Stress Test ===\n");

    // 🔧 Inicialização
    grape_log_init(GRAPE_LEVEL_DEBUG, GRAPE_LOG_ALL);
    grape_backend_console_init();

    clock_t start = clock();

    // 🔥 Loop massivo
    for (int i = 0; i < TEST_ITERATIONS; i++) {

        GrapeLogCategory cat = random_category();
        enum GrapeLogLevel level = random_level();

        const char* msg = random_string();

        GRAPE_LOG(cat, level,
            "[%d] %s | value=%d | float=%.2f",
            i,
            msg,
            rand() % 1000,
            (float)rand() / RAND_MAX * 100.0f
        );

        // 🧪 Simula burst (pico) ddd
        if (i % 10000 == 0) {
            printf("Checkpoint: %d logs\n", i);
        }
    }

    clock_t end = clock();

    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;

    printf("\n=== RESULTADO ===\n");
    printf("Total logs: %d\n", TEST_ITERATIONS);
    printf("Tempo: %.2f segundos\n", time_spent);
    printf("Logs/segundo: %.2f\n", TEST_ITERATIONS / time_spent);

    return 0;
}