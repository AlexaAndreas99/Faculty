#include "controler.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>


medication* create_med(char* name, int price, int qnt, int con) {
	medication* m = malloc(sizeof(medication));
	m->concentration = con;
	m->quantity = qnt;
	m->price = price;
	m->name = malloc(strlen(name) + 1);
	strcpy(m->name, name);
	return m;

}
void destroy_med(medication* m) {
	free(m->name);
	free(m);
}
medication* copy_med(medication* og) {
	medication* m = malloc(sizeof(medication));
	m->concentration = og->concentration;
	m->price = og->price;
	m->quantity = og->quantity;
	m->name = malloc(strlen(og->name) + 1);
	strcpy(m->name, og->name);
	return m;
}





void sort_by_con(medication *copy, int m)
{
	int i,aux=0, ok = 0;
	
	do
	{
		ok = 1;
		for (i = 0;i < m;i++)
			if (copy[i].concentration<copy[i + 1].concentration)
			{
				aux=copy[i].concentration;
				copy[i].concentration=copy[i + 1].concentration;
				copy[i + 1].concentration = aux;
				ok = 0;
			}
	} while (ok == 0);
}

int equal_med(medication* m1, medication* m2) {
	if (strcmp(m1->name, m2->name) == 0 && m1->concentration == m2->concentration)
		return 1;
	else
		return 0;
}
char* get_name(medication* m) {
	char* name = malloc(strlen(m->name)+1);
	strcpy(name, m->name);
	return name;
}
int get_con(medication* m) {
	return m->concentration;
}
int get_qnt(medication* m) {
	return m->quantity;
}
int get_price(medication* m) {
	return m->price;
}

char set_name(medication* m,char* name) {
	return strcpy(m->name, name);

}

int set_price(medication* m, int price) {
	return m->price = price;
}

int set_qnt(medication* m, int qnt) {
	return m->quantity = qnt;
}

int add_qnt(medication* m1, medication* m2) {
	int s = m2->quantity;
	return m1->quantity = m1->quantity + s;
}