#ifndef ORDERED_LIST_H_
#define ORDERED_LIST_H_
#include "list.h"

/* The ordered list maintains a list of objects ordered by their less-than operator*/
template<typename Item_Type>
class Ordered_List {

private:
	/**A list to contain the ordered list*/
	list<Item_Type> a_list;

public:
	//Typedefs
	typedef typename list<Item_Type>::const_iterator const_iterator;
	typedef typename list<Item_Type>::iterator iterator;

	//Functions
	/** inserts a new item into the ordered list, maintaining order.
	@param an_item The item to be inserted
	*/

	// Copy constructor 
	Ordered_List<Item_Type>(const Ordered_List<Item_Type>& other) {
		a_list = other.a_list;
	}

	Ordered_List<Item_Type>() {}

	Ordered_List<Item_Type>& operator=(const Ordered_List<Item_Type>& other) {
		a_list = other.a_list;
		return *this;
	}

	iterator erase(iterator pos) {
		return a_list.erase(pos);
	}

	void insert(Item_Type& an_item){
		typename list<Item_Type>::iterator itr = a_list.begin();
		
		if (a_list.empty()) {
			a_list.insert(itr, an_item);
			return;
		}
		while (itr != a_list.end() && *itr > an_item)
			++itr; //itr points to the first item >= an_item
			//or the end
		if (itr == a_list.end()) {
			a_list.insert(itr, an_item);
		}
		else if (*itr == an_item) {
			an_item = *itr + an_item;
			a_list.insert(itr, an_item);
			a_list.erase(itr);
		}
		else {
			a_list.insert(itr, an_item);
		}
	}

	/** Remove an item from the ordered list.
	@param item The value to be removed
	*/
	void remove(const Item_Type& item){
		a_list.remove(item);
	}

	/** Return an iterator to the begining */
	iterator begin() {
		return a_list.begin();
	}

	/** Return an iterator to the end */
	iterator end() {
		return a_list.end();
	}

	/** Return an iterator to the begining */
	const_iterator begin(int) {
		return a_list.begin(int);
	}

	/** Return an iterator to the end */
	const_iterator end(int) {
		return a_list.end(int);
	}

	size_t size() {
		return a_list.size();
	}

	// removes all nodes in ordered list
	void emptyList() {
		a_list.emptyList();
	}

};

#endif