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

FILE *file = fopen("/Users/samara/Documents/ORI/Trab1/data.txt", "a");

void getInput(char *message, char *variable, int size){
    printf("\n %s: ", message);
    fgets(variable, sizeof(char) * size, stdin);
    sscanf(variable, "%[^\n]", variable);
}

// Leitura de um registro Pessoa
void readPerson() {
	getInput("Key", p.key, sizeof(p.key)); 
	getInput("Last name", p.lastname, sizeof(p.lastname));
	getInput("First name", p.firstname, sizeof(p.firstname));
	getInput("Address", p.address, sizeof(p.address));
	getInput("City", p.city, sizeof(p.city));
	getInput("State", p.state, sizeof(p.state));
	getInput("Zip code", p.zip, sizeof(p.zip));
	getInput("Phone", p.phone, sizeof(p.phone));
}

void writePersonToFile() {
	//fseek(file, 0, SEEK_SET);
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

	// Ler registros Pessoa
	char option = '\0';

	do {
		readPerson();
		writePersonToFile();
		getInput("Nova pessoa? (y/n)", &option, 3);
	} while(option=='y');

	//fclose(data);

	return 0;
}

