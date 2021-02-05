/*
 * RWTH-CPP-Praktikum
 * Abgabe 6
 */

#include "sudoku.h"
#include <fstream>


/* Definitionen */
int main () {

	std::ifstream ifs("Sudoku1.txt");
	Sudoku S;
	ifs >> S;
	ifs.close();

	while (		S.valid()
		and	S.getNumEmpty() != 0 ) {

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
		std::cout << "Schade! Das Sudoku ist leider nicht gültig. Machen Sie sich nichtfertig und versuchen Sie es einfach erneut.
		Tipp: Versuchen Sie das Sudoku erst auf Papier zu lösen, und übertragen Sie es erst dann.";
	}
	return 0;
}
