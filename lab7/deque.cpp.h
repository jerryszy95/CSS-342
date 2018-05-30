template<class Object>
Deque<Object>::Deque() {                          // the constructor
    front = back = NULL;
}


///////////////////////////////////copy constructor/////////////////////////////////
template<class Object>
Deque<Object>::Deque(const Deque &rhs) {         // the copy constructor
    front = back = NULL;
    *this = rhs;
}

///////////////////////////////////Destructor/////////////////////////////////

template<class Object>
Deque<Object>::~Deque() {                         // the destructor
    clear();
}

///////////////////////////////////isEmpty/////////////////////////////////
// return whether the list is empty
template<class Object>
bool Deque<Object>::isEmpty() const {             // check if a deque is empty
    return front == NULL;
} // end isEmpty

///////////////////////////////////size/////////////////////////////////
// return the size of the list

template<class Object>
int Deque<Object>::size() const {                 // retrieves # deque nodes
    int i = 0;
    for (DequeNode *ptr = front; ptr != NULL; ptr = ptr->next) // traverse que
        ++i;
    
    return i;
}

///////////////////////////////////getFront/////////////////////////////////
// return the front of the list
template<class Object>
const Object &Deque<Object>::getFront() const {   // retrieve the front node
    if (isEmpty())
        throw "empty queue";
    return front->item;
}

///////////////////////////////////getBack/////////////////////////////////
// return the back of the list
template<class Object>
const Object &Deque<Object>::getBack() const {    // retrieve the tail node
    if (isEmpty())
        throw "empty queue";
    return back->item;
}

///////////////////////////////////clear/////////////////////////////////
// clears the list
template<class Object>
void Deque<Object>::clear() {          // clean up all entries.
    while (!isEmpty())                 // dequeue till the queue gets empty.
        removeFront();
}

///////////////////////////////////addFront/////////////////////////////////
// add the the obj to the front of the list
template<class Object>
void Deque<Object>::addFront(const Object &obj) {// add a new node to  front
    // Implement the function body.
    DequeNode *newPtr = new DequeNode;
    
    newPtr->item = obj;
    
    // checks whether the list is empty, if so set both the newPtr as the front and back
    if (isEmpty()) {
        front = newPtr;
        back = newPtr;
        newPtr->next = NULL;
        newPtr->prev = NULL;
    }
    else {
        newPtr->next = front;   // connecting the new node to the old front
        front->prev = newPtr;   // connecting the old front to the new node
        newPtr->prev = NULL;    // setting the left element of the new node to null
        front = newPtr; // moving the front to the new node
    }
}

///////////////////////////////////addBack/////////////////////////////////
// add the the obj to the back of the list
template<class Object>
void Deque<Object>::addBack(const Object &obj) { // add a new node to tail
    // Implement the function body.
    DequeNode *newPtr = new DequeNode();
    newPtr->item = obj;
    
    // checks whether the list is empty, if so set both the newPtr as the front and back
    if (isEmpty()) {
        front = newPtr;
        back = newPtr;
        newPtr->next = NULL;
        newPtr->prev = NULL;
    }
    else {
        newPtr->prev = back; // connecting the new node to the old back
        back->next = newPtr; // connecting the old back to the new node
        newPtr->next = NULL; // setting the right element of the new node to null
        back = newPtr; // moving the back to the new node
    }
}

///////////////////////////////////removeFront/////////////////////////////////
// removes the front element and returns the object
template<class Object>
Object Deque<Object>::removeFront() {  // remove the front node
    // Implement the function body.
    Object retrieve = front->item; // save the obj
    
    DequeNode *temp = front;
    if(front->next != NULL) { // list has two or more elements
        front->prev = NULL; // de link the front to the next element
        front = front->next; // moving from to the right element
    } else { // if list only has the one element
        front = NULL;
        back = NULL; // sets to null to prevent core dumped
    }
    
    delete temp;
    return retrieve;
} // end removeFront

///////////////////////////////////removeBack/////////////////////////////////
// removes the back element and returns its object

template<class Object>
Object Deque<Object>::removeBack() {   // remove the tail node
    // Implement the function body.
    Object retrieve = back->item; // saves the obj
    
    DequeNode *temp = back;
    if (back->prev != NULL) { // list has two or more elements
        back->next = NULL;  // de link the back to the left element
        back = back->prev; // moving back to the left element
    } else {  // if list only has the one element
        back = NULL;
        front = NULL;  // sets to null to prevent core dumped
    }
    delete temp;
    return retrieve;
    
}

/////////////////////////////////operator=/////////////////////////////////
// Overloaded =:

template<class Object>
const Deque<Object> &Deque<Object>::operator=(const Deque &rhs) { // assign
    if (this != &rhs) { // avoid self assignment
        clear();
        for (DequeNode *rptr = rhs.front; rptr != NULL; rptr = rptr->next)
            addBack(rptr->item);
    }
    return *this;
}

