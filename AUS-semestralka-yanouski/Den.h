#pragma once

#include "structures\heap_monitor.h"
#include <iostream>
using namespace std;

class Den {
	int den;
	int mesiac;
	int rok;
public:
	Den();
	Den(const Den&);
	Den(int, int, int);
	~Den();
	int getDen() const;
	int getMesiac() const;
	int getRok() const;
	void setDen(int);
	void setMesiac(int);
	void setRok(int);
	void next();
	void operator=(const Den&);
	friend bool operator==(Den, Den);
	friend bool operator>(Den, Den);
	friend bool operator<(Den, Den);
	friend bool operator>=(Den, Den);
	friend bool operator<=(Den, Den);
	friend int operator-(Den, Den);
	friend bool operator!=(Den, Den);
	friend ostream& operator<<(ostream&, const Den&);
};

inline bool operator!=(Den l, Den r) {
	return !(l == r);
}

inline int operator-(Den l, Den r) {
	if (l == r) return 0;
	int result = 0;
	if (l > r) {
		while (l != r) {
			r.next();
			result++;
		}
	}else{
		while (l != r) {
			l.next();
			result--;
		}	
	}
	return result;
}

inline bool operator>=(Den prvy, Den druhy) {
	return prvy > druhy || prvy == druhy;
}

inline bool operator<=(Den prvy, Den druhy) {
	return prvy < druhy || prvy == druhy;
}

inline bool operator==(Den prvy, Den druhy) {
	return prvy.den == druhy.den && prvy.mesiac == druhy.mesiac && prvy.rok == druhy.rok;
}
inline bool operator>(Den prvy, Den druhy) {
	if (prvy.rok > druhy.rok) {
		return true;
	}
	if (prvy.mesiac > druhy.mesiac) {
		return true;
	}
	if (prvy.den > druhy.den) {
		return true;
	}
	return false;
}
inline bool operator<(Den prvy, Den druhy) {
	return !(prvy > druhy);
}

inline ostream& operator<<(ostream& out, const Den& den) {
	return out << den.den << "." << den.mesiac << "." << den.rok;
}