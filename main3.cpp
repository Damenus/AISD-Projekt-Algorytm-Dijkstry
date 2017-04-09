#include <iostream>

struct vector {
	int x, y, *wartosc;
	int *wsk;
public:
	vector::vector() {
		this->x = 0;
		this->y = 0;
		this->wartosc = 0;
	}
	vector::~vector() {}
	vector::vector(int x, int y, int *wartosc)
	{
		this->x = x;
		this->y = y;
		this->wartosc = wartosc;
	}
};

const int max = 100;
const int MAXINT = 2147483647;
int szerokosc, wysokosc, start_szerokosc, start_wysokosc, finish_szerokosc, finish_wysokosc, liczba_wyciagow;
int wyciag_start_szerokosc[10000], wyciag_start_wysokosc[10000], wyciag_finish_szerokosc[10000], wyciag_finish_wysokosc[10000], wyciag_czas_podrozy[10000], wyciag_czas_odjazdu[10000];
int **tab;
int **Q;

int limit;
int zmienna;

vector *T;
int n;
bool **S;



void swap(vector &a, vector &b)
{
	vector c;
	c = a;
	a = b;
	b = c;
}

void sort()
{
	int wejscie = n;
	for (int j = wejscie - 1; j >= 0; j--)
	{
		if (*T[((j - 1) / 2)].wartosc > *T[j].wartosc)
			swap(T[((j - 1) / 2)], T[j]);
	}
}


vector heap_pull()
{
	int j = 0;
	//sort();
	vector tab = T[0];
	T[0] = T[n - 1];
	n--;

	while (j < (n - 1) / 2) {

		if (*T[j].wartosc > *T[2 * j + 1].wartosc)
			swap(T[j], T[2 * j + 1]);
		if (*T[j].wartosc > *T[2 * j + 2].wartosc)
			swap(T[j], T[2 * j + 2]);
		j++;
	}

	return tab;


}

void heap_push(int *v, int x, int y)
{
	int i, j;

	i = n;
	n++;
	j = (i - 1) / 2;
	T[i] = vector(x, y, v);

	while (i > 0 && T[j].wartosc > v)
	{
		swap(T[i], T[j]);
		i = j;
		j = (i - 1) / 2;
	}

}


void dijskra(){


	limit = wysokosc * szerokosc;
	Q[start_szerokosc][start_wysokosc] = 0;
	S[start_szerokosc][start_wysokosc] = true;
	heap_push(&Q[start_szerokosc][start_wysokosc], start_szerokosc, start_wysokosc);
	vector temp;

	while (n != 0) {
		temp = heap_pull();
		start_szerokosc = temp.x;
		start_wysokosc = temp.y;


		if (start_szerokosc + 1 < szerokosc) {
			if (tab[start_szerokosc + 1][start_wysokosc] < tab[start_szerokosc][start_wysokosc]) {
				if (Q[start_szerokosc + 1][start_wysokosc] > (zmienna = Q[start_szerokosc][start_wysokosc] + 1)) {
					Q[start_szerokosc + 1][start_wysokosc] = zmienna;
					heap_push(&Q[start_szerokosc + 1][start_wysokosc], start_szerokosc + 1, start_wysokosc);
				}
			}
			else
				if (Q[start_szerokosc + 1][start_wysokosc] > (zmienna = Q[start_szerokosc][start_wysokosc] + tab[start_szerokosc + 1][start_wysokosc] - tab[start_szerokosc][start_wysokosc] + 1)) {
				Q[start_szerokosc + 1][start_wysokosc] = zmienna;
				heap_push(&Q[start_szerokosc + 1][start_wysokosc], start_szerokosc + 1, start_wysokosc);
				}

		}
		if (start_szerokosc - 1 >= 0) {
			if (tab[start_szerokosc - 1][start_wysokosc] < tab[start_szerokosc][start_wysokosc]) {
				if (Q[start_szerokosc - 1][start_wysokosc] > (zmienna = Q[start_szerokosc][start_wysokosc] + 1)) {
					Q[start_szerokosc - 1][start_wysokosc] = zmienna;
					heap_push(&Q[start_szerokosc - 1][start_wysokosc], start_szerokosc - 1, start_wysokosc);
				}
			}
			else
				if (Q[start_szerokosc - 1][start_wysokosc] > (zmienna = Q[start_szerokosc][start_wysokosc] + tab[start_szerokosc - 1][start_wysokosc] - tab[start_szerokosc][start_wysokosc] + 1)) {
				Q[start_szerokosc - 1][start_wysokosc] = zmienna;
				heap_push(&Q[start_szerokosc - 1][start_wysokosc], start_szerokosc - 1, start_wysokosc);
				}

		}
		if (start_wysokosc + 1 < wysokosc) {
			if (tab[start_szerokosc][start_wysokosc + 1] < tab[start_szerokosc][start_wysokosc]) {
				if (Q[start_szerokosc][start_wysokosc + 1] > (zmienna = Q[start_szerokosc][start_wysokosc] + 1)) {
					Q[start_szerokosc][start_wysokosc + 1] = zmienna;
					heap_push(&Q[start_szerokosc][start_wysokosc + 1], start_szerokosc, start_wysokosc + 1);
				}
			}
			else
				if (Q[start_szerokosc][start_wysokosc + 1] > (zmienna = Q[start_szerokosc][start_wysokosc] + tab[start_szerokosc][start_wysokosc + 1] - tab[start_szerokosc][start_wysokosc] + 1)) {
				Q[start_szerokosc][start_wysokosc + 1] = zmienna;
				heap_push(&Q[start_szerokosc][start_wysokosc + 1], start_szerokosc, start_wysokosc + 1);
				}


		}
		if (start_wysokosc - 1 >= 0) {
			if (tab[start_szerokosc][start_wysokosc - 1] < tab[start_szerokosc][start_wysokosc]) {
				if (Q[start_szerokosc][start_wysokosc - 1] > (zmienna = Q[start_szerokosc][start_wysokosc] + 1)) {
					Q[start_szerokosc][start_wysokosc - 1] = zmienna;
					heap_push(&Q[start_szerokosc][start_wysokosc - 1], start_szerokosc, start_wysokosc - 1);
				}
			}
			else
				if (Q[start_szerokosc][start_wysokosc - 1] > (zmienna = Q[start_szerokosc][start_wysokosc] + tab[start_szerokosc][start_wysokosc - 1] - tab[start_szerokosc][start_wysokosc] + 1)) {
				Q[start_szerokosc][start_wysokosc - 1] = zmienna;
				heap_push(&Q[start_szerokosc][start_wysokosc - 1], start_szerokosc, start_wysokosc - 1);
				}

		}


		for (int i = 0; i < liczba_wyciagow; i++) {
			if (start_szerokosc == wyciag_start_szerokosc[i] && start_wysokosc == wyciag_start_wysokosc[i]) {
				zmienna = Q[start_szerokosc][start_wysokosc] + wyciag_czas_podrozy[i] + (wyciag_czas_odjazdu[i] - (Q[start_szerokosc][start_wysokosc] % wyciag_czas_odjazdu[i])) % wyciag_czas_odjazdu[i];
				if (Q[wyciag_finish_szerokosc[i]][wyciag_finish_wysokosc[i]] > zmienna) {
					Q[wyciag_finish_szerokosc[i]][wyciag_finish_wysokosc[i]] = zmienna;
				
					heap_push(&Q[wyciag_finish_szerokosc[i]][wyciag_finish_wysokosc[i]], wyciag_finish_szerokosc[i], wyciag_finish_wysokosc[i]);	
				
				}
			}
		}
	}
}

int main()
{
	int wpisywana;


	scanf("%i %i %i %i %i %i %i", &wysokosc, &szerokosc, &start_wysokosc, &start_szerokosc, &finish_wysokosc, &finish_szerokosc, &liczba_wyciagow);
	for (int i = 0; i < liczba_wyciagow; i++)
			scanf("%i %i %i %i %i %i", &wyciag_start_wysokosc[i], &wyciag_start_szerokosc[i], &wyciag_finish_wysokosc[i], &wyciag_finish_szerokosc[i], &wyciag_czas_podrozy[i], &wyciag_czas_odjazdu[i]);


	tab = new int *[szerokosc];
	Q = new int *[szerokosc];
	S = new bool *[szerokosc];
	T = new vector[szerokosc*wysokosc];

	for (int i = 0; i < szerokosc; i++) {
		tab[i] = new int[wysokosc];
		Q[i] = new int[wysokosc];
		S[i] = new bool[wysokosc];
	}

	for (int i = 0; i < szerokosc; i++)
		for (int j = 0; j < wysokosc; j++)
		{
		scanf("%i", &wpisywana);
		tab[i][j] = wpisywana;
		Q[i][j] = MAXINT;
		S[i][j] = false;
		}

	dijskra();

	printf("%i", Q[finish_szerokosc][finish_wysokosc]);

	for (int i = 0; i < szerokosc; i++) {
		delete[] tab[i];
		delete[] Q[i];
		delete[] S[i];
	}

	delete[] tab;
	delete[] Q;
	delete[] S;
	delete[] T;

	return 0;
}
