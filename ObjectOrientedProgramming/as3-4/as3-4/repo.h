#pragma once
#include "Windows.h"
typedef void* TElem;
typedef struct{
	TElem* elems;
	int size;
	int cap;

}DV;

/*
creator
*/
DV* create_dv(int);
/*
destructor
*/
void destroy_DV(DV*, void(*destroy)(TElem));
/*
adds an item to the repo
input: repo, item,copy function,equal function,add quantity function
output: -
*/
void add_DV(DV*, TElem,TElem(*copy)(TElem), TElem(*equal)(TElem, TElem), int(*add_qnt)(TElem, TElem));
int get_size(DV*);
int set_size(DV* dv, int size);

/* 
searches for an item in list and returns it
input: repo,item,equal function,copy function
output: copy of item if found
		NULL if not found
*/
TElem search_DV(DV*, TElem, int(*equal)(TElem, TElem), TElem(*copy)(TElem));
/*
removes an item from the repo
input: repo,item,equal unction,destroy function
output: -
*/
void remove_DV(DV*, TElem, int(*equal)(TElem, TElem),void(*destroy)(TElem));
/*
updates the price of an item
input: repo,item,equal function,set price function
output: -
*/
void update_price(DV* , TElem, int(*equal)(TElem, TElem), int(*set_price)(TElem, TElem),int);
/*
updates the quantity of an item
input: repo,item,equal function,set quantity function
output: -
*/
void update_qnt(DV*, TElem, int(*equal)(TElem, TElem), int(*set_qnt)(TElem, TElem), int);
/*
makes a new list with the partial matched items name
input: repo, copy,string
output: copy with found items
*/
void search(DV*, DV*,char);
/*
sorts repo by name
input: repo
output: the sorted list
*/
void sort_by_name(DV*);
/*
makes a new list with the quantity lower than a given int
input: repo, copy, int
output: copy with found items
*/

void search_below(DV*, DV*, int);