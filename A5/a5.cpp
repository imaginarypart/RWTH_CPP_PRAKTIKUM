/* 
 * RWTH-C++-Praktikum
 * Abgabe 5
 */

#include <iostream>
#include <vector>
#include <ostream>
#include <istream>

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

	/* 
	 * Der implizit vorhandene Destruktor reicht aus, da hier keine dynamischen Variablen
	 * freigegeben werden müssen.
	 */
};

/* Sudoku an out senden */
std::ostream& operator<< (std::ostream& out, const Sudoku& S);

/* Sudoku von in einlesen */
std::istream& operator>> (std::istream& in, Sudoku& S);

int main () {
	
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

