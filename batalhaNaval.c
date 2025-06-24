#include <stdio.h>
#include <stdlib.h>

int TAMANHO_LINHA = 10,TAMANHO_COLUNA = 10,tabuleiro [10][10];

// FUNÇÕES TABULEIRO
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
            printf("\t%d", tabuleiro[i][j]);
        }
        printf("\n\n");
    }
}


// FUNÇÕES NAVIO
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

// FUNÇÕES PODERES

int posicao_dentro_tabuleiro(int posicao, int limite_tabuleiro) {
    return posicao >= 0 && posicao < TAMANHO_LINHA;
}

usar_cone(int centro_x,int centro_y) {
    int limite_x=5,limite_y=3;
    int inic_x = centro_x-limite_x/2, inic_y= centro_y-limite_y/2 + 1;
    int pos_efeito_x, pos_efeito_y;

    for (int i = 0; i < limite_y; i++) {
        for (int j = 0; j < limite_x; j++) {
            if (i + j >= limite_x/2 && i+j <=limite_x/2+2*i) {
                pos_efeito_x= inic_x + j;
                pos_efeito_y= inic_y + i;
                if (posicao_dentro_tabuleiro(pos_efeito_x,TAMANHO_LINHA) &&
                    posicao_dentro_tabuleiro(pos_efeito_y, TAMANHO_COLUNA)) {
                    tabuleiro[pos_efeito_y][pos_efeito_x] = 5;
                }
            }

        }
    }

}

void usar_cruz(int centro_x,int centro_y) {

    for (int i = 0; i < TAMANHO_COLUNA; i++) {
        for (int j = 0; j < TAMANHO_LINHA; j++) {
            if (i == centro_y || j == centro_x)
                tabuleiro[i][j] = 5;
        }
    }

}

int usar_octaedro(int centro_x,int centro_y) {
    int limite_x=5,limite_y=5,metade_limite_x= limite_x/2;
    int posicao_x, posicao_y;
    for (int i = 0; i < limite_y; i++) {
        for (int j = 0; j < limite_x; j++) {
            posicao_x = centro_x-limite_x/2 + j;
            posicao_y= centro_y-limite_y/2 + i;
            if (posicao_dentro_tabuleiro(posicao_x, TAMANHO_LINHA) && posicao_dentro_tabuleiro(posicao_y, TAMANHO_COLUNA)) {
                if (i<=metade_limite_x && i+j>=metade_limite_x && i+j<=metade_limite_x+2*i)

                    tabuleiro[posicao_y][posicao_x] = 5;
                else if (i>=metade_limite_x && j+2>=i && j+i <=limite_x +1)
                    tabuleiro[posicao_y][posicao_x] = 5;
            }
        }
    }
}

int main(void) {
    inicializar_tabuleiro();

    generate_and_insert_navio(0,0,2,0);
    generate_and_insert_navio(4,3,4,5);
    generate_and_insert_navio(1,1,3,3);
    generate_and_insert_navio(9,9,7,7);

    usar_cone(0,0);
    usar_cruz(5,5);
    usar_octaedro(7,7);

    imprimir_tabuleiro();
    system("pause");


    return 0;
}
