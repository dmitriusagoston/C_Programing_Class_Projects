//-----------------------------------------------------------------------------
// Dmitrius Agoston
// dagoston
// pa4
//
// List.cpp
// Implementation file for List ADT
//-----------------------------------------------------------------------------
#include<iostream>
#include<string>
#include<stdexcept>
#include"List.h"


// Private Constructor --------------------------------------------------------

// Node constructor
List::Node::Node(ListElement x) {
	data = x;
	next = nullptr;
	prev = nullptr;
}
// Class Constructors & Destructors -------------------------------------------

// Creates a new List in the empty state.
List::List() {
    frontDummy = new Node(-1);
    backDummy = new Node(-2);
	beforeCursor = frontDummy;
	afterCursor = backDummy;
	pos_cursor = 0;
	num_elements = 0;
    frontDummy->next = backDummy;
    backDummy->prev = frontDummy;
}

// Copy Constructor
List::List(const List& L) {
	// make this an empty List
    frontDummy = new Node(-1);
    backDummy = new Node(-2);
	beforeCursor = frontDummy;
	afterCursor = backDummy;
	pos_cursor = 0;
	num_elements = 0;
    frontDummy->next = backDummy;
    backDummy->prev = frontDummy;
	// load elements of L into this List
	Node* N = L.frontDummy->next;
	while (N->next != nullptr) {
		this->insertBefore(N->data);
		N = N->next;
	}
    moveFront();
}

// Destructor
List::~List() {
	clear();
    if (frontDummy != nullptr) {
        delete frontDummy;
        frontDummy = nullptr;
    }
    if (backDummy != nullptr) {
        delete backDummy;
        backDummy = nullptr;
    }
    return;
}

// Acess functions

// length()
// Returns the length of this List.
int List::length() const {
	return(num_elements);
}

// front()
// Returns the front element in this List.
// pre: length()>0
ListElement List::front() const {
	if (length() == 0) {
		throw std::length_error("List: front(): emptry List");
	}
	return(frontDummy->next->data);
}

// back()
// Returns the back element in this List.
// pre: length()>0
ListElement List::back() const {
	if (length() == 0) {
		throw std::length_error("List: back(): emptry List");
	}
	return(backDummy->prev->data);
}

// position()
// Returns the position of cursor in this List: 0 <= position() <= length().
int List::position() const {
	if (pos_cursor < 0 || pos_cursor > length()) {
		throw std::range_error("List: position(): invalid position()");
	}
	return(pos_cursor);
}

// peekNext()
// Returns the element after the cursor.
// pre: position()<length()
ListElement List::peekNext() const {
	if (position() >= length()) {
		throw std::range_error("List: peekNext(): invalid position()");
	}
	return(afterCursor->data);
}

// peekPrev()
// Returns the element before the cursor.
// pre: position()>0
ListElement List::peekPrev() const {
	if (position() <= 0) {
		throw std::range_error("List: peekPrev(): invalid position()");
	}
	return(beforeCursor->data);
}

// Manipulation procedures -------------------------------------------------

// clear()
// Deletes all elements in this List, setting it to the empty state.
void List::clear() {
    moveFront();
    while(length() > 0) {
        eraseAfter();
    }
    return;
}

// moveFront()
// Moves cursor to position 0 in this List.
void List::moveFront() {
	pos_cursor = 0;
    beforeCursor = frontDummy;
    afterCursor = frontDummy->next;
}

// moveBack()
// Moves cursor to position length() in this List.
void List::moveBack() {
	pos_cursor = length();
    beforeCursor = backDummy->prev;
    afterCursor = backDummy;
}

// moveNext()
// Advances cursor to next higher position. Returns the List element that
// was passed over. 
// pre: position()<length() 
ListElement List::moveNext() {
	if (position() >= length()) {
		throw std::range_error("List: moveNext(): No higher position");
	}
    beforeCursor = beforeCursor->next;
    afterCursor = afterCursor->next;
    pos_cursor++;
	return(beforeCursor->data);
}

// movePrev()
// Advances cursor to next lower position. Returns the List element that
// was passed over. 
// pre: position()>0
ListElement List::movePrev() {
	if (position() <= 0) {
		throw std::range_error("List: movePrev(): No lower position");
	}
    beforeCursor = beforeCursor->prev;
    afterCursor = afterCursor->prev;
    pos_cursor--;
    return(afterCursor->data);
}

// insertAfter()
// Inserts x after cursor.
void List::insertAfter(ListElement x) {
Node *N = new Node(x);
    N->prev = beforeCursor;
    N->next = afterCursor;
    beforeCursor->next = N;
    afterCursor->prev = N;
    afterCursor = N;
    num_elements++;
    return;
}

// insertBefore()
// Inserts x before cursor.
// front|1|2|back
void List::insertBefore(ListElement x) {
	Node *N = new Node(x);
    N->prev = beforeCursor;
    N->next = afterCursor;
    beforeCursor->next = N;
    afterCursor->prev = N;
    beforeCursor = N;
    pos_cursor++;
    num_elements++;
    return;
}

// setAfter()
// Overwrites the List element after the cursor with x.
// pre: position()<length()
void List::setAfter(ListElement x) {
	if (position() >= length()) {
		throw std::range_error("List: setAfter(): No higher position"); 
	}
	afterCursor->data = x;
}

// setBefore()
// Overwrites the List element before the cursor with x.
// pre: position()>0
void List::setBefore(ListElement x) {
	if (position() <= 0) {
		throw std::range_error("List: setBefore(): No lower position"); 
	}
	beforeCursor->data = x;
}

// eraseAfter()
// Deletes element after cursor.
// pre: position()<length()
void List::eraseAfter() {
	if (position() >= length()) {
		throw std::range_error("List: eraseAfter(): No higher position");
	}
	beforeCursor->next = afterCursor->next;
    afterCursor->next->prev = beforeCursor;
    delete afterCursor;
    afterCursor = beforeCursor->next;
    num_elements--;
    return;
}

// eraseBefore()
// Deletes element before cursor.
// pre: position()>0
void List::eraseBefore() {
	if (position() <= 0) {
		throw std::range_error("List: erasebefore(): No lower position");
	}
    afterCursor->prev = beforeCursor->prev;
    beforeCursor->prev->next = afterCursor;
    delete beforeCursor;
    beforeCursor = afterCursor->prev;
    num_elements--;
    pos_cursor--;
    return;
}

// Other Functions ---------------------------------------------------------

// findNext()
// Starting from the current cursor position, performs a linear search (in 
// the direction front-to-back) for the first occurrence of element x. If x
// is found, places the cursor immediately after the found element, then 
// returns the final cursor position. If x is not found, places the cursor 
// at position length(), and returns -1. 
int List::findNext(ListElement x) {
	for (int i = position(); i < length(); i++) {
		if (moveNext() == x) {
			return(position());
		}
	}
    beforeCursor = backDummy->prev;
    afterCursor = backDummy;
	pos_cursor = length();
	return -1;
}

// findPrev()
// Starting from the current cursor position, performs a linear search (in 
// the direction back-to-front) for the first occurrence of element x. If x
// is found, places the cursor immediately before the found element, then
// returns the final cursor position. If x is not found, places the cursor 
// at position 0, and returns -1. 
int List::findPrev(ListElement x) {
	for (int i = position(); i > 0; i--) {
		if (movePrev() == x) {
			return(position());
		}
	}
    beforeCursor = frontDummy;
    afterCursor = frontDummy->next;
	pos_cursor = 0;
	return -1;
}

// cleanup()
// Removes any repeated elements in this List, leaving only unique elements.
// The order of the remaining elements is obtained by retaining the frontmost 
// occurrance of each element, and removing all other occurances. The cursor 
// is not moved with respect to the retained elements, i.e. it lies between 
// the same two retained elements that it did before cleanup() was called.
void List::cleanup() {
    if (length() < 2) {
        return;
    }
    int pos = position();
    int dec = 0;
    List T;
    moveFront();
    for (int i = 0; i < length(); i++) {
        int cur = peekNext();
        T.moveBack();
        if (T.findPrev(moveNext()) == -1) {
            T.moveBack();
            T.insertBefore(cur);
        } else {
            if (position() <= pos) {
                dec++;
            }
        }
    }
    pos -= dec;
    *this = T;
    if (pos == length()) {
        moveBack();
        return;
    }
    if (pos == length() - 1) {
        moveBack();
        movePrev();
        return;
    }
    moveFront();
    for (int i = 0; i < pos; i++) {
        moveNext();
    }
	return;
}
 
// concat()
// Returns a new List consisting of the elements of this List, followed by
// the elements of L. The cursor in the returned List will be at position 0.
List List::concat(const List& L) const {
	List C = *this;
    for (Node *N = L.frontDummy->next; N->next != nullptr; N = N->next) {
        C.moveBack();
        C.insertAfter(N->data);
    }
    C.moveFront();
	return C;
}

// to_string()
// Returns a string representation of this List consisting of a comma 
// separated sequence of elements, surrounded by parentheses.
std::string List::to_string() const{
	std::string s = "(";
	for (Node *N = frontDummy->next; N->next != nullptr; N = N->next) {
		s += std::to_string(N->data)+", ";
	}
    s.pop_back();
    s.pop_back();
    s += ")";
	return s;
}

// equals()
// Returns true if and only if this List is the same integer sequence as R.
// The cursors in this List and in R are unchanged.
bool List::equals(const List& R) const{
	bool eq = false;
	Node *N = this->frontDummy;
	Node *M = R.frontDummy;
	eq = (this->length() == R.length());
	while (eq && N != nullptr) {
		eq = (N->data == M->data);
		N = N->next;
		M = M->next;
	}
	return eq;
}

// Overriden Operators -----------------------------------------------------
   
// operator<<()
// Inserts string representation of L into stream.
std::ostream& operator<<( std::ostream& stream, const List& L ) {
	return stream << L.List::to_string();
}

// operator==()
// Returns true if and only if A is the same integer sequence as B. The 
// cursors in both Lists are unchanged.
bool operator==( const List& A, const List& B ) {
	return A.List::equals(B);
}
// operator=()
// Overwrites the state of this List with state of L.
List& List::operator=( const List& L ) {
	if( this != &L ){ // not self assignment
      // make a copy of L
      List temp = L;

      // then swap the copy's fields with fields of this
      std::swap(frontDummy, temp.frontDummy);
      std::swap(backDummy, temp.backDummy);
      std::swap(beforeCursor, temp.beforeCursor);
      std::swap(afterCursor, temp.afterCursor);
      std::swap(pos_cursor, temp.pos_cursor);
      std::swap(num_elements, temp.num_elements);
   }
   // return this with the new data installed
   return *this;

   // the copy, if there is one, is deleted upon return
}
