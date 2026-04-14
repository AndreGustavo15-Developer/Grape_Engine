# 🍇 Contributing to Grape Engine

Obrigado por contribuir com a Grape Engine!

Este documento define padrões e diretrizes para manter o projeto consistente, performático e alinhado com sua filosofia: **modularidade, performance extrema e arquitetura viva**.

---

# 🧠 Filosofia do Projeto

A Grape Engine segue três princípios principais:

* ⚡ Performance extrema (hot paths devem ser mínimos e previsíveis)
* 🧱 Modularidade (componentes desacoplados e substituíveis)
* 🍇 Arquitetura viva (sistemas evoluem sem quebrar o núcleo)

Antes de contribuir, considere sempre:

> “Essa mudança mantém o sistema simples, rápido e desacoplado?”

---

# 🛠️ Como Contribuir

## 1. Fork & Branch

Crie uma branch descritiva:

```bash
git checkout -b feat/logger-ring-buffer
```

## 2. Faça mudanças pequenas e focadas

Evite commits gigantes.

✔ Bom:

* Um commit por problema
* Um commit por feature

❌ Ruim:

* Misturar refactor + feature + bugfix

## 3. Siga o padrão de commits

Formato obrigatório:

```bash
type(scope): descrição curta
```

---

## 🧾 Tipos de Commit

| Tipo       | Uso                     |
| ---------- | ----------------------- |
| `feat`     | Nova funcionalidade     |
| `fix`      | Correção de bug         |
| `perf`     | Melhoria de performance |
| `refactor` | Mudança estrutural      |
| `docs`     | Documentação            |
| `build`    | Build/configuração      |
| `test`     | Testes                  |

---

## 🧩 Scopes

Use o sistema afetado:

* `logger`
* `ecs`
* `renderer`
* `physics`
* `audio`
* `io`
* `core`
* `memory`
* `platform`
* `tools`
* `editor`

---

## ✍️ Regras de Commit

* Use verbo no imperativo (add, fix, remove, improve)
* Máximo de 72 caracteres na primeira linha
* Não use ponto final
* Sempre use `scope`
* Seja claro e direto

---

## 🧪 Exemplos de Commits

```bash
fix(logger): avoid dangling pointer in log message

feat(logger): add ring buffer for async logging

perf(logger): remove time() call from hot path

refactor(logger): separate dispatch from backend execution
```

---

# 🧪 Código e Performance

## ⚡ Hot Path Rules (IMPORTANTE)

Código crítico (ex: logger, ECS, renderer):

* ❌ Não usar malloc/free

* ❌ Evitar chamadas pesadas (`printf`, `time`, etc.)

* ❌ Evitar branches desnecessários

* ❌ Nunca executar I/O no hot path

* ✔ Preferir estruturas contínuas (arrays, buffers)

* ✔ Cache-friendly

* ✔ Determinístico

---

## 📝 Logging

* Logs devem ser **self-contained**
* Nunca usar ponteiros para memória temporária (stack/local)
* Eventos devem ser seguros para uso assíncrono
* O logger não deve bloquear o hot path

---

## 🧱 Modularidade

* Evite dependências diretas entre sistemas
* Use interfaces simples (function pointers, structs)
* Pense em DLL/plugin desde o início

---

# 🧹 Código

* Código claro > código “esperto”
* Evite macros complexas sem necessidade
* Prefira C simples e previsível

---

# 📚 Documentação

Se sua mudança:

* altera comportamento
* muda API
* adiciona sistema

👉 Atualize a documentação

---

# 🚀 Pull Request

Antes de abrir PR:

* [ ] Código compila
* [ ] Segue padrão de commits
* [ ] Não quebra API existente (ou documenta)
* [ ] Não introduz custo desnecessário no hot path
* [ ] Está alinhado com a filosofia da engine

---

# 🏗️ Diretrizes de Arquitetura

* Dados devem ser self-contained ao atravessar sistemas
* Evite dependência de estado global implícito
* Prefira composição em vez de acoplamento direto
* Sistemas devem ser substituíveis (plugável / DLL-friendly)

---

# 🧭 Direção do Projeto

A Grape Engine NÃO busca:

* abstração excessiva
* complexidade desnecessária
* overengineering

A Grape Engine busca:

* simplicidade
* previsibilidade
* performance real

---

# 💬 Dúvidas

Se estiver em dúvida:

> escolha a solução mais simples, previsível e performática — sempre priorizando o hot path

---

🍇 Obrigado por contribuir com a Grape Engine!
