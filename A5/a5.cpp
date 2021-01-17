/* 
 * RWTH-C++-Praktikum
 * Abgabe 5
 */

#include <map>
#include <iostream>
#include <vector>
#include <ostream>
#include <istream>
#include <fstream>

#define SUDOKU_SQR_LENGTH 3
#define SUDOKU_ROW_LENGTH 9
#define SUDOKU_SIZE 81 /* 81 = 9*9 */

/* typedefs */


/* Deklarationen */
class Sudoku {
		
	/* Data speichert für jedes Feld des Sudoku einen int */
	std::vector<int> Data;

	public:
	/* Default-Konstruktor */
	Sudoku();
	
	/* Lese- und Schreiboperator */
	int& operator() (int r, int c);

	/* Leseoperator */
	int operator() (int r, int c) const;

	/* Ist die Zeile r gültig? */
	bool validRow (int r) const;

	/* Ist die Spalte r gültig? */
	bool validCol (int r) const;

	/* Ist das Quadrat (a,b) gültig? */
	bool validSqr ( int a, int b) const;

	/* Ist alles gültig */
	bool valid() const;
	
	/* Anzahl leerer Felder */
	int numEmpty () const {
		int num = 0;
		for ( int i=0; i<SUDOKU_SIZE; ++i ) { if (Data[i] == 0) ++num; }
		return num;
	}

	/* Sudoku gelöst? */
	bool solved() const {
		if ( numEmpty() == 0 and valid() ) return true;
		return false;
	}

	/* 
	 * Der implizit vorhandene Destruktor reicht aus, da hier keine dynamischen Variablen
	 * freigegeben werden müssen.
	 */
};

/* Sudoku an out senden */
std::ostream& operator<< (std::ostream& out, const Sudoku& S);

/* Sudoku von in einlesen */
std::istream& operator>> (std::istream& in, Sudoku& S);


/* Definitionen */
int main () {
	
	std::ifstream ifs("Sudoku1.txt");
	Sudoku S;
	ifs >> S;
	ifs.close();

	while (		S.valid()
		and	S.numEmpty() != 0 ) {
		
		std::cout 	<< S
				<< "Wählen Sie den Index aus, den Sie bearbeiten wollen.\n"
				<< "Format: (i,j).\n"
				<< "i: ";

		int i;
		std::cin >> i;

		std::cout	<< "j: ";
		int j;
		std::cin >> j;

		std::cout 	<< "Der Eintrag ("
				<< i << ", " << j
				<< ") besitzt aktuell den Wert "
				<< S(i,j) << ". "
				<< "Geben Sie den neuen Wert an, den der Index annehmen soll."
				<< std::endl << "Neuer Wert: ";
		
		int neu;
		std::cin >> neu;

		S(i,j)=neu;
	}

	if (S.valid()) {
		std::cout << "Herzlichen Glückwunsch! Sie sind ein wunderbarer Mensch!";
	} else {
		std::cout << "Schade! Das Sudoku ist leider nicht gültig. Machen Sie sich nichtfertig und versuchen Sie es einfach erneut. Tipp: Versuchen Sie das Sudoku erst auf Papier zu lösen, und übertragen Sie es erst dann.";
	}
	return 0;
}

/* Default-Konstruktor */
Sudoku::Sudoku () {
	Data.resize(SUDOKU_SIZE);
}

/* Lese-/Schreiboperator */
int& Sudoku::operator() (int r, int c) {
	
	/* Existiert der angeforderte Index? */
	if ( 
		   r < 1 or r > SUDOKU_ROW_LENGTH
		or c < 1 or c > SUDOKU_ROW_LENGTH 
	   ) {
		std::cerr << "FEHLER: Es wurde ein falscher Index gewählt.\n";
		return Data[0];
	}

	int index = (r-1)*SUDOKU_ROW_LENGTH + (c-1);
	return Data[index]; 
}

/* Leseoperator */
int Sudoku::operator() (int r, int c) const {
	
	/* Existiert der angeforderte Index? */
	if ( 
		   r < 1 or r > SUDOKU_ROW_LENGTH
		or c < 1 or c > SUDOKU_ROW_LENGTH 
	   ) {
		std::cerr << "FEHLER: Es wurde ein falscher Index gewählt.\n";
		return Data[0];
	}

	int index = (r-1)*SUDOKU_ROW_LENGTH + (c-1);
	return Data[index]; 
}

/* Gibt ein Sudoku an out aus und gibt out zurück */
std::ostream& operator<< (std::ostream& out, const Sudoku& S) {
	for (int i=1; i <= SUDOKU_ROW_LENGTH; ++i) {
		for (int j=1; j <= SUDOKU_ROW_LENGTH; ++j) {
			out << S(i,j);
			if ( j != SUDOKU_ROW_LENGTH ) out << " ";
		}
		out << std::endl;
	}
	return out;
}

/* Sudoku von in einlesen */
std::istream& operator>> (std::istream& in, Sudoku& S) {
	for ( int i=1; i <= SUDOKU_ROW_LENGTH; ++i ) {
		for ( int j=1; j <= SUDOKU_ROW_LENGTH; ++j ) {
			in >> S(i,j);
		}
	}
	return in;
}

/* Zeile r gültig? */
bool Sudoku::validRow (int r) const {
	/* Vorkommen der Zahlen in einer Map speichern: n |-> Anzahl(n) */
	std::map<int, int> Anzahl;

	/* Zahlen mit 0 initialisieren */

	for (int i=1; i<=SUDOKU_ROW_LENGTH; ++i) {
		Anzahl[i] = 0;
	}
	
	for (int i=1; i<=SUDOKU_ROW_LENGTH; ++i) {
		if (operator() (r,i) != 0 ) {
			if ( Anzahl[operator() (r,i)]==1 ) return false;
			++Anzahl[operator() (r,i)];
		}
	}

	return true;
}

/* Spalte r gültig? */
bool Sudoku::validCol (int r) const {
	/* Vorkommen der Zahlen in einer Map speichern: n |-> Anzahl(n) */
	std::map<int, int> Anzahl;

	/* Zahlen mit 0 initialisieren */

	for (int i=1; i<=SUDOKU_ROW_LENGTH; ++i) {
		Anzahl[i] = 0;
	}
	
	for (int i=1; i<=SUDOKU_ROW_LENGTH; ++i) {
		if (operator() (i,r) != 0 ) {
			if ( Anzahl[operator() (i,r)]==1 ) return false;
			++Anzahl[operator() (i,r)];
		}
	}

	return true;
}

/* Quadrat (a,b) gültig? */
bool Sudoku::validSqr (int a, int b) const {
	int r = SUDOKU_SQR_LENGTH*(a-1) +1;
	int c = SUDOKU_SQR_LENGTH*(b-1) +1;
	
	std::map<int, int> Anzahl;

	for (int i=1; i<=SUDOKU_ROW_LENGTH; ++i) {
		Anzahl[i]=0;
	}

	for (int i=1; i<=SUDOKU_SQR_LENGTH; ++i) { /* Zeile */
		for (int j=1; j<=SUDOKU_SQR_LENGTH; ++j) { /* Spalte */
			if (operator() (i,j) != 0 ) {
				if (Anzahl[operator() (i,j)] ==1 ) return false;
				++Anzahl[operator() (i,j)];
			}
		}
	}

	return true;
}


/* Ist alles gültig? */
bool Sudoku::valid () const {

	/* alle Zeilen durchgehen */
	for (int i=1; i<=SUDOKU_ROW_LENGTH; ++i) if (!validRow(i)) return false; 
	
	/* alle Spalten durchgehen */
	for (int i=1; i<=SUDOKU_ROW_LENGTH; ++i) if (!validCol(i)) return false;

	/* alle Quadrate durchgehen */
	for (int i=1; i<=SUDOKU_SQR_LENGTH; ++i) {
		for (int j=1; j<=SUDOKU_SQR_LENGTH; ++j) {
			if (!validSqr(i,j)) return false;
		}
	}
	
	/* alles richtig? */
	return true;
}
