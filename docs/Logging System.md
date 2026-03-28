# 🍇 Grape Engine Logging System

## Documento de Engenharia de Software

---

# 1.  Introdução

O **Grape Engine Logging System** é o subsistema de registro de eventos da Grape Engine. Ele foi projetado para ser **modular, extensível, de baixo acoplamento e adequado para uso em engine**. A ideia central é permitir que qualquer parte da engine gere mensagens de log sem depender diretamente da forma de saída dessas mensagens.

O sistema foi desenhado seguindo a filosofia da Grape Engine:

- **modularidade**: o logger é dividido em partes independentes;
- **plugabilidade**: novos backends podem ser adicionados sem alterar o core;
- **desempenho**: o processamento é simples, previsível e sem alocação dinâmica no caminho principal;
- **clareza**: a API é pequena e fácil de usar;
- **evolução gradual**: o sistema pode crescer para suportar arquivo, rede, overlay, buffers assíncronos e outros destinos.

O logger atual suporta:

- níveis de log: `DEBUG`, `INFO`, `WARNING`, `ERROR`, `FATAL`;
- categorias de log por subsistema: `RENDER`, `AUDIO`, `PHYSICS`, `ECS`, `IO`;
- backends múltiplos;
- contexto adicional por backend via `user_data`;
- filtragem em tempo de execução por nível e categoria.
---

# 2. Objetivo do sistema

O logger resolve um problema muito comum em motores de jogo e aplicações de tempo real:

> Como registrar mensagens de depuração, erro e diagnóstico sem acoplar o código que gera o log ao código que o exibe ou armazena?

A resposta foi separar o sistema em três partes:

- **API pública**: macros e funções visíveis ao usuário da engine.
- **Core do logger**: cria eventos, aplica filtros e distribui para backends.
- **Backends**: recebem eventos e decidem o destino final da mensagem.

Esse modelo permite que a engine continue organizada mesmo quando crescer para muitos módulos.

---

# 3. Arquitetura geral
O sistema foi dividido em arquivos com responsabilidades claras.

#### 3.1. `grape_system_log_types.h`
Contém tipos e definições compartilhadas entre core, backends e usuários.

#### 3.2. `grape_system_log.h`
Contém a API pública do logger e as macros de conveniência.

#### 3.3. `grape_system_log_backend.h`
Contém a interface de registro de backends.

#### 3.4. `grape_system_log_internal.h`
Contém funções internas usadas apenas pelo core.

#### 3.5. `grape_system_log.c`
Contém o estado global do logger, o dispatch e o registro dos backends.

#### 3.6. `grape_backend_console.c`
Implementa o backend de console.

---

# 4. Tipos e estruturas
#### 4.1. Níveis de log
```c
enum GrapeLogLevel {
    GRAPE_LEVEL_DEBUG,
    GRAPE_LEVEL_INFO,
    GRAPE_LEVEL_WARNING,
    GRAPE_LEVEL_ERROR,
    GRAPE_LEVEL_FATAL,
};
```

Os níveis servem para definir a importância da mensagem. A engine pode decidir ignorar mensagens abaixo do nível configurado.

**Interpretação prática**
- `DEBUG` — informação detalhada para desenvolvimento.
- `INFO` — eventos normais do sistema.
- `WARNING` — situação suspeita, mas recuperável.
- `ERROR` — falha real.
- `FATAL` — falha crítica.

Essa separação ajuda na filtragem e na leitura dos logs.

---

#### 4.2. Categorias de log
```c
typedef uint32_t GrapeLogCategory;

#define GRAPE_LOG_RENDER  ((GrapeLogCategory)(1u << 0))
#define GRAPE_LOG_AUDIO   ((GrapeLogCategory)(1u << 1))
#define GRAPE_LOG_PHYSICS ((GrapeLogCategory)(1u << 2))
#define GRAPE_LOG_ECS     ((GrapeLogCategory)(1u << 3))
#define GRAPE_LOG_IO      ((GrapeLogCategory)(1u << 4))

#define GRAPE_LOG_ALL \
    GRAPE_LOG_RENDER | GRAPE_LOG_AUDIO | GRAPE_LOG_PHYSICS | \
    GRAPE_LOG_ECS | GRAPE_LOG_IO
```
As categorias organizam os logs por subsistema.
Exemplos:

- renderização;
- áudio;
- física;
- ECS;
- IO.

A escolha por bitmask permite combinar várias categorias no mesmo valor:
```c
GRAPE_LOG_RENDER | GRAPE_LOG_ECS
```
Isso é útil para filtrar logs de forma rápida.

---

#### 4.3. Estrutura do evento
```c
typedef struct GrapeLogEvent {
    uint64_t timestamp;
    const char* file;
    const char* function;
    uint32_t line;
    uint32_t category;
    uint8_t level;
    const char* message;
    void* user_data;
} GrapeLogEvent;
```
Essa estrutura representa um log já processado pelo core.

**Campos**
- `timestamp`: momento em que o log foi gerado;
- `file`: arquivo de origem;
- `function`: função de origem;
- `line`: linha de origem;
- `category`: categoria do evento;
- `level`: nível do evento;
- `message`: mensagem formatada;
- `user_data`: campo reservado para extensões futuras ou contexto do backend.

**Por que `message` é um ponteiro?**

Porque o core evita copiar conteúdo desnecessário. A mensagem formatada é colocada em um buffer local dentro do dispatch e repassada para os backends como ponteiro. Isso reduz custo e simplifica o processamento.

**Observação importante**

`message` é válido apenas durante a execução síncrona do dispatch. Um backend que queira armazenar a mensagem por mais tempo precisa copiar o conteúdo para a própria memória.

---

#### 4.4. Estrutura do backend
```c
typedef struct Backend {
    void (*write)(const GrapeLogEvent* event, void* user_data);
    void* user_data;
} Backend;
```
Cada backend é uma unidade plugável do sistema.

**Campos**
- `write`: função callback responsável por consumir o evento;
- `user_data`: ponteiro para estado ou contexto específico do backend.

**Exemplo de uso**
backend de console: `user_data = NULL;`
backend de arquivo: `user_data = FILE*;`
backend de rede: `user_data = socket/contexto;`
backend customizado: qualquer estrutura definida pelo usuário.

---

#### 4.5. Estado global do logger
```c
typedef struct GrapeLoggerState {
    enum GrapeLogLevel level;
    Backend backends[16];
    uint32_t backend_count;
    GrapeLogCategory category_mask;
} GrapeLoggerState;

static GrapeLoggerState g_logger;
```
O `g_logger` é o estado central do logger.

**O que ele guarda**
- nível mínimo aceito;
- lista de backends registrados;
- quantidade de backends ativos;
- máscara global de categorias.

**Por que `static?`**
Porque ele deve ser visível apenas dentro do arquivo do core. Assim o resto da engine só interage com ele por meio de funções públicas.

Isso é encapsulamento em C.

---

# 5. API pública

A API pública foi mantida pequena e objetiva.

**Funções principais**
```c
enum GrapeLogLevel grape_log_get_level(void);
GrapeLogCategory grape_log_get_category_mask(void);

void grape_log_init(enum GrapeLogLevel level, GrapeLogCategory category);

void grape_log_dispatch(
    GrapeLogCategory category,
    enum GrapeLogLevel level,
    const char* file,
    uint32_t line,
    const char* function,
    const char* fmt,
    ...
);

void grape_log_add_backend(
    void (*write)(const GrapeLogEvent*, void*),
    void* user_data);
```

**Responsabilidade de cada função**

- `grape_log_init` configura o estado global;
- `grape_log_get_level` retorna o nível ativo;
- `grape_log_get_category_mask` retorna a máscara ativa;
- `grape_log_dispatch` cria o evento e distribui para os backends;
- `grape_log_add_backend` registra um novo backend.

---

# 6. Macros de uso

As macros são a interface mais conveniente para o desenvolvedor.

**Macro base**
```c
#define GRAPE_LOG(cat, level, fmt, ...) \
    do { \
        if ((cat & grape_log_get_category_mask()) && \
            (level) >= grape_log_get_level()) \
            grape_log_dispatch(cat, \
                level, \
                __FILE__, \
                __LINE__, \
                __func__, \
                fmt, \
                ##__VA_ARGS__); \
    } while (0)
```
Essa macro faz duas coisas antes de chamar o dispatch:
1. verifica se a categoria está habilitada;
2. verifica se o nível é aceitável.

Isso evita trabalho desnecessário.

**Macros por nível**
```c
#define GRAPE_LOG_DEBUG(...)
#define GRAPE_LOG_INFO(...)
#define GRAPE_LOG_WARNING(...)
#define GRAPE_LOG_ERROR(...)
#define GRAPE_LOG_FATAL(...)
```
Essas macros apenas preenchem o nível automaticamente, evitando repetição.

---

# 7. Fluxo de dados

O fluxo do sistema é a parte mais importante para entender como tudo funciona.

---
#### 7.1. Fluxo básico
```text
Código do usuário
    ↓
Macro GRAPE_LOG_*
    ↓
Verificação de categoria e nível
    ↓
grape_log_dispatch(...)
    ↓
Criação do GrapeLogEvent
    ↓
Formatação da mensagem
    ↓
Iteração dos backends registrados
    ↓
Backend escolhido processa o evento
```
---

#### 7.2. Fluxo detalhado
```text
┌─────────────────────────────┐
│ Código do desenvolvedor     │
│ GRAPE_LOG_ERROR(...)        │
└─────────────┬───────────────┘
              │
              ▼
┌─────────────────────────────┐
│ Macro do logger             │
│ - captura file              │
│ - captura line              │
│ - captura function          │
│ - aplica filtros            │
└─────────────┬───────────────┘
              │
              ▼
┌─────────────────────────────┐
│ grape_log_dispatch()        │
│ - cria GrapeLogEvent        │
│ - formata message           │
│ - define timestamp          │
│ - preenche categoria/nível  │
└─────────────┬───────────────┘
              │
              ▼
┌─────────────────────────────┐
│ g_logger.backends[]         │
│ - backend 0                 │
│ - backend 1                 │
│ - backend N                 │
└─────────────┬───────────────┘
              │
              ▼
┌─────────────────────────────┐
│ Backend concreto            │
│ console / file / network    │
└─────────────────────────────┘
```

---

# 8. Core do logger

O core é responsável por:
- manter o estado global;
- aplicar filtros de nível e categoria;
- criar o evento;
- distribuir o evento aos backends;
- impedir que o sistema dependa da saída final.

**Lógica central do dispatch**
1. verifica nível;
2. verifica categoria;
3. retorna se não houver backend;
4. formata a mensagem;
5. cria o evento;
6. envia para cada backend.

---

# 9. Backend de console
O backend de console é o primeiro backend concreto do sistema.

**Implementação conceitual**
```c
void console_write(const GrapeLogEvent* event, void* user_data) {
    (void)user_data;
    printf("[%llu] %s:%u %s(): %s\n",
        (unsigned long long)event->timestamp,
        event->file,
        event->line,
        event->function,
        event->message);
}

void grape_backend_console_init(void) {
    grape_log_add_backend(console_write, NULL);
}
```

**Função do backend**
- recebe o evento;
- decide o formato final;
- imprime no terminal.

**Responsabilidade clara**
O backend não participa da criação do evento.
Ele apenas consome o evento já pronto.

---

# 10. Por que o sistema foi desenhado assim
A arquitetura foi escolhida para equilibrar:

- simplicidade;
- modularidade;
- desempenho;
- clareza de responsabilidade.

**Decisões principais**
| Decisão                                       | Motivo                                        |
| --------------------------------------------- | --------------------------------------------- |
| `GrapeLogEvent` exposto no header             | permite backends externos e módulos plugáveis |
| `message` como ponteiro                       | evita cópia desnecessária                     |
| `user_data` em backend                        | permite contexto por backend                  |
| backends plugáveis                            | facilita console, arquivo, rede, overlay      |
| filtros por nível e categoria                 | reduz ruído e custo                           |
| `g_logger` global static                      | centraliza estado sem expor detalhes          |
| macros com `__FILE__`, `__LINE__`, `__func__` | capturam contexto automaticamente             |

---

# 11. Exemplo de uso
```c
int main(void) {
    grape_log_init(GRAPE_LEVEL_FATAL, GRAPE_LOG_RENDER);
    grape_backend_console_init();

    GRAPE_LOG_DEBUG(GRAPE_LOG_RENDER, "Shader carregado com sucesso!");
    GRAPE_LOG_INFO(GRAPE_LOG_AUDIO, "Audio system iniciado");
    GRAPE_LOG_WARNING(GRAPE_LOG_PHYSICS, "Objeto fora do mundo físico");
    GRAPE_LOG_ERROR(GRAPE_LOG_ECS, "Falha ao criar entidade");
    GRAPE_LOG_FATAL(GRAPE_LOG_IO, "Erro crítico: não foi possível salvar o arquivo");

    return 0;
}
```

**O que acontece nesse exemplo**
- o logger é inicializado com nível `FATAL`;
- apenas a categoria `RENDER` está habilitada;
- o backend de console é registrado;
- os logs só passam se satisfizerem os filtros;
- o backend console imprime o evento.

---

# 12. Estrutura de build

O projeto foi organizado para ficar coerente com a arquitetura do logger.

**Exemplo de estrutura**
```text
Grape_Engine/
├── include/
│   └── log/
│       ├── grape_system_log.h
│       ├── grape_system_log_types.h
│       ├── grape_system_log_backend.h
│       └── grape_system_log_internal.h
├── src/
│   └── log/
│       ├── grape_system_log.c
│       └── backends/
│           └── grape_backend_console.c
├── examples/
│   └── test.c
└── CMakeLists.txt
```

**Motivação**
Essa organização separa:
- tipos compartilhados;
- API pública;
- core interno;
- backends concretos;
- exemplos de uso.

---

# 13. Limitações atuais

Como todo sistema em evolução, a versão atual ainda tem algumas limitações intencionais:

#### 13.1. `message` vive na stack do dispatch
Isso significa que os backends precisam usar a mensagem de forma síncrona. Se quiserem persistir a string, precisam copiá-la.

#### 13.2. Sem logging assíncrono

O logger é síncrono. Isso é mais simples e previsível, mas ainda pode evoluir para fila e thread dedicada.

#### 13.3. Número fixo de backends

O sistema usa um array fixo de 16 backends. Isso simplifica a implementação, mas pode ser evoluído depois para estrutura dinâmica.

#### 13.4. Sem formatação visual avançada

Ainda não há cores, prefixos customizados, JSON ou timestamp de alta resolução.

---

# 14. Melhorias futuras
O logger está em uma base boa para crescer. As próximas evoluções naturais são:

#### 14.1. Backend de arquivo
Permite persistir logs em disco.

#### 14.2. Backend de rede
Permite enviar logs para outra máquina ou ferramenta externa.

#### 14.3. Formatação customizada
Permite diferentes estilos de saída por backend.

#### 14.4. Timestamp de alta precisão
Em vez de `time(NULL)`, usar resolução maior.

#### 14.5. Logging assíncrono
Mover a escrita para outra thread para reduzir impacto no frame principal.

#### 14.6. Ring buffer
Armazenar os últimos logs em memória para debug e overlay.

#### 14.7. Filtro por backend
Cada backend pode decidir quais categorias ou níveis quer receber.

#### 14.7. Remover Log em modo release
Colocar algum mecanismo que desativer o log no modo release, ou deixe so
ativo os `ERROR`, `FATAL`