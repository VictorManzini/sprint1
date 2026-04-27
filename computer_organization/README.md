Entregavel:
Projeto de Tomadas Inteligentes

a) (3 pontos) Desenvolver, no simulador Wokwi, um projeto capaz de medir a corrente elétrica em uma tomada, utilizando o microcontrolador ESP32;

b) (3 pontos) Integrar ao sistema um relé de estado sólido, permitindo o controle (ligar/desligar) da tomada por meio de comandos do ESP32;

c) (2 pontos) Desenvolver o programa embarcado no ESP32 responsável por realizar a leitura da corrente elétrica e possibilitar o acionamento remoto do relé.

d) (2 pontos) Explicar como o sistema acima pode ser implementado ao projeto do Challenge para proteger o sistema de carga de carros elétricos.

#Apenas a versão atual estará disponível na pasta do projeto.
Versões: 

Mark0.1-beta:
Simulação símples, com apenas 3 componentes, ESP32, Relé, potenciômetro. 
Modo de funcionamento: O potenciômetro envia o valor para o ESP32, valores de 0 a 4093. O ESP32
lê os valores avalia, se o valor recebido for maior que 2047, o ESP32 envia um input para o relé abrir e não 
deixar o valor seguir a diante; se o valor for menor que 2047, o ESP32 envia um inpt para o relé fechar e deixar o valor seguir.
O que precisa melhorar: O uso do potenciômetro impossibilita o uso de valores reais de corrente e tensão,
impossibilitando o cálculo de potência e consumo. Mesmo se adicionarmos um potenciômetro dedicado para tensão 
e outro para corrente, o cálculo não seria possível. 
O protótipo Mark0.1-beta não possúi display, impossibilitando a visualização dos valores sem o uso de um terminal do ESP32.
Notas:
O protótipo Mark0.1-beta é apenas a lógica do produto final. Melhorias serão implementadas na próxima versão.
Data de fim da versão: Mark0.1-beta encerrada 26/04/2026.

Mark1-beta:
Início: 27/04/2026
