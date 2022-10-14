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
void freeWinners(winner *winners, int nbGagnants);
void infosAnnee(int annee);
winner getWinnerByYear(winner *, int, int);
void showWinner(winner winner);

int main(int argc, char *argv[])
{
	if(argc == 3 && strcmp(argv[1], "infosAnnee") == 0){
		int annee = atoi(argv[2]);
		infosAnnee(annee);
	}
	else{
		int nbGagnants = scanLineAsInt();
		printf("%i\n",nbGagnants);

		winner *winners = readWinners(nbGagnants);
		printWinners(winners, nbGagnants);
		freeWinners(winners, nbGagnants);
	}
	return EXIT_SUCCESS;
}

winner *readWinners(int nbGagnants){
	winner *winners = malloc(50*sizeof(winner));
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