#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "controler.h"
#include <assert.h>
#include<crtdbg.h>
#include <Windows.h>
#include "repo.h"
#define _CRTDBG_MAP_ALLOC
#include "undo.h"

void print_all(DV* dv)
{
	int i;
	for (i = 0;i <get_size(dv);i++) {
		printf("Name: %s/", get_name(dv->elems[i]));
		printf(" Concentration: %d/", get_con(dv->elems[i]));
		printf(" Quantity: %d/", get_qnt(dv->elems[i]));
		printf(" Price: %d\n", get_price(dv->elems[i]));
	}

}

void set_up(DV* dv)
{
	medication* m = create_med("ketonal", 13, 12, 1200);
	add_DV(dv, m, copy_med, equal_med, add_qnt);
	destroy_med(m);
	
	m = create_med("augmentin", 15, 12, 2000);
	add_DV(dv, m, copy_med, equal_med, add_qnt);
	destroy_med(m);

	m = create_med("paracetamol", 10, 12, 300);
	add_DV(dv, m, copy_med, equal_med, add_qnt);
	destroy_med(m);

	m = create_med("ibuprofen", 13, 12, 600);
	add_DV(dv, m, copy_med, equal_med, add_qnt);
	destroy_med(m);

	 m = create_med("aspirin", 8, 12, 500);
	add_DV(dv, m, copy_med, equal_med, add_qnt);
	destroy_med(m);

	 m = create_med("no-spa", 10, 12, 400);
	add_DV(dv, m, copy_med, equal_med, add_qnt);
	destroy_med(m);

	 m = create_med("nurofen", 8, 12, 200);
	add_DV(dv, m, copy_med, equal_med, add_qnt);
	destroy_med(m);

	m = create_med("tagremin", 15, 12, 400);
	add_DV(dv, m, copy_med, equal_med, add_qnt);
	destroy_med(m);

	m = create_med("algocalmin", 14, 10, 400);
	add_DV(dv, m, copy_med, equal_med, add_qnt);
	destroy_med(m);

	m = create_med("nurofen", 12, 24, 400);
	add_DV(dv, m, copy_med, equal_med, add_qnt);
	destroy_med(m);
}


void menu() {
	printf("1. Add medication\n");
	printf("2. Delete medication\n");
	printf("3. Update medication price\n");
	printf("4. Update medication quantity\n");
	printf("5. Show all available medications containing a given string\n");
	printf("6. Show those medication that are less than a given value\n");
	printf("7. Show all medications\n");
	printf("8. Undo\n");
	printf("9. Redo\n");
	printf("0. Exit\n");
	printf("\n");

}
void test_med() {
	medication* m = create_med("Nurofen", 12, 24, 200);
	char* name = get_name(m);
	assert(strcmp(name, "Nurofen") == 0);
	free(name);
	destroy_med(m);
	}
void test_repo() {
	DV* dv = create_dv(20);
	assert(get_size(dv) == 0);

	medication* m = create_med("Nurofen", 12, 24, 200);
	add_DV(dv, m, copy_med,equal_med,add_qnt);
	assert(get_size(dv) == 1);

	medication* f_cheie = create_med("Nurofen", 12, 24, 200);
	medication* f_obt = search_DV(dv, f_cheie, equal_med, copy_med);
	assert(equal_med(f_obt, m) == 1);

	remove_DV(dv, f_cheie, equal_med, destroy_med);
	assert(get_size(dv) == 0);



	destroy_med(f_cheie);
	destroy_med(f_obt);
	destroy_med(m);
	destroy_DV(dv,destroy_med);
}
int main()
{
	int n = -1,m=-1, unu = 1, con, qnt, price, v[10], ok = 0,nr;
	char input,name[50],str[50];
	test_med();
	test_repo();
	
	DV* dv=create_dv(20);
	set_up(dv);
	operation undol[100],undor[100];
	int len = -1,lenr=-1;
	n++;

	while (unu == 1)
	{
		menu();
		scanf("%c", &input);
		
		if (input=='1')
		{ 
			printf("Insert the medication name: ");
			scanf("%s", &name);

			printf("Insert the medication concentration: ");
			scanf("%d", &con);

			printf("Insert the medication quantity: ");
			scanf("%d", &qnt);

			printf("Insert the medication price: ");
			scanf("%d", &price);
			medication* m = create_med(name, price, qnt, con);
			add_DV(dv, m, copy_med, equal_med, add_qnt);
			
			
			len++;
			strcpy(undol[len].op, "delete");
			strcpy(undol[len].name, get_name(m));
			undol[len].concentration = get_con(m);
			destroy_med(m);
		}
		if (input == '7')
			print_all(dv);
		
		if (input == '2')
		{	
			nr=get_size(dv);

			printf("Insert the medication name you want to delete: ");
			scanf("%s", &name);

			printf("Insert the medication concentration you want to delete: ");
			scanf("%d", &con);
			medication* m= create_med(name, 1, 1, con);
			remove_DV(dv, m, equal_med, destroy_med);
			if (nr== get_size(dv))
				printf("The requested medication does not exist!\n");
				
			

			len++;
			strcpy(undol[len].op, "add");
			strcpy(undol[len].name, get_name(m));
			undol[len].concentration = get_con(m);
			undol[len].price = get_price(m);
			undol[len].quantity = get_qnt(m);
			destroy_med(m);
		}
		
		if (input == '3')
		{	
			printf("Insert the medication name you want to change: ");
			scanf("%s", &name);

			printf("Insert the medication concentration you want to change: ");
			scanf("%d", &con);

			printf("Insert the new medication price: ");
			scanf("%d", &price);
			medication* m = create_med(name, 1, 1, con);

			len++;
			strcpy(undol[len].op, "update");
			strcpy(undol[len].name, get_name(m));
			undol[len].concentration = get_con(m);
			undol[len].price = get_price(m);
			undol[len].quantity = get_qnt(m);


			update_price(dv, m, equal_med, set_price, price);
			destroy_med(m);
			
		}
		if (input == '0') {
			destroy_DV(dv, destroy_med);
			return 0;
		}
		if (input == '4')
		{
			printf("Insert the medication name you want to change: ");
			scanf("%s", &name);

			printf("Insert the medication concentration you want to change: ");
			scanf("%d", &con);

			printf("Insert the new medication quantity: ");
			scanf("%d", &qnt);

			medication* m = create_med(name, 1, 1, con);

			update_qnt(dv, m, equal_med, set_qnt, qnt);
			destroy_med(m);

			


		}
		
		if (input == '5')
		{
			DV* copy = create_dv(20);
			printf("Insert a string: ");
			//scanf("%s", &str);
			_fgetchar();
			fgets(str, 50, stdin);

			str[strlen(str) - 1] = '\0';

			search(dv, copy, str);
			sort_by_name(copy);
			print_all(copy);
			destroy_DV(copy, destroy_med);
			
		}
		
		if (input == '6') {
			DV* copy = create_dv(20);
			printf("Please provide a value: ");
			scanf("%d", &qnt);

			search_below(dv, copy, qnt);
			print_all(copy);
			destroy_DV(copy, destroy_med);
		}
		if (input == '8')
		{
		
			if (len < 0)
				printf("No more undos!\n");
			else
			{
				if (strcmp(undol[len].op, "delete") == 0)
				{
					medication* m = create_med(undol[len].name, 1, 1, undol[len].concentration);
					remove_DV(dv, m, equal_med, destroy_med);
					len--;
					
					lenr++;
					strcpy(undor[lenr].op, "add");
					strcpy(undor[lenr].name, get_name(m));
					undor[lenr].concentration = get_con(m);
					undor[lenr].price = get_price(m);
					undor[lenr].quantity = get_qnt(m);

					destroy_med(m);
				}
				if (strcmp(undol[len].op, "add") == 0)
				{
					medication* m = create_med(undol[len].name, undol[len].price, undol[len].quantity, undol[len].concentration);
					add_DV(dv, m, copy_med, equal_med, add_qnt);
					len--;

					lenr++;
					strcpy(undor[lenr].op, "delete");
					strcpy(undor[lenr].name, get_name(m));
					undor[lenr].concentration = get_con(m);

					destroy_med(m);

				}
				if (strcmp(undol[len].op, "update") == 0)
				{	
					medication* m = create_med(undol[len].name, undol[len].price, undol[len].quantity, undol[len].concentration);
					update_price(dv, m, equal_med, set_price,undol[len].price);
					len --;

					lenr++;
					strcpy(undor[lenr].op, "update");
					strcpy(undor[lenr].name, get_name(m));
					undor[lenr].concentration = get_con(m);
					undor[lenr].price = get_price(m);
					undor[lenr].quantity = get_qnt(m);



					destroy_med(m);

				}
			}
		}
		if (input == '9') {
			
			if (lenr <0)
				printf("No more redos!\n");
			else
			{
				if (strcmp(undor[lenr].op, "add") == 0)
				{
					medication* m = create_med(undor[lenr].name, undor[lenr].price, undor[lenr].quantity, undor[lenr].concentration);
					add_DV(dv, m, copy_med, equal_med, add_qnt);
					lenr--;
					destroy_med(m);

				}
				if (strcmp(undor[lenr].op, "delete") == 0)
				{
					medication* m = create_med(undor[lenr].name, 1, 1, undor[lenr].concentration);
					remove_DV(dv, m, equal_med, destroy_med);
					lenr--;
					destroy_med(m);
				}
				if (strcmp(undor[lenr].op, "update") == 0)
				{
					medication* m = create_med(undor[lenr].name, undor[lenr].price, undor[lenr].quantity, undor[lenr].concentration);
					update_price(dv, m, equal_med, set_price, undor[lenr].price);
					lenr--;

				}
			}
		}
	
	}
	
	_CrtDumpMemoryLeaks();
	return 0;
}