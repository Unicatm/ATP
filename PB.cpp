#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <conio.h>


typedef struct {

	int nr_mat;
	char nume[30];
	int grupa;
	char pp;
	char teme[10];
	char exam;

}STUDENT;


void inregistrare(FILE *bin) {  // a fost prima data inregistrare si acuma am adugat numai noi srudenti un student

	bin = fopen("inrgStud.dat", "rb+"); // LA REINREGISTRARE DESCHID CU RB+

	STUDENT x;

	if (!bin) {
		printf("ERR");
	}
	else {
		printf("Good\n");

		printf("Introduceti nr matricol NOU sau CTRL Z: ");
		scanf("%d", &x.nr_mat);

		while (!feof(stdin)) {

			fseek(bin, 0, 2);

			printf("Nume: ");
			scanf("%s", &x.nume);

			printf("Grupa: ");
			scanf("%d", &x.grupa);

			printf("Punctaj proba practica <<0-30>>: ");
			scanf("%d", &x.pp);

			

			for (int i = 0; i < 10; i++) {
				x.teme[i] = 0;
				printf("tema[%d] = %d\n", i + 1, x.teme[i]);
			}

			printf("Punctaj exam <<0-50>>: ");
			scanf("%d", &x.exam);

			fwrite(&x, sizeof(STUDENT), 1, bin);

			printf("\n");

			printf("Introduceti nr matricol NOU sau CTRL Z: ");
			scanf("%d", &x.nr_mat);

		}
	}

	fclose(bin);
}

void text(FILE *bin) {

	FILE* txt;

	bin = fopen("TemaSase.dat", "rb");
	txt = fopen("TemaSase.txt", "w");

	STUDENT x;


	fprintf(txt, "Nr.mat   \tNume  %10sGrupa   Proba Practica  Teme   Examen  \n", "");
	fread(&x, sizeof(STUDENT), 1, bin);

	while (!feof(bin)) {

		fprintf(txt, "\n\t%d  \t%3s  \t%3d \t%5d", x.nr_mat, x.nume, x.grupa, x.pp);

		for (int i = 0; i < 10; i++) {
			fprintf(txt, "%2d", x.teme[i]);
		}

		fprintf(txt, "\t%2d", x.exam);

		fread(&x, sizeof(STUDENT), 1, bin);

	}

	fclose(bin);
	fclose(txt);

}


void temaSase(FILE *bin) {

	bin = fopen("TemaSase.dat", "rb+");

	STUDENT x;
	int cautat;

	if (!bin) {
		printf("ERR");
	}
	else {
		printf("Good!\n");

		printf("Introdu nr matricol cautat: ");
		scanf("%d", &cautat);

		fread(&x, sizeof(STUDENT), 1, bin);

		while (!feof(bin)) {

			if (cautat == x.nr_mat) {

				printf("Punctajul la tema 6: ");
				scanf("%d", &x.teme[6]);
				
				//fseek(bin, 0, 2); //trecere in scriere
				fseek(bin, ftell(bin) - sizeof(STUDENT), SEEK_SET); //ma duce la inceputul articolului meu
				fwrite(&x, sizeof(STUDENT), 1, bin);
				fseek(bin, 0, 1); //trecere in citire

				fread(&x, sizeof(STUDENT), 1, bin);
			}
			else {
				fread(&x, sizeof(STUDENT), 1, bin);
			}

		}

	}

	fclose(bin);
}



int main() {
	FILE* bin;
	bin = NULL;

	//inregistrare(bin);
	//temaSase(bin);
	text(bin);

	return 0;
}