/**
 Compilation
 gcc --std=c99 -W -Wall -o prixTuring prixTuring.c

 Exécution
 ./prixTuring < turingWinners.txt > out.txt

 Tests
 diff out.txt turingWinners.txt

 Détection de fuites mémoires
 valgrind --leak-check=yes --leak-check=full --show-leak-kinds=all --show-reachable=no ./prixTuring < turingWinners.txt > out.txt
**/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
	int year;
	char *name;
	char *field;
	} winner;

/* This function scans a line of text (until \n) and returns a char* that contains all characters on the line (up to 255) excluding \n.
It also ensures the \0 termination.
**WARNING**: The result of this function has been allocated (calloc) by the function */
char* scanLine()
{
	int maxLineSize = 255;
	char c, *line = calloc(maxLineSize+1,sizeof(char));

	scanf("%250[^\n]", line);

	if ( (c = getchar()) != '\n') {
		/* we did not get all the line */
		line[250] = '[';
		line[251] = line[252] = line[253] = '.';
		line[254] = ']';
		// line[255] = '\0'; // useless because already initialized by calloc

		// let's skip all chars untli the end of line
		while (( (c = getchar()) != '\n') && c != EOF) ;
	}

	return line;
}

/* This function scans a line of text (until \n), converts it as an integer and returns this integer */
int scanLineAsInt() {
	int buf;
	scanf("%i\n",&buf);
	return buf;
}


winner *readWinners(int);
void printWinners(winner *, int);
void freeWinners(winner *, int);
void infosAnnee(int);
winner getWinnerByYear(winner *, int, int);
void showWinner(winner);
void sortTuringWinnersByYear(winner *, int);
int foundLatest(winner *, int);
void exchangeLatest(winner *, int);
winner *addNewWinner(int);
void scanNewWinner(winner *);

int main(int argc, char *argv[])
{
	if(argc == 3 && strcmp(argv[1], "infosAnnee") == 0){
		int annee = atoi(argv[2]);
		infosAnnee(annee);
	}
	else{
		int nbGagnants = scanLineAsInt();
		printf("%i\n",nbGagnants);

		winner *winners;
		if(argc == 2 && strcmp(argv[1], "addNewWinner") == 0){
			winners = addNewWinner(nbGagnants);
			nbGagnants++;
			argv[1] = "sort";
		}
		else{
			winners = readWinners(nbGagnants);
		}
		if(argc == 2 && strcmp(argv[1], "sort") == 0)
			sortTuringWinnersByYear(winners, nbGagnants);
		printWinners(winners, nbGagnants);
		freeWinners(winners, nbGagnants);
	}
	return EXIT_SUCCESS;
}

winner *readWinners(int nbGagnants){
	winner *winners = malloc(nbGagnants*sizeof(winner));
	for(int i=0; i<nbGagnants; i++){
		winners[i].year = scanLineAsInt();
		winners[i].name = scanLine();
		winners[i].field = scanLine();
	}
	return winners;
}

void printWinners(winner *winners, int nbGagnants){
	for(int i=0; i<nbGagnants; i++){
		printf("%i\n%s\n%s\n", winners[i].year, winners[i].name, winners[i].field);
	}
}

void freeWinners(winner *winners, int nbGagnants){
	for(int i=0; i<nbGagnants; i++){
		free(winners[i].name);
		free(winners[i].field);
	}
	free(winners);
	winners = NULL;
}

void infosAnnee(int annee){
	int nbGagnants = scanLineAsInt();
	winner *winners = readWinners(nbGagnants);
	winner winner = getWinnerByYear(winners, nbGagnants, annee);
	freeWinners(winners, nbGagnants);
	showWinner(winner);
}

winner getWinnerByYear(winner *winners, int nbGagnants, int annee){
	for(int i = 0; i<nbGagnants; i++){
		if(winners[i].year == annee){
			return winners[i];
		}
	}
	winner winner;
	winner.year = annee;
	winner.name = "not found";
	winner.field = "not found";
	return winner;
}

void showWinner(winner winner){
	printf("L'annee %i, le(s) gagnant(s) ont été : %s\n", winner.year, winner.name);
	printf("Nature des travaux : %s\n", winner.field);
}

void sortTuringWinnersByYear(winner *winners, int nbGagnants){
	if(nbGagnants == 1)
		return;
	int minIndex = foundLatest(winners, nbGagnants);
	exchangeLatest(winners, minIndex);
	sortTuringWinnersByYear(winners+1, nbGagnants-1);
}

int foundLatest(winner *winners, int nbGagnants){
	int minYear = winners[0].year;
	int minIndex = 0;
	for(int i=0; i<nbGagnants; i++){
		if(winners[i].year < minYear){
			minYear = winners[i].year;
			minIndex = i;
		}	
	}
	return minIndex;
}

void exchangeLatest(winner *winners, int minIndex){
	winner tmp = winners[0];
	winners[0] = winners[minIndex];
	winners[minIndex] = tmp;
}

winner *addNewWinner(int nbGagnants){
	winner *winners = malloc((nbGagnants+1)*sizeof(winner));
	for(int i=0; i<nbGagnants; i++){
		winners[i].year = scanLineAsInt();
		winners[i].name = scanLine();
		winners[i].field = scanLine();
	}
	scanNewWinner(&winners[nbGagnants]);
	return winners;
}

void scanNewWinner(winner *winner){
	printf("Entrer une annee : ");
	scanf("%i", &(winner->year));
	printf("Entrer le(s) gagnants : ");
	scanf("%s", winner->name);
	printf("Nature des travaux : ");
	scanf("%s", winner->field);
}