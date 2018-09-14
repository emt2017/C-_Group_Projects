#ifndef ORDERED_POLYNOMIAL_H
#define ORDERED_POLYNOMIAL_H

#include "Polynomial.h"

template<typename ItemType>
class OrderedPoly{

private:
	//polynomial to use
	Polynomial <ItemType> Poly;

public:
	typedef typename Polynomial<ItemType>::const_piterator const_piterator;
	typedef typename Polynomial<ItemType>::piterator piterator;
	//*ordering functions*//
	//function~find position based on exponent value, then insert
	OrderedPoly<ItemType>() {}
	/*
	OrderedPoly<ItemType>(const OrderedPoly<ItemType>& other) {
	Poly = other.Poly;
	}
	*/
	

	void insert(const ItemType& coefficientIN, const ItemType& exponentIN){
		if (coefficientIN == 0)
			return;
		typename Polynomial<ItemType>::piterator itr = Poly.begin();
		while ((itr != Poly.end()) && (*itr > exponentIN)) {
			++itr;
		}
		Poly.insert(itr, coefficientIN, exponentIN);
	}
	//function~remove specific exponent
	void remove(const ItemType & exponentIN){
		return Poly.remove(exponentIN);
	}
	//function~ const iterator to leading Term
	const_piterator begin() const{
		return Poly.begin();
	}
	//function~ const iterator to lowest Term
	const_piterator end() const{
		return Poly.end();
	}

	//function~return lead degree
	const ItemType& getLeadDegree() const{
		return Poly.getLeadDegree();
	}

	const size_t size() {
		return Poly.size();
	}

	void emptyPoly() {
		Poly.emptyPoly();
	}

	/*
	OrderedPoly<ItemType>& operator=(const OrderedPoly<ItemType>& other) {
	Poly = other.Poly;
	return *this;
	}
	*/
	

};//end of OrderedPoly class
#endif
