#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>

int potomkowie[40];

void funk2(int num){
	if(num==10) {
    int i;
    for (i=0;i<40;i++){
        if(potomkowie[i]>0){
			printf("%d ", potomkowie[i]);
			kill(potomkowie[i], SIGTERM);
        }
    }
	exit(0);
	}
}
 
int main(int argc, char* argv[]){
	if(argc != 2) {
		printf("Prosze podac w wywolanie jeden arguemnt(ilosc procesow potomnych)\n");
		exit(0);
	}
	time_t czas; 			
	srand(time(&czas));
	signal(10, funk2); 					// obsluga sygnalu SIGUSR1
	int i;
	int num = atoi(argv[1]);
	int rodzic = getpid(); 				// PID procesu macierzystego
	printf("Ilosc procesow potomnych do utworzenia: %d\n", num);
	printf("PID procesu mcierzystego: %d\n", getpid());
	for(i=0; i<num; i++){
	int czas2 = rand()%10+6; 			// wyliczenie loswoego czasu oczekiwania dla procesu potomnego
	potomkowie[i] = fork(); 				// zapisanie pid procesu potomnego
		if(!potomkowie[i]){
		  printf("PID: %d PPID: %d czas oczekiwania: %d\n", getpid(), getppid(), czas2);
		  sleep(czas2);
		  printf("Proces PID: %d obudzil sie jako pierwszy i wysyla sygnal SIGTERM do procesow: \n", getpid());
		  kill(rodzic, 10); 			// pierwszy obudzony proces wysyla SIGUSR1 do procesu macierzystego
		  exit(0);
		}
	}
	for(;;) wait(1); 					// rodzic czeka na sygnal od pierwszy proces potomnego
	return 0;
}
