#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void *doKwadratu(void *arg){		// funkcja obliczająca kwadrat z podanego argument
  int kwad = *((int*)arg);
  int wynik = kwad*kwad; 			// do kwadratu
  return (int*)wynik;				// zwrocenie wyniku
}

int main (int n, char *argv[]){		// funkcja main ze zmiennymi do zapisania argumentow z jakimi zostala wywolana i ich ilosci
 
		if(n!=1){					// jezeli uzytkownik podal argumenty to wyswietlamy je na ekran
			printf("Ilosc podanych argumentow: %d\n", n-1);
		}
		else {
			printf("Nie podano argumentow.\n");			// obsługa nie podania argumentow przez uzytkownika
			exit(1);
		}

  pthread_t id_watki[n]; 						// tablica do przechowywania kolejnych watkow
		
  int watek, i, arg[n];													// zmienne wykorzystane w petli przy tworzeniu watkow i tablica to przechowywania wartosci arugmentow
  
	    for(i=1; i<n; i++){												// przejscie w petli for tyle razy ile argumentow podal uzytkownik
		arg[i] = atoi(argv[i]);											// przypisanie danemu indeksowi tablicy wartosci argumentu  - skonwertowana do postaci liczby typu int 
		watek = pthread_create(&id_watki[i], NULL, doKwadratu, &arg[i]);	// utworzeni watku i przekazanie w argumentach zmiennej do zapisania id watku oraz nazwa funkcji do wywolania i jej agument, uzywam domyślne atrubuty watku - NULL
			if(watek){															// obsluga bledu utworzenia watku
			  printf("Blad wywolania watku\n");
			  exit(-1);
			}
		}

  int suma=0;																// zmienna do przechowywania sumy kwadratow
  
	  for(i=1; i<n; i++){													// petla przchodzaca po kolejnym watku aby wyciagnac id i wynik
		void *wynik=0;
		pthread_join(id_watki[i], &wynik);									// oczekiwanie na zakonczenie danego watka
		printf("Watek o ID: %d otrzymał wynik: %d\n", id_watki[i], wynik);	// wypisanie wartości na ekran
		suma+=(int)wynik;													// dodawanie kolejnych wynikow watku to ostatecznego wyniku sumy
	  }
  printf("......................................\n");
  printf("Suma kwadratow argumentow wynosi: %d\n", suma);					// wypisanie wyniku na ekan
  pthread_exit(NULL);
}


