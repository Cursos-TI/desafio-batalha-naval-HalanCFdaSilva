#include <stdio.h>
#include <stdlib.h>
int TAMANHO_LINHA = 10,TAMANHO_COLUNA = 10,tabuleiro [10][10];

void inicializar_tabuleiro() {
    for (int i = 0; i < TAMANHO_LINHA; i++) {
        for (int j = 0; j < TAMANHO_COLUNA; j++) {
            tabuleiro[i] [j]= 0;
        }
    }
};

void imprimir_tabuleiro() {
    for (int i = 0; i < TAMANHO_LINHA; i++) {
        for (int j = 0; j < TAMANHO_COLUNA; j++) {
            printf("%d\t", tabuleiro[i][j]);
        }
        printf("\n\n");
    }
}



struct navio {
    int pos_x;
    int pos_y;
    struct navio *proximaPosicao;
};

int muda_posicao(int pos, int pos_fim) {
    if (pos>pos_fim)
        pos--;
    else if (pos<pos_fim)
        pos++;
    return pos;
}

void generateNavio(struct navio* navio,int pos_inic_x,int pos_inic_y,int pos_fim_x,int pos_fim_y) {

    do{
        navio->proximaPosicao = (struct navio*)malloc(sizeof(struct navio));
        navio->pos_x = pos_inic_x;
        navio->pos_y = pos_inic_y;
        navio = navio->proximaPosicao;
        navio->proximaPosicao = (struct navio*)malloc(sizeof(struct navio));
        pos_inic_x = muda_posicao(pos_inic_x,pos_fim_x);
        pos_inic_y = muda_posicao(pos_inic_y,pos_fim_y);

    }while (pos_inic_x != pos_fim_x || pos_inic_y != pos_fim_y);
    navio->pos_x = pos_inic_x;
    navio->pos_y =pos_inic_y;
    navio->proximaPosicao = NULL;
}

int posicao_navio_valida(struct navio* navio) {
    int posicao_valida = 1;
    while (navio != NULL) {
        if (navio->pos_x > 9 || navio->pos_y > 9 || (tabuleiro[navio->pos_y][navio->pos_x]==3)) {
            posicao_valida = 0;
            break;
        }
        navio = navio->proximaPosicao;
    }
    return posicao_valida;
}
void inserir_navio(struct navio* navio) {
    if (posicao_navio_valida(navio)) {
        while (navio != NULL) {
            tabuleiro[navio->pos_y][navio->pos_x] = 3;
            navio = navio->proximaPosicao;
        }
    }
}

void generate_and_insert_navio(int pos_inic_x,int pos_inic_y,int pos_fim_x, int pos_fim_y) {
    struct navio navio;
    generateNavio(&navio,pos_inic_x,pos_inic_y,pos_fim_x,pos_fim_y);
    inserir_navio(&navio);
}
int main(void) {
    inicializar_tabuleiro();

    generate_and_insert_navio(0,0,2,0);
    generate_and_insert_navio(4,3,4,5);
    generate_and_insert_navio(1,1,3,3);
    generate_and_insert_navio(9,9,7,7);

    imprimir_tabuleiro();
    system("pause");

    return 0;
}
