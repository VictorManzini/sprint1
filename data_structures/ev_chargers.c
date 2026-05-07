#include <stdio.h> 
#include <unistd.h>
#include <string.h>
#include <time.h>


//Todas as variáveis que serão usadas ao longo do programa:
float potencia_sessao;
float bateria_inicio = -1; // Inicializa em -1 por causa da validação, dentro do sistema a bateria_inicial não pode ser menor que 0 ou maior que 100
float potencia_bateria;
int tempo_max_simulacao;
int tempo_simulacao;
int tempo_atual;
float kwh_consumido; 
float preco;
int h_inicio;
int m_inicio;
float tarifa_kWh;
int dia_sem;
int dia;
int mes;
int ano;

//Menu de inicialização:
void menu(){
    char ID[50]; //ID e senha fictícios, pode digitar qualquer palavra ou seu nome no ID e na senha pode ser qualquer número.
    int senha;
    printf("\n");
    printf("BEM-VINDO AO CONTROLE DE GESTAO DE EV CHARGERS GoodWe\n");
    printf("\nAtencao!!\n");
    printf("O programa eh uma simulacao. ID e senha sao ficticios\n");
    printf("Voce pode digitar seu nome no ID e qualquer numero na senha para a validacao\n");
    printf("ID obrigatorio ser uma string | senha obrigatorio ser um numero inteiro\n");
    printf("\nDigite o usuario: ");
    fgets(ID, sizeof(ID), stdin);
    ID[strlen(ID) - 1] = '\0';
    printf("\nDigite a senha: ");
    scanf("%d", &senha);
    while(getchar() != '\n');
    printf("\nAcesso liberado...\n");
}

void capacidade(){ // Verifica se tem energia para o carregamento e se o carregador está conectado no carro
    int energia = 0; //Inicializa em false pra forçar a entrada no loop 
    int carregador_conectado; //Armazena se o carregador está conectado ou não
    do {
    printf("\nA energia esta conectada?\n");
    printf("(Digite 1 para sim | 2 para não): ");
    scanf("%d", &energia);//Lê o input do usuário
    if (energia == 2){ //Usuário confirmou que não tem energia ou ela está desconectada
        printf("ENERGIA: SEM ENERGIA SUFICIENTE PARA O CARREGAMENTO\n");
        printf("\nVerifique a energia por favor e se necessário reinicie o carregador.\n");
        energia = 0; //Força 0 para repetir o loop
    }
    else if (energia > 2 || energia < 1){ //Verifica se o input foi válido. 
        printf("\nOpcao invalida... tente novamente\n");
        energia = 0;
    }
    } while (energia == 0); //Força o loop até que o usuário confirme que tem energia
    do {
        printf("O carregador esta conectado no veiculo?\n");
        printf("(Digite 1 para sim | 2 para não): ");
        scanf("%d", &carregador_conectado);//Lê a resposta do usuário
        if (carregador_conectado == 2){ //Usuário confirmou que o carregador não está conecatado 
            printf("\nPor favor conecte o carregador.\n");
            carregador_conectado = 0;//Força 0 para repetir o loop
        }
        else if (carregador_conectado < 1 || carregador_conectado > 2){//Verifica se o input foi válido 
            printf("\nOpcao invalida... tente novamente\n");
            carregador_conectado = 0;//Força 0 novamente
        }
    }while(carregador_conectado == 0);//Repete até que o usuário confirme que o carregador está conectado

    if(energia == 1 && carregador_conectado == 1){//Ambos OK
        printf("ENERGIA: OK\n");
        printf("CARREGADOR: CONECTADO\n");
    }
}

void battery(){ //Confirma a porentagem da bateria do carro e guarda na variável bateria_inicio.
    int confirm = 0;// Inicializa em 0 para forçar a entradad no loop de confirmação 
    int confirm2 = 0;// Inicializa em 0 para forçar a entradad no loop de potência
    do{ 
        while(bateria_inicio < 0 || bateria_inicio > 100){ // Repete até um valor válido (0 a 100)
            printf("\nDigite a porcentagem da bateria: ");
            scanf("%f", &bateria_inicio); // Lê a porcentagem da bateria
            if(bateria_inicio >100){
                printf("Porcentagem da bateria nao pode ser maior que 100\n");
                printf("Tente novamente...\n");
                bateria_inicio = -1 ; //Força -1 para repetir o loop 
            }
            else if (bateria_inicio < 0){
                printf("Porcentagem da bateria nao pode ser menor que 0\n");
                printf("Tente novamente...\n");
                bateria_inicio = -1;// Força -1 para repetir o loop
            }
        }
        printf("O nivel da bateria esta em %.2f correto? \n", bateria_inicio);
        printf("(Digite 1 para sim | 2 para nao): ");
        scanf("%d", &confirm);// Lê a confirmação do usuário
        if(confirm == 2){
            confirm = 0;//Usuário negou, força 0 para repetir 
        }
        else if (confirm > 2){
            confirm = 0;// Entrada inválida, força 0 para repetir
            printf("Opcao invalida... tente novamente\n");
        }
    }while (confirm == 0); // Repete até o usuário confirmar a porentagem da bateria
    do {
        printf("\nDeseja selecionar manualmente qual a potencia da bateria do carro em kWh?\n");
        printf("Se digitado 2 a potencia definida por padrao eh: 38.8kWh\n");
        printf("(Digite 1 para sim | 2 para nao): ");
        scanf("%d", &confirm2); // Lê a escolha do usuário
    if (confirm2 == 2){
        printf("A bateria do carro foi selecionada pelo sistema: 38.8kWh\n");
        potencia_bateria = 38.8; //Definida potência padrão 
    }
    else if(confirm2 == 1){
        printf("Digite a potencia da bateria em kWh: ");
        scanf("%f", &potencia_bateria);
        printf("A potencia da bateria foi selecionada em: %.2fkWh\n", potencia_bateria);
    }
    else{
        printf("Opcao invalida... tente novamente\n");
        confirm2 = 0; // entrada inválida, força 0 para repetir o loop
    }
    }while(confirm2 == 0); // Repete até escolha válida 
}

void potencia(){ // Seleção do modo de carregamento que define o tempo máximo de execução 
    int selecao_carregador; //Armazena a escolha do tipo do carregador (1 ou 2)
    do{
    printf("\nSelecione o modo de carregamento:\n");
    printf("Digite:\n");
    printf("1 para carregamento lento AC(potencia 7.4kW)\n"); //Caregador comum de parede tipo WallBox
    printf("2 para carregamento rapido DC(potencia 50kW)\n"); //Fast Charger 
    printf(": ");
    scanf("%d", &selecao_carregador); // Lê a escolha do usuário
    switch(selecao_carregador){
        case 1:
        printf("Carregamento lento selecionado\n");
        potencia_sessao = 7.4; // Define a potência do carregador em kW
        tempo_max_simulacao = 600; // 600 segundos = 10 minutos de simulação
        break;

        case 2:
        printf("Carregamento rapido selecionado\n");
        potencia_sessao = 50; //Define a potiencia do carregador em kW
        tempo_max_simulacao = 300; // 300 segundos = 5 minutos de simulação 
        break;

        default:
        printf("Opcao invalida... tente novamente\n"); //Entrada inválida 
    }
    }while(selecao_carregador < 1 || selecao_carregador > 2); // Repete até um valor válido (1 ou 2)
}
void sessao(){  //Grava data e horário de início, calcula tempo estimado real e simulado 
    time_t agora = time(NULL); // Captura data e horário atual do computador
    struct tm *horario = localtime(&agora); // Converte para estrutura com dia, mês, hora e etc.
    h_inicio = horario->tm_hour; // Guarda hora de início 
    m_inicio = horario->tm_min; // Guarda minuto de início 
    dia = horario->tm_mday; // Guarda dia do mês
    mes = horario->tm_mon +1; // tm_mon vai de 0 - 11, soma 1 para valor real
    ano = horario->tm_year + 1900; //tm_year conta desde 1900, soma para ano real
    dia_sem = horario->tm_wday; // Guarda dia da semana (0 = domingo, 6 = sabado)
    tempo_atual = h_inicio * 60 + m_inicio; // Converte horário para minutos totais (usando tarifa)
    if (dia_sem == 0){ printf("\nDATA: Domingo ");}
    else if (dia_sem == 1){ printf("\nDATA: Segunda-feira ");}
    else if (dia_sem == 2){ printf("\nDATA: Terca-feira ");}
    else if (dia_sem == 3){ printf("\nDATA: Quarta-feira ");}
    else if (dia_sem == 4){ printf("\nDATA: Quinta-feira ");}
    else if (dia_sem == 5){ printf("\nDATA: Sexta-feira ");}
    else if (dia_sem == 6){ printf("\nDATA: Sabado ");}
    printf("%d/%d/%d\n",dia, mes, ano);
    printf("Horario de inicio: %02d:%02d\n", horario->tm_hour, horario->tm_min);
    float energia_necessaria = potencia_bateria*((100 - bateria_inicio)/100.0); // kWh necessário para carga completa   
    float tempo_horas = energia_necessaria / potencia_sessao; // Tempo real em horas (energia / potência)
    int horas = (int)tempo_horas;                             // Parte inteira = horas 
    int minutos = (int)((tempo_horas - horas)*60);            // Parte decimal convertida para miutos
    printf("Tempo real estimado ate a carga total: %dh %dm\n", horas, minutos);
    tempo_simulacao = tempo_max_simulacao * (100 - bateria_inicio) / 100.0; // Tempo simulado proporcional à carga restante 
    int min_simulacao = tempo_simulacao / 60; // Extrai minutos do tempo simulado 
    int seg_simulacao = tempo_simulacao % 60; // Extrai segundos restantes com operador módulo 
    printf("Tempo simulado ate a carga total: %dm:%ds\n", min_simulacao, seg_simulacao);
}

void tarifa(){ // Define a tarifa com base no horário e dia da semana, calcula kWh e preço
    // Tarifas baseadas nos horários reais da ENEL de São Paulo
    if ((dia_sem > 0 && dia_sem < 6)&&(tempo_atual >= 1050 && tempo_atual <= 1230)){
        // Horário de pico: seg - sex das 17:30 às 20:30
        printf("\nHorario de pico, tarifa mais cara\n");
        tarifa_kWh = 1.12;
        printf("Tarifa do horario: %.2fkWh\n", tarifa_kWh);
    }
    else if ((dia_sem > 0 && dia_sem < 6) && (tempo_atual >= 990 && tempo_atual <= 1290)) {
        // Horário intermediário: seg - sex das 16:30-17:30 e 20:30-21:30
        printf("Horario intermediario\n");
        tarifa_kWh = 0.72;
        printf("Tarifa do horario: %.2fkWh\n", tarifa_kWh);
        }
    else {
        // Fora de ponta: demais horários e fins de semana
        printf("Horario fora de ponta\n");
        tarifa_kWh = 0.51;
        printf("Tarifa do horario: %.2fkWh\n", tarifa_kWh);
    }
    kwh_consumido = (tempo_simulacao / 3600.0) * potencia_sessao; // Converte segundos para horas e multiplica pela potência
    preco = kwh_consumido * tarifa_kWh; // Preço final = energia consumida x tarifa aplicada 
}

void simulacao(){ // Simula a recarga da bateria em tempo real 
    float carregamento_por_segundo = 100.0 /tempo_max_simulacao; // Taxa de incremento da bateria por segundo 
    printf("\nA bateria esta em: %.2f \n", bateria_inicio);
    for( ; bateria_inicio <= 100; bateria_inicio +=  carregamento_por_segundo){ // Loop roda uma vez por segundo até 100%
        sleep(1); // Aguarda 1 segundo antes de atualizar
        printf("Carregando...%.2f\n", bateria_inicio); // exibe porcentagem atual da bateria
    }
    printf("Bateria carregada em 100\n"); // Exibe mensagem de conclusão 
}

void final(){ // Exibe o relatório final da sessão de recarga 
    time_t fim = time(NULL); // Captura horário de término da sessão 
    struct tm *horario_fim = localtime(&fim); // Converte para a estrutura legível 
    printf("\nData da recarga: %d/%d/%d\n", dia, mes, ano); 
    printf("Horario de inicio da sessao: %02d:%02d\n", h_inicio, m_inicio);
    printf("Horario de fim da sessao: %02d:%02d\n", horario_fim->tm_hour, horario_fim->tm_min);
    printf("Tarifa do horario em que a sessao foi executada: %.2f\n", tarifa_kWh);
    printf("kWh consumidos: %.2fkW\n", kwh_consumido);
    printf("Preco a pagar: %.2fR$\n", preco); // Exibe o valor final a pagar
}

int main(){
    menu();
    capacidade();
    battery();
    potencia();
    sessao();
    tarifa();
    simulacao();
    final();

    return 0;
}