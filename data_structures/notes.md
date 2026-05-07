O fluxo tem 5 fases principais:
Autenticação — RFID/ID do usuário com laço de rejeição em caso de ID inválido.
Controle de energia — verifica se o sistema tem capacidade disponível antes de liberar a sessão (simula o gerenciamento de demanda que o ChargeGrid precisa fazer).
Sessão ativa — loop de monitoramento contínuo (kWh acumulado, potência) com decisão de encerramento — por botão do usuário, carga completa ou tempo limite.
Cobrança — aplica a tarifa sobre o kWh consumido (aqui é onde entram as regras de tarifação dinâmica, se o projeto exigir).
Registro e exibição — salva os dados e exibe o relatório da sessão.
Antes de codificar: a decisão mais importante que você precisa tomar é como vai simular o tempo real em C. Vai usar sleep() com incrementos fixos de kWh, ou vai pedir entrada do usuário para simular o avanço da sessão? Isso define boa parte da estrutura do seu main.