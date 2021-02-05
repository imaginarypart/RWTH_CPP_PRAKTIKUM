#include "sudoku.h"
#include <vector>
// ----------------------------------------------------------------------
// Klasse Sudoku


// Ein-/Ausgabeoperatoren
ostream& operator<< (ostream& out, const Sudoku& S) {
    for (int r=1; r<=9; ++r) {
        for (int c=1; c<=9; ++c) {
            const int z= S(r,c);
            if (z==0)
                out << ". ";
            else
                out << z << ' ';
        }
        out << '\n';
    }
    return out;
}

istream& operator>> (istream& in, Sudoku& S) {
    for (int r=1; r<=9; ++r)
        for (int c=1; c<=9; ++c)
            in >> S(r,c);
    return in;
}

// Sudoku-Methoden

void Sudoku::check( int& idx) const {
    if (idx < 1) {
        cout << "Index " << idx << " ist ungueltig." << endl;
        idx= 1;
    }
    if (idx > 9) {
        cout << "Index " << idx << " ist ungueltig." << endl;
        idx= 9;
    }
}

int Sudoku::getNumEmpty() const {
    int num_empty= 0;
    for (int i=0; i<81; ++i)
        if (Data[i]==0)
            ++num_empty;
    return num_empty;
}

bool Sudoku::validRow( int r) const {
    int haeufigkeit[10]= {}; // mit Nullen initialisiert

    for (int c=1; c<=9; ++c) {
        int z= (*this)(r,c);
        if (z != 0) {
            haeufigkeit[z]++;
            if (haeufigkeit[z] > 1) // z kommt mehr als einmal vor
                return false;
        }
    }
    return true;
}

bool Sudoku::validCol( int c) const {
    int haeufigkeit[10]= {}; // mit Nullen initialisiert

    for (int r=1; r<=9; ++r) {
        int z= (*this)(r,c);
        if (z != 0) {
            haeufigkeit[z]++;
            if (haeufigkeit[z] > 1)
                return false;
        }
    }
    return true;
}

bool Sudoku::validSqr( int a, int b) const {
    int haeufigkeit[10]= {}; // mit Nullen initialisiert
    // Eintrag oben links ist (r,c)
    const int r= 3*(a-1)+1, c= 3*(b-1)+1;

    for (int i=0; i<3; ++i) {
      for (int j=0; j<3; ++j) {
        int z= (*this)(r+i,c+j);
        if (z != 0) {
            haeufigkeit[z]++;
            if (haeufigkeit[z] > 1)
                return false;
        }
      }
    }
    return true;
}

bool Sudoku::valid() const {
    bool val= true;

    for (int i=1; i<=9; ++i) {
        val= val && validRow(i)
                 && validCol(i);
    }
    for (int i=1; i<=3; ++i)
        for (int j=1; j<=3; ++j)
            val= val && validSqr( i, j);

    return val;
}


// ----------------------------------------------------------------------
// Klasse PossibleDigits fuer die Hilfszahlen
PossibleDigits::PossibleDigits(bool all_possible = false) {
	possible.resize(9);
	if (all_possible)
		for (int i = 0; i<possible.size(); ++i) possible[i] = all_possible;
}

int PossibleDigits::numPossible() const {
    int num = 0;
    for ( bool digit : possible ) if (digit) num++;
    return num;
}

bool PossibleDigits::isPossible(int digit) const {
    return possible[digit-1];
}

void PossibleDigits::enable (int digit) {
    possible[digit-1] = true;
}

void PossibleDigits::disable (int digit) {
    possible[digit-1] = false;
}

ostream& operator<<( ostream& out, const PossibleDigits& a) {
    for ( int i=1; i<=9; ++i) {
        if (a.isPossible(i)) out << i << "\n";
    }
    return out;
}

PossibleDigits operator&&( const PossibleDigits& a, const PossibleDigits& b ) {

    PossibleDigits cap(false);

    for ( int i=1; i<=9; ++i )
        if( a.isPossible(i) && b.isPossible(i) ) cap.enable(i);

    return cap;
}


// ----------------------------------------------------------------------
// Klasse SudokuSolver
/*
SudokuSolver::SudokuSolver ( Sudoku& S) {
    pd_row.resize(9);
    pd_col.resize(9);
    pd_sqr.resize(9);
    sudo = S;


    for ( int i=1; i <= 9; ++i )     }
}

*/
