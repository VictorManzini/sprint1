Orientações gerais:  

1. 2. Esta atividade será realizada conforme os grupos do Challenge; 

2. A Challenge Sprint I vale 10 pontos; 

3. O prazo de entrega final é até 22/05/2026 (sexta-feira);

4. As questões podem ser respondidas a partir de códigos escritos em Python, seja na forma de computação simbólica (exemplo: sympy) ou computação numérica (exemplo: numpy e scipy). 

Descrição:  

Uma plataforma monitora e controla a potência elétrica entregue a veículos  em um eletroposto comercial. Suponha que, em uma determinada sessão  de recarga controlada, a potência instantânea total entregue pelo sistema,  em kW, seja modelada por 

P(t) = 18 + 24t / t + 2         t >= 0

em que t representa o tempo, em minutos, contado a partir do início da  sessão. 

Entrega final:

Um Jupyter Notebook, com código escrito em Python. Ele deve conter tanto os códigos que realizam as operações matemáticas e os textos respondendo as perguntas. Todas as células de código devem ser executadas, para que os outputs e as imagens estejam salvas no arquivo final 

Perguntas: 

a. Elabore o gráfico desta função racional dentro de um intervalo de tempo adequado. (1 ponto)

b. Qual o valor do limite de P(t) para t ? 0+? E para t ? 8? Pode ser utilizada computação simbólica com este propósito. Explique o que esses valores representam para o comportamento da recarga ao longo do tempo.  (2 pontos)

c. Calcule a variação média da potência entre t = 1 e t = 3. O que  esses resultados indicam para o gerenciamento da infraestrutura?   (1 ponto)

d. Determine a derivada analítica de P(t), denotada P'(t). Pode ser utilizada computação simbólica com este propósito. (1 ponto)

e. Avalie numericamente P'(1) e P'(6) e compare os resultados. Para isso, basta substituir o valor no argumento no lugar de x. (1 ponto)

f. A partir do gráfico de P(t), podemos analisar em que intervalos a potência está  aumentando e diminuindo. Como que a derivada P’(t) se relaciona com esses comportamentos? (2 pontos)

g. Este modelo pode ser visto como uma representação idealizada de recarga controlada. Caso a gente fosse capaz de ter um modelo cada vez mais preciso, como poderíamos utilizá-lo na proposta do sistema desenvolvido durante o desafio? Em quais etapas ele poderia contribuir? (2 pontos)