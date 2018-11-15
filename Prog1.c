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

void getText(char *message, char *variable, int size){
    printf("\n %s: ", message);
    fgets(variable, sizeof(char) * size, stdin);
    sscanf(variable, "%[^\n]", variable);
}

// Leitura de um registro Pessoa
void readPerson() {

	getText("Key", p.key, sizeof(p.key));
	getText("Last name", p.lastname, sizeof(p.lastname));
	getText("First name", p.firstname, sizeof(p.firstname));
	getText("Address", p.address, sizeof(p.address));
	getText("City", p.city, sizeof(p.city));
	getText("State", p.state, sizeof(p.state));
	getText("Zip code", p.zip, sizeof(p.zip));
	getText("Phone", p.phone, sizeof(p.phone));
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

