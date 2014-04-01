#include<iostream>
#include<string>
#include<time.h>
#include<ncurses.h>
#include<stdio.h>
#include <stdlib.h>

#define ZERO 0
#define UM 1
#define DOIS 2
#define TRES 3
#define QUATRO 4
#define OITO 8
#define NOVE 9
#define DEZ 10
#define CEM 100
#define NOVECENTOS_E_NOVENTA_E_CINCO 995
#define NOVECENTOS_E_NOVENTA_E_NOVE 999
#define MIL 1000
#define DOIS_MIL_E_QUARENTA_E_OITO 2048
#define MARGEM_LATERAL 4
#define MARGEM_TOP 4

using namespace std;

int matriz[QUATRO][QUATRO];
int pontos = 0;
int valorVitoria = DOIS_MIL_E_QUARENTA_E_OITO;
int contador = 0;

void inicializandoTela();
void sair();
void printNumero(int numero);

void debug();

int acrescentarEspaco(int x);
int somarPontos(int x) {
	pontos += x;
}
int getRandom();
int getNumero();

void inicializaMatriz();
void desenhaMatriz();

void loopJogo();

bool moveEsquerda();
bool moveDireita();
bool moveCima();
bool moveBaixo();

void novoNumero();
bool perdeu();
bool venceu();

int main() {
	inicializandoTela();
	desenhaMatriz();
	loopJogo();
	sair();
	return ZERO;
}
void desenhaMatriz() {
	clear();
	bool linha = true;
	int contadorLinha = ZERO;
	for (int i = ZERO; i < NOVE; ++i) {
		move(MARGEM_TOP + i, MARGEM_LATERAL);
		if (linha) {
			printw("+-------------------+");
		} else {
			printw("+");
			printNumero(matriz[contadorLinha][ZERO]);
			printw("+");
			printNumero(matriz[contadorLinha][UM]);
			printw("+");
			printNumero(matriz[contadorLinha][DOIS]);
			printw("+");
			printNumero(matriz[contadorLinha][TRES]);
			printw("+");
			contadorLinha++;
		}
		linha = !linha;
	}
	move(MARGEM_TOP - DOIS, MARGEM_LATERAL + DOIS);
	printw("Pontos:%i", pontos);
	debug();
	refresh();
}

void sair() {
	endwin();
}

void inicializaMatriz() {
	for (int linha = ZERO; linha < QUATRO; ++linha) {
		for (int coluna = ZERO; coluna < QUATRO; ++coluna) {
			matriz[linha][coluna] = ZERO;
		}
	}
	int x1, x2, y1, y2;

	x1 = getRandom();
	y2 = getRandom();
	do {
		y1 = getRandom();
		x2 = getRandom();
	} while (x2 == x1 && y1 == y2);
	matriz[x1][y1] = getNumero();
	matriz[x2][y2] = getNumero();
}

void inicializandoTela() {
	initscr();
	start_color();
	init_pair(UM, COLOR_WHITE, COLOR_BLUE);
	init_pair(DOIS, COLOR_BLACK, COLOR_WHITE);
	bkgd(COLOR_PAIR(1));
	attron(COLOR_PAIR(2));
	inicializaMatriz();
}

int acrescentarEspaco(int x) {
	if (x == ZERO) {
		return QUATRO;
	} else if (x < DEZ) {
		return TRES;
	} else if (x >= DEZ && x < CEM) {
		return DOIS;
	} else if (x >= CEM && x < MIL) {
		return UM;
	} else {
		return ZERO;
	}
}

void loopJogo() {
	char tecla;
	bool movimento = false;
	while (true) {
		move(MARGEM_TOP + DEZ, MARGEM_LATERAL + QUATRO);
		printw("Pressione um das setas!");
		refresh();
		tecla = cin.get();
		cin.ignore(256,'\r');
		attron(COLOR_PAIR(1));
		move(MARGEM_TOP + DEZ, MARGEM_LATERAL + QUATRO);
		printw("                                     ");
		attron(COLOR_PAIR(2));
		refresh();
		if (tecla == 'w' || tecla == 'W') {
			movimento = moveCima();
		} else if (tecla == 's' || tecla == 'S') {
			movimento = moveBaixo();
		} else if (tecla == 'd' || tecla == 'D') {
			movimento = moveDireita();
		} else if (tecla == 'a' || tecla == 'A') {
			movimento = moveEsquerda();
		}
		bool derrota = perdeu();
		bool vitoria = venceu();
		if(movimento && !derrota && !vitoria){
			novoNumero();
		}
		if(vitoria){
			move(MARGEM_TOP + DEZ, MARGEM_LATERAL + QUATRO);
			printw("Parabéns voce venceu!!!");
			move(MARGEM_TOP + DEZ + UM, MARGEM_LATERAL + QUATRO);
			printw("DESEJA CONTINUAR?(S/N)");
			do{
				cin >> tecla;
			}while((tecla != 's' || tecla != 'S')&&(tecla != 'n' || tecla != 'N'));
			if((tecla == 's' || tecla == 'S')){
				inicializaMatriz();
				valorVitoria *= DOIS;
				clear();
			}else{
				break;
			}
		}else if(derrota){
			move(MARGEM_TOP + DEZ, MARGEM_LATERAL + QUATRO);
			printw("Voce perdeu!!!");
			move(MARGEM_TOP + DEZ + UM, MARGEM_LATERAL + QUATRO);
			printw("DESEJA CONTINUAR?(S/N)");
			do{
				cin >> tecla;
			}while((tecla != 's' || tecla != 'S')&&(tecla != 'n' || tecla != 'N'));
			if((tecla == 's' || tecla == 'S')){
				clear();
				pontos = ZERO;
				inicializaMatriz();
			}else{
				break;
			}
		}
		desenhaMatriz();
	}
}

void printNumero(int numero) {
	int resto = acrescentarEspaco(numero);
	for (int i = ZERO; i < resto; ++i) {
		printw(" ");
	}
	if (resto < QUATRO) {
		printw("%i", numero);
	}
}
int getNumero() {
	srand(time( NULL));
	int r = rand() % MIL + 1;
	if (r >= NOVECENTOS_E_NOVENTA_E_CINCO && r <= NOVECENTOS_E_NOVENTA_E_NOVE) {
		return QUATRO;
	} else if (r > NOVECENTOS_E_NOVENTA_E_NOVE) {
		return OITO;
	} else {
		return DOIS;
	}
}

int getRandom() {
	srand(time( NULL));
	int r = rand() % QUATRO;
}

bool moveDireita() {
	bool fezMovimento = false;
	for (int linha = ZERO; linha < QUATRO; linha++) {
		for (int coluna = ZERO; coluna <= TRES; coluna++) {
			if (matriz[linha][coluna] != ZERO) { //Tem Número
				for (int coluna2 = coluna + UM; coluna2 < QUATRO; coluna2++) {
					if (matriz[linha][coluna2] != ZERO
							&& matriz[linha][coluna2]
									!= matriz[linha][coluna]) {
						break;
					} else if (matriz[linha][coluna2] != ZERO
							&& matriz[linha][coluna2]
									== matriz[linha][coluna]) {
						matriz[linha][coluna2] += matriz[linha][coluna];
						somarPontos(matriz[linha][coluna2]);
						matriz[linha][coluna] = ZERO;
						coluna = ++coluna2;
						fezMovimento = true;
					}
				}
			}
		}
	}
	for (int linha = ZERO; linha < QUATRO; linha++) {
		int colunaAtual = TRES;
		for (int coluna = colunaAtual; coluna >= ZERO; coluna--) {
			if(matriz[linha][coluna] != ZERO){
				colunaAtual--;
				continue;
			}
			for(int reposiciona = coluna - UM; reposiciona >= ZERO; reposiciona--){
				//Procura os próximos números para reposicionar
				if(matriz[linha][reposiciona] !=ZERO){
					matriz[linha][colunaAtual] = matriz[linha][reposiciona];
					matriz[linha][reposiciona] = ZERO;
					colunaAtual--;
					fezMovimento = true;
				}
			}
		}
	}

	return fezMovimento;
}

bool moveEsquerda() {
	bool fezMovimento = false;
	for (int linha = ZERO; linha < QUATRO; linha++) {
		for (int coluna = TRES; coluna > ZERO; coluna--) {
			if (matriz[linha][coluna] != ZERO) { //Tem Número
				for (int coluna2 = coluna - UM; coluna2 >= ZERO; coluna2--) {
					if (matriz[linha][coluna2] != ZERO
							&& matriz[linha][coluna2]
									!= matriz[linha][coluna]) {
						break;
					} else if (matriz[linha][coluna2] != ZERO
							&& matriz[linha][coluna2]
									== matriz[linha][coluna]) {
						matriz[linha][coluna2] += matriz[linha][coluna];
						somarPontos(matriz[linha][coluna2]);
						matriz[linha][coluna] = ZERO;
						coluna = --coluna2;
						fezMovimento = true;
					}
				}
			}
		}
	}
	//	Reordenar
	for (int linha = ZERO; linha < QUATRO; linha++) {
			int colunaAtual = ZERO;
			for (int coluna = colunaAtual; coluna < QUATRO; coluna++) {
				if(matriz[linha][coluna] != ZERO){
					colunaAtual++;
					continue;
				}
				for(int reposiciona = coluna + UM; reposiciona < QUATRO; reposiciona++){
					//Procura os próximos números para reposicionar
					if(matriz[linha][reposiciona] !=ZERO){
						matriz[linha][colunaAtual] = matriz[linha][reposiciona];
						matriz[linha][reposiciona] = ZERO;
						colunaAtual++;
						fezMovimento = true;
					}
				}
			}
		}
	return fezMovimento;
}

bool moveBaixo() {
	bool fezMovimento = false;
	for (int coluna = ZERO; coluna < QUATRO; coluna++) {
		for (int linha = ZERO; linha < TRES; linha++) {
			if (matriz[linha][coluna] != ZERO) { //Tem Número
				for (int linha2 = linha + UM; linha2 < QUATRO; linha2++) {
					if (matriz[linha2][coluna] != ZERO
							&& matriz[linha2][coluna]
									!= matriz[linha][coluna]) {
						break; //Sai do for
					} else if (matriz[linha2][coluna] != ZERO
							&& matriz[linha2][coluna]
									== matriz[linha][coluna]) {
						matriz[linha2][coluna] += matriz[linha2][coluna];
						somarPontos(matriz[linha2][coluna]);
						matriz[linha][coluna] = ZERO;
						linha = ++linha2;
						fezMovimento = true;
					}
				}
			}
		}
	}
	//	Reordenar
		for (int coluna = ZERO; coluna < QUATRO; coluna++) {
				int linhaAtual = TRES;
				for (int linha = linhaAtual; linha >= ZERO; linha--) {
					if(matriz[linha][coluna] != ZERO){
						linhaAtual--;
						continue;
					}
					for(int reposiciona = linha - UM; reposiciona >= ZERO; reposiciona--){
						//Procura os próximos números para reposicionar
						if(matriz[reposiciona][coluna] !=ZERO){
							matriz[linhaAtual][coluna] = matriz[reposiciona][coluna];
							matriz[reposiciona][coluna] = ZERO;
							linhaAtual--;
							fezMovimento = true;
						}
					}
				}
			}

	return fezMovimento;
}

bool moveCima() {
	bool fezMovimento = false;
	for (int coluna = ZERO; coluna < QUATRO; coluna++) {
		for (int linha = TRES; linha > ZERO; linha--) {
			if (matriz[linha][coluna] != ZERO) { //Tem Número
				for (int linha2 = linha - UM; linha2 >= ZERO; linha2--) {
					if (matriz[linha2][coluna] != ZERO
							&& matriz[linha2][coluna]
									!= matriz[linha][coluna]) {
						break; //Sai do for
					} else if (matriz[linha2][coluna] != ZERO
							&& matriz[linha2][coluna]
									== matriz[linha][coluna]) {
						matriz[linha2][coluna] += matriz[linha][coluna];
						somarPontos(matriz[linha2][coluna]);
						matriz[linha][coluna] = ZERO;
						linha = --linha2;
						fezMovimento = true;
					}
				}
			}
		}
	}
	//	Reordenar
			for (int coluna = ZERO; coluna < QUATRO; coluna++) {
					int linhaAtual = ZERO;
					for (int linha = linhaAtual; linha < QUATRO; linha++) {
						if(matriz[linha][coluna] != ZERO){
							linhaAtual++;
							continue;
						}
						for(int reposiciona = linha + UM; reposiciona < QUATRO; reposiciona++){
							//Procura os próximos números para reposicionar
							if(matriz[reposiciona][coluna] !=ZERO){
								matriz[linhaAtual][coluna] = matriz[reposiciona][coluna];
								matriz[reposiciona][coluna] = ZERO;
								linhaAtual++;
								fezMovimento = true;
							}
						}
					}
				}
	return fezMovimento;
}
void debug() {
	contador++;
	int linha = ZERO;
	move(ZERO, 80);
	printw("contador: %i", contador);
	linha++;
	move(linha, 80);
	for (int i = ZERO; i < QUATRO; ++i) {
		for (int j = ZERO; j < QUATRO; ++j) {
			printw("Matriz[%i][%i] = %i", i, j, matriz[i][j]);
			move(linha, 80);
			linha++;
		}
	}
}

void novoNumero(){
	int x,y;
	do {
		y = getRandom();
		x = getRandom();
	} while (matriz[x][y] != ZERO);
	matriz[x][y] = getNumero();
}

bool perdeu(){
	bool perdeu = true;
	for(int i = ZERO; i< QUATRO;i++){
		for(int j = ZERO; j< QUATRO;j++){
			if(matriz[i][j] == ZERO){
				perdeu = false;
				break;
			}
		}
	}
	return perdeu;
}

bool venceu(){
	for(int i = ZERO; i< QUATRO;i++){
		for(int j = ZERO; j< QUATRO;j++){
			if(valorVitoria = matriz[i][j]){
				return true;
			}
		}
	}
	return false;
}


