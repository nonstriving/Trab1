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


// Campo genérico
void readField(){
	char field[20];
	scanf("%s", &field);
}

