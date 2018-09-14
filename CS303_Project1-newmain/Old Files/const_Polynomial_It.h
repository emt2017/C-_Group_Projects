#ifndef CONST_POLYNOMIAL_ITERATOR_H
#define CONST_POLYNOMIAL_ITERATOR_H


class const_piterator{
	friend class Polynomial<ItemType>;
	//for read only operations
private:
	//reference to parent
	const Polynomial<ItemType>* parent;
	//pointer to selected term
	typename Polynomial<ItemType>::Term* current;

	//Constructor
	const_piterator(const Polynomial<ItemType>* itParent, Term* position):
		parent(itParent), current(position){}

public:
	//function~returns coefficient of selected term if valid
	const ItemType getCo() const{
		if (current==NULL)
			throw std::invalid_argument("end() has no Coefficient");
		return current->coefficient;
	}
	//function~returns reference to coefficient of selected term if valid
	const ItemType getCoRef()const{
		if (current == NULL)
			throw std::invalid_argument("end() has no Coefficient");
		return &(current->coefficient);
	}
	//operator~returns exponent of selected term if valid
	const ItemType& operator*() const{
		if (current==NULL)
			throw std::invalid_argument("Cannot dereference end()");
		return current->exponent;
	}
	//operator~returns reference to exponent in selected term if valid
	const ItemType* operator->() const{
		if (current==NULL)
			throw std::invalid_argument("Cannot dereference end()");
		return &(current->exponent);
	}
	//operator~advance iterator
	const_piterator& operator++(){
		if (current == NULL)
			throw std::invalid_argument("Cannot advance past end()");
		current = current->next;
		return *this;
	}
	//operator~retreat iterator
	const_piterator& operator--(){
		if (current==parent->leadingTerm)
			throw std::invalid_argument("Cannot retreat before begin()");
		if (current==NULL)
			current = parent->lowestTerm;
		else
			current = current->prev;
		return *this;
	}
	//operator~return value, then advance iterator
	const_piterator operator++(int){
		const_piterator originalValue = *this;
		++(*this);
		return originalValue;
	}
	//operator~return value, then retreat iterator
	const_piterator operator--(int){
		const_piterator originalValue = *this;
		--(*this);
		return originalValue;
	}
	//operator~equality
	bool operator ==(const const_piterator&other){
		return current ==other.current;
	}
	//operator~inequality
	bool operator != (const const_piterator&other){
		return current !=other.current;
	}
	
	};//end of const iterator class

#endif // !CONST_POLYNOMIAL_ITERATOR_H
