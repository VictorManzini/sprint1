"""
Chatbot GoodWe — ChargeGrid Intelligence | EV ChargeOps
Disciplina: Prompt and Artificial Intelligence — FIAP 2026
Grupo: Victor Manzini, Guilherme Santos, Caio Marinho, Ricardo Tunes, Luiz Conti
"""

# stdlib
import os

# terceiros
import streamlit as st
from dotenv import load_dotenv
import ollama

# ──────────────────────────────────────────────
# Configuração de ambiente
# ──────────────────────────────────────────────
load_dotenv()

OLLAMA_HOST = os.environ.get("OLLAMA_HOST", "http://localhost:11434")
CHATBOT_MODEL = os.environ.get("CHATBOT_MODEL", "llama3")

# ──────────────────────────────────────────────
# System prompt — ChargeAssistente v2
# (atualizado com seção ESCALADA_HUMANA e few-shot)
# ──────────────────────────────────────────────


# Caminho absoluto baseado na localização do chatbot.py
BASE_DIR = os.path.dirname(os.path.abspath(__file__))

PROMPT_PATH = os.path.join(
    BASE_DIR,
    "prompts",
    "system_prompt.md"
)

try:
    with open(PROMPT_PATH, "r", encoding="utf-8") as arquivo:
        SYSTEM_PROMPT = arquivo.read()
except Exception as e:
    raise RuntimeError(
        f"Erro ao carregar o system prompt: {e}"
    )

# ──────────────────────────────────────────────
# Limite de histórico (evita estouro de contexto)
# ──────────────────────────────────────────────
MAX_HISTORICO = 20  # últimas N mensagens (sem contar o system prompt)


def construir_mensagens(historico: list[dict]) -> list[dict]:
    """
    Monta a lista de mensagens para o modelo:
    system prompt fixo + histórico recente limitado.

    Args:
        historico: lista de dicts com chaves 'role' e 'content'.

    Returns:
        Lista formatada para a API do Ollama.
    """
    mensagens = [{"role": "system", "content": SYSTEM_PROMPT}]
    # Mantém apenas as últimas MAX_HISTORICO mensagens
    mensagens += historico[-MAX_HISTORICO:]
    return mensagens


def chamar_modelo(historico: list[dict]) -> str:
    """
    Chama o modelo LLM via Ollama e retorna o texto da resposta.

    Args:
        historico: histórico completo da conversa.

    Returns:
        String com a resposta do modelo.
    """
    cliente = ollama.Client(host=OLLAMA_HOST)
    resposta = cliente.chat(
        model=CHATBOT_MODEL,
        messages=construir_mensagens(historico),
        options={
            "temperature": 0.3,   # baixa = mais consistente e no escopo
            "top_p": 0.9,
            "num_predict": 512,
        },
    )
    return resposta["message"]["content"]


def verificar_turno_resumo(n_turnos: int) -> bool:
    """
    Verifica se é hora de oferecer um resumo da conversa (a cada 5 turnos).

    Args:
        n_turnos: número de turnos do usuário até agora.

    Returns:
        True se deve oferecer resumo.
    """
    return n_turnos > 0 and n_turnos % 5 == 0


# ──────────────────────────────────────────────
# Configuração da página Streamlit
# ──────────────────────────────────────────────
st.set_page_config(
    page_title="ChargeAssistente — GoodWe",
    page_icon="⚡",
    layout="centered",
)

# CSS personalizado — identidade visual GoodWe (verde + cinza escuro)
st.markdown(
    """
    <style>
    /* Fundo geral */
    .stApp { background-color: #0f1117; }

    /* Cabeçalho */
    .header-box {
        background: linear-gradient(135deg, #1a472a 0%, #145a32 100%);
        border-radius: 12px;
        padding: 1.2rem 1.5rem;
        margin-bottom: 1rem;
        display: flex;
        align-items: center;
        gap: 0.8rem;
    }
    .header-box h1 {
        color: #e8f5e9;
        font-size: 1.4rem;
        margin: 0;
        font-weight: 700;
    }
    .header-box p {
        color: #a5d6a7;
        font-size: 0.85rem;
        margin: 0;
    }

    /* Badge de status */
    .status-badge {
        background: #1b5e20;
        color: #69f0ae;
        border-radius: 20px;
        padding: 0.2rem 0.7rem;
        font-size: 0.75rem;
        font-weight: 600;
        display: inline-block;
        margin-bottom: 0.8rem;
    }

    /* Balões de chat */
    [data-testid="stChatMessage"] {
        border-radius: 10px;
        margin-bottom: 0.4rem;
    }

    /* Input */
    .stChatInput textarea {
        background-color: #1e1e2e !important;
        color: #e0e0e0 !important;
        border: 1px solid #2e7d32 !important;
        border-radius: 8px !important;
    }
    </style>
    """,
    unsafe_allow_html=True,
)

# ──────────────────────────────────────────────
# Cabeçalho
# ──────────────────────────────────────────────
st.markdown(
    """
    <div class="header-box">
        <div>
            <h1>⚡ ChargeAssistente</h1>
            <p>GoodWe EV ChargeOps — Suporte ao Morador</p>
        </div>
    </div>
    """,
    unsafe_allow_html=True,
)

st.markdown('<span class="status-badge">🟢 Online</span>', unsafe_allow_html=True)

# ──────────────────────────────────────────────
# Estado da sessão
# ──────────────────────────────────────────────
if "historico" not in st.session_state:
    st.session_state.historico = []       # mensagens user/assistant
if "n_turnos" not in st.session_state:
    st.session_state.n_turnos = 0        # contador de turnos do usuário

# Saudação inicial (apenas uma vez)
if not st.session_state.historico:
    saudacao = (
        "Olá! Sou o **ChargeAssistente**, seu assistente de eletropostos "
        "GoodWe aqui no condomínio. 😊\n\n"
        "Posso te ajudar com:\n"
        "- Disponibilidade e agendamento de pontos de recarga\n"
        "- Como funciona o rateio de consumo\n"
        "- Regras do regimento de uso dos carregadores\n"
        "- Problemas simples (sessão que não inicia, cabo não reconhecido, etc.)\n\n"
        "Como posso te ajudar hoje?"
    )
    st.session_state.historico.append(
        {"role": "assistant", "content": saudacao}
    )

# ──────────────────────────────────────────────
# Renderizar histórico de mensagens
# ──────────────────────────────────────────────
for msg in st.session_state.historico:
    avatar = "⚡" if msg["role"] == "assistant" else "🏠"
    with st.chat_message(msg["role"], avatar=avatar):
        st.markdown(msg["content"])

# ──────────────────────────────────────────────
# Input do usuário
# ──────────────────────────────────────────────
entrada = st.chat_input("Digite sua dúvida sobre os carregadores…")

if entrada:
    # Exibe mensagem do usuário imediatamente
    with st.chat_message("user", avatar="🏠"):
        st.markdown(entrada)

    # Adiciona ao histórico
    st.session_state.historico.append({"role": "user", "content": entrada})
    st.session_state.n_turnos += 1

    # Chama o modelo
    with st.chat_message("assistant", avatar="⚡"):
        with st.spinner("Consultando…"):
            try:
                resposta = chamar_modelo(st.session_state.historico)
            except Exception as erro:
                resposta = (
                    "⚠️ Não consegui me conectar ao modelo agora. "
                    "Verifique se o Ollama está rodando (`ollama serve`) "
                    f"e tente novamente.\n\n_Detalhe técnico: {erro}_"
                )

        st.markdown(resposta)

    # Adiciona resposta ao histórico
    st.session_state.historico.append(
        {"role": "assistant", "content": resposta}
    )

    # Oferta de resumo a cada 5 turnos
    if verificar_turno_resumo(st.session_state.n_turnos):
        st.info(
            "💬 Já conversamos bastante! Quer um resumo do que discutimos? "
            "É só digitar **'resumo'**."
        )

# ──────────────────────────────────────────────
# Sidebar — informações do sistema
# ──────────────────────────────────────────────
with st.sidebar:
    st.markdown("### ⚙️ Configuração")
    st.markdown(f"**Modelo:** `{CHATBOT_MODEL}`")
    st.markdown(f"**Host Ollama:** `{OLLAMA_HOST}`")
    st.markdown(f"**Turnos:** {st.session_state.n_turnos}")
    st.markdown(f"**Mensagens no histórico:** {len(st.session_state.historico)}")

    st.divider()
    st.markdown("### 📋 Perguntas rápidas")
    perguntas_rapidas = [
        "Tem carregador disponível agora?",
        "Como faço para reservar um ponto?",
        "Qual o horário permitido para carregar?",
        "Meu carregamento não iniciou, o que faço?",
        "Como é calculado meu consumo no rateio?",
    ]
    for pq in perguntas_rapidas:
        if st.button(pq, use_container_width=True):
            st.session_state.historico.append({"role": "user", "content": pq})
            st.session_state.n_turnos += 1
            try:
                resp = chamar_modelo(st.session_state.historico)
            except Exception as e:
                resp = f"⚠️ Erro ao conectar ao modelo: {e}"
            st.session_state.historico.append({"role": "assistant", "content": resp})
            st.rerun()

    st.divider()
    if st.button("🗑️ Limpar conversa", use_container_width=True):
        st.session_state.historico = []
        st.session_state.n_turnos = 0
        st.rerun()