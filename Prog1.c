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

int main(){

	// Ler registros Pessoa
	char option;

	printf("Nova pessoa? (y/n)\n");
	scanf("%c", &option);

	if(option=='y'){
		readPerson();
	}

	return 0;
}

