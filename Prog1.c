// Programa 1
// campos de tamanho fixo em bytes + registros de tamanho fixo em bytes
typedef struct {
	char key[2]
	char lastname[20]
	char firstname[20]
	char address[20]
	char city[10]
	char state[10]
	char zip[10]
	char phone[14]
} person;

person p;

// Leitura de um registro Pessoa
void readPerson(){

	printf("Key: ");
	scanf("%s", &p.key);

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

void writePersonToFile(FILE *file){
	fwrite(&p.key, sizeof(char), 2, file);
	fwrite(&p.lastname, sizeof(char), 20, file);
	fwrite(&p.firstname, sizeof(char), 20, file);
	fwrite(&p.address, sizeof(char), 20, file);
	fwrite(&p.city, sizeof(char), 10, file);
	fwrite(&p.state, sizeof(char), 10, file);
	fwrite(&p.zip, sizeof(char), 10, file);
	fwrite(&p.phone, sizeof(char), 14, file);
}

int main(){

	FILE *data = fopen("/Users/samara/Documents/ORI/Trab1/data.txt", "rw");

	// Ler registros Pessoa
	char option;

	printf("Nova pessoa? (y/n)\n");
	scanf("%c", &option);

	if(option=='y'){
		readPerson();
	}

	return 0;
}

