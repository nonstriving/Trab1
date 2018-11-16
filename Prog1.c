#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Programa 1
// campos de tamanho fixo em bytes + registros de tamanho fixo em bytes
typedef struct {
	char key[4]; // Ultimo caracter armazena '\n'
	char lastname[22];
	char firstname[22];
	char address[22];
	char city[12];
	char state[12];
	char zip[12];
	char phone[16];
} person;

person p;

FILE *file;

void fillString(char *variable, int size){
	for(int i = 0; i < size - 2; i++){
		if(variable[i] == '\0'){
			variable[i] = ' ';
			variable[i + 1] = '\0';
		}
	}
}

void getInput(char *message, char *variable, int size){
    printf("\n %s: ", message);
    fgets(variable, sizeof(char) * size, stdin);
    sscanf(variable, "%[^\n]", variable);
    fillString(variable, size);
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

void writeData(){
	char option = '\0';

	do {
		readPerson();
		writePersonToFile();
		getInput("Nova pessoa? (y/n)", &option, 3);
	} while(option=='y');
}

void displayData(){
	printf("Key: %s\n", p.key);
	printf("Last name: %s\n", p.lastname);
	printf("First name: %s\n", p.firstname);
	printf("Address: %s\n", p.address);
	printf("City: %s\n", p.city);
	printf("State: %s\n", p.state);
	printf("Zip code: %s\n", p.zip);
	printf("Phone: %s\n", p.phone);
	printf("\n");
}
void retrieveData(){

	while(fread(p.key, strlen(p.key) - 1, 1, file) == 1){
		fread(p.lastname, strlen(p.lastname) - 1, 1, file);
		fread(p.firstname, strlen(p.firstname) - 1, 1, file);
		fread(p.address, strlen(p.address) - 1, 1, file);
		fread(p.city, strlen(p.city) - 1, 1, file);
		fread(p.state, strlen(p.state) - 1, 1, file);
		fread(p.zip, strlen(p.zip) - 1, 1, file);
		fread(p.phone, strlen(p.phone) - 1, 1, file);
		displayData();
	}
	if(feof(file)){
		printf("\nEnd of file\n");
	}
}

int main() {

	// Ler registros Pessoa
	file = fopen("/Users/samara/Documents/ORI/Trab1/data.txt", "w");
	writeData();
	fclose(file);

	//Recuperar dados
	file = fopen("/Users/samara/Documents/ORI/Trab1/data.txt", "r");
	retrieveData();
	fclose(file);

	return 0;
}

