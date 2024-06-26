#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() {
  List* lista = malloc(sizeof(List));
  lista -> head = NULL;
  lista -> tail = NULL;
  lista -> current = NULL;
  return lista;
}

void * firstList(List * list) 
{
  list -> current = list -> head;
  if(list -> current)
    return list -> current -> data;
  else return NULL;
}

void * nextList(List * list) {
  if(list -> current != NULL)
    list -> current = list -> current -> next;
  if(list -> current != NULL)
      return list -> current -> data;
  else return NULL;
}

void * lastList(List * list) {
  Node* aux = list -> head;
  while(aux -> next != NULL)
      aux = aux -> next;
  list -> current = aux;
  if(list -> current != NULL) return list -> current -> data;
  return NULL;
}

void * prevList(List * list) {
  if(list -> current != NULL)
    list -> current = list -> current -> prev;
  if(list -> current != NULL) return list -> current -> data;
  else return NULL;
}

void pushFront(List * list, void * dato) {
  Node *nuevo_nodo = malloc(sizeof(Node));
  nuevo_nodo -> data = dato;
  nuevo_nodo -> next = NULL;
  nuevo_nodo -> prev = NULL;
  if(list -> current != NULL)
  {
    nuevo_nodo -> next = list -> current;
    list -> current -> prev = nuevo_nodo;
    list -> head = nuevo_nodo;
  }
  else
  {
    list -> head = nuevo_nodo;
    list -> tail = nuevo_nodo;
  }
  
}

void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, void * dato) {
  Node *nuevo_nodo = createNode(dato);
  if(list -> current != NULL)
  {
    nuevo_nodo -> prev = list -> current;
    list -> current -> next = nuevo_nodo;
    list -> tail = nuevo_nodo;
  }
}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list) {
  if(list -> current == NULL) return NULL;
  Node *aux = list -> current;
  void *dato = aux -> data;
  //Si queremos eliminar el primer nodo
  if(aux == list -> head)
  {
    list -> head = aux -> next;
    list -> current = aux -> next;
    aux -> next -> prev = NULL;
  }
  //Si queremos eliminar la cola de la lista
  else if(aux == list -> tail)
  {
    aux -> prev -> next = NULL;
    list -> tail = aux -> prev;
    list -> current = aux -> prev;
  }
    
  //Si queremos eliminar un dato de el medio
  else 
  {
    aux -> prev -> next = aux -> next;
    aux -> next -> prev = aux -> prev;
    list -> current = aux -> next;
  }
  free(aux);
  return dato;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}