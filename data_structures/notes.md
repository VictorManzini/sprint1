Explicação da lógica do programa:
1- Objetivo, o que o programa faz: 
O objetivo do programa é simular uma recarga de carros elétricos.

2- Fluxo Geral: 
Menu():
 Imprime algumas informações necessárias para o início do programa e guarda o usuário e senha, mesmo que fictícios por enquanto;

capacidade():
 verifica se a energia e o carregador estão conectados via validação do usuário. Loop interno com árvore de decisao, se o usuário digitar 2 para a energia ou para o carregador, o loop volta e verifica novamente até energia e carregador serem 1. Se for digitado algum número menor que 1 ou maior que 2, o programa exibe erro e volta para o começo do loop. 

battery():
 aguarda o input da porcentagem da bateria do carro e verifica se ela é real, ou seja, entre 0% a 100%. A função battery() também verifica a potência da bateria do carro perguntando para o usuário se ele deseja inserir a potência ou deixar o sistema escolher automaticamente, por padrão a potência da bateria ,se o usuário não informar, é de 38.8kWh     que é o padrão em carros elétricos pequenos como o BYD Dolphin Mini;

potencia():
 decide em qual modo de carregamento a simulação vai rodar. Existem dois modos, baseado nos reais, carregamento lento, onde usa corrente alternada e tem potência de 7.4kW e carregamento rápido, onde usa corente contínua e tem potência de 50.0kW. A decisão do usuário impacta diretamente no quanto o carregador consumirá de energia, impactando também no custo da operação;
 
sessao():
 grava a data, com dia da semana, dia, mês e ano e o horário em que a sessão de carregamento começa. 
 Além disso a função calcula uma previsão de quanto tempo a sessão irá durar. As informações que a função sessao() grava são fundamentais para o cálculo de custo, calculando quanto tempo a sessão durou e qual foi a janela de horário que a sessão foi executada;

tarifa():
 antes mesmo de a sessão rodar, o preço que o usuário irá pagar já  foi calculado com as informações que foram geradas pelas funções anteriores. Também ela analisa quando a sessão foi iniciada, se foi em um horário de pico, onde o preço do kWh sobe, se está em um horário intermediário, onde a tarifa costuma ser mais barata do que no horario de pico porém mais cara que o horário fora de ponta e se está em um horário fora de ponta. Eu calculei isso com base nos preços da ENEL de São Paulo capital, os dados de horários que podem ser encontrados na função tarifa() são os horários reais em que a nossa energia custa mais ou menos no dia a dia;

simulacao():
 como o nome já diz, ela simula a recarga, ela pega a porcentagem da bateria inicial e por meio das variáveis já definidas em funções anteriores, recarrega a bateria do veículo com base na capacidade máxima da bateria(100%) e o quanto de bateria tem no veículo;

final():
 exibe um relatório final com data, horario de início da sessão e horario de fim da sessão, kWh consumido, preço e qual o tipo da tarifa que foi cobrada.
