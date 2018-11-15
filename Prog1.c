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
	fgets(p.key, 2, stdin);

	printf("Last name: ");
	scanf("%s", &p.lastname);

	printf("First name: ");
	scanf("%s", &p.firstname);

	printf("Address: ");
	scanf("%s", &p.address);

	printf("City: ");
	scanf("%s", &p.city);

	printf("State: ");
	scanf("%s", &p.state);	

	printf("Zip Code: ");
	scanf("%s", &p.zip);

	printf("Phone: ");
	scanf("%s", &p.phone);
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

