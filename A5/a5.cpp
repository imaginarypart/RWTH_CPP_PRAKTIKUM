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
ostream& operator<< (ostream& out, const Sudoku& S);

int main () {
	
	return 0;
}

Sudoku::Sudoku () {
	Data.resize(SUDOKU_SIZE);
}

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

ostream& operator<< (ostream& out, const Sudoku& S) {
	/* TO DO */
	return out;
}
