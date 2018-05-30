//Zeyu shen
//May 11 2017
//The purpose of MTF lists is to place the most recently used item to the top (front) of a list, and thus the least recently
//used item will eventually move to the tail. Given more "find" operations than "delete" or "insert", MTF alleviates the
//cost of locating items that need to be frequently accessed. The algorithm is implemented below in the find( ) method:

template<class Object>
int MtfList<Object>::find( const Object &obj ) {
    DListNode<Object> *top = DList<Object>::header->next;
    DListNode<Object> *found = top;
//try to find the element
    
    for ( ; found != NULL && found->item != obj;  found = found->next )// for loop stop until find the element or reach the end
        ++DList<Object>::cost;
    
    if ( found == NULL )
        return -1; // not found
    
    if ( found == top )
        return 0;  // no need to move to front
    
//already find the element now swap
    
    // remove found from the current position
    Object temp = found->item;
    DList<Object>::remove(found->item);
    
    // insert found between header and top
    DList<Object>::insert(temp, 0);
    return 0;
    
}
