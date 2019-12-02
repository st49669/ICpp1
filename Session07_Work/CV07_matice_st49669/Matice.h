#ifndef MATICE_H_
#define MATICE_H_

#include <stdexcept>

template<typename T>
class Matice {
private:
	T **prvek;
	int radky, sloupce;

public:
	Matice(int radky, int sloupce);
	Matice(const Matice<T>& m);
	~Matice();
	
	void Nastav(int radek, int sloupec, T hodnota);
	void NastavZ(T* pole);
	T& Dej(int radek, int sloupec);
	const T& Dej(int radek, int sloupec) const;

	Matice Transpozice() const;
	Matice Soucin(const Matice& m) const;
	Matice Soucin(T skalar) const;
	Matice Soucet(const Matice& m) const;
	Matice Soucet(T skalar) const;

	bool JeShodna(const Matice& m) const;
	void Vypis() const;

	template<typename U>  //rozdilna sablona pro moznost predani jineho typu k pretypovani
	Matice<U> Pretypuj();
};

template<typename T>
Matice<T>::Matice(int radky, int sloupce) {
	this->radky = radky;
	this->sloupce = sloupce;
	prvek = new T*[radky];
	for (int i = 0; i < radky; i++)
	{
		prvek[i] = new T[sloupce];
		for (int j = 0; j < sloupce; j++) {
			prvek[i][j] = 0;
		}
	}
}

template<typename T>
Matice<T>::~Matice() {
	for (int i = 0; i < radky; ++i) {
		delete[] prvek[i];
	}
	delete[] prvek;
}

template<typename T>
Matice<T>::Matice(const Matice<T>& m) {
	prvek = new T*[m.radky];
	radky = m.radky;
	sloupce = m.sloupce;
	for (int i = 0; i < m.radky; i++) {
		prvek[i] = new T[m.sloupce];
		for (int j = 0; j < m.sloupce; j++) {
			prvek[i][j] = m.Dej(i, j);
		}
	}
}

template<typename T>
template<typename U>
Matice<U> Matice<T>::Pretypuj() {
	Matice<U> nova = Matice<U>{ radky, sloupce };
	for (int i = 0; i < radky; i++) {
		for (int j = 0; j < sloupce; j++) {
			nova.Nastav(i, j, (U)prvek[i][j]);
		}
	}
	return nova;
}

template<typename T>
void Matice<T>::Nastav(int radek, int sloupec, T hodnota){
	if (radek < 0 || sloupec < 0 || radek >= radky || sloupec >= sloupce) {
		throw new std::out_of_range("Zadaný index je pro tuto matici neplatný.");
	}
	prvek[radek][sloupec] = hodnota;
}

template<typename T>
void Matice<T>::NastavZ(T* pole) {
	int poz = 0;
	for (int i = 0; i < radky; i++)
	{
		for (int j = 0; j < sloupce; j++) {
			prvek[i][j] = pole[poz];
			++poz;
		}
	}
}

template<typename T>
T& Matice<T>::Dej(int radek, int sloupec) {
	if (radek < 0 || sloupec < 0 || radek >= radky || sloupec >= sloupce) {
		throw new std::out_of_range("Prvek v matici na tomto indexu neexistuje.");
	}
	return prvek[radek][sloupec];
}


template<typename T>
const T& Matice<T>::Dej(int radek, int sloupec) const {
	if (radek < 0 || sloupec < 0 || radek >= radky || sloupec >= sloupce) {
		throw new std::out_of_range("Prvek v matici na tomto indexu neexistuje.");
	}
	return prvek[radek][sloupec];
}

template<typename T>
Matice<T> Matice<T>::Transpozice() const {
	Matice<T> nova = Matice{ sloupce, radky };
	for (int i = 0; i < sloupce; i++)
	{
		for (int j = 0; j < radky; j++) {
			nova.prvek[i][j] = prvek[j][i];
		}
	}
	return nova;
}

template<typename T>
Matice<T> Matice<T>::Soucin(const Matice& m) const {
	if (sloupce != m.radky) {
		throw std::invalid_argument("Tyto matice spolu nelze násobit.");
	}
	Matice<T> nova = Matice{ radky, m.radky };
	for (int i = 0; i < radky; i++){
		for (int j = 0; j < sloupce; j++) {
			nova.Nastav(i, j, 0);
			for (int k = 0; k < sloupce; k++){
				nova.Nastav(i, j, nova.Dej(i,j) + (prvek[i][k] * m.prvek[k][j]));
			}
		}
	}
	return nova;
}

template<typename T>
Matice<T> Matice<T>::Soucin(T skalar) const {
	Matice<T> nova = Matice{ radky, sloupce };
	for (int i = 0; i < radky; i++) {
		for (int j = 0; j < sloupce; j++) {
			nova.Nastav(i, j, prvek[i][j] * skalar);
		}
	}
	return nova;
}

template<typename T>
Matice<T> Matice<T>::Soucet(const Matice& m) const {
	if (radky != m.radky || sloupce != m.sloupce) {
		throw std::invalid_argument("Tyto dvì matice nelze sèítat.");
	}
	Matice<T> nova = Matice{ radky, sloupce };
	for (int i = 0; i < radky; i++) {
		for (int j = 0; j < sloupce; j++) {
			nova.Nastav(i, j, prvek[i][j] + m.prvek[i][j]);
		}
	}
	return nova;
}

template<typename T>
Matice<T> Matice<T>::Soucet(T skalar) const {
	Matice<T> nova = Matice{ radky, sloupce };
	for (int i = 0; i < radky; i++) {
		for (int j = 0; j < sloupce; j++) {
			nova.Nastav(i, j, prvek[i][j] + skalar);
		}
	}
	return nova;
}

template<typename T>
bool Matice<T>::JeShodna(const Matice& m) const {
	if (radky == m.radky && sloupce == m.sloupce) {
		for (int i = 0; i < radky; i++) {
			for (int j = 0; j < sloupce; j++) {
				if (prvek[i][j] != m.prvek[i][j]) return false;
			}
		}
		return true;
	}
	return false;
}

template<typename T>
void Matice<T>::Vypis() const {
	for (int i = 0; i < radky; i++) {
		for (int j = 0; j < sloupce; j++) {
			std::cout << "\t" << prvek[i][j];
		}
		std::cout << std::endl;
	}
}



#endif
