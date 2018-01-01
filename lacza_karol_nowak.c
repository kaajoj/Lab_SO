#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

void main(){

int pip1[2], pip2[2], pip3[2], pip4[2];											// zmienne dla deskryptorow odpowiednich laczy;
pipe(pip1), pipe(pip2), pipe(pip3), pipe(pip4);									// utworzenie czterech laczy nienazwanych

int P1, P2;																		// zmienne potomkow

P1=fork();																				// utworzenie pierwszego potomka - P1
	if(P1==0){
		int i;
		char liczba1[15], liczba2[15];
		char *operator[15];
		
		close(pip1[0]); 																// zablokowanie odczytu
		printf("Podaj pierwsza liczbe dla procesu potomnego P1:\n");					
		scanf("%s", liczba1);																// zapisanie pierwszej podanej liczby
		printf("Podaj jeden z operatorow do wykonania dzialania: +, -, *, /\n");		
		scanf("%s", operator);																// zapisanie operatora
		printf("Podaj druga liczbe dla P1:\n");											
		scanf("%s", liczba2);																// zapisanie drugiej podanej liczby

		char tabDanych[60];																	// tabDanychlica do przechowywania danych
		
		for (i=0;i<60;i++) tabDanych[i]=NULL;

		strncat(tabDanych,liczba1, sizeof(tabDanych) + sizeof(liczba1));						// utworzenie jednego wyrazenia z trzech
		strncat(tabDanych,operator, sizeof(tabDanych) + sizeof(operator));
		strncat(tabDanych,liczba2, sizeof(tabDanych) + sizeof(liczba2));

		printf("P1 otrzymal wyrazenie: %s\n", tabDanych);
		printf("P1 zapisuje do potoku 1\n");
		write(pip1[1], tabDanych, 60);											// zapisywanie do potoku 1 wyrazenia do obliczen

		close(pip4[1]);													// zablokowaniue zapisu
		char final[60];
		read(pip4[0], final, 60);										//odczytywanie wyniku z potoku 4
		printf("P1 odczytuje z potoku 4 wartosc: %s\n", final);
		printf("P1 wyswietla wynik: %s\n", final);						// wyswietlenie koncowego wyniku
		exit(0);														// zakonczenie dzialania procesu P1
	}

	else {						
	P2 = fork();											// utworzenie drugiego potomka - P2 przez proces macierzysty - PM
		if (P2==0){
			int j;
			char wart2[60];
			
			close(pip2[1]);												// zablokowanie zapisu
			read(pip2[0], wart2, 60);									// odczytywanie z potoku 2
			printf("P2 odczytal z potoku 2 wartosc: %s\n", wart2);
			int licznik = 0;
			int x = 0, y = 0;
			char z;
			char pomtabDanych1[15], pomtabDanych2[15];
			for (j=0;j<15;j++){
				pomtabDanych1[j]=NULL;
				pomtabDanych2[j]=NULL;
			}
																// obsluga pierwszej liczby
			while (licznik == 0 || (wart2[licznik] != '+' && wart2[licznik] != '-' && wart2[licznik] != '*' && wart2[licznik] != '/')){
					pomtabDanych1[licznik] = wart2[licznik];
					licznik++;
				}	
			x = atoi(pomtabDanych1);
			
			z = wart2[licznik];									// operatorerator							
			licznik++;
			
			int pom = 0;										// obsluga drugiej liczby
			while (wart2[licznik] != NULL){
					pomtabDanych2[pom] = wart2[licznik];
					licznik++;
					pom++;
				}
			y = atoi(pomtabDanych2);
			int wynik=0;
			switch(z){
			case '+':
				wynik=x+y;
				break;
			case '-':
				wynik=x-y;
				break;
			case '*':
				wynik=x*y;
				break;
			default:
				if(y==0) {										//obsluga beldu dzielenia przez 0	
					close(pip3[0]);
					printf("P2 zapisuje do potoku 3\n");
					write(pip3[1], "blad dzielenia przez zero", 60);
					exit(0);
				}
				else
				wynik = x/y;
			}

			printf("P2 oblicza wynik dzialania: %d\n", wynik);
			char w[60];
			sprintf(w, "%d", wynik);
			
			close(pip3[0]);									// zablokowanie odczytu
			printf("P2 zapisuje wynik do potoku 3\n");
			write(pip3[1], w, 60);							// zapisanie wyniku do potoku 3, ktory odczyta PM
			exit(0); 										// koniec P2
		}
		else {												// dzialania procesu macierzystego
			close(pip1[1]); 								// zablokowanie zapisu
			char wart[60];
			read(pip1[0], wart, 60); 						// odczytywanie wyrazenia z potoku 1 zapisanego przez P1
			printf("PM odczytuje z potoku 1 wartosc: %s\n", wart);
			
			close(pip2[0]);									// zablokowanie odczytu
			printf("PM zapisuje do potoku 2\n");		
			write(pip2[1], wart, 60);						// zapisanie do potoku 2

			close(pip3[1]);									// zablokowanie zapisu
			char wart3[60];
			read(pip3[0], wart3, 60);						// odczytywanie wyniku z potoku 3
			printf("PM odczytuje z potoku 3 wartosc: %s\n", wart3);

			close(pip4[0]);									// zablokowanie odczytu
			printf("PM zapisuje do potoku 4\n");
			write(pip4[1], wart3, 60);						// zapisanie wyniku do potoku 4 z ktorego odczyta P1
			wait(NULL); 		
		}
	}
wait(NULL);
}