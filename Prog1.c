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
int personSize;

FILE *file;
FILE *secondaryIndexFile;

void fillString(char *variable, int size){
	for(int i = 0; i < size - 3; i++){
		if(variable[i] == '\0'){
			variable[i] = ' ';
			variable[i + 1] = '\0';
		}
	}
}

void getInput(char *message, char *variable, int size){
    printf("\n%s", message);
    fgets(variable, sizeof(char) * size, stdin);
    sscanf(variable, "%[^\n]", variable);
    fillString(variable, size);
}

// Leitura de um registro Pessoa
void readPerson() {
	getInput("Key: ", p.key, sizeof(p.key)); 
	getInput("Last name: ", p.lastname, sizeof(p.lastname));
	getInput("First name: ", p.firstname, sizeof(p.firstname));
	getInput("Address: ", p.address, sizeof(p.address));
	getInput("City: ", p.city, sizeof(p.city));
	getInput("State: ", p.state, sizeof(p.state));
	getInput("Zip code: ", p.zip, sizeof(p.zip));
	getInput("Phone: ", p.phone, sizeof(p.phone));
}

void writePersonToFile() {
	//fseek(file, 0, SEEK_SET);
	fwrite(&p.key, sizeof(char), sizeof(p.key)/sizeof(char) - 1, file);
	fwrite(&p.lastname, sizeof(char), sizeof(p.lastname)/sizeof(char) - 1, file);
	fwrite(&p.firstname, sizeof(char), sizeof(p.firstname)/sizeof(char) - 1, file);
	fwrite(&p.address, sizeof(char), sizeof(p.address)/sizeof(char) - 1, file);
	fwrite(&p.city, sizeof(char), sizeof(p.city)/sizeof(char) - 1, file);
	fwrite(&p.state, sizeof(char), sizeof(p.state)/sizeof(char) - 1, file);
	fwrite(&p.zip, sizeof(char), sizeof(p.zip)/sizeof(char) - 1, file);
	fwrite(&p.phone, sizeof(char), sizeof(p.phone)/sizeof(char) - 1, file);
}

void writePersonToIndexFile() {
	fwrite(&p.firstname, sizeof(char), sizeof(p.firstname)/sizeof(char) - 1, file);
	fwrite(&p.key, sizeof(char), sizeof(p.key)/sizeof(char) - 1, file);
}

char displayDataObject(){
	char next = '\0';

	printf("Key: %s\n", p.key);
	printf("Last name: %s\n", p.lastname);
	printf("First name: %s\n", p.firstname);
	printf("Address: %s\n", p.address);
	printf("City: %s\n", p.city);
	printf("State: %s\n", p.state);
	printf("Zip code: %s\n", p.zip);
	printf("Phone: %s\n", p.phone);
	printf("Pressione enter para visualizar o proximo registro.");
	scanf("%c", &next);

	return next;
}

int retrieveDataObject(){
	int returnValue = 0;

	if(fread(p.key, sizeof(char), sizeof(p.key)/sizeof(char) - 1, file) == 3){
		returnValue = 1;
		fread(p.lastname, sizeof(char), sizeof(p.lastname)/sizeof(char) - 1, file);
		fread(p.firstname, sizeof(char), sizeof(p.firstname)/sizeof(char) - 1, file);
		fread(p.address, sizeof(char), sizeof(p.address)/sizeof(char) - 1, file);
		fread(p.city, sizeof(char), sizeof(p.city)/sizeof(char) - 1, file);
		fread(p.state, sizeof(char), sizeof(p.state)/sizeof(char) - 1, file);
		fread(p.zip, sizeof(char), sizeof(p.zip)/sizeof(char) - 1, file);
		fread(p.phone, sizeof(char), sizeof(p.phone)/sizeof(char)- 1, file);
	}

	return returnValue;
}

void searchByKey(int key) {
	fseek(file, 0, SEEK_SET);
	while(retrieveDataObject()) {
		printf("entered searchByKey while \n");
		if(atoi(p.key) >= key){
			printf("entered if\n");
			fseek(file, - personSize, SEEK_CUR);
			return;
		}
	}
	fseek(file, 0, SEEK_END);
}

void writePersonSortedByKey() {
	person p2;
	person pcopy;
	p2 = p;
	printf("p2 key %s\n", p2.key);
	searchByKey(atoi(p.key));
	int retrieveDataObjectReturnValue;
	do {
		retrieveDataObjectReturnValue = retrieveDataObject();
		if(retrieveDataObjectReturnValue) {
			fseek(file, - personSize, SEEK_CUR);
		}
		// Trocar p com p2
		pcopy = p;
		p = p2;
		p2 = pcopy;
		writePersonToFile();
	} while(retrieveDataObjectReturnValue);
}

void writePersonSortedByName() {
	person p2;
	person pcopy;
	p2 = p;
	printf("p2 key %s\n", p2.firstname);
	searchByName(atoi(p.firstname));
	int retrieveDataObjectReturnValue;
	do {
		retrieveDataObjectReturnValue = retrieveDataObjectIndex();
		if(retrieveDataObjectReturnValue) {
			fseek(file, - personSize, SEEK_CUR);
		}
		// Trocar p com p2
		pcopy = p;
		p = p2;
		p2 = pcopy;
		writePersonToIndexFile();
	} while(retrieveDataObjectReturnValue);
}

void writeData(){
	char option = '\0';

	do {
		readPerson();
		writePersonSortedByKey();
		writePersonToIndexFile();
		printf("Nova pessoa? (y/n) ");
		scanf("%c", &option);
		getchar();
	} while(option=='y');
}

int retrieveDataObjectIndex(){
	int returnValue = 0;

	if(fread(p.firstname, sizeof(char), sizeof(p.firstname)/sizeof(char) - 1, secondaryIndexFile) == 21){
		returnValue = 1;
		fread(p.key, sizeof(char), sizeof(p.key)/sizeof(char) - 1, secondaryIndexFile);
	}

	return returnValue;
}

void displayData(){
	char next = '\n';
	while(retrieveDataObject() && next == '\n'){
		next = displayDataObject();
	}
	if(feof(file)){
		printf("\nEnd of file\n");
	}
}

void displayDataObjectByNumber(int dataObjectNumber){
	int dataObjectPosition = 0;

	dataObjectPosition = personSize * (dataObjectNumber);

	fseek(file, dataObjectPosition, SEEK_SET);
	retrieveDataObject();
	displayDataObject();
}

void displayDataObjectByKey(int dataObjectKey){
	while(retrieveDataObject()) {
		if(atoi(p.key) == dataObjectKey){
			displayDataObject();
			break;
		}
	}
}

int menu(){
	//Menu
	int option;
	printf("Opcoes:\n");
	printf("(1) Entrar registros\n");
	printf("(2) Recuperar dados\n");
	printf("(3) Recuperar registro especifico por numero\n");
	printf("(4) Recuperar registro especifico por key\n");
	printf("(0) Sair\n");
	scanf("%d", &option);
	getchar();
	return option;
}

void calculatePersonSize() {
	personSize = 0;
	personSize += sizeof(p.key)/sizeof(char) - 1;
	personSize += sizeof(p.lastname)/sizeof(char) - 1;
	personSize += sizeof(p.firstname)/sizeof(char) - 1;
	personSize += sizeof(p.address)/sizeof(char) - 1;
	personSize += sizeof(p.city)/sizeof(char) - 1;
	personSize += sizeof(p.state)/sizeof(char) - 1;
	personSize += sizeof(p.zip)/sizeof(char) - 1;
	personSize += sizeof(p.phone)/sizeof(char)- 1;
}

int main() {

	int menuItem;
	int dataObjectNumber;
	int dataObjectKey;

	calculatePersonSize();

	do {
		menuItem = menu();
		switch(menuItem) {
			case 1 :
				// Ler registros Pessoa
				file = fopen("/Users/samara/Documents/ORI/Trab1/data.bin", "wb+");
				secondaryIndexFile = fopen("/Users/samara/Documents/ORI/Trab1/data.bin", "wb");
				writeData();
				fclose(file);
				break;

			case 2 :
				//Recuperar dados
				file = fopen("/Users/samara/Documents/ORI/Trab1/data.bin", "rb");
				displayData();
				fclose(file);
				break;

			case 3 :
				//Recuperar registro especifico
				file = fopen("/Users/samara/Documents/ORI/Trab1/data.bin", "rb");
				printf("Numero do registro: ");
				scanf("%d", &dataObjectNumber);
				getchar();
				displayDataObjectByNumber(dataObjectNumber);
				fclose(file);
				break;
			case 4 :
				//Recuperar registro especifico
				file = fopen("/Users/samara/Documents/ORI/Trab1/data.txt", "rb");
				printf("Key do registro: ");
				scanf("%d", &dataObjectKey);
				getchar();
				displayDataObjectByKey(dataObjectKey);
				fclose(file);
				break;
			case 5 :

		}
	} while(menuItem != 0);

	return 0;
}

