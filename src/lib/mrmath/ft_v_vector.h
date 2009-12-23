// ------------------------------------------------------------------------
// Proces:		-
// Plik:			mathtr.h
// System:	QNX/MRROC++  v. 6.3
// Opis:		Klasy K_vector, Homog_matrix, Ft_v_vector,  Jacobian_matrix
//				- definicja klas
//
// Autor:		tkornuta
// Data:		14.02.2007
// ------------------------------------------------------------------------


#ifndef __FT_V_VECTOR_H
#define __FT_V_VECTOR_H

#include <iostream>
#include <math.h>
#include <string.h>

#include "lib/impconst.h"	// frame_tab

namespace mrrocpp {
namespace lib {



// klasa reprezentujaca wektor sila-moment i wektora predkosci
class Ft_v_vector
{
protected:
	double w[6];
public:
	friend class Ft_v_tr;						// klasa Ft_v_tr musi miec dostep do prywatnych


	Ft_v_vector();													// konstruktor domniemany [0, 0, 0, 0, 0, 0]
	Ft_v_vector(const double t[6]);										// utworzenie wektora na podstawie podanej tablicy
	Ft_v_vector(double fx, double fy, double fz, double tx, double ty, double tz);


	Ft_v_vector(const Ft_v_vector &);								// konstruktor kopiujacy

	void set_values(const double t[6]);										// wypelnienie wektora na podstawie podanej tablicy
	void set_values(double fx, double fy, double fz, double tx, double ty, double tz);

	// Ustawienie elementu wektora.
	void set_value(int i, const double value);
	// Zwrocenie elementu wektora.
	void get_value(int i, double &value) const;
	// Zwrocenie elementu wektora.
	double get_value(int i) const;

	// Wyspisanie na ekran wektora
	void wypisz_wartosc_na_konsole() const;

	// in theory, the RHS operator
    double operator[](const int i) const;
      // in theory, the LHS operator
    double& operator[](const int i);

	void operator+=(const Ft_v_vector &);

	void to_table(double tablica[6]) const;					// przepisanie wektora do tablicy podanej jako argument

	friend std::ostream& operator<<(std::ostream & s, Ft_v_vector & w);		// operator wypisania

	//Sibi
	//Wyciagniecie max elementu z wektora
	double max_element ();	//wyciagniecie maksymalnego elementu wektora


	// Odwracanie macierzy.
	Ft_v_vector operator!() const;
	Ft_v_vector operator-() const;
	Ft_v_vector & operator=(const Ft_v_vector &);			// operator przypisania
	Ft_v_vector operator+(const Ft_v_vector &) const;
	Ft_v_vector operator-(const Ft_v_vector &) const;
	Ft_v_vector operator*(double) const;					// skalowanie wektora

};// end class Ft_v_vector



// klasa reprezentujaca wektor sila-moment i wektora predkosci
class Ft_vector : public Ft_v_vector
{

public:
	friend class Ft_tr;

												// skladnikow klasy Ft_v_vector

	Ft_vector();													// konstruktor domniemany [0, 0, 0, 0, 0, 0]
	Ft_vector(const double t[6]);										// utworzenie wektora na podstawie podanej tablicy
	Ft_vector(double fx, double fy, double fz, double tx, double ty, double tz);

	Ft_vector(const Ft_vector &);								// konstruktor kopiujacy

	// Odwracanie macierzy.
	Ft_vector operator!() const;
	Ft_vector operator-() const;
	Ft_vector & operator=(const Ft_vector &);			// operator przypisania
	Ft_vector operator+(const Ft_vector &) const;
	Ft_vector operator-(const Ft_vector &) const;
	Ft_vector operator*(double) const;					// skalowanie wektora
};// end class Ft_vector


// klasa reprezentujaca wektor sila-moment i wektora predkosci
class V_vector : public Ft_v_vector
{

public:

	friend class V_tr;
												// skladnikow klasy Ft_v_vector
     friend class Jacobian_matrix;			//Klasa Jacobian_matrix ma miec dostep do skladowych - Sibi

											// skladnikow klasy Ft_v_vector

	V_vector();													// konstruktor domniemany [0, 0, 0, 0, 0, 0]
	V_vector(const double t[6]);										// utworzenie wektora na podstawie podanej tablicy
	V_vector(double fx, double fy, double fz, double tx, double ty, double tz);

	V_vector(const V_vector &);								// konstruktor kopiujacy

	// Odwracanie macierzy.
	V_vector operator!() const;
	V_vector operator-() const;
	V_vector & operator=(const V_vector &);			// operator przypisania
	V_vector operator+(const V_vector &) const;
	V_vector operator-(const V_vector &) const;
	V_vector operator*(double) const;					// skalowanie wektora

	//Sibi
	 //Wektor predkosci jako odleglosc dwuch pozycji zadanych w postaci ramek
	void position_distance(frame_tab* local_current_end_effector_frame, frame_tab* local_desired_end_effector_frame);

};// end class Ft_vector







} // namespace lib
} // namespace mrrocpp

#endif
