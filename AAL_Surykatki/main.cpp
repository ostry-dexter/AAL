/**
* Autor: Damian Ostrowski, 237489
* Przedmiot: AAL, EiTI
* Problem: Surykatki
* Dane wejœciowe:
* Szerokoœæ rzeki - w
* Maksymalny zasiêg skoku surykatki - j
* Liczba krokodyli na rzece - n
* n wierszy z parami 'b' i 'e' takimi, ¿e b<e
* Za³o¿enia na dane:
* Krokodyle s¹ roz³oczne ze sob¹ i brzegami rzeki
* maksymalna odleg³oœæ miêdzy krokodylami <= j
**/

/*
Test:
36
7
6
30 32
25 26
17 20
15 16
3 4
8 10

*/

#include <iostream>
#include <algorithm> // algorytm sort()
#include <vector> // lista krkodyli
#include <stdlib.h> // srand()
#include <time.h> // time()
#include <ctime> // clock()

using namespace std;

/**
* Struktura przechowuj¹ce informacje o krokodylu
**/
struct Crocodile
{
	int begin;
	int end;
	int id;
};

bool compCrocodile(Crocodile a, Crocodile b) { return (a.begin<b.begin); }

/**
* Struktura przechowuj¹ce informacje o punkcie reprezentuj¹cym krokodyla.
**/
struct Point
{
	int d; // odleg³oœæ do nastêpnego punktu
	int crocodileId; // id krokodyla
};

int generateJump(const int &min, const int &max)
{
	srand(time(NULL));
	return rand() % (max - min + 1) + min;
}

int generateNumberOfCrocodiles(const int &min, const int& max)
{
	srand(time(NULL));
	return rand() % (max - min + 1) + min;
}

vector<Crocodile> generateCrocodiles(const int &n, const int &jump, const bool &shuffle = true, const int &jumpAsymp = 40, const int &maxSize = 5)
{
	srand(time(NULL));
	int pos = 0;
	vector<Crocodile> c;
	for (int i = 0; i < n; ++i)
	{
		Crocodile tmp;
		tmp.begin = pos + (rand() % (jump - static_cast<int>(jump*jumpAsymp/100)) + 1);
		pos = tmp.begin;
		tmp.end = pos + (rand() % maxSize + 1);
		pos = tmp.end;
		c.push_back(tmp);
	}
	if (shuffle)
		random_shuffle(c.begin(), c.end());
	int i = 1;
	for (vector<Crocodile>::iterator it = c.begin(); it != c.end(); ++it)
		it->id = i++;
	return c;
}

int generateRiverWidth(vector<Crocodile> &c, const int &jump)
{
	int max = 0;
	for (vector<Crocodile>::iterator it = c.begin(); it != c.end(); ++it)
	if (it->end > max)
		max = it->end;
	return max + (rand() % (jump)+1);
}


int main()
{
	int jump = generateJump(5, 11); // zasiêg skoku surykatki
	int cNumber = generateNumberOfCrocodiles(100, 101); // liczba krokodyli;
	vector<Crocodile> crocodiles = generateCrocodiles(cNumber, jump,false); // lista krokodyli
	int riverWidth = generateRiverWidth(crocodiles, jump); // szerokoœæ rzeki

	int jumpSum = 0; // suma obecnych skokow surykatki

	Crocodile tmp;
	tmp.begin = 0;
	tmp.end = 0;
	tmp.id = -1;
	crocodiles.push_back(tmp); // sztuczny pocz¹tek
	tmp.begin = riverWidth;
	tmp.end = riverWidth;
	crocodiles.push_back(tmp); // sztuczny koniec

	/* ****************** wczytywanie z klawiatury *********************
	cin >> riverWidth;
	cin >> jump;	
	cin >> cNumber;	
	for (int i = 0; i < cNumber; ++i)
	{
	Crocodile c;
	cin >> c.begin >> c.end;
	c.id = i + 1;
	crocodiles.push_back(c);
	}
	*/
	
// ----------------------------------------------
// --------------- START ------------------------
// ----------------------------------------------
	clock_t start = clock();

	sort(crocodiles.begin(), crocodiles.end(), compCrocodile); // sorotwanie krokodyli wg odleg³oœci od lewego brzegu
	// lub Smoothsort, Heapsort, Block sort (stabilnoœæ nie jest wymagana) wydajne pamiêciowo

	/*
	for (vector<Crocodile>::iterator c = crocodiles.begin(); c != crocodiles.end(); ++c)
		cout << c->begin << " " << c->end << " id: " << c->id << endl;
	*/
	//cout << "\nskok: " << jump << "\n";

	//vector<Point> stones; // lista kamieni

	printf("Miedzyczas po sortowaniu: %lu ms\n", clock() - start);
	Point s1;
	vector<int> id;
	for (vector<Crocodile>::iterator c = crocodiles.begin(); c + 1 != crocodiles.end(); ++c)
	{
		Point s;
		s.d = (c + 1)->begin - c->end; // odleg³oœæ miêdzy krokodylami
		s.crocodileId = (c + 1)->id;
	//	cout << s.d << " ";
	//	stones.push_back(s); // dodaj kamienie
		
		if (jumpSum + s.d <= jump) // mo¿esz skoczyæ dalej
		{
			jumpSum += s.d;
		}
		else
		{
			id.push_back(s1.crocodileId);
			jumpSum = s.d;
		}
		s1 = s;
	}

	//printf("Miedzyczas: %lu ms\n", clock() - start);
	/*
	
	for (vector<Point>::iterator s = stones.begin(); s != stones.end(); ++s)
	{
		if (jumpSum + s->d <= jump) // mo¿esz skoczyæ dalej
		{
			jumpSum += s->d;
		}
		else
		{
			id.push_back((s - 1)->crocodileId); // skacz
			jumpSum = s->d;
		}

	}
	*/
// ----------------------------------------------
// --------------- KONIEC -----------------------
// ----------------------------------------------
	printf("Czas wykonywania: %lu ms, dla n = %d\n", clock() - start,cNumber);
	// poka¿ numery krokodyli po których nale¿y skoczyæ
	for (vector<int>::iterator it = id.begin(); it != id.end(); ++it)
		cout << *it << " ";
	getchar();
	system("pause");

	return 0;
}