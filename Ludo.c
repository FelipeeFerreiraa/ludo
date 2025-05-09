#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Azul posicao inicial 31 posicao final 85, Vermelho posicao inicial 18 posicao final 72, Verde posicao inicial 5 posicao final 59, Amarelo posicao inicial 68 posicao final 98
//Casas coloridas: Azul 111 a 116, Vermelho 105 a 110, Verde 99 a 104, Amarelo 117 a 122
//Comer peao, casas iguais ou se posicao >52 entao compara posicao com posicao - 52
//Casas protegidas: Azul 31, 83 e 88, Vermelho 18, 70 e 75, Verde 5, 57, 10 e 62, Amarelo 44, 96 e 49 (estrela somente uma vez, ja que o amarelo nao ira passar nela 2 vezes)
struct jogador {
	int posicao_peao[4], peao_liberado[4], jogada[4], vitoria_p[4], reta_f[4];
	int dado, vitoria_j;
};

// TRABALHO REALIZADO NA MATÉRIA DE ALGORITMOS E ESTRUTURAS DE DADOS 2
// ENGENHARIA DA COMPUTAÇÃO - UEMG - 2° SEMESTRE 2023

int rolar_dado ();

int mover_peao (struct jogador *jog_p, int i, int j);
/*int mover_peao (int posicao[][4], int j, int peao_liberado[][4], int i, int volta[][4], int dado[], int jogada[][4]);*/

int liberar_peao (int i, struct jogador *jog_p);

int main() {
	struct jogador jog_p[4];
	int i, j, k, m, n, num_jog, vitorias=0, loop=0, verifica=0, fim_jog=0, ver_p=0, aux_lib=0;
	int cont=0;
	char jog_nov, input;
	while(loop==0) {
		while (verifica==0) {
			for (i=0;i<4;i++) {
				for (j=0;j<4;j++) {
					jog_p[i].jogada[j] = 0;
					jog_p[i].peao_liberado[j] = 0;
					jog_p[i].vitoria_p[j] = 0;
					jog_p[i].posicao_peao[j]=0;
					jog_p[i].reta_f[j] = 0;
				}		
			}
			printf("Digite quantos jogadores irao jogar\n");
			scanf("%d", &num_jog);
			if (num_jog==2) {
				verifica++;
				fim_jog = 0;
				while (fim_jog==0) {
					if (fim_jog==0) {
						for (i=0;i<2;i++) {
							if (fim_jog==0) {
								cont = 3;
								while (jog_p[i].dado==6 || cont!=0) {
									printf("\nTabuleiro:\n");
									for (k=0;k<2;k++) { //Imprime tabuleiro
										for (j=0;j<4;j++) {
											if(jog_p[k].posicao_peao[j]==0) {
												printf("Jogador %d - Peao %d - Em casa\n", k+1, j+1);
											}
											else if (jog_p[k].posicao_peao[j]<53){
												printf("Jogador %d - Peao %d - %d\n", k+1, j+1, jog_p[k].posicao_peao[j]);
											}
											else if (jog_p[k].vitoria_p[j]==1) {
												printf("Jogador %d - Peao %d - Casa Final\n", k+1, j+1);
											}
											else if (jog_p[k].posicao_peao[j]>=100 && jog_p[k].peao_liberado[j]>0) {
												if (k==0) {
													printf("Jogador %d - Peao %d - Reta Final %d\n", k+1, j+1, jog_p[k].posicao_peao[j]-99);
												}
												else if (k==1) {
													printf("Jogador %d - Peao %d - Reta Final %d\n", k+1, j+1, jog_p[k].posicao_peao[j]-105);
													}
											}
											else {
												printf("Jogador %d - Peao %d - Segunda Volta %d\n", k+1, j+1, jog_p[k].posicao_peao[j]-52);
											}
										}
									}
									printf("\n\n");
									printf("Jogador %d, pressione ENTER para rolar o dado ", i+1);
									fflush(stdin);
									scanf("%c", &input);
									jog_p[i].dado = rolar_dado();
									if (jog_p[i].dado==6) { //Repetir turnos, se igual a 0 entao turno nao se repete, ira rodar ate 3 vezes
										cont--;
										}
										else { //Se o dado for diferente de 6 entao o contador zera
											cont = 0;
									}
									if (cont==0 && jog_p[i].dado==6) {
										printf("3 dados 6 consecutivos, pula a vez\n");
									}
									else {
										printf("Dado: %d\n", jog_p[i].dado);
										ver_p = 0;
										aux_lib = 0;
										for (m=0;m<4;m++) {
											if (jog_p[i].vitoria_p[m]==0 && jog_p[i].peao_liberado[m]!=0) { //vai somar caso tenha peao liberado e que nao esta na casa final
												aux_lib++;
											}
										}
										if (aux_lib!=0) { //tem peao liberado e podem ser movidos
											while (ver_p==0) {
												printf("\nJogador %d, selecione o peao que deseja mover\n", i+1);
													scanf("%d", &j);
												j--;
												if (j<0 || j>3) {
													printf("Peao selecionado eh invalido, selecione um peao de 1 a 4\n");
												}
												else if (jog_p[i].vitoria_p[j]==1) {
													printf("Peao selecionado ja esta na casa final, selecione outro peao\n");
												}
												else if (jog_p[i].peao_liberado[j]==0 && jog_p[i].dado!=6) {
													printf("Peao selecionado esta em casa e nao pode ser liberado, selecione outro peao\n");
												}
												else {
													ver_p++;
												}
											}
										}
										else if (aux_lib==0 && jog_p[i].dado==6) { //nenhum peao liberado, mas pode ser liberado
											while (ver_p==0) {
												printf("\nJogador %d, selecione um peao para liberar\n", i+1);
												scanf("%d", &j);
												j--;
												if (j<0 || j>3) {
													printf("Peao selecionado eh invalido, selecione um peao de 1 a 4\n");
												}
												else {
													ver_p++;
												}
											}
										}
										else { //nenhum peao liberado
											printf("Dado diferente de 6, nao eh possivel liberar nenhum peao\n");
											j = -1;
										}
										if (j!=-1) { //se j=-1 entao o movimento anterior eh invalido
											if (jog_p[i].peao_liberado[j]==0) {
												jog_p[i].posicao_peao[j] = liberar_peao(i, &jog_p[i]);
												if (jog_p[i].posicao_peao[j]!=0) {
													jog_p[i].peao_liberado[j]++;
													jog_p[i].jogada[j]++;
												}
											}										
											else {
												jog_p[i].posicao_peao[j] = mover_peao(&jog_p[i], i, j);
												jog_p[i].jogada[j]++;							
											}
											if (jog_p[i].posicao_peao[j]<=98 && jog_p[i].peao_liberado[j]==1) { //comer peao, somente valido se peao nao estiver na reta final e estiver liberado
												for (m=0;m<2;m++) {
													if (m!=i) { //jogador que eh comido nao eh o jogador comendo
														for (n=0;n<4;n++) {
															if (jog_p[m].posicao_peao[n]<=98) { //peao inimigo nao esta na reta final
																if (jog_p[i].posicao_peao[j]==jog_p[m].posicao_peao[n] || jog_p[i].posicao_peao[j]==jog_p[m].posicao_peao[n]-52) {
																	if (m==0) { //casa segura verde
																		if (jog_p[m].posicao_peao[n]==5 || jog_p[m].posicao_peao[n]==57 || jog_p[m].posicao_peao[n]==10 || jog_p[m].posicao_peao[n]==62) {
																			printf("Peao adversario esta em uma casa segura, nao eh possivel comer\n");
																		}
																		else {
																			printf("O peao %d do jogador %d comeu o peao %d do jogador %d\n", j+1, i+1, n+1, m+1);
																			jog_p[m].posicao_peao[n] = 0;
																			jog_p[m].peao_liberado[n] = 0;
																		}
																	}
																	else if (m==1) { //casa segura vermelho
																		if (jog_p[m].posicao_peao[n]==18 || jog_p[m].posicao_peao[n]==70 || jog_p[m].posicao_peao[n]==23 || jog_p[m].posicao_peao[n]==75) {
																			printf("Peao adversario esta em uma casa segura, nao eh possivel comer\n");
																		}
																		else {
																			printf("O peao %d do jogador %d comeu o peao %d do jogador %d\n", j+1, i+1, n+1, m+1);
																			jog_p[m].posicao_peao[n] = 0;
																			jog_p[m].peao_liberado[n] = 0;
																		}
																	}
																}
															}
														}
													}
												}		
											}
										}
										for (m=0;m<4;m++) { //Vitoria do jogador
											jog_p[i].vitoria_j += jog_p[i].vitoria_p[m];
										}
										if (jog_p[i].vitoria_j==4) {
											printf("Jogador %d venceu!\n", i+1);
											fim_jog = 1;
										}
										else {
											jog_p[i].vitoria_j = 0;
											fim_jog = 0;
											cont = 0;
										}
									}
								}
							}
							else {
								break;
							}
						}
					}
				}
			}
			else if (num_jog==4) {
				verifica++;
				fim_jog = 0;
				while (fim_jog==0) {
					if (fim_jog==0) {
						for (i=0;i<4;i++) {
							if (fim_jog==0) {
								cont = 3;
								while (jog_p[i].dado==6 || cont!=0) {
									printf("\nTabuleiro:\n");
									for (k=0;k<4;k++) { //Imprime tabuleiro
										for (j=0;j<4;j++) {
											if(jog_p[k].posicao_peao[j]==0) {
												printf("Jogador %d - Peao %d - Em casa\n", k+1, j+1);
											}
											else if (jog_p[k].posicao_peao[j]<53){
												printf("Jogador %d - Peao %d - %d\n", k+1, j+1, jog_p[k].posicao_peao[j]);
											}
											else if (jog_p[k].vitoria_p[j]==1) {
												printf("Jogador %d - Peao %d - Casa Final\n", k+1, j+1);
											}
											else if (jog_p[k].posicao_peao[j]>=100 && jog_p[k].peao_liberado[j]>0) {
												if (k==0) {
													printf("Jogador %d - Peao %d - Reta Final %d\n", k+1, j+1, jog_p[k].posicao_peao[j]-99);
												}
												else if (k==1) {
													printf("Jogador %d - Peao %d - Reta Final %d\n", k+1, j+1, jog_p[k].posicao_peao[j]-105);
												}
												else if (k==2) {
													printf("Jogador %d - Peao %d - Reta Final %d\n", k+1, j+1, jog_p[k].posicao_peao[j]-111);
												}
												else if (k==3) {
													printf("Jogador %d - Peao %d - Reta Final %d\n", k+1, j+1, jog_p[k].posicao_peao[j]-117);
												}
											}
											else {
												printf("Jogador %d - Peao %d - Segunda Volta %d\n", k+1, j+1, jog_p[k].posicao_peao[j]-52);
											}
										}
									}
									printf("\n\n");
									printf("Jogador %d, pressione ENTER para rolar o dado ", i+1);
									fflush(stdin);
									scanf("%c", &input);
									jog_p[i].dado = rolar_dado();
									if (jog_p[i].dado==6) { //Repetir turnos, se igual a 0 entao turno nao se repete, ira rodar ate 3 vezes
										cont--;
										}
										else { //Se o dado for diferente de 6 entao o contador zera
											cont = 0;
									}
									if (cont==0 && jog_p[i].dado==6) {
										printf("3 dados 6 consecutivos, pula a vez\n");
									}
									else {
										printf("Dado: %d\n", jog_p[i].dado);
										ver_p = 0;
										aux_lib = 0;
										for (m=0;m<4;m++) {
											if (jog_p[i].vitoria_p[m]==0 && jog_p[i].peao_liberado[m]!=0) { //vai somar caso tenha peao liberado e que nao esta na casa final
												aux_lib++;
											}
										}
										if (aux_lib!=0) { //tem peao liberado e podem ser movidos
											while (ver_p==0) {
												printf("\nJogador %d, selecione o peao que deseja mover\n", i+1);
													scanf("%d", &j);
												j--;
												if (j<0 || j>3) {
													printf("Peao selecionado eh invalido, selecione um peao de 1 a 4\n");
												}
												else if (jog_p[i].vitoria_p[j]==1) {
													printf("Peao selecionado ja esta na casa final, selecione outro peao\n");
												}
												else if (jog_p[i].peao_liberado[j]==0 && jog_p[i].dado!=6) {
													printf("Peao selecionado esta em casa e nao pode ser liberado, selecione outro peao\n");
												}
												else {
													ver_p++;
												}
											}
										}
										else if (aux_lib==0 && jog_p[i].dado==6) { //nenhum peao liberado, mas pode ser liberado
											while (ver_p==0) {
												printf("\nJogador %d, selecione um peao para liberar\n", i+1);
												scanf("%d", &j);
												j--;
												if (j<0 || j>3) {
													printf("Peao selecionado eh invalido, selecione um peao de 1 a 4\n");
												}
												else {
													ver_p++;
												}
											}
										}
										else { //nenhum peao liberado
											printf("Dado diferente de 6, nao eh possivel liberar nenhum peao\n");
											j = -1;
										}
										if (j!=-1) { //se j=-1 entao o movimento anterior eh invalido
											if (jog_p[i].peao_liberado[j]==0) {
												jog_p[i].posicao_peao[j] = liberar_peao(i, &jog_p[i]);
												if (jog_p[i].posicao_peao[j]!=0) {
													jog_p[i].peao_liberado[j]++;
													jog_p[i].jogada[j]++;
												}
											}										
											else {
												jog_p[i].posicao_peao[j] = mover_peao(&jog_p[i], i, j);
												jog_p[i].jogada[j]++;							
											}
											if (jog_p[i].posicao_peao[j]<=98 && jog_p[i].peao_liberado[j]==1) { //comer peao, somente valido se peao nao estiver na reta final e estiver liberado
												for (m=0;m<4;m++) {
													if (m!=i) { //jogador que eh comido nao eh o jogador comendo
														for (n=0;n<4;n++) {
															if (jog_p[m].posicao_peao[n]<=98) { //peao inimigo nao esta na reta final
																if (jog_p[i].posicao_peao[j]==jog_p[m].posicao_peao[n] || jog_p[i].posicao_peao[j]==jog_p[m].posicao_peao[n]-52) {
																	if (m==0) { //casa segura verde
																		if (jog_p[m].posicao_peao[n]==5 || jog_p[m].posicao_peao[n]==57 || jog_p[m].posicao_peao[n]==10 || jog_p[m].posicao_peao[n]==62) {
																			printf("Peao adversario esta em uma casa segura, nao eh possivel comer\n");
																		}
																		else {
																			printf("O peao %d do jogador %d comeu o peao %d do jogador %d\n", j+1, i+1, n+1, m+1);
																			jog_p[m].posicao_peao[n] = 0;
																			jog_p[m].peao_liberado[n] = 0;
																		}
																	}
																	else if (m==1) { //casa segura vermelho
																		if (jog_p[m].posicao_peao[n]==18 || jog_p[m].posicao_peao[n]==70 || jog_p[m].posicao_peao[n]==23 || jog_p[m].posicao_peao[n]==75) {
																			printf("Peao adversario esta em uma casa segura, nao eh possivel comer\n");
																		}
																		else {
																		printf("O peao %d do jogador %d comeu o peao %d do jogador %d\n", j+1, i+1, n+1, m+1);
																		jog_p[m].posicao_peao[n] = 0;
																		jog_p[m].peao_liberado[n] = 0;
																		}
																	}
																	else if (m==2) { //casa segura azul
																		if (jog_p[m].posicao_peao[n]==31 || jog_p[m].posicao_peao[n]==83 || jog_p[m].posicao_peao[n]==36 || jog_p[m].posicao_peao[n]==88) {
																			printf("Peao adversario esta em uma casa segura, nao eh possivel comer\n");
																		}
																		else {
																		printf("O peao %d do jogador %d comeu o peao %d do jogador %d\n", j+1, i+1, n+1, m+1);
																		jog_p[m].posicao_peao[n] = 0;
																		jog_p[m].peao_liberado[n] = 0;
																		}
																	}
																	else if (m==3) { //casa segura amarelo
																		if (jog_p[m].posicao_peao[n]==44 || jog_p[m].posicao_peao[n]==96 || jog_p[m].posicao_peao[n]==46 || jog_p[m].posicao_peao[n]==98) {
																			printf("Peao adversario esta em uma casa segura, nao eh possivel comer\n");
																		}
																		else {
																		printf("O peao %d do jogador %d comeu o peao %d do jogador %d\n", j+1, i+1, n+1, m+1);
																		jog_p[m].posicao_peao[n] = 0;
																		jog_p[m].peao_liberado[n] = 0;
																		}
																	}
																}
															}
														}
													}
												}		
											}
										}
										for (m=0;m<4;m++) { //Vitoria do jogador
											jog_p[i].vitoria_j += jog_p[i].vitoria_p[m];
										}
										if (jog_p[i].vitoria_j==4) {
											printf("Jogador %d venceu!\n", i+1);
											fim_jog = 1;
										}
										else {
											jog_p[i].vitoria_j = 0;
											fim_jog = 0;
											cont = 0;
										}
									}
								}
							}
							else {
								break;
							}
						}
					}
				}
			}
			else {
				printf("Numero de jogadores invalido\n");
			}
		}
		printf("Digite S para jogar novamente e N para encerrar\n");
		fflush(stdin);
		scanf("%c", &jog_nov);
		if (jog_nov=='n' || jog_nov=='N') {
			printf("\nFim do jogo\n");
			loop++;
		}
		else if (jog_nov=='s' || jog_nov=='S'){
			verifica = 0;
		}
	}
	return 0;
}

int rolar_dado () {
	int dado_r = 0;
	while (dado_r==0 || dado_r>6) {
		srand(time(NULL));
		dado_r = rand()%7;
	}
	return dado_r;
}

int mover_peao (struct jogador *jog_p, int i, int j) {
	int k = j;
	int move = 0;
	int liberado = jog_p->peao_liberado[k];
	int jogada_aux = jog_p->jogada[k];
	int move_aux;
	move = jog_p->posicao_peao[k] + jog_p->dado;
	if (i==0) {
		if (move>=59) { //Jogador 1, Verde
			if (move>59 && jog_p->reta_f[k]==0) {
				move = 99 + move - 59;
				jog_p->reta_f[k] = 1;
			}
			if (move>104) {
				printf("Dado acima do necessario para ganhar\n");
				move -= jog_p->dado;
				jog_p->reta_f[k] = 1;
			}
			else if (move==104) {
				jog_p->vitoria_p[k] = 1;
				jog_p->reta_f[k] = 1;
			}
		}
	}
	else if (i==1) { //Jogador 2, Vermelho
		if (move>=72) {
			if (move>72 && jog_p->reta_f[k]==0) {
				move = 105 + move - 72;
				jog_p->reta_f[k] = 1;
			}
			if (move>110) {
				printf("Dado acima do necessario para ganhar\n");
				move -= jog_p->dado;
				jog_p->reta_f[k] = 1;
			}
			else if (move==110) {
				jog_p->vitoria_p[k] = 1;
				jog_p->reta_f[k] = 1;
			}
		}
	}
	else if (i==2) { //Jogador 3, Azul
		if (move>=85) {
			if (move>85 && jog_p->reta_f[k]==0) {
				move = 111 + move - 85;
				jog_p->reta_f[k] = 1;
			}
			if (move>116) {
				printf("Dado acima do necessario para ganhar\n");
				move -= jog_p->dado;
				jog_p->reta_f[k] = 1;
			}
			else if (move==116) {
				jog_p->vitoria_p[k] = 1;
				jog_p->reta_f[k] = 1;
			}
		}
	}
	else if (i==3) { //Jogador 4, Amarelo
		if (move>=98) {
			if (move>98 && jog_p->reta_f[k]==0) {
				move = 117 + move - 98;
				jog_p->reta_f[k] = 1;
			}
			if (move>122) {
				printf("Dado acima do necessario para ganhar\n");
				move -= jog_p->dado;
				jog_p->reta_f[k] = 1;
			}
			else if (move==122) {
				jog_p->vitoria_p[k] = 1;
				jog_p->reta_f[k] = 1;
			}
		}
	}
	else {
		printf("\nErro, jogador nao existe\n");
	}
	return move;
}

int liberar_peao (int i, struct jogador *jog_p) {
	int move;
	int dado_r = jog_p->dado;
	if (dado_r==6) {
		switch (i) {
		case 0: //Jogador 1, Verde
			move = 5;
			break;
		case 1: //Jogador 2, Vermelho
			move = 18;
			break;
		case 2: //Jogador 3, Azul
			move = 31;
			break;
		case 3: //Jogador 4, Amarelo
			move = 44;
			break;
		default:
			printf("\nErro, jogador nao existe\n");
			move = 0;
			break;
		}
	}
	else {
		printf("\nPeao nao ira ser liberado\n");
	}
	return move;
}
