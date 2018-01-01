#include <stdio.h>			
#include <unistd.h>
#include <stdlib.h>

int p2,p3,p4,p5,p6,p7,p10,p8,p9;		// zmienne wykorzystane do wyswietlenia potomkow

int main() {

	switch(p2=fork()) {						// utworzenie pierwszego potomka(P2) dla procesu P1
	case 0:
	/* P2 */
	printf("P2 PID: %d PPID: %d\n", getpid(), getppid());		// wypisanie na ekran id procesu P2 i id jego przodka
	exit(0);

	case -1:
	printf("Blad funkcji fork\n");			// obsluga bledów
	exit(1);

	default:
	/* P1 */ 

		switch(p3=fork()) {			// utworzenie drugiego potomka(P3) dla procesu P1
		case 0:
		/* P3 */
		
			switch(p6=fork()) {			// utworzenie pierwszego potomka(P6) dla procesu P3
			case 0:
			/* P6 */	
			printf("P6 PID: %d PPID: %d\n", getpid(), getppid());		// wypisanie na ekran id procesu P2 i id jego przodka
			exit(0);
			
			
			case -1:
			printf("Blad funkcji fork\n");			// obsluga bledów
			exit(1);
		
			default:

					switch(p7=fork()) {			// utworzenie drugiego potomka(P7) dla procesu P3
					case 0:
					/* P7 */

						switch(p10=fork()) {		// utworzenie potomka(P10) dla procesu P7
						case 0:
						/* P10 */
						printf("P10 PID: %d PPID: %d\n", getpid(), getppid());		// wypisanie na ekran id procesu P2 i id jego przodka
						exit(0);	
			
						case -1:
						printf("Blad funkcji fork\n");			// obsluga bledów
						exit(1);
			
						default:
						wait(NULL);				// oczekiwanie na zakonczenie potomka
						}	
						
					printf("P7 PID: %d PPID: %d potomkowie: %d\n", getpid(), getppid(),p10); 	// wypisanie na ekran id procesu P7, id jego przodka i potomka
					exit(0);	
			
					case -1:
					printf("Blad funkcji fork\n");			// obsluga bledów
					exit(1);
			
					default:
					wait(NULL);				// oczekiwanie na zakonczenie potomka
					}	
			
			wait(NULL);				// oczekiwanie na zakonczenie potomka
			}
			
		printf("P3 PID: %d PPID: %d potomkowie: %d %d\n", getpid(), getppid(),p6,p7); 	// wypisanie na ekran id procesu P3, id jego przodka i potomkow
		exit(0);	
		
		case -1:
		printf("Blad funkcji fork\n");			// obsluga bledów
		exit(1);
		
		default:
			switch(p4=fork()) {			// utworzenie trzeciego potomka(P4) dla procesu P1
			case 0:
			/* P4 */
			printf("P4 PID: %d PPID: %d\n", getpid(), getppid());			// wypisanie na ekran id procesu P2 i id jego przodka
			exit(0);	
		
			case -1:
			printf("Blad funkcji fork\n");			// obsluga bledów
			exit(1);
		
			default:

					switch(p5=fork()) {				// utworzenie czwartego potomka(P4) dla procesu P1
					case 0:
					/* P5 */

						switch(p8=fork()) {			// utworzenie pierwszego potomka(P8) dla procesu P4
						case 0:
						/* P8 */
						printf("P8 PID: %d PPID: %d\n", getpid(), getppid());			// wypisanie na ekran id procesu P2 i id jego przodka
						exit(0);	
		
						case -1:
						printf("Blad funkcji fork\n");			// obsluga bledów
						exit(1);
		
						default:

							switch(p9=fork()) {			// utworzenie drugiego potomka(P9) dla procesu P4
							case 0:
							/* P9 */
							printf("P9 PID: %d PPID: %d\n", getpid(), getppid());		// wypisanie na ekran id procesu P2 i id jego przodka
							exit(0);	
		
							case -1:
							printf("Blad funkcji fork\n");			// obsluga bledów
							exit(1);
		
							default:
							wait(NULL);			// oczekiwanie na zakonczenie potomka
							}	

						wait(NULL);			// oczekiwanie na zakonczenie potomka
						}

					printf("P5 PID: %d PPID: %d potomkowie: %d %d\n", getpid(), getppid(),p8,p9); // wypisanie na ekran id procesu P5, id jego przodka i potomkow
					exit(0);	
		
					case -1:
					printf("Blad funkcji fork\n");			// obsluga bledów
					exit(1);
		
					default:
					wait(NULL);		// oczekiwanie na zakonczenie potomka
					}	

			wait(NULL);			// oczekiwanie na zakonczenie potomka
			}
	
		wait(NULL);			// oczekiwanie na zakonczenie potomka
		}

	wait(NULL);			// oczekiwanie na zakonczenie potomka
	}

printf("P1 PID: %d PPID: %d potomkowie: %d %d %d %d\n", getpid(), getppid(),p2,p3,p4,p5);	// wypisanie na ekran id procesu P10, id jego przodka i potomkow

return 0;
}
