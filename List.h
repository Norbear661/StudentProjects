//Norbert Manatad
//nmanatad
//List.h
//cmps101 from pa2
#ifndef _List_H_INCLUDE_
#define _List_H_INCLUDE_

#include <stdio.h>
// Exported type --------------------------------------------------------------

/*typedef struct NodeObj{
        struct NodeObj* next;
        struct NodeObj* prev;
        int data;
}NodeObj;

typedef NodeObj* Node;

typedef struct ListObj{
        Node front;
        Node back;
        Node cursor;
        int length;
        int index;
} ListObj;*/

typedef struct ListObj* List;
// Constructors-Destructors ---------------------------------------------------


List newList(void);


void freeList(List* pL);


// Access functions -----------------------------------------------------------


int length(List L);


int getIndex(List L);


int front(List L);


int back(List L);


int get(List L);
int equals(List A, List B);


int isEmpty(List L);

// Manipulation procedures ----------------------------------------------------


void clear(List L);


void moveFront(List L);


void movePrev(List L);


void moveNext(List L);


void prepend(List L, int data);


void append(List L, int data);


void insertBefore(List L, int data);


void insertAfter(List L, int data);


void deleteFront(List L);


void deleteBack(List L);


void delete(List L);

// Other Functions ------------------------------------------------------------


void printList(FILE* out, List L);


List copyList(List L);


#endif
