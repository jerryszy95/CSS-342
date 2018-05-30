//Zeyu Shen
//2017 May 14

#include <cstdlib>
#include <iostream>

//////////////////////////////SList constructor///////////////////////////////
template<class Object>
SList<Object>::SList( ) {
    init( );
}

//////////////////////////SList copy constructor///////////////////////////////

template<class Object>
SList<Object>::SList( const SList &rhs ) {
    init( );
    *this = rhs;                             // then assign rhs to this.
}

/////////////////////////////////////init//////////////////////////////////////
template<class Object>
void SList<Object>::init( ) {
    for ( int i = 0; i < LEVEL; i++ ) {  // for each level
        // create the left most dummy nodes;
        header[i] = new SListNode<Object>;
        header[i]->prev = NULL;
        header[i]->down = ( i > 0 ) ? header[i - 1] : NULL;
        header[i]->up = NULL;
        if ( i > 0 ) header[i - 1]->up = header[i];
        
        // create the right most dummy nodes;
        header[i]->next = new SListNode<Object>; // +inf
        header[i]->next->next = NULL; // +inf ->next = null
        header[i]->next->prev = header[i]; //
        header[i]->next->down = ( i > 0 ) ? header[i - 1]->next : NULL;
        header[i]->next->up = NULL;
        if ( i > 0 ) header[i - 1]->next->up = header[i]->next;
    }
    
    // reset cost.
    cost = 0;
}

///////////////////////////////SList destructor///////////////////////////////////

template<class Object>
SList<Object>::~SList( ) {
    clear( );                                      // delete items starting 1st
    for ( int i = 0; i < LEVEL; i++ ) {
        delete header[i]->next;                      // delete the right most dummy
        delete header[i];                            // delete the left most dummy
    }
} // end destructor

/////////////////////////////////////isEmpty///////////////////////////////////////
template<class Object>
bool SList<Object>::isEmpty( ) const {
    return ( header[0]->next->next == NULL );
}

///////////////////////////////////////size/////////////////////////////////////////
template<class Object>
int SList<Object>::size( ) const {
    SListNode<Object> *p = header[0]->next; // at least the right most dummy
    int size = 0;
    
    for ( ; p->next != NULL; p = p->next, ++size );
    return size;
}

///////////////////////////////////////clear///////////////////////////////////////

template<class Object>
void SList<Object>::clear( ) {
    for ( int i = 0; i < LEVEL; i++ ) {        // for each level
        SListNode<Object> *p = header[i]->next;  // get the 1st item
        while ( p->next != NULL ) {              // if this is not the left most
            SListNode<Object> *del = p;
            p = p->next;                           // get the next item
            delete del;                            // delete the current item
        }
        
        header[i]->next = p;                     // p now points to the left most
    }                                          // let the right most point to it
}

//////////////////////////////////////insert///////////////////////////////////////
template<class Object>
void SList<Object>::insert( const Object &obj ) {
    // right points to the level-0 item before which a new object is inserted.
    SListNode<Object> *right = searchPointer( obj );
    //SListNode<Object> *up = NULL;
    
    if ( right->next != NULL && right->item == obj )
        // there is an identical object
        return;
    
    // Implement the rest by yourself /////////////////////////////////////////
    
    SListNode<Object> *cur = new SListNode<Object>; // new node in level-0
    
    cur->item = obj;
    cur->next = right;            // new node pointing to its right element
    cur->prev = right->prev;      // new node pointing to its left element
    
    right->prev->next = cur;       // left element pointing to new node
    right->prev = cur;             // right element pointing to new node
    
    cur->down = NULL;
    cur->up = NULL;
    
    // chooses whether new node is inserted to the next level
    for(int i = 1; rand() % 2 == 1 && i != LEVEL - 1; i++){
        // the node on the left of the new node in level-0
        SListNode<Object> *temp = cur->prev;
        
        while(temp->up == NULL)
            temp = temp->prev; // traverse until a link going up is found
        
        temp = temp->up; // once found goes up
        SListNode<Object> *p = new SListNode<Object>; // new node in each level
        p->item = obj;
        p->next = temp->next;         // new node pointing to the right of temp
        p->prev = temp;               // new node pointing to temp
        temp->next->prev = p;         // right element pointing to new node
        temp->next = p;               // left element pointing to new node
        p->down = cur;            // links up and down
        cur->up = p;
        p->up = NULL;
        temp = p;                      // resets temp to proper place
        cur = p;                   // resets currPtr to proper place
    }
}
///////////////////////////////////////find///////////////////////////////////////
template<class Object>
bool SList<Object>::find( const Object &obj ) {
    // points to the level-0 item close to a given object
    SListNode<Object> *p = searchPointer( obj );
    
    return ( p->next != NULL && p->item == obj );     // true if obj was found
}

//////////////////////////////////searchPointer/////////////////////////////////
template<class Object>
SListNode<Object> *SList<Object>::searchPointer( const Object &obj ) {
    SListNode<Object> *p = header[LEVEL - 1];     // start from the top left
    while ( p->down != NULL ) {                   // toward level 0
        p = p->down;                                // shift down once
        cost++;
        
        if ( p->prev == NULL ) {                    // at the left most item
            if ( p->next->next == NULL )              // no intermediate items
                continue; // no items it goes down
            else {                                    // some intermadiate items
                if ( p->next->item <= obj )             // if 1st item <= obj
                    p = p->next;                          // shift right to item 1
                cost++;
            }
        }
        
        while ( p->next->next != NULL && p->next->item <= obj ) {
            // shift right through intermediate items as far as the item value <= obj
            p = p->next;
            cost++;
        } // end inner while loop
    } // end outer while loop
    
    // now reached the bottom. shift right once if the current item < obj
    if ( p->prev == NULL || p->item < obj ) {
        p = p->next;
        cost++;
    }
    return p; // return the pointer to an item >= a given object.
}

//////////////////////////////////////remove//////////////////////////////////////

template<class Object>
void SList<Object>::remove( const Object &obj ) {
    // p points to the level-0 item to delete
    SListNode<Object> *p = searchPointer(obj);
    
    // validate if p is not the left most or right most and exactly contains the
    // item to delete
    if (p->prev == NULL || p->next == NULL || p->item != obj)
        return;
    
    // Implement the rest by yourself /////////////////////////////////////////
    
    while (p->up != NULL) {
        p->next->prev = p->prev; // remove the link to the right element
        p->prev->next = p->next; // remove the link to the left element
        p = p->up; // traverse up
        delete p->down; // deletes the bottom of the node while it traverse
    }
}

/////////////////////////////////////operator=/////////////////////////////////////

template<class Object>
const SList<Object> &SList<Object>::operator=( const SList &rhs ) {
    if ( this != &rhs ) { // avoid self-assignment
        clear( );           // deallocate old items
        
        int index;
        SListNode<Object> *rnode;
        for ( index = 0, rnode = rhs.header[0]->next; rnode->next != NULL;
             rnode = rnode->next, ++index )
            insert( rnode->item );
        
        cost = rhs.cost;
    }
    return *this;
} // end operator=

//////////////////////////////////////getCost///////////////////////////////////

template<class Object>
int SList<Object>::getCost( ) const {
    return cost;
} // end getCost

///////////////////////////////////show/////////////////////////////////////////
template<class Object>
void SList<Object>::show( ) const {
    cout << "contents:" << endl;
    for ( SListNode<Object> *col = header[0]; col != NULL; col = col->next ) {
        SListNode<Object> *row = col;
        for ( int level = 0; row != NULL && level < LEVEL; level++ ) {
            if ( row->prev == NULL )
                cout << "-inf\t";
            else if ( row->next == NULL )
                cout << "+inf\t";
            else
                cout << row->item << "\t";
            row = row->up;
        }
        cout << endl;
    }
}
