
# Chatbot GoodWe — ChargeGrid Intelligence | EV ChargeOps

Chatbot conversacional desenvolvido para o **EV Challenge 2026 (FIAP x GoodWe)**,
disciplina **Prompt and Artificial Intelligence** — 1º Ano de Ciência da Computação.

---

## Integrantes

- Victor Manzini - RM: 572123 - turma CCPH
- Guilherme De Oliveira Santos - RM: 572195 - turma CCPH
- Caio Marinho Pereira - RM: 572873 - turma CCPH
- Ricardo Tunes - RM: 555919 - turma CCPH
- Luiz Cesar Conti Salvador - RM: 571305 - turma CCPH

## Problema abordado

Moradores de condomínios com eletropostos compartilhados enfrentam quatro dores
operacionais sem suporte adequado: não sabem se há um ponto de recarga disponível
antes de descer ao estacionamento, desconhecem como seu consumo individual é medido
para o rateio condominial, têm dificuldade em entender as regras do regimento de uso
dos carregadores e, quando algo falha, precisam acionar o síndico para resolver
bloqueios simples. O chatbot atua como interface inteligente entre o morador e a
infraestrutura GoodWe EV ChargeOps, respondendo essas dúvidas em linguagem natural
e reduzindo a fricção operacional do dia a dia.

---

## Persona atendida

**Morador — usuário final do ponto de recarga condominial.**
Escolhemos essa persona porque é o elo mais desassistido da cadeia: o síndico já
dispõe de painéis administrativos, enquanto o morador depende de interfaces técnicas
pouco intuitivas para entender disponibilidade, custos e regras. Ao atender
diretamente quem carrega o carro no dia a dia, o chatbot gera valor imediato e
mensurável — menos chamados ao síndico e maior autonomia do morador.

---

## Contexto escolhido

**Contexto B — EV ChargeOps (uso condominial)**

O chatbot opera no contexto de edifícios residenciais com pontos de recarga
compartilhados entre moradores. As quatro dores operacionais cobertas são:

- **Agendamento e fila:** orientar o morador sobre disponibilidade dos pontos e
  como evitar conflitos quando há mais veículos do que carregadores disponíveis.
- **Rateio de custo:** esclarecer como o consumo individual em kWh é medido por
  sessão para posterior rateio na taxa condominial.
- **Regras do regimento:** responder dúvidas sobre horários permitidos, prioridades
  de uso e restrições definidas pela assembleia do condomínio.
- **Suporte ao morador:** resolver bloqueios simples (cabo não reconhecido, sessão
  que não inicia) sem necessidade de acionar o síndico.

O chatbot **não** cobre: orquestração de potência elétrica, faturamento B2B,
configuração de hardware, gestão de frotas corporativas ou integração com sistemas
de terceiros — mantendo o escopo focado na persona do morador.

---

## Tecnologias utilizadas

- **Modelo:** Llama 3 (8B) via [Ollama](https://ollama.com) — execução 100% local
- **Linguagem:** Python 3.10+
- **Interface:** [Streamlit](https://streamlit.io)
- **Bibliotecas principais:** `ollama` (Python SDK), `streamlit`, `python-dotenv`

### Comparativo de modelos considerados

| Modelo | Prós | Contras | Decisão |
|---|---|---|---|
| **Llama 3 8B (Ollama)** ✅ | Gratuito, local, privado, sem dependência de rede, reproduzível | Requer GPU/CPU adequada; PT ligeiramente inferior ao GPT-4 | **Escolhido** |
| Mistral 7B (Ollama) | Leve, rápido, bom em instruções | Português menos fluente; contexto menor (8k tokens) | Descartado |
| GPT-3.5 / GPT-4 (OpenAI API) | Melhor qualidade em PT, grande contexto | Custo por token, exposição de dados, dependência de internet | Descartado |
| Llama 3 70B (Ollama) | Qualidade próxima ao GPT-4 | Requer ~40 GB de VRAM — inviável em hardware acadêmico | Descartado |
| Hugging Face Inference API | Sem setup local | Rate limits no plano gratuito, latência, token exposto no repo | Descartado |

### Comparativo de interfaces consideradas

| Interface | Prós | Contras | Decisão |
|---|---|---|---|
| **Streamlit** ✅ | Fácil de usar, componentes de chat nativos (`st.chat_message`), deploy simples | Menos flexível para layouts complexos | **Escolhida** |
| Gradio | Ideal para demos rápidas de ML | Customização limitada; visual mais genérico | Descartado |
| Terminal (rich) | Zero dependências de UI | Não demonstrável em vídeo com qualidade profissional | Descartado |

---

## Justificativa técnica

**Por que Llama 3 8B + Ollama?**
O Llama 3 da Meta oferece a melhor relação qualidade/custo para português entre os
modelos open-source de até 10B parâmetros. O Ollama abstrai quantização e serving
em um único binário, tornando a demo 100% reproduzível offline sem expor tokens de
API em repositórios públicos — requisito crítico num projeto acadêmico aberto.

**Por que Streamlit?**
O Streamlit oferece componentes de chat nativos (`st.chat_message`, `st.chat_input`)
que mapeiam diretamente para a UX de um chatbot, com histórico de conversa gerenciado
via `st.session_state`. Isso mantém o código enxuto e focado na lógica de prompting,
sem desviar atenção para frontend — alinhado aos objetivos pedagógicos da disciplina.

**Por que não APIs externas?**
APIs externas introduzem custo por token, latência de rede e risco de vazamento de
dados do morador. Como o chatbot lida com informações de consumo energético e rotina
de uso do veículo, manter o processamento local é uma decisão alinhada à LGPD.

---

## Como executar

### Pré-requisitos

1. Instale o [Ollama](https://ollama.com/download) para seu sistema operacional.
2. Baixe o modelo Llama 3:

```bash
ollama pull llama3
```

### Instalação do projeto

```bash
git clone https://github.com/VictorManzini/sprint1.git
cd sprint1/prompt_ia
pip install -r requirements.txt
```

### Executar o chatbot

```bash
streamlit run chatbot.py
```

> O Ollama precisa estar rodando em background (`ollama serve`) antes de iniciar
> o chatbot. Na maioria dos sistemas ele sobe automaticamente após a instalação.

### Variáveis de ambiente (opcional)

| Variável | Padrão | Descrição |
|---|---|---|
| `OLLAMA_HOST` | `http://localhost:11434` | Endpoint do servidor Ollama |
| `CHATBOT_MODEL` | `llama3` | Nome do modelo a usar |

Crie um arquivo `.env` na raiz com os valores desejados (o `.gitignore` já o
ignora por padrão).

---

## Estrutura do projeto

```
prompt_ia/
├── README.md                        # Este arquivo
├── .gitignore                       # Ignora .env, __pycache__, etc.
├── requirements.txt                 # Dependências Python
├── chatbot.py                       # Aplicação Streamlit principal
├── docs/
│   └── fluxograma.png               # Diagrama do fluxo do chatbot
├── prompts/
│   └── system_prompt.md             # System prompt comentado por blocos
└── tests/
    └── modelo_de_teste.md           # 5+ perguntas, respostas esperadas e categorias
```

---

## Exemplos de perguntas suportadas

- _"Tem ponto de recarga disponível agora?"_
- _"Como é calculado o meu consumo no rateio do condomínio?"_
- _"Qual o horário permitido para carregar o carro?"_
- _"Meu carregamento não iniciou, o que eu faço?"_
- _"Posso reservar um ponto para amanhã de manhã?"_

---

## Licença

Projeto acadêmico — FIAP 2026. Uso restrito aos fins educacionais do EV Challenge.
