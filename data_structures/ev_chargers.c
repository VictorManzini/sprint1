#include <stdio.h> 
#include <unistd.h>
#include <string.h>
#include <time.h>

float potencia_sessao;
float bateria_inicio;
float potencia_bateria;
int tempo_max_simulacao;
int tempo_simulacao;
float kwh_consumido; 
float preco;
int h_inicio;
int m_inicio;
float tarifa_kWh;
int dia_sem;

void menu(){
    char ID[50];
    int senha;
    printf("BEM-VINDO AO CONTROLE DE GESTAO DE EV CHARGERS GoodWe\n");
    printf("Digite o usuario: ");
    fgets(ID, sizeof(ID), stdin);
    ID[strlen(ID) - 1] = '\0';
    printf("\nDigite a senha: ");
    scanf("%d", &senha);
    while(getchar() != '\n');
    printf("\nAcesso liberado...\n");
}

void capacidade(){
    int energia = 0;
    int carregador_conectado;
    do {
    printf("A energia esta conectada? (1 para sim | 2 para não)\n");
    printf("(Digite 1 para sim | 2 para não): ");
    scanf("%d", &energia);
    if (energia == 2){
        printf("ENERGIA: SEM ENERGIA SUFICIENTE PARA O CARREGAMENTO\n");
        printf("\nVerifique a energia por favor e se necessário reinicie o carregador.\n");
        energia = 0;
    }
    else if (energia > 2 || energia < 1){
        printf("\nOpcao invalida... tente novamente\n");
        energia = 0;
    }
    } while (energia == 0);
    do {
        printf("O carregador esta conectado no veiculo? (1 para sim | 2 para não)\n");
        printf("(Digite 1 para sim | 2 para não): ");
        scanf("%d", &carregador_conectado);
        if (carregador_conectado == 2){
            printf("\nPor favor conecte o carregador.\n");
            carregador_conectado = 0;
        }
        else if (carregador_conectado < 1 || carregador_conectado > 2){
            printf("\nOpcao invalida... tente novamente\n");
            carregador_conectado = 0;
        }
    }while(carregador_conectado == 0);

    if(energia == 1 && carregador_conectado == 1){
        printf("ENERGIA: OK\n");
        printf("CARREGADOR: CONECTADO\n");
    }
}

void sessao(){  
    time_t agora = time(NULL);
    struct tm *horario = localtime(&agora);
    printf("Inicio: %02d:%02d\n", horario->tm_hour, horario->tm_min);
    h_inicio = horario->tm_hour;
    m_inicio = horario->tm_min;
    float energia_necessaria = potencia_bateria*((100 - bateria_inicio)/100.0);
    float tempo_horas = energia_necessaria / potencia_sessao;
    int horas = (int)tempo_horas;
    int minutos = (int)((tempo_horas - horas)*60);
    printf("Tempo real estimado ate a carga total: %dh %dm\n", horas, minutos);
    tempo_simulacao = tempo_max_simulacao * (100 - bateria_inicio) / 100.0;
    int min_simulacao = tempo_simulacao / 60;
    int seg_simulacao = tempo_simulacao % 60;
    printf("Tempo simulado ate a carga total: %dm:%ds\n", min_simulacao, seg_simulacao);
}

void battery(){
    int confirm = 0;
    int confirm2 = 0;
    do{ 
        printf("Digite a porcentagem da bateria: ");
        scanf("%f", &bateria_inicio);
        printf("O nivel da bateria esta em %.2f correto? \n", bateria_inicio);
        printf("(Digite 1 para sim | 2 para nao): ");
        scanf("%d", &confirm);
        if(confirm == 2){
            confirm = 0;
        }
        else if (confirm > 2){
            confirm = 0;
            printf("Opcao invalida... tente novamente\n");
        }
    }while (confirm == 0);
    do {
        printf("Deseja selecionar manualmente qual a potencia da bateria do carro em kWh?\n");
        printf("(Digite 1 para sim | 2 para nao): ");
        scanf("%d", &confirm2);
    if (confirm2 == 2){
        printf("A bateria do carro foi selecionada pelo sistema: 38.8kWh\n");
        potencia_bateria = 38.8;
    }
    else if(confirm2 == 1){
        printf("Digite a potencia da bateria em kWh: ");
        scanf("%f", &potencia_bateria);
        printf("A potencia da bateria foi selecionada em: %.2fkWh\n", potencia_bateria);
    }
    else{
        printf("Opcao invalida... tente novamente\n");
        confirm2 = 0;
    }
    }while(confirm2 == 0);
}

void potencia(){
    int selecao_carregador;
    do{
    printf("Selecione o modo de carregamento:\n");
    printf("Digite:\n");
    printf("1 para carregamento lento AC(potencia 7.4kW)\n");
    printf("2 para carregamento rapido DC(potencia 50kW)\n");
    printf(": ");
    scanf("%d", &selecao_carregador);
    switch(selecao_carregador){
        case 1:
        printf("Carregamento lento selecionado\n");
        potencia_sessao = 7.4;
        tempo_max_simulacao = 600;
        break;

        case 2:
        printf("Carregamento rapido selecionado\n");
        potencia_sessao = 50;
        tempo_max_simulacao = 300;
        break;

        default:
        printf("Opcao invalida... tente novamente\n");
    }
    }while(selecao_carregador < 1 || selecao_carregador > 2);
}

void tarifa(){
    time_t hoje = time(NULL);
    struct tm *data = localtime(&hoje);
    dia_sem = data->tm_wday;
    int tempo_atual = h_inicio * 60 + m_inicio;
    if (dia_sem == 0){ printf("DATA: Domingo ");}
    else if (dia_sem == 1){ printf("DATA: Segunda-feira ");}
    else if (dia_sem == 2){ printf("DATA: Terca-feira ");}
    else if (dia_sem == 3){ printf("DATA: Quarta-feira ");}
    else if (dia_sem == 4){ printf("DATA: Quinta-feira ");}
    else if (dia_sem == 5){ printf("DATA: Sexta-feira ");}
    else if (dia_sem == 6){ printf("DATA: Sabado ");}
    printf("%d/%d/%d\n", data->tm_mday, data->tm_mon +1, data->tm_year + 1900);
    if ((dia_sem > 0 && dia_sem < 6)&&(tempo_atual >= 1050 && tempo_atual <= 1230)){tarifa_kWh = 1.12;}
    else if ((dia_sem > 0 && dia_sem < 6) && (tempo_atual >= 990 && tempo_atual <= 1290)) { tarifa_kWh = 0.72;}
    else {tarifa_kWh = 0.51;}
    kwh_consumido = (tempo_simulacao / 3600.0) * potencia_sessao;
    preco = kwh_consumido * tarifa_kWh;
}

void simulacao(){
    float carregamento_por_segundo = 100.0 /tempo_max_simulacao;
    printf("A bateria esta em: %.2f \n", bateria_inicio);
    for( ; bateria_inicio <= 100; bateria_inicio +=  carregamento_por_segundo){
        sleep(1);
        printf("Carregando...%.2f\n", bateria_inicio);
    }
    printf("Bateria carregada em 100\n");
}

void final(){
    time_t fim = time(NULL);
    struct tm *horario_fim = localtime(&fim);
    printf("Horario de inicio da sessao: %02d:%02d\n", h_inicio, m_inicio);
    printf("Horario de fim da sessao: %02d:%02d\n", horario_fim->tm_hour, horario_fim->tm_min);
    printf("kWh consumidos: %.2f\n", kwh_consumido);
    printf("Preco a pagar: %.2fR$\n", preco);
}

int main(){
    menu();
    capacidade();
    battery();
    potencia();
    sessao();
    simulacao();
    tarifa();
    final();

    return 0;
}