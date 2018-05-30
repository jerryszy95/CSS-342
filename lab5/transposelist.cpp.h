//Zeyu shen
//May 11 2017
//The purpose of transposing a list is to swap the most recently used item with its neighbor, which would be closer to the
//top (front of the list).  The more frequently accessed items will move closer to the top. Eventually, all the list's items
//will be ordered in based on their access frequency. The algorithm is implemented in find( ) as follows:

template<class Object>
int TransposeList<Object>::find( const Object &obj ) {
    DListNode<Object> *found = DList<Object>::header->next;
//try to find the element
    int i = 0;
    for ( ; found != NULL && found->item != obj;  found = found->next, ++i )// for loop stop until find the element or reach the end

        ++DList<Object>::cost;
    
    if ( found == NULL )
        return -1; // not found
    
    if ( found == DList<Object>::header->next )
        return 0;  // no need to swap

//already find the element now swap

    // remove found from the current position
    Object temp  = found->item;
    DList<Object>::remove(found->item);
    
    // insert found before previous
    DList<Object>::insert(temp, i - 1);
    
    return i;
}
