//
//  List.h
//  
//
//
//  Created by Leon Pham on 10/14/17.
//  Copyright © 2017 Leon Pham. All rights reserved.
//

#ifndef List_h
#define List_h
#include <stdlib.h>
#include <stdio.h>
//#ifndef _LIST_H_INCLUDE_
//#define _LIST_H_INCLUDE_


//exported type------------------------
typedef struct ListObj* List;

//Constructors-Destructors--------------

//Returns reference to new empty List object.
List newList(void);

//Frees all heap memory associated with Queue *pL, and
//sets *pL to NULL
void freeList(List* pL);


//Accessors---------------------

//Returns the value at the front of L.
//pre: !isEmpty(L) aka check if empty first
int front(List L);

//returns value at the back of L.
int back(List L);

//Returns the index where ever the cursor is.
int index(List L);

//returns the data where the cursor is.
int get(List L);

//returns length of L
int length(List L);

//returns 1 or 0 which is true or false
int equals(List A, List B);

//isEmpty()
//Returns true(1) if List is empty, otherwise returns false (0)
int isEmpty(List L);

//Manipulation procedures-----------------------
void clear(List L);
void moveFront(List L);
void moveBack(List L);
void movePrev(List L);
void moveNext(List L);
void prepend(List L, int data);
void append(List L, int data);
void insertBefore(List L, int data);
void insertAfter(List L, int data);
void deleteFront(List L);
void deleteBack(List L);
void delete(List L);

//Other operations------------------------------
void printList(FILE* out, List L);
List copyList(List L);




#endif /* List_h */
