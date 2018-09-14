#ifndef POLYNOMIAL_ITERATOR_H
#define POLYNOMIAL_ITERATOR_H


class piterator{
	//Parent Class Access
	friend class Polynomial<ItemType>;

private:
	//reference to parent
	Polynomial<ItemType>* parent;
	//pointer to selected term
	typename Polynomial<ItemType>::Term* current;

	//iterator constructor
	piterator(Polynomial<ItemType>* itParent, Term* position) :
		parent(itParent), current(position) {}

public:
	//operator~returns coefficient of selected term if valid
	ItemType getCo() const {
		if (current == NULL)
			throw std::invalid_argument("Cannot dereference end()");
		return current->coefficient;
	}

	//operator~enforce reference to coefficient of selected Term if valid
	ItemType getCoRef(){
		if (current == NULL)
			throw std::invalid_argument("Cannot dereference end()");
		return &(current->coefficient)
	}

	//operator~returns exponent of selected Term if valid
	ItemType& operator*() const {
		if (current == NULL)
			throw std::invalid_argument("Cannot dereference end()");
		return current->exponent;
	}

	//operator~enforce reference to exponent of selected Term if valid
	ItemType& operator->(){
		if (current == NULL)
			throw std::invalid_argument("Cannot dereference end()");
		return &(current->exponent)
	}

	//operator~advance iterator
	piterator& operator++(){
		if (current == NULL)
			throw std::invalid_argument("Cannot advance past end()");
		current = current->next;
		return *this;
	}

	//operator~retreat iterator
	piterator& operator--(){
		if (current == parent->leadingTerm)
			throw std::invalid_argument("Cannot retreat before begin()");
		if (current==NULL)
			current = parent->lowestTerm;
		else
			current = current->prev;
		return *this;
	}
	//operator~return value prior to advance
	piterator operator++(int){
		piterator originalValue =*this;
		++(*this);
		return originalValue;
	}
	//operator~return value prior to retreat
	piterator operator--(int){
		piterator originalValue = *this;
		--(*this);
		return originalValue;
	}

	//operator~equality operator
	bool operator ==(const piterator& other){
		return current == other.current;
	}
	//operator~!=inequality operator
	bool operator !=(const piterator& other){
		return current != other.current;
	}

	};//end of iterator class

#endif
