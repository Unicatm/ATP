#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <conio.h>

typedef struct {

	int nr_mat;
	char nume[30];
	char an;
	int grupa;
	char tip;

	struct {
		char zi;
		char luna;
		int an;
	}data;

	struct {
		char ora;
		char min;
	}intrare;

	struct {
		char ora;
		char min;
	}iesire;


}STUDENT;


void text(FILE *bin) {

	FILE* txt;

	STUDENT x;

	bin = fopen("PB3.dat", "rb");
	txt = fopen("PB3.txt", "w");

	if(!bin) {
		printf("ERR");
	}
	else {
		printf("Good to go!\n");

		fprintf(txt, "Nr. mat%30s \tNume \tOra intrare \tOra iesire\n", "");
		fread(&x, sizeof(STUDENT),1, bin);

		while (!feof(bin)) {

			fprintf(txt, "%5d %5s %d:%d     %d:%d", x.nr_mat, x.nume, x.intrare.ora, x.intrare.min, x.iesire.ora, x.iesire.min);
			fread(&x, sizeof(STUDENT), 1, bin);

		}
	}
	fclose(bin);
	fclose(txt);

}

void calc(FILE *bin) {

	STUDENT x;
	bin = fopen("PB3.dat", "rb");

	int nrmat_cautat;

	if (!bin) {
		printf("ERR");
	}
	else {
		printf("Good to go!\n");

		fread(&x, sizeof(STUDENT), 1, bin);

		printf("Nr matricol cautat: ");
		scanf("%d", &nrmat_cautat);

		while (!feof(bin)) {

			if (x.tip != 'L') {
				printf("Ora de studiu: 0h00min\n");
				printf("Tip: %c\n", x.tip);
				fread(&x, sizeof(STUDENT), 1, bin);
			}
			else {
				printf("Tip: %c", x.tip);
				int calc = 0;
				int oraCalc = 0;
				int minCalc = 0;
				int oraToMin = 0;
				int oraFin = 0;
				int minFin = 0;
				int oraInMin = 0;

				if (nrmat_cautat = x.nr_mat) {

					oraCalc = x.iesire.ora - x.intrare.ora;
					minCalc = x.iesire.min - x.intrare.min;

					if (minCalc < 0) {
						oraToMin = oraCalc * 60;
						oraInMin = oraToMin + minCalc;
						oraFin = oraInMin / 60;
						minFin = oraInMin % 60;
					}
					else {
						oraFin = oraCalc;
						minFin = minCalc;
					}

					printf("Ora intrare: %d:%d\n", x.intrare.ora, x.intrare.min);
					printf("Ora iesire: %d:%d\n", x.iesire.ora, x.iesire.min);
					printf("Ora de studiu: %dh%dmin\n", oraFin, minFin);

				}

				fread(&x, sizeof(STUDENT), 1, bin);

				printf("Nr matricol NOU cautat sau CTRL Z:");
				scanf("%d", &nrmat_cautat);
			}

		}

	}
	fclose(bin);

}

int main() {

	FILE* bin;
	bin = NULL;

	text(bin);

}

