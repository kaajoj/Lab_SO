#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void wypisz(int num) {				// sprawdzenie warunkow dla poszczegolnych sygnalow
	if(num == 2) {
		printf("Nr sygnalu: 2, nazwa: SIGINT, wywolany skrotem: Ctrl + c\n");
		exit(0);					// obsługa wyjscia
	}
	else if (num == 3) {
		printf("Nr sygnalu: 3, nazwa: SIGQUIT, wywolany skrotem: Ctrl + \\\n");
	}
	else if (num == 20) {		
		printf("Nr sygnalu: 20, nazwa: SIGTSTP, wywolany skrotem: Ctrl + z\n");
	}
}

int main(int argc, char* argv[]) {			// glowna funkcja
	int i;									// zmienna do petli
	printf("Program sprawdzajacy jaki sygnal zostal wywolany przez kombinajce klawiszy.\n");
	printf("Sygnalu SIGINT - Ctrl + c konczy dzialnie programu.\n");
	for (i=1;i<32;i++){
		signal(i, wypisz);					// wywolanie funkcji signal i wywolie wypisz
	}
	while(1);		
	return 0;
}
