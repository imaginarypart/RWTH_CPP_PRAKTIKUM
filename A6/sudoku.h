#include <vector>
#include <iostream>

using std::cin;
using std::cout;
using std::endl;
using std::istream;
using std::ostream;
using std::vector;

// ----------------------------------------------------------------------
// Klasse Sudoku

class Sudoku
{
  private:
    vector<int> Data;     // Attribute

    void check( int& idx) const; // Index pruefen, evtl. korrigieren und
                                 // Fehlermeldung ausgeben
  public:
    Sudoku()
    {
        Data.resize(81);  // mit Nullen belegt
    }

    // Impliziter Destruktor ausreichend, da keine dyn. Speicherverwaltung.
    // Gleiches gilt fuer impliziten Kopierkonstr. und Zuweisungsoperator.

    // Zugriffsoperatoren
    int& operator() (int r, int c)
    {
        check(r); check(c);
        return Data[ (r-1)*9 + (c-1)];
    }

    int operator() (int r, int c) const
    {
        check(r); check(c);
        return Data[ (r-1)*9 + (c-1)];
    }

    // Methoden, die die Gueltigkeit pruefen
    bool validRow( int r) const;
    bool validCol( int c) const;
    bool validSqr( int a, int b) const;
    bool valid() const;

    bool solved() const
    { return getNumEmpty()==0 && valid(); }

    // Anzahl der leeren Felder
    int getNumEmpty() const;
};

// Ein-/Ausgabeoperatoren
ostream& operator<< (ostream& out, const Sudoku& S);

istream& operator>> (istream& in, Sudoku& S);


// ----------------------------------------------------------------------
// Klasse PossibleDigits fuer Hilfszahlen:
// welche Ziffern sind moeglich (true) bzw. nicht (false)?


class PossibleDigits
{
  private:
    vector<bool> possible;    // 9 bool-Eintraege

  public:
    // Konstruktor mit Initialisierungswert fuer alle 9 Ziffern
    PossibleDigits( bool all_possible= true);

    // Anzahl der moeglichen Ziffern
    int numPossible() const;

    // Praedikat: Ist die Ziffer moeglich?
    bool isPossible( int digit) const;

    // Setze die Ziffer als moeglich
    void enable ( int digit);
    // Setze die Ziffer als nicht moeglich
    void disable( int digit);

    // Friend
    friend PossibleDigits operator&&( const PossibleDigits& a, const PossibleDigits& b);
};

ostream& operator<<( ostream& out, const PossibleDigits& a);

// a && b berechnet die Schnittmenge der Hilfszahlen a und b
PossibleDigits operator&&( const PossibleDigits& a, const PossibleDigits& b);


// ----------------------------------------------------------------------
// Klasse SudokuSolver

class SudokuSolver
{
  private:
    vector<PossibleDigits> pd_row, pd_col, pd_sqr; // jeweils 9 Eintraege
    Sudoku&                sudo;

    static int getSqr( int r, int c) { return 3*((r-1)/3) + (c-1)/3 + 1; }

  public:
    SudokuSolver( Sudoku& S);

    // trage Ziffer in Eintrag (r,c) ein und passe Hilfszahlen an
    void setDigit  ( int r, int c, int digit);
    // entferne Ziffer in Eintrag (r,c) und passe Hilfszahlen an
    void unsetDigit( int r, int c);

    // Hilfszahlen zum Eintrag (r,c)
    PossibleDigits getPossible( int r, int c) const;

    // gibt Eintrag (r_min,c_min) mit moeglichst wenigen Hilfszahlen zurueck
    void getNextCell( int& r_min, int& c_min) const;

    bool solve( int num_empty);
};
