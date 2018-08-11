//Norbert Manatad
//nmanatad
//List.c
//cmps101 from pa2
#include <stdio.h>
#include <stdlib.h>
#include "List.h"

typedef struct NodeObj{
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
} ListObj;

Node newNode(int data){
        Node node = malloc(sizeof(NodeObj));
        if(node == NULL){
                return NULL;
        }
        node->next = NULL;
        node->prev = NULL;
        node->data = data;
        return node;
}

void freeNode(Node* pN){
        if(pN != NULL && *pN != NULL){
                free(*pN);
                *pN = NULL;
        }
}

List newList(void){
        List list;
        list = malloc(sizeof(ListObj));
        if(list == NULL){
                return NULL;
        }
        list->front = NULL;
        list->back = NULL;
        list->cursor = NULL;
        list->length = 0;
        list->index = -1;
        return list;
}
void freeList(List* pL){

   if(pL!=NULL && *pL!=NULL) {
      while( length(*pL) > 0 ) {
         deleteFront(*pL);
      }
      //clear(*pL);
      free(*pL);
      *pL = NULL;
   }
}

int length(List L){
        return L->length;
}

int getIndex(List L){
        return L->index;
}

int front(List L){
        return L->front->data;
}

int back(List L){
        return L->back->data;
}

int get(List L){
        return L->cursor->data;
}
int equals(List A, List B){
        if(A == NULL || B == NULL){
                printf("List Error: calling equals() on NULL List reference\n");
                exit(1);
            }
                Node ListThis = A->front;
                Node ListL = B->front;

                int counter = 0;
                int lengthThis = A->length;
                int lengthL = B->length;
                if(lengthThis == lengthL){
                        for( ; ListL != NULL; ListL = ListL->next){
                                if(ListL->data == ListThis->data){
                                        counter++;
                                }
                                ListThis = ListThis->next;
                        }
                }
                if(counter == lengthL){
                        return 1;
                } else {
                        return 0;
                }
        }

void clear(List L){
        L->front = NULL;
        L->back = NULL;
        L->cursor = NULL;
        L->index = -1;
        L->length = 0;
}
   void moveFront(List L){
                if (L->length != 0){
                        L->cursor = L->front;
                        L->index = 0;
                } else {
                        ;
                }
        }

        void moveBack(List L){
                if (L->length != 0){
                        L->cursor = L->back;
                        L->index = L->length;
                } else {
                        ;
                }
        }

        void movePrev(List L){
                if(L->cursor != NULL && L->cursor != L->front){
                        L->cursor = L->cursor->prev;
                        L->index--;
                } else if(L->cursor != NULL && L->cursor == L->front){
                        L->cursor = NULL;
                        L->index = -1;
                }
        }


        void moveNext(List L){
                if(L->cursor != NULL && L->cursor != L->back){
                        L->cursor = L->cursor->next;
                        L->index++;
                }else if(L->cursor != NULL && L->cursor == L->back){
                        L->cursor = NULL;
                        L->index = -1;
                }
        }
void prepend(List L, int data){
                if(L->length != 0){
                        Node newNod = newNode(data);

                        L->front->prev = newNod;
                        newNod->next = L->front;
                        newNod->prev = NULL;
                        L->front = newNod;
                        L->length++;
                }else{
                        Node newNod = newNode(data);
                        L->front = newNod;
                        L->back = newNod;
                        L->length++;
                }
        }
        void append(List L, int data){
                if(L->length != 0){
                        Node newNod = newNode(data);

                        newNod->prev = L->back;
                        newNod->next = NULL;
                        L->back->next = newNod;
                        L->back = newNod;
                        L->length++;
                }else{
                        Node newNod = newNode(data);
                        L->back = newNod;
                        L->front = newNod;
                        L->length++;
                }
        }
void insertBefore(List L, int data){
                if(L->length > 0 && L->index >= 0){
                        Node temp = newNode(data);
                        if(L->cursor->prev != NULL){

                                Node holder;
                                holder = L->cursor->prev;
                                L->cursor->prev->next = temp;
                                L->cursor->prev = temp;
                                temp->next = L->cursor;
                                //cursor.prev.next = temp;
                                temp->prev = holder;
                                L->length++;

                        } else {
                                //Node temp = new Node(data);
                                L->cursor->prev = temp;
                                temp->next = L->cursor;
                                temp->prev = NULL;
                                L->front = temp;
                                L->length++;
                        }

                }
        }

        void insertAfter(List L, int data){
                if(L->length > 0 && L->index >= 0){
                        Node temp = newNode(data);
                        if(L->cursor->next != NULL){
                                Node holder;
                                holder  = L->cursor->next;
                                L->cursor->next->prev = temp;
                                L->cursor->next = temp;
                                temp->prev = L->cursor;
                                temp->next = holder;
                                L->length++;
                        } else {
                                L->cursor->next = temp;
                                temp->prev = L->cursor;
                                temp->next = NULL;
                                L->back = temp;
                                L->length++;
                        }
                }
        }
void deleteFront(List L){
                Node temp = L->front;
                if(L->length == 1){
                    temp = NULL;
                    L->length--;
                } else {
                    temp->next->prev = NULL;
                    //temp = NULL;
                    L->front = temp->next;
                    L->length--;
                }
                freeNode(&temp);
        }

        void deleteBack(List L){
                Node temp = L->back;
                if(L->length == 1){
                    temp = NULL;
                    L->length--;
                } else {
                        temp->prev->next = NULL;
                        L->back = temp->prev;
                        L->length--;
                }
                freeNode(&temp);

        }

        void delete(List L){
                if (L->length > 0 && L->index >= 0){
                        L->cursor = NULL;
                        L->length--;
                }
        }

        void printList(FILE* out, List L){
                Node N = NULL;

                if(L == NULL){
                    printf("List Error: calling printList() on NULL List reference\n");
                    exit(1);
                }

                for(N = L->front; N != NULL; N = N->next){
                    fprintf(out,"%d ", N->data);
                }
                fprintf(out, "\n");
        }
        List copyList(List L){
                List retList = newList();
                Node temp = L->front;
                while(temp != NULL){
                        append(retList, temp->data);
                        temp = temp->next;
                }
                return retList;
        }

