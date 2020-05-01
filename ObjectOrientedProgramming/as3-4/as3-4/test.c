#include <stdio.h>
#include <string.h>

typedef struct
{
	medication repo[100];
	int length;
}med_repo;

typedef struct {
	char name[50];
	int concentration;
	int quantity;
	int price;
}medication;

void print_all( med_repo *repo)
{
	int i;
	for (i = 0;i < repo->length;i++) {
		printf("Name: %s/", repo->repo[i].name);
		printf(" Concentration: %d/", repo->repo[i].concentration);
		printf(" Quantity: %d/", repo->repo[i].quantity);
		printf(" Price: %d\n", repo->repo[i].price);
	}

}

int test()
{
	med_repo repo;
	medication m;
	m.price = 1;
	m.concentration = 1;
	m.quantity = 1;
	strcpy(m.name, "asd");
	repo.length = 1;
	repo.repo[0] = m;
	print_all(&repo);

	return 0;
}
test();