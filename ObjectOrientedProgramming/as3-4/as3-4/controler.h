#pragma once

typedef struct {
	char* name;
	int concentration;
	int quantity;
	int price;
}medication;


medication* create_med( char*, int , int , int );
medication* copy_med(medication*);
void destroy_med(medication*);
void delete(medication *repo, int *n, int name, int con);
void sort_by_con(medication *copy, int m);
int equal_med(medication*, medication*);
char* get_name(medication*);
int get_con(medication*);
int get_qnt(medication*);
int get_price(medication*);
int set_price(medication*, int);
int set_qnt(medication* , int );
int add_qnt(medication* , medication* ); 
char set_name(medication*);