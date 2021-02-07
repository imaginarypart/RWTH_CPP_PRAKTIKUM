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
PossibleDigits::PossibleDigits(bool all_possible)
    :   possible(9,false)   {
	if (all_possible)
		for (int i=0; i<9; ++i) possible[i] = all_possible;
}

int PossibleDigits::numPossible() const {
    int num = 0;
    for ( int i = 0; i < 9; ++i ) {
        if (possible[i]) num+=1;

    }
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

    for ( int i=0; i<9; ++i )
        cap.possible[i]=a.possible[i] && b.possible[i];

    return cap;
}


// ----------------------------------------------------------------------
// Klasse SudokuSolver
SudokuSolver::SudokuSolver ( Sudoku& S)
    :   pd_row(9),
        pd_col(9),
        pd_sqr(9),
        sudo{S}
    {
        //Zeilen initialisieren
        for (int r=1; r<=9; ++r) {
            for (int c=1; c<=9; ++c) {
                std::cout << "(r,c) = " <<"(" << r << ", " << c<< ")" << '\n';
                std::cout << sudo(r,c) << '\n';
                if (sudo(r,c) != 0)
                    pd_row[r-1].disable(sudo(r,c));
            }
        }

        //Spalten initialisieren
        for (int c=1; c<=9; ++c) {
            for (int r=1; r<=9; ++r) {
                std::cout << "(r,c) = " <<"(" << r << ", " << c<< ")" << '\n';
                if (sudo(r,c) != 0)
                    pd_col[c-1].disable(sudo(r,c));
            }
        }

        //Quadrate initialisieren
        for (int r=1; r<=9; ++r) {
            for (int c=1; c<=9; ++c) {
                std::cout << "(r,c) = " <<"(" << r << ", " << c<< ")" << '\n';
                if (sudo(r,c) != 0)
                    pd_sqr[getSqr(r,c)-1].disable(sudo(r,c));
            }
        }
    }

void SudokuSolver::setDigit (int r, int c, int digit) {
    sudo(r,c) = digit;
    pd_row[r-1].disable(digit);
    pd_col[c-1].disable(digit);
    pd_sqr[getSqr(r,c)-1].disable(digit);
}

void SudokuSolver::unsetDigit (int r, int c) {
    int digit = sudo(r,c);
    pd_row[r-1].enable(digit);
    pd_col[c-1].enable(digit);
    pd_sqr[getSqr(r,c)-1].enable(digit);
    sudo(r,c) = 0;
}

PossibleDigits SudokuSolver::getPossible(int r, int c) const {
    PossibleDigits DigList(false);
    if (sudo(r,c) == 0)
        DigList = pd_row[r-1] && pd_col[c-1] && pd_sqr[getSqr(r,c)-1];
    return DigList;
}

void SudokuSolver::getNextCell (int& r_min, int& c_min) const {
    r_min= 1;
    c_min=1;
    int rcval;
    int current_min;
    for (int r = 1; r<=9; ++r ) {
        for (int c = 1; c <= 9; ++c ) {
            rcval = getPossible(r,c).numPossible();
            current_min = getPossible(r_min,c_min).numPossible();
            if (rcval == 0) continue;
            if ( rcval < current_min || current_min == 0) {
                r_min = r;
                c_min = c;
            }
        }
    }
}

bool SudokuSolver::solve(int num_empty)  {
    //Abbruchbedingung
    std::cout << "num_empty = " << num_empty << '\n';
    if (num_empty == 0) return sudo.valid();
    //Wähle Feld mit min an freien Hilfszahlen
    int r=1;
    int c=1;
    getNextCell(r,c);
    //std::cout << "(r,c) = (" << r << ", " << c << ")" << '\n';

    PossibleDigits tocheck = getPossible(r,c);
    //&std::cout << tocheck << '\n';
    //std::cout << "tocheck passed!" << '\n';
    for (int i = 1; i<=9; ++i) {
        if (tocheck.isPossible(i)) {
            //std::cout << "i = " << i << '\n';
            setDigit(r,c,i);
            //std::cout << "setDigit = " << i << '\n';
            if (solve(num_empty - 1)) return true;
            unsetDigit(r,c);
            //std::cout << "unsetDigit = (" << r << ", " << c << ")" << '\n';
        }
    }
    return false;
}
