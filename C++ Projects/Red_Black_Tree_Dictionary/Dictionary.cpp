//-----------------------------------------------------------------------------
// Dmitrius Agoston
// Dagoston
// pa6
//
// Dictionary.cpp
// Implementation file for Dictionary ADT
//-----------------------------------------------------------------------------
#include<iostream>
#include<string>
#include"Dictionary.h"

// Private Constructor --------------------------------------------------------

// Node Constructor
Dictionary::Node::Node(keyType k, valType v) {
	key = k;
	val = v;
	parent = nullptr;
	left = nullptr;
	right = nullptr;
    color = 0;
}

// Helper Functions (Optional) -----------------------------------------------

// inOrderString()
// Appends a string representation of the tree rooted at R to string s. The
// string appended consists of: "key : value \n" for each key-value pair in
// tree R, arranged in order by keys.
void Dictionary::inOrderString(std::string& s, Node* R) const {
	if (R->val == -1) {
		return;
	}
	// left traversal
	inOrderString(s, R->left);
	// append current key and val
    s += R->key + " : " + std::to_string(R->val) + "\n";
	// right traversal
	inOrderString(s, R->right);
}

// preOrderString()
// Appends a string representation of the tree rooted at R to s. The appended
// string consists of keys only, separated by "\n", with the order determined
// by a pre-order tree walk.
void Dictionary::preOrderString(std::string& s, Node* R) const {
	if (R->val == -1) {
		return;
	}
	// append current key
	s.append((std::string) R->key);
    s.append("\n");
	// left traversal
	preOrderString(s, R->left);
	// right traversal
	preOrderString(s, R->right);
}

// preOrderCopy()
// Recursively inserts a deep copy of the subtree rooted at R into this 
// Dictionary. Recursion terminates at N.
void Dictionary::preOrderCopy(Node* R, Node* N) {
    if (R->val == -1) {
        return;
    }
    setValue(R->key, R->val);
    if (R == N) {
        return;
    }
    preOrderCopy(R->left, N);
    preOrderCopy(R->right, N);
}

// postOrderDelete()
// Deletes all Nodes in the subtree rooted at R, sets R to nil.
void Dictionary::postOrderDelete(Node* R) {
    if (R->val == -1) {
        return;
    }
    postOrderDelete(R->left);
    postOrderDelete(R->right);
    if (R->parent->left == R) {
        R->parent->left = nil;
    }
    if (R->parent->right == R) {
        R->parent->right = nil;
    }
    delete R;
    R = nil;
    num_pairs--;
}

// search()
// Searches the subtree rooted at R for a Node with key==k. Returns
// the address of the Node if it exists, returns nil otherwise.
Dictionary::Node* Dictionary::search(Node* R, keyType k) const {
	// using in order search
	Node *found = nil;
	// left traversal
	if (R->left->val != -1) {
		found = search(R->left, k);
	}
	// check current node
	if (R->val != -1 && R->key == k) {
        found = R;
		return found;
	}
    // break case
    if (found->val != -1) {
        return found;
    }
	// right traversal
	if (R->right->val != -1) {
		found = search(R->right, k);
	}
	return found;
}

// findMin()
// If the subtree rooted at R is not empty, returns a pointer to the 
// leftmost Node in that subtree, otherwise returns nil.
Dictionary::Node* Dictionary::findMin(Node* R) {
	// empty case
	if (R == nil) {
		return nil;
	}
	Node *min = R;
	// traverse left until end is hit
	while (min->left != nil || min->right != nil) {
		if (min->left != nil) {
            min = min->left;
            continue;
        }
        min = min->right;
	}
	return min;
}

// findMax()
// If the subtree rooted at R is not empty, returns a pointer to the 
// rightmost Node in that subtree, otherwise returns nil.
Dictionary::Node* Dictionary::findMax(Node* R) {
	// empty case
	if (R->val == -1) { 
		return nil;
	}
    Node *max = R;
    // traverse right until end is hit
    while(max->right != nil || max->left != nil) {
        if (max->right != nil) {
            max = max->right;
            continue;
        }
        max = max->left;
    }
    return max;
}

// findNext()
// If N does not point to the rightmost Node, returns a pointer to the
// Node after N in an in-order tree walk.  If N points to the rightmost 
// Node, or is nil, returns nil. 
Dictionary::Node* Dictionary::findNext(Node* N) {
	if (N->val == -1) {
		return nil;
	}
    Node *max = root;
    while (max->right->val != -1) {
        max = max->right;
    }
    if (max == N) {
        return nil;
    }
	// find min of right subtree
	if (N->right->val != -1) {
        if (N->right->left->val == -1) {
            return N->right;
        }
        return findMin(N->right);
    }
	// find parent that exists with left child
	Node *cur = N;
	while (cur->parent->val != -1) {
		if (cur == cur->parent->left) {
			return cur->parent;
		}
		cur = cur->parent;
	}
	return nil;
}

// findPrev()
// If N does not point to the leftmost Node, returns a pointer to the
// Node before N in an in-order tree walk.  If N points to the leftmost 
// Node, or is nil, returns nil.
Dictionary::Node* Dictionary::findPrev(Node* N) {
	if (N->val == -1) {
		return nil;
	}
    Node *min = root;
    while (min->left->val != -1) {
        min = min->left;
    }
    if (min == N) {
        return nil;
    }
	// find max of left subtree
	if (N->left->val != -1) {
        if (N->left->right->val == -1) {
            return N->left;
        }
        return findMax(N->left);
    }
	// find parent that exists with right child
	Node *cur = N;
	while (cur->parent->val != -1) {
		if (cur == cur->parent->right) {
			return cur->parent;
		}
		cur = cur->parent;
	}
	return nil;
}

// RBT Helper Functions -------------------------------------------------------

// LeftRotate()
void Dictionary::LeftRotate(Node* N) {
    // set y
    Node *y = N->right;

    // turn y's left subtree into x's right subtree
    N->right = y->left;
    if (y->left != nil) {
        y->left->parent = N;
    }

    // link y's parent to N
    y->parent = N->parent;
    if (N->parent == nil) {
        root = y;
    } else if (N == N->parent->left) {
        N->parent->left = y;
    } else {
        N->parent->right = y;
    }

    // put N on y's left
    y->left = N;
    N->parent = y;
}

// RightRotate()
void Dictionary::RightRotate(Node* N) {
    // set y
    Node *y = N->left;

    // turn y's left subtree into x's right subtree
    N->left = y->right;
    if (y->right != nil) {
        y->right->parent = N;
    }

    // link y's parent to N
    y->parent = N->parent;
    if (N->parent == nil) {
        root = y;
    } else if (N == N->parent->right) {
        N->parent->right = y;
    } else {
        N->parent->left = y;
    }

    // put N on y's left
    y->right = N;
    N->parent = y;
}

// RB_InsertFixUP()
void Dictionary::RB_InsertFixUp(Node* N) {
    while (N->parent->color == 1) {
        if (N->parent == N->parent->parent->left) {
            Node *y = N->parent->parent->right;
            if (y->color == 1) {
                N->parent->color = 0;
                y->color = 0;
                N->parent->parent->color = 1;
                N = N->parent->parent;
            } else {
                if (N == N->parent->right) {
                    N = N->parent;
                    LeftRotate(N);
                }
                N->parent->color = 0;
                N->parent->parent->color = 1;
                RightRotate(N->parent->parent);
            }
        } else {
            Node *y = N->parent->parent->left;
            if (y->color == 1) {
                N->parent->color = 0;
                y->color = 0;
                N->parent->parent->color = 1;
                N = N->parent->parent;
            } else {
                if (N == N->parent->left) {
                    N = N->parent;
                    RightRotate(N);
                }
                N->parent->color = 0;
                N->parent->parent->color = 1;
                LeftRotate(N->parent->parent);
            }
        }
    }
    root->color = 0;
}

// RB_Transplant()
void Dictionary::RB_Transplant(Node* u, Node* v) {
    if (u->parent == nil) {
        root = v;
    } else if (u == u->parent->left) {
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }
    v->parent = u->parent;
}

// RB_DeleteFixUp()
void Dictionary::RB_DeleteFixUp(Node* N) {
    while (N != root && N->color == 0) {
        if (N == N->parent->left) {
            Node *w = N->parent->right;
            if (w->color == 1) {
                w->color = 0;
                N->parent->color = 1;
                LeftRotate(N->parent);
                w = N->parent->right;
            }
            if (w->left->color == 0 && w->right->color == 0) {
                w->color = 1;
                N = N->parent;
            } else {
                if (w->right->color == 0) {
                    w->left->color = 0;
                    w->color = 1;
                    RightRotate(w);
                    w = N->parent->right;
                }
                w->color = N->parent->color;
                N->parent->color = 0;
                w->right->color = 0;
                LeftRotate(N->parent);
                N = root;
            }
        } else {
            Node *w = N->parent->left;
            if (w->color == 1) {
                w->color = 0;
                N->parent->color = 1;
                RightRotate(N->parent);
                w = N->parent->left;
            }
            if (w->right->color == 0 && w->left->color == 0) {
                w->color = 1;
                N = N->parent;
            } else {
                if (w->left->color == 0) {
                    w->right->color = 0;
                    w->color = 1;
                    LeftRotate(w);
                    w = N->parent->left;
                }
                w->color = N->parent->color;
                N->parent->color = 0;
                w->left->color = 0;
                RightRotate(N->parent);
                N = root;
            }
        }
    }
    N->color = 0;
}

// RB_Delete()
void Dictionary::RB_Delete(Node* N) {
    Node *y = N;
    int y_ogc = y->color;
    Node *x = nil;
    if (N->left == nil) {
        x = N->right;
        RB_Transplant(N, N->right);
    } else if (N->right == nil) {
        x = N->left;
        RB_Transplant(N, N->left);
    } else {
        Node *min = N->right;
        while (min->left->val != -1) {
            min = min->left;
        }
        y = min;
        y_ogc = y->color;
        x = y->right;
        if (y->parent == N) {
            x->parent = y;
        } else {
            RB_Transplant(y, y->right);
            y->right = N->right;
            y->right->parent = y;
        }
        RB_Transplant(N, y);
        y->left = N->left;
        y->left->parent = y;
        y->color = N->color;
    }
    delete N;
    if (y_ogc == 0) {
        RB_DeleteFixUp(x);
    }
}

// Class Constructors & Destructors -------------------------------------------
   
// Creates new Dictionary in the empty state. 
Dictionary::Dictionary() {
	nil = new Node((std::string) "-1", -1);
    nil->parent = nil;
    nil->left = nil;
    nil->right = nil;
	root = nil;
	current = nil;
	num_pairs = 0;
}

// Copy constructor.
Dictionary::Dictionary(const Dictionary& D) {
	nil = new Node((std::string) "-1", -1);
    nil->parent = nil;
    nil->left = nil;
    nil->right = nil;
    root = nil;
    current = nil;
	num_pairs = 0;
    Node *max = D.root;
    // traverse right until end is hit
    while(max->right != D.nil || max->left != D.nil) {
        if (max->right != D.nil) {
            max = max->right;
            continue;
        }
        max = max->left;
    }
	// load dict
    preOrderCopy(D.root, max);
}

// Destructor
Dictionary::~Dictionary() {
	clear();
    delete nil;
}

// Access functions -----------------------------------------------------------

// size()
// Returns the size of this Dictionary.
int Dictionary::size() const {
	return num_pairs;
}

// contains()
// Returns true if there exists a pair such that key==k, and returns false
// otherwise.
bool Dictionary::contains(keyType k) const {
    if (num_pairs == 0) {
        return false;
    }
	if (search(root, k)->val == -1) {
		return false;
	}
	return true;
}

// getValue()
// Returns a reference to the value corresponding to key k.
// Pre: contains(k)
valType& Dictionary::getValue(keyType k) const {
	if (!contains(k)) {
		throw std::invalid_argument("Dictionary does not have key");
	}
	Node *N = search(root, k);
	return N->val;
}

// hasCurrent()
// Returns true if the current iterator is defined, and returns false 
// otherwise.
bool Dictionary::hasCurrent() const {
	if (current->val == -1) {
		return false;
	}
	return true;
}

// currentKey()
// Returns the current key.
// Pre: hasCurrent() 
keyType Dictionary::currentKey() const {
	if (!hasCurrent()) {
		throw std::invalid_argument("Dictionary does not have current");
	}
	return current->key;
}

// currentVal()
// Returns a reference to the current value.
// Pre: hasCurrent()
valType& Dictionary::currentVal() const {
	if (!hasCurrent()) {
		throw std::invalid_argument("Dictionary does not have current");
	}
	return current->val;
}

// Manipulation procedures ----------------------------------------------------

// clear()
// Resets this Dictionary to the empty state, containing no pairs.
void Dictionary::clear() {
	postOrderDelete(root);
    current = nil;
}

// setValue()
// If a pair with key==k exists, overwrites the corresponding value with v, 
// otherwise inserts the new pair (k, v).
void Dictionary::setValue(keyType k, valType v) {
	// empty case
	if (num_pairs == 0) {
		Node *cur = new Node(k, v);
		root = cur;
        root->left = nil;
        root->right = nil;
        root->parent = nil;
        num_pairs++;
		return;
	}
	Node *cur = search(root, k);
	if (cur != nil) {
		cur->val = v;
	} else {
        num_pairs++;
        Node *z = new Node(k, v);
        Node *y = nil;
        Node *x = root;
        while (x != nil) {
            y = x;
            if (z->key < y->key) {
                x = x->left;
            } else {
                x = x->right;
            }
        }
        z->parent = y;
        if (y == nil) {
            root = z;
        } else if (z->key < y->key) {
            y->left = z;
        } else {
            y->right = z;
        }
        z->left = nil;
        z->right = nil;
        z->color = 1;
        RB_InsertFixUp(z);
    }
}

// remove()
// Deletes the pair for which key==k. If that pair is current, then current
// becomes undefined.
// Pre: contains(k).
void Dictionary::remove(keyType k) {
	// precondition
	if (!contains(k)) {
		throw std::invalid_argument("Dictionary does not have key");
	}
	Node *cur = search(root, k);
	// case for only 1 node
	if (num_pairs == 1) {
        delete root;
        num_pairs = 0;
        current = nil;
		return;
	}
	// check if current
	if (cur->val == current->val) {
		current = nil;
	}
    num_pairs--;
    RB_Delete(cur);
}

// begin()
// If non-empty, places current iterator at the first (key, value) pair
// (as defined by the order operator < on keys), otherwise does nothing. 
void Dictionary::begin() {
	if (num_pairs == 0) {
		return;
	}
    Node *min = root;
    while (min->left->val != -1) {
        min = min->left;
    }
	current = min;
}

// end()
// If non-empty, places current iterator at the last (key, value) pair
// (as defined by the order operator < on keys), otherwise does nothing. 
void Dictionary::end() {
	if (num_pairs == 0) {
		return;
	}
    Node *max = root;
    while (max->right->val != -1) {
        max = max->right;
    }
	current = max;
}

// next()
// If the current iterator is not at the last pair, advances current 
// to the next pair (as defined by the order operator < on keys). If 
// the current iterator is at the last pair, makes current undefined.
// Pre: hasCurrent()
void Dictionary::next() {
    if (!hasCurrent()) {
        return;
    }
	current = findNext(current);
}
// prev()
// If the current iterator is not at the first pair, moves current to  
// the previous pair (as defined by the order operator < on keys). If 
// the current iterator is at the first pair, makes current undefined.
// Pre: hasCurrent()
void Dictionary::prev() {
    if (!hasCurrent()) {
        return;
    }
	current = findPrev(current);
}

// Other Functions ------------------------------------------------------------

// to_string()
// Returns a string representation of this Dictionary. Consecutive (key, value)
// pairs are separated by a newline "\n" character, and the items key and value 
// are separated by the sequence space-colon-space " : ". The pairs are arranged 
// in order, as defined by the order operator <.
std::string Dictionary::to_string() const {
    std::string s = "";
	inOrderString(s, root);
	return s;
}

// pre_string()
// Returns a string consisting of all keys in this Dictionary. Consecutive
// keys are separated by newline "\n" characters. The key order is given
// by a pre-order tree walk.
std::string Dictionary::pre_string() const {
    std::string s = "";
	preOrderString(s, root);
	return s;	
}

// equals()
// Returns true if and only if this Dictionary contains the same (key, value)
// pairs as Dictionary D.
bool Dictionary::equals(const Dictionary& D) const {
	std::string A = "";
    std::string B = "";
    preOrderString(A, this->root);
    preOrderString(B, D.root);
    if (A.compare(B) == 0) {
        return true;
    }
    return false;
}

// Overloaded Operators -------------------------------------------------------
   
// operator<<()
// Inserts string representation of Dictionary D into stream, as defined by
// member function to_string().
std::ostream& operator<<( std::ostream& stream, Dictionary& D ) {
	return stream << D.Dictionary::to_string();
}

// operator==()
// Returns true if and only if Dictionary A equals Dictionary B, as defined
// by member function equals(). 
bool operator==( const Dictionary& A, const Dictionary& B ) {
	return A.Dictionary::equals(B);
}

// operator=()
// Overwrites the state of this Dictionary with state of D, and returns a
// reference to this Dictionary.
Dictionary& Dictionary::operator=( const Dictionary& D ) {
	if (this != &D) {
		Dictionary temp = D;
		
		std::swap(nil, temp.nil);
		std::swap(root, temp.root);
		std::swap(current, temp.current);
		std::swap(num_pairs, temp.num_pairs);
		
	}
	return *this;
}
