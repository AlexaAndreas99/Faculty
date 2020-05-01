#include "repo.h"
#include <stdlib.h>
#include <Windows.h>
#include "controler.h"
DV* create_dv(int cap) {
	DV* dv = malloc(sizeof(DV));
	dv->size = 0;
	dv->cap = cap;
	dv->elems = malloc(sizeof(TElem)*cap);
	return dv;
}

void add_DV(DV* dv, TElem e, TElem(*copy)(TElem), TElem(*equal)(TElem, TElem), int(*add_qnt)(TElem, TElem)) {
	TElem cpy = copy(e);
	if (dv->size == dv->cap) {
		TElem* n_elems = malloc(sizeof(TElem)*dv->cap * 2);
		int i = 0;
		for (; i < dv->size; i++) {
			n_elems[i] = dv->elems[i];
		}
		free(dv->elems);
		dv->elems = n_elems;
	}

	int i = 0,ok=0;
	for (; i < dv->size; i++) {
		if (equal(dv->elems[i], e) == 1)
		{
			ok = 1;
			add_qnt(dv->elems[i], e);
		}
	}
	if (ok == 0) {
		dv->elems[dv->size] = cpy;
		dv->size++;
	}
	//free(cpy);
}

int get_size(DV* dv){
	return dv->size;
}

int set_size(DV* dv, int size) {
	return dv->size = size;
}
void destroy_DV(DV* dv,void(*destroy)(TElem)){
	int i = 0;
	for (; i < dv->size; i++) {
		destroy(dv->elems[i]);
	}
	free(dv->elems);
	free(dv);
}

TElem search_DV(DV* dv, TElem e, int(*equal)(TElem, TElem), TElem(*copy)(TElem)) {
	int i = 0;
	for (; i < dv->size; i++) {
		if (equal(e, dv->elems[i]) == 1) {
			return copy(dv->elems[i]);
		}
	}
	return NULL;
}

void remove_DV(DV* dv, TElem e, int(*equal)(TElem, TElem), void(*destroy)(TElem)) {
	int i = 0;
	int pos = -1;
	for (; i < dv->size; i++) {
		if (equal(e, dv->elems[i]) == 1) {
			pos = i;
			break;
		}
	}
	if (pos != -1) {
		destroy(dv->elems[pos]);
		i = pos;
		for (; i < dv->size - 1; i++) {
			dv->elems[i] = dv->elems[i + 1];
		}
		dv->size--;
	}
}

void update_price(DV* dv, TElem e, int(*equal)(TElem, TElem),int(*set_price)(TElem,TElem),int price) {
	int i = 0;
	for (; i < dv->size; i++) {
		if (equal(e, dv->elems[i]) == 1) {
			set_price(dv->elems[i], price);
		}
	}

}
void update_qnt(DV* dv, TElem e, int(*equal)(TElem, TElem), int(*set_qnt)(TElem, TElem), int qnt) {
	int i = 0;
	for (; i < dv->size; i++) {
		if (equal(e, dv->elems[i]) == 1) {
			set_qnt(dv->elems[i], qnt);
		}
	}

}

void search(DV* dv, DV* copy, char str[50])  {
	int i=0;
	char *ret;
	for (; i <get_size(dv); i++)
	{
		ret = strstr(get_name(dv->elems[i]), str);
		if (ret != 0)
		{
			add_DV(copy, dv->elems[i], copy_med, equal_med, add_qnt);
		}
	}

}

void sort_by_name(DV* dv) {
	int i, ok = 0;
	char aux[50];
	medication* m;
	do
	{
		ok = 1;
		for (i = 0; i < get_size(dv)-1; i++)
			
			if (strcmp(get_name(dv->elems[i]), get_name(dv->elems[i+1])) == 1)
			{
				m = dv->elems[i];
				dv->elems[i] = dv->elems[i + 1];
				dv->elems[i + 1] = m;
				
				ok = 0;
			}
	} while (ok == 0);
	//destroy_med(m);
}

void search_below(DV* dv, DV* copy, int qnt) {
	int i = 0;
	for (; i < get_size(dv); i++) {
	
		if (get_qnt(dv->elems[i]) < qnt) {
			add_DV(copy, dv->elems[i], copy_med, equal_med, add_qnt);
		}
	}
}