#include <stdio.h>
#include <stdlib.h>
// Programa 1
// campos de tamanho fixo em bytes + registros de tamanho fixo em bytes
typedef struct {
	char key[2];
	char lastname[20];
	char firstname[20];
	char address[20];
	char city[10];
	char state[10];
	char zip[10];
	char phone[14];
} person;

person p;

// Leitura de um registro Pessoa
void readPerson() {

	printf("Key: ");
	fgets(p.key, sizeof(p.key), stdin);

	printf("Last name: ");
	fgets(p.lastname, sizeof(p.lastname), stdin);

	printf("First name: ");
	fgets(p.firstname, sizeof(p.firstname), stdin);

	printf("Address: ");
	fgets(p.address, sizeof(p.address), stdin);

	printf("City: ");
	fgets(p.city, sizeof(p.city), stdin);

	printf("State: ");
	fgets(p.state, sizeof(p.state), stdin);

	printf("Zip Code: ");
	fgets(p.zip, sizeof(p.zip), stdin);

	printf("Phone: ");
	fgets(p.phone, sizeof(p.phone), stdin);
}

void writePersonToFile(FILE *file) {
	fwrite(&p.key, sizeof(char), sizeof(p.key)/sizeof(char), file);
	fwrite(&p.lastname, sizeof(char), sizeof(p.lastname)/sizeof(char), file);
	fwrite(&p.firstname, sizeof(char), sizeof(p.firstname)/sizeof(char), file);
	fwrite(&p.address, sizeof(char), sizeof(p.address)/sizeof(char), file);
	fwrite(&p.city, sizeof(char), sizeof(p.city)/sizeof(char), file);
	fwrite(&p.state, sizeof(char), sizeof(p.state)/sizeof(char), file);
	fwrite(&p.zip, sizeof(char), sizeof(p.zip)/sizeof(char), file);
	fwrite(&p.phone, sizeof(char), sizeof(p.phone)/sizeof(char), file);
}

int main() {

	FILE *data = fopen("/Users/samara/Documents/ORI/Trab1/data.txt", "rw");

	// Ler registros Pessoa
	char option;

	do {
		readPerson();
		writePersonToFile(data);
		printf("Nova pessoa? (y/n)\n");
		scanf("%c", &option);
	} while(option=='y');

	return 0;
}

