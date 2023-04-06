#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <conio.h>

typedef struct {

	char is;
	int nr_mat;
	char nume[30];
	int grupa;
	char an;
	
	struct{
		char curs;
		char seminar;
	}abs[5];

}STUDENT;

int nr_art(FILE *bin, long l){

	long p;
	int n;
	p = ftell(bin);
	fseek(bin, 0, 2);
	n = ftell(bin)/l;
	fseek(bin, p, 0);

	return n;
}

void text(const char* numeBin, const char* numeText) {

	FILE *g, *f;
	STUDENT x;

	g = NULL;

	f = fopen(numeBin, "rb");

	if (!f) {
		printf("ERR");
	}
	else {

		g = fopen(numeText, "w");
		
		printf("Good");

		fprintf(g, "Nr matricol    Nume    Grupa   An              Absente\n", "");

		fread(&x, sizeof(STUDENT), 1, f);

		while (!feof(f)) {

			if (x.is == 1)
			{
				fprintf(g, "\n%10d %17s %10d %4d", x.nr_mat, x.nume, x.grupa, x.an);

				for (int i = 0; i < 5; i++)
				{
					fprintf(g, "%d %d ", x.abs[i].curs, x.abs[i].seminar);
				}

			}
			fread(&x, sizeof(STUDENT), 1, f);
		}


	}

	fclose(f);
	fclose(g);

}


int main() {
	
	//inregistrare(bin);
	//temaSase(bin);
	text("Fis_relativ_abs.dat", "FisTxt.txt");

	return 0;
}