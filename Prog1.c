#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Programa 1
// campos de tamanho fixo em bytes + registros de tamanho fixo em bytes
typedef struct {
	char key[4];
	char lastname[22];
	char firstname[22];
	char address[22];
	char city[12];
	char state[12];
	char zip[12];
	char phone[16];
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

	FILE *data = fopen("/Users/samara/Documents/ORI/Trab1/data.txt", "w+");

	// Ler registros Pessoa
	char option = '\0';

	do {
		readPerson();
		writePersonToFile(data);
		getText("Nova pessoa? (y/n)", &option, 3);
	} while(option=='y');

	return 0;
}

