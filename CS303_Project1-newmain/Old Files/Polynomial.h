#include <cstddef>

template <typename ItemType>
class Polynomial{
private://================================================================================================
		struct Term{
			//term components
			ItemType coefficient;
			ItemType exponent;
			//Pointer to next term
			Term* next;
			//Pointer to previous term
			Term* prev;

			//Term Constructor
			Term (const ItemType& givenCoefficient, const ItemType& givenExponent, 
				Term* prevValue = NULL, Term* nextValue =NULL) :
				coefficient(givenCoefficient), exponent(givenExponent), prev(prevValue), next(nextValue){}
		};//end of term struct

		//reference to head
		Term* leadingTerm;
		//reference to tail
		Term* lowestTerm;

		//current number of terms
		size_t numTerms;
		//overload operators to test exponents
		/*bool operator >(const Term& other){
				return (exponent>other.exponent);
		}
		bool operator <(const Term& other){
				return (exponent<other.exponent);
		}*/
public://==========================================================

#include "const_Polynomial_It.h"
	friend class const_piterator;
#include "Polynomial_It.h"
	friend class piterator;
	

	//Polynomial constructor
	Polynomial() : leadingTerm(NULL),lowestTerm(NULL),numTerms(0){}


	//Polynomial copy constructor
	/*Polynomial(const Polynomial<ItemType>& other) :
		leadingTerm(NULL),lowestTerm(NULL),numTerms(0){
			for (const_piterator itr = other.begin(); itr!= other.end(); itr++){
				insert(itr, itr.getCo(), *itr);
			}
	}*/
	// Polynomial Destructor
	~Polynomial(){
		while (leadingTerm!=NULL){
			Term* current = leadingTerm;
			leadingTerm = leadingTerm->next;
			delete current;
		}
		lowestTerm = NULL;
		numTerms = 0;
	}

//*Polynomial functions*//------------------------------------------------------

	//operator~Polynomial overwrite--not yet working
	
	Polynomial<ItemType>& operator=(const Polynomial<ItemType>& other){
		Polynomial<ItemType> temp(other);
		swap(temp);
		return *this;
	}
	
	//function~push new Term to front of polynomial
	void push_front(const ItemType& coefficientIN, const ItemType& exponentIN){
		//if matching exponents, replace leading term with new term combining coefficients
		if((leadingTerm!=NULL) && (leadingTerm->exponent==exponentIN)){
			ItemType newCoefficient = (leadingTerm->coefficient)+coefficientIN;
			Term* doomed = leadingTerm;
			Term* nextTerm = leadingTerm->next;
			leadingTerm = new Term(newCoefficient, exponentIN, NULL, doomed->next);
			if (doomed->next!=NULL)
				doomed->next->prev = leadingTerm;
			if (lowestTerm==NULL)//if Polynomial had only that term, new leading term is also lowest term
				lowestTerm = leadingTerm;
			delete doomed;
		}
		else{
			leadingTerm = new Term(coefficientIN,exponentIN, NULL, leadingTerm);//create new Term
			if (leadingTerm->next !=NULL)//if next Term is not null, Make next term's previous this Term
			leadingTerm->next->prev = leadingTerm;
			if (lowestTerm==NULL)//if Polynomial was empty, leading term is also lowest term
				lowestTerm = leadingTerm;
			numTerms++;//increase number of terms in Polynomial
		}
	}
	//function~push new Term to back of polynomial
	void push_back(const ItemType& coefficientIN, const ItemType& exponentIN){
		//if matching exponents, replace lowest term with new term combining coefficients
		if ((leadingTerm!=NULL) && (lowestTerm->exponent==exponentIN)){
			ItemType newCoefficient = (lowestTerm->coefficient)+coefficientIN;
			Term* doomed = lowestTerm;
			lowestTerm = new Term(newCoefficient, exponentIN, doomed->prev, NULL);
			doomed->prev->next = lowestTerm;
			delete doomed;
		}
		else{
			if (lowestTerm!=NULL){//if at least one term present, create new term after lowest
				lowestTerm->next = new Term(coefficientIN, exponentIN, lowestTerm, NULL);
				lowestTerm = lowestTerm->next;//make current lowest Term's next the new lowest term
				numTerms++;//increase number of terms
			}
			else //Polynomial was empty, 
				push_front(coefficientIN, exponentIN);
		}
	}
	//function~remove leading Term of Polynomial
	void pop_front(){
		if (leadingTerm==NULL)//prevent attempt to pop empty list
			throw std::invalid_argument("Cannot Pop from empty list!");
		Term* removedTerm = leadingTerm;//save pointer to leading term
		leadingTerm = leadingTerm->next;//2nd highest term is new leading term
		delete removedTerm; //delete previous leading term
		if (leadingTerm != NULL)//if polynomial is not empty, make sure leading term has none before it
			leadingTerm->prev = NULL;
		else{
			lowestTerm = NULL;//if polynomial is empty, reset lowest term;
		}
		numTerms--;//decrease number of terms
	}
	//function~remove lowest term of Polynomial
	void pop_back(){
		if (lowestTerm==NULL)
			throw std::invalid_argument("Cannot Pop from empty list!");
		Term* removedTerm = lowestTerm;//save pointer to lowest term
		lowestTerm = lowestTerm->prev;//2nd lowest is new lowest term
		delete removedTerm;//delete previous lowest term
		if (lowestTerm!=NULL)//if not empty, make sure lowest term is last
			lowestTerm->next=NULL;
		else
			leadingTerm = NULL;//if polynomial is empty, reset leading term;
		numTerms--;
	}

		//iterator definition


//*iterator functions*//------------------------------------------------
	//function~send iterator to beginning of Polynomial
	piterator begin(){
		return piterator(this, leadingTerm);
	}
	//function~send const iterator to beginning of Polynomial
	const_piterator begin() const{
		return const_piterator(this, leadingTerm);
	}
	//function~send iterator to end of Polynomial
	piterator end(){
		return piterator(this, NULL);
	}
	//function~send const iterator to end of Polynomial
	const_piterator end() const{
		return const_piterator(this, NULL);
	}

	//function~insert new Term based on iterator position and reorder links to keep structure
	piterator insert(piterator position, const ItemType& coefficientIN, const ItemType& exponentIN){
		if (position.current == leadingTerm){//iterator at begin()
			push_front(coefficientIN, exponentIN);
			return begin();
		}
		else if (position.current==NULL){//piterator at end()
			push_back(coefficientIN, exponentIN);
			return piterator(this, lowestTerm);
		}
		//insert Term before current iterator position
		//newly created term's previous and next match currently selected terms previous and next
		//if matching exponents, replace selected term with new term combining coefficients
		if (position.current->exponent ==exponentIN){
			 ItemType newCoefficient = position.current->coefficient+coefficientIN;
			 Term* doomed =position.current;
			 Term* newCurrent = new Term(newCoefficient, exponentIN,position.current->prev, position.current->next);
			 if (doomed->next!=NULL)
				doomed->next->prev = newCurrent;
			 if (doomed->prev!=NULL)
				doomed->prev->next = newCurrent;
			 delete doomed;
		}
		else{
		Term* newTerm = new Term(coefficientIN, exponentIN, position.current->prev, position.current);
		position.current->prev->next = newTerm;//term berfore selected's new next is new term
		position.current->prev = newTerm;//selected term's new previous is new term
		numTerms++;//increment number of terms
		return piterator(this, newTerm);//send iterator to location of new term
		}
	}
	/*
	const_piterator insert(const_piterator position, const ItemType& coefficientIN, const ItemType& exponentIN) {
		if (position.current == leadingTerm) {//iterator at begin()
			push_front(coefficientIN, exponentIN);
			return begin();
		}
		else if (position.current == NULL) {//piterator at end()
			push_back(coefficientIN, exponentIN);
			return const_piterator(this, lowestTerm);
		}
		//insert Term before current iterator position
		//newly created term's previous and next match currently selected terms previous and next
		//if matching exponents, replace selected term with new term combining coefficients
		if (position.current->exponent == exponentIN) {
			ItemType newCoefficient = position.current->coefficient + coefficientIN;
			Term* doomed = position.current;
			Term* newCurrent = new Term(newCoefficient, exponentIN, position.current->prev, position.current->next);
			if (doomed->next != NULL)
				doomed->next->prev = newCurrent;
			if (doomed->prev != NULL)
				doomed->prev->next = newCurrent;
			delete doomed;
		}
		else {
			Term* newTerm = new Term(coefficientIN, exponentIN, position.current->prev, position.current);
			position.current->prev->next = newTerm;//term berfore selected's new next is new term
			position.current->prev = newTerm;//selected term's new previous is new term
			numTerms++;//increment number of terms
			return const_piterator(this, newTerm);//send iterator to location of new term
		}
	}

	*/
	
	//function~remove specific Term matching exponent and repair links to keep structure
	void remove(const ItemType& exponentIN){
		Term* current = leadingTerm;
		while (current!=NULL){
			if (current->exponent==exponentIN){//if current Term matches degree chosen for deletion
				if (current->next==null)//lowest term case
					return pop_back;
				if (current==leadingTerm)//leading term case
				leadingTerm = current->next;
				Term* doomed = current;//save current term for deletion
				//have next term's previous pass over to current's previous
				current->next->prev = current->prev;
				//if not leading Term, have the previous Term's next pass over to current's next
				if (current->prev!=NULL)
					current->prev->next = current->next;
				current = current->next;//move to next term. final detachment
				delete doomed; //delete abandoned term
				numTerms--; //decrement number of terms
			}//end of while
			else current = current->next;//skip terms that don't match
		}
	}
	//function~check for empty polynomial
	bool empty(){
		return numTerms = 0;
	}
	//function~erase term at iterator position
	piterator erase(piterator position){
		if (empty())
			throw std::invalid_argument("Cannot erase terms from empty polynomial");
		if (position.current ==NULL)
			throw std::invalid_argument("Cannot erase end()");
		piterator newPosition = position;//create iterator to return
		++newPosition;//advance returning iterator to something that will exist
		if (position.current==leadingTerm){//leading term case
			pop_front();
			return newPosition;
		}
		else if(position.current==lowestTerm){//lowest term case
			pop_back();
			return newPosition;
		}
		else{
			Term* doomed = position.current;//save currently selected Term for deletion
			doomed->prev->next = doomed->next;//previous skips doomed for doomed's next
			doomed->next->prev = doomed->prev;//next skips doomed for doomed's prev
			delete doomed; //delete abandoned term
			return newPosition;
		}
	}
	//function~check lowest degree
	ItemType& getLowDegree(){
		if (lowestTerm!= NULL)
			return lowestTerm->exponent;
		return NULL;
	}
	//function~READ ONLY check lowest degree
	const ItemType& getLowDegree() const{
		if (lowestTerm!= NULL)
			return lowestTerm->exponent;
		return NULL;
	}
	//function~check lowest term's coefficient
	ItemType& getlowTermCo(){
		if (lowestTerm!= NULL)
			return lowestTerm->coefficient;
		return NULL;
	}
	//function~READ ONLY check lowest term's coefficient
	const ItemType& getLowTermCo() const{
		if (lowestTerm!= NULL)
			return lowestTerm->coefficient;
		return NULL;
	}
	//function~check degree of leading term
	ItemType& getLeadDegree(){
		if (leadingTerm != NULL)
			return leadingTerm->exponent;
		return NULL;
	}
	//function~READ ONLY check degree of leading term
	const ItemType& getLeadDegree() const{
		if (leadingTerm != NULL)
			return leadingTerm->exponent;
		return NULL;
	}
	//function~check coefficient of leading term
	ItemType& getLeadCo(){
		if (leadingTerm != NULL)
			return leadingTerm->coefficient;
		return NULL;
	}
	//function~check coefficient of leading term
	const ItemType& getLeadCo() const{
		if (leadingTerm != NULL)
			return leadingTerm->coefficient;
		return NULL;
	}

	// function to transfer data from another poly
	// into this poly
	void swap(Polynomial<ItemType>& other){
		std::swap(leadingTerm, other.leadingTerm);
		std::swap(lowestTerm, other.lowestTerm);
		std::swap(numTerms, other.numTerms);
		//empty this polynomial then transfer over terms
		//from other
		emptyPoly();
		piterator itr = other.begin();
		for (itr; itr != other.end(); itr++) {
			insert(itr,itr.getCo(), *itr);
		}
	}

	//function~return number of terms in polynomial
	size_t size()const{
		return numTerms;
	}
	//function~move iterator to a term with a specific degree
	piterator find(ItemType target){
		for (piterator itr = begin(); itr!=end; ++itr){
			if (*itr == target)
				return itr;
		}
		return end;//target not found
	}

	void emptyPoly() {
		piterator itr = begin();
		for (itr; itr != end(); itr++) {
			erase(itr);
		}
	}
};//end of polynomial class
