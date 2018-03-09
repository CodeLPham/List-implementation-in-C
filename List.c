//
//  List.c
//
//  
//
//  Created by Leon Pham on 10/14/17.
//  Copyright © 2017 Leon Pham. All rights reserved.
//


#include <stdlib.h>
#include "List.h"

typedef struct NodeObj{
    int data;
    struct NodeObj* next;
    struct NodeObj* prev;
    
} NodeObj;


typedef NodeObj* Node;

typedef struct ListObj{
    Node front;
    Node back;
    int length;
    Node cursor;
    int index;
} ListObj;


//------------------Constructors/Destructors------------

Node newNode(int data){ //constructor
    Node N = malloc(sizeof(NodeObj));
    N->data = data;
    N->next = NULL;
    N->prev = NULL;
    return(N);
}

//freeNode() Deconstructor
void freeNode(Node* pN){
    if( pN != NULL && *pN != NULL){
        free(*pN);
        *pN = NULL;
    }
}

List newList(void){
    List L = malloc(sizeof(ListObj));
    L->front = L->back = L->cursor = NULL;
    L->length = 0;
    L->index = -1;
    return(L);
}



void freeList(List* pL){
    
    if(pL != NULL && *pL != NULL) {
        clear(*pL);
        free(*pL);
        *pL = NULL;
    }
    
}

int front(List L){
    if(L->front == NULL){
        printf("front() called on empty list");
        exit(1);
    }
    return L->front->data;
}

int back(List L){
    if(L->back == NULL){
        printf("back() called on empty list");
        exit(1);
    }
    return L->back->data;
}

int index(List L){
    if(L->cursor == NULL){
        L->index = -1;
    }
    return L->index;
}

int get(List L){
    if(L == NULL){
        printf("get() called on NULL list");
        exit(1);
    }
    
    if(length(L) == 0){
        printf("get() called on empty list");
        exit(1);
    }
    if(index(L) == -1){
        printf("get() called on undefined cursor");
        exit(1);
    }
    return L->cursor->data;
}

int length(List L){
    if(L == NULL){
        printf("length called on non-existant list\n");
        exit(1);
    }
    return L->length;
}

//isEmpty
int isEmpty(List L){
    if(L == NULL){
        printf("List Error: calling isEmpty() on NULL List reference\n");
        exit(1);
    }
    return (L->length == 0);
}

void clear(List L){
    
    if(L == NULL){
        printf("Calling clear() on an already NULL list\n");
        exit(0);
    }
    //L->front = L->back = L->cursor = NULL;
    freeNode(&L->cursor);
    freeNode(&L->back);
    freeNode(&L->front);
    L->index = -1;
    L->length = 0;
}

void moveFront(List L){
    if(!isEmpty(L)){ //non-empty
        L->cursor = L->front;
        L->index = 0;
    }
}

void moveBack(List L){
    if(!isEmpty(L)){
        L->cursor = L->back;
        L->index = length(L) - 1;
    }
}

void movePrev(List L){ //cursor method
    if(L->cursor != NULL && L->cursor != L->front){
        L->index--;
        L->cursor = L->cursor->prev; //move cursor back 1
    }
    else if(L->cursor != NULL && L->cursor == L->front){
        L->index = -1;
        L->cursor = NULL;
    }
}

void moveNext(List L){
    if(L->cursor != NULL && L->cursor != L->back){
        L->index++;
        L->cursor = L->cursor->next;
    }
    else if(L->cursor != NULL && L->cursor == L->back){
        L->index = -1;
        L->cursor = NULL;
    }
}

void prepend(List L, int data){
    
    //always check to see if list pointer is null
    if(L == NULL){
        printf("prepend() called on NULL list");
        exit(1);
    }
    
    Node new_element = newNode(data);
    
    if(length(L) == 0){
        L->front = L->back = new_element;
    }
    else{
        //on non-empty list
        L->front->prev = new_element;
        new_element->next = L->front;
        L->front = new_element;
        L->index++;
    }
    L->length++;
    
}

void append(List L, int data){
    
    if(L == NULL){
        printf("append() called on NULL list");
        exit(1);
    }
    
    Node new_element = newNode(data);
    
    if(length(L) == 0){
        L->front = L->back = new_element;
    }
    else{
        L->back->next = new_element;
        new_element->prev = L->back;
        L->back = new_element;
    }
    L->length++;
}

void insertBefore(List L, int data){
    if(isEmpty(L)){
        printf("insertBefore() called on empty List\n");
        exit(0);
    }
    if(index(L) == -1){
        printf("Cannot call insertBefore() with undefined cursor");
        exit(0);
    }
    
    if(L->cursor == L->front){
        prepend(L,data);
    }
    else{
        Node new_element = newNode(data);
        new_element->next = L->cursor;
        new_element->prev = L->cursor->prev;
        L->cursor->prev = new_element;
        L->length++;
        L->index++;
    }
    
    
}

void insertAfter(List L, int data){
    if(isEmpty(L)){
        printf("insertAfter() called on empty List\n");
        exit(0);
    }
    if(index(L) == -1){
        printf("Cannot call insert() with undefined cursor");
        exit(0);
    }
    if(L->cursor == L->back){
        append(L,data);
    }
    else{
        Node new_element = newNode(data);
        new_element->prev = L->cursor;
        new_element->next = L->cursor->next;
        L->cursor->next = new_element;
        L->length++;
        //insertAfter() does not change cursor index
    }
    
}

void deleteFront(List L){ // get help with this
    if(length(L) == 0){
        printf("Called deleteFront() on empty List");
        exit(0);
    }
    if(L == NULL){
        printf("deleteFront() called on NULL list");
    }
    
    if(L->cursor == L->front){
        L->cursor = NULL;
        L->index = -1;
    }
    Node temp = L->front;
    L->front = L->front->next;
    L->front->prev = NULL;
    L->length--;
    L->index--;
    freeNode(&temp);
    
}

void deleteBack(List L){
    
    if(L == NULL){
        printf("Called deleteBack() on empty List");
        exit(1);
    }
    
    if(length(L) == 0){
        printf("Called deleteFront() on empty List");
        exit(1);
    }
    
    if(L->cursor == L->back){ //check if we delete a node w/ cursor
        L->cursor = NULL;
        L->index = -1;
    }
    
    Node temp = L->back;
    if(length(L) <= 1){
        L->back = NULL;
    }
    else{
        L->back = L->back->prev;
        L->back->next = NULL;
    }
    L->length--;
    freeNode(&temp);
}

void delete(List L){
    if(length(L) <= 0){
        printf("delete() called on empty List");
        exit(0);
    }
    if(index(L) == -1){
        printf("delete() called on undefined cursor");
        exit(0);
    }
    if(L->cursor == L->front){
        deleteFront(L);
    }
    else if(L->cursor == L->back){
        deleteBack(L);
    }
    else{
        
        Node N = L->cursor;
        L->cursor->next->prev = L->cursor->prev;
        L->cursor->prev = L->cursor->next;
        L->index = -1;
        L->length--;
        freeNode(&N);
    }
}

void printList(FILE* out, List L) {
    Node N = NULL;
    
    if(L==NULL){
        printf("List Error: calling printList() on NULL List reference\n");
        exit(0);
    }
    
    for(N = L->front; N != NULL; N = N->next){
        fprintf(out,"%d ", N->data);
    }
    fprintf(out,"\n");
}

List copyList(List L){
    //List A is the one being copied
    List new_list = newList();
    //create new node then chain more to the ends
    Node new_node = L->front;
    while(new_node != NULL){
        append(new_list,new_node->data);
        new_node = new_node->next;
    }
    return new_list;
}

int equals(List A, List B){
    int T_or_F = 1;
    
    Node Node_A = A->front;
    Node Node_B = B->front;
    
    //check for null first
    if( A == NULL || B == NULL){
        printf("Calling equals() on NULL list");
        exit(1);
    }
    //both lengths
    if( A->length == B->length){
        while(T_or_F == 1 && Node_A != NULL && Node_B != NULL){
            T_or_F = (Node_A->data == Node_B->data);
            Node_A = Node_A->next;
            Node_B = Node_B->next;
        }
        return T_or_F;
    }
    else{return T_or_F = 0;}
}



