#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct nunumber_struct{
	struct nunumber_struct * expo;
	struct nunumber_struct * next;
};

typedef struct nunumber_struct nunumber;

/* STACK*/
/*procedury obsługi stosu przechowującego liliczby */
struct LIFO_s{
	struct nunumber_struct * node;  /*na stosie przechowywane są liliczby*/
	struct LIFO_s* next;
};
typedef struct LIFO_s LIFO;

LIFO* initLIFO(void)/*inicjalizacja pustego stosu*/{
	LIFO* ret;
	ret=NULL;
	return ret;
}

bool empty(LIFO* stack)/*sprawdzenie, czy stos jest pusty*/{
	return (stack==NULL);
}

void push(LIFO** stack, nunumber* x)/*dodanie elementu na stos*/{
	LIFO* aux;


	aux=(malloc(sizeof(LIFO))); /*rezerwuje miejsce*/
	(*aux).node=x;              /*wpisuje liliczbę na pole .node*/
	(*aux).next=*stack;         /*następnym elementem stosu jest poprzedni pierwszy element stosu*/
	*stack=aux;                 /*przywraca pod *stack adres pierwszego elementu na stosie*/
}


void buildStack(LIFO** stack, nunumber* nu)/*procedura do tworzenia stosu z listy liliczb*/{
/*na wejściu dostaje listę liliczb uporządkowaną rosnąco*/
/*tworzy stos liliczb, od najbardziej znaczących na górze*/
	nunumber* aux;


	if (nu){
		aux=nu;
		while(aux){
			push(stack, aux);
			aux=aux->next;
		}
	}
}


nunumber* pop(LIFO** stack){
/*przyjmuje wartość najwyższego elementu na stosie, zwalnia pamięć po nim, przebudowuje stos*/
	nunumber* aux=NULL;
	LIFO* aux2;


	if (!empty(*stack)){
		aux=(*stack)->node; /*na aux trafia liliczba*/
		aux2=(*stack); /*aux2 przyjmuje adres najwyższego elementu na stosie*/
		*stack=(*stack)->next; /*przesuwa adres najwyższego elementu na stosie na następny*/
		free(aux2); /*usuwa poprzedni element*/
	}
	return aux; /*funkcja przyjmuje wartość najwyższego elementu na stosie*/
}

void freeStack(LIFO** stack)/*usuwanie stosu z pamięci*/{
	LIFO* aux;


	while(*stack){
		aux=*stack;
		*stack=(*stack)->next;
		free(aux);
	}
}

/* /STACK*/


nunumber* init(){ /*zainicjowanie liliczby O WARTOŚCI 1*/
	nunumber* nu=malloc(sizeof(nunumber));
	nu->expo=NULL;
	nu->next=NULL;
	return nu;
}

nunumber* loadNunumber(){ /*procedura wczytująca liliczbę wg. przyjętej konwencji*/
	char YZ;
	nunumber* nu;


	YZ=getchar();
	if (YZ=='Y'){
		nu=init();
		(nu->expo)=loadNunumber();
		(nu->next)=loadNunumber();	
	}
	else nu=NULL;
	return nu;
}


void printNunumber(nunumber *nu)/*procedura wypisująca liliczbę*/{
	if (nu){
		putchar('Y');
		printNunumber(nu->expo);
		printNunumber(nu->next);
	}
	else putchar('Z');
}

void wipeoutNunumber(nunumber **nu)/*procedura usuwająca liliczbę z pamięci*/
{
	if((*nu)->expo) wipeoutNunumber(&((*nu)->expo));
	if((*nu)->next) wipeoutNunumber(&((*nu)->next));
 free(*nu);
}


int compare(nunumber* first, nunumber *second){
	/*wejście: first, second: nunumber* znormalizowane!
	  wyjście: 1 iff first > second
	           2 iff first < second
	           0 iff first = second
	*/
	LIFO *stack1;
	LIFO *stack2;
	nunumber* aux1;
	nunumber* aux2;
	int aux=0;


	if      ( first && !second) return 1; /*druga liliczba się skończyła, a pierwsza nie, więc pierwsza jest większa*/
	else if (!first &&  second) return 2; /*pierwsza liliczba się skończyła, a druga nie, więc druga jest większa*/
	else if (!first && !second) return 0; /*obie liliczby się skończyły, więc są równe*/
	else{/*w przeciwnym przypadku:*/
		stack1=initLIFO(); /*przygotuj 2 stosy*/
		stack2=initLIFO();
		if (first) buildStack(&stack1, first); /*stwórz stos z liliczb składających się na liliczbę first*/
		if (second) buildStack(&stack2, second); /*stwórz stos z liliczb składających się na liliczbę second*/
		while ((!empty(stack1) && (!empty(stack2)) && aux==0))/*dopóki żaden ze stosów nie jest pusty i nie stwierdzono, która liliczba jest większa*/{

			aux1=pop(&stack1); /*zdejmij najbardziej znaczącą liliczbę ze stosu1*/
			aux2=pop(&stack2); /*zdejmij najbardziej znaczącą liliczbę ze stosu2*/
			aux=compare(aux1->expo, aux2->expo); /*porównaj te liliczby*/
		}
		/*w tym miejscu: skończył się co najmniej jeden ze stosów lub stwierdzono, która liliczba jest większa*/
		if (aux==0){ /*jeśli nie stwierdzono, to sprawdź, który stos się skończył*/
			     if ( stack1 && !stack2){ /*jeśli pierwszy stos nie jest pusty, a drugi tak, to: */
			     		freeStack(&stack1); /*usuń stos pierwszy*/
			    		aux= 1;} /*zapamiętaj, że większa była pierwsza liliczba*/
			else if (!stack1 &&  stack2){ /*jeśli drugi stos nie jest pusty, a pierwszy tak, to: */
						freeStack(&stack2);  /*usuń stos drugi*/
						aux= 2;} /*zapamiętaj, że większa była druga liliczba*/
			else                       aux= 0; /*jeśli żaden z poprzednich warunków nie jest spełniony,
												to oba stosy są puste i porównywane liliczby są równe*/
		}
		if (stack1){freeStack(&stack1);free(stack1);} /*jeżeli któryś ze stosów został, to pozbywam się go*/
		if (stack2){freeStack(&stack2);free(stack2);}
		return aux;
	}
}

void addOneNode(nunumber** one){ 
/*!przed użyciem tej procedury trzeba zadbać o to, by nie zgubić adresu (*one)->next!*/
/*procedura dodaje pojedynczy węzeł, którego pole exp jest null, na początku listy wykładników liliczby *one*/
/*a także ustawia adres (*one)->next na (*one)->next->next, służy do łączenia dwóch równych liliczb ustawionych kolejno w jedną*/
	nunumber* aux;


	(*one)->next=((*one)->next)->next;
	aux=((*one)->expo);
	((*one)->expo)=init();
	((*one)->expo)->next=aux;
}

void swap(nunumber** one, nunumber** two)/*zamienia miejscami dwie liliczby na liście*/{
	nunumber* aux;


	aux=(**one).expo;
	(**one).expo=(**two).expo;
	(**two).expo=aux;

}


void bubbleSort(nunumber **nu)/*sortuje listę znormalizowanych liliczb, zwraca je uporządkowane ściśle rosnąco*/
{
	nunumber* del; /*od delete - służy do zapamiętywania adresów pamięci do zwolnienia*/
	nunumber* ptr=*nu; /*od pointer - służy do poruszania się po liście, zaczyna od pierwszego elementu*/
	int comp; /*do uniknięcia wielokrotnego wyliczania porównania dwóch liliczb*/
	bool swapped; 

/*bubble sort ze szczególnym uwzględnieniem przypadku równych liczb*/
	do{
		swapped = false;
		ptr=*nu;
		while((ptr->next!=NULL)){
			comp=(compare(ptr->expo, ptr->next->expo));
			if(comp==1){
				swap(&ptr, &(ptr->next));
				swapped = true;
			}
			else if(comp==0){ /*jeśli podczas sortowania trafiamy na dwie równe liliczby obok siebie, to chcemy je złączyć w jedną*/
				del=ptr->next; /*jedną z nich należy usunąć*/
				addOneNode(&ptr); /*a w drugiej (nazwijmy ją pierwszą) dodać jeden do wykładnika, oraz ustawić adres następnej liliczby*/
				bubbleSort(&(ptr->expo)); /*mogliśmy zepsuć porządek w wykładniku!*/
				swapped=true;
				if (del->expo) wipeoutNunumber(&(del->expo)); /*zwalniamy pamięć po drugiej liliczbie*/
				free(del);
			}
			if(ptr->next) ptr=ptr->next;
		}
	}while (swapped);
}

nunumber* copy(nunumber *n)/*tworzenie kopii liliczby*/{
	nunumber* ret; /*pomocnicza zmienna do return*/


	if (n!=NULL){
		ret=init();
		(ret->expo)=copy(n->expo);
		(ret->next)=copy(n->next);
		return ret;
	}
	else return NULL;
}

void normalize(nunumber **nu) /*normalizacja!*/
{
	if (*nu){
		normalize(&((*nu)->expo)); /*znormalizuj wykładniki*/
		normalize(&((*nu)->next)); /*znormalizuj następne liliczby*/
		bubbleSort(nu); /*posortuj!*/
		}
}

nunumber* merge(nunumber* a, nunumber* b)
{
	/*wejście: a, b : nunumber*
	  wyjście: liliczba będąca zlepieniem a i b*/
	/*jest to inny merge niż w przypadku merge-sort*/
	nunumber* aux;
	nunumber* ret;


	/*jeśli jedna z liliczb jest pusta, to zwróć niepustą*/
	if      ( a && !b) return a;
	else if (!a &&  b) return b;
	else if (!a && !b) return NULL; /*jeśli obie są puste, to zwróć NULL*/
	else{aux=a; /*jeśli nie zachodzi żaden z poprzednich przypadków, doklej b na końcu a*/
		ret=aux;
		while(aux->next) aux=aux->next;
		aux->next=b;
		return ret;
	}
}

nunumber* sum(nunumber *a, nunumber *b){
	/*wejście: a, b : nunumber*
	  wyjście: znormalizowana suma a i b : nunumber* */
	nunumber* ret; /*pomocnicza zmienna do return*/
	nunumber* cpa; /*kopia liliczby a*/
	nunumber* cpb; /*kopia liliczby b*/


	cpa=copy(a); cpb=copy(b); /*przypisanie kopii*/
	ret=merge(cpa,cpb); /*po złączeniu liliczb*/
	normalize(&ret); /*normalizuję je*/
	return ret; /*zwracam wskaźnik na pierwszy element na liście*/
}

nunumber* multiply(nunumber *a, nunumber *b){
	nunumber* Result;
	nunumber* auxResult; /*żeby nie zgubić adresu result przy dodawaniu*/
	nunumber* tempSum;
	nunumber* tempNode;
	/*----------------------------*/
	nunumber* auxa;
	nunumber* auxb;
	/*do poruszania się po listach*/
	nunumber* auxbHead;
	nunumber* auxaHead;
	/*do zapamiętania początków kopii list*/


	auxaHead=auxa=copy(a);
	auxbHead=auxb=copy(b);
	Result=NULL;
	while (auxa){
		while (auxb){
			tempSum=sum(auxa->expo,auxb->expo);

			tempNode=init();
			(tempNode->expo)=tempSum; /*w ten sposób uzyskujemy 2^(suma wykładników)*/

			auxResult=sum(Result, tempNode); /*dodajemy 2^(suma wykładników) do obecnej liliczby*/
			/*na auxResult, aby nie zgubić adresu*/
			if(Result)wipeoutNunumber(&Result); /*czyścimy poprzednią wartość Result*/
			Result=auxResult; /*adres wyniku wraca na swoje miejsce*/
			auxb=auxb->next; /*przechodzimy do następnej liliczby*/
			wipeoutNunumber(&tempNode); /*zwalniamy pamięć 2^(suma wykładników) - na Result są ich kopie*/
		}
	auxa=auxa->next;
	auxb=auxbHead;
	}
	if(auxaHead) wipeoutNunumber(&auxaHead);
	if(auxbHead) wipeoutNunumber(&auxbHead);
	/*ostrożne czyszczenie pamięci*/
	return Result;
}

void loadTwo(nunumber **one, nunumber **two){
	*one=loadNunumber();
	getchar(); /*pozbycie się znaku nowej linii*/
	*two=loadNunumber();
	getchar(); /*pozbycie się znaku nowej linii*/
}

int main(void){
	nunumber* nu1;
	nunumber* nu2;
	nunumber* result;
 	
 	loadTwo(&nu1, &nu2); /*wczytanie obu wejściowych liliczb*/
	normalize(&nu1); /*normalizacja pierwszej liliczby*/
	normalize(&nu2); /*normalizacja drugiej liliczby*/
	result=multiply(nu1, nu2); /*pomnóż dwie liliczby*/
	normalize(&result); /*znormalizuj wynik*/
	printNunumber(result); /*wypisz wynik!*/
	putchar('\n');
	/*ostrożne zwalnianie pamięci*/
	if(nu1)wipeoutNunumber(&nu1);
	if(nu2)wipeoutNunumber(&nu2);
	if(result)wipeoutNunumber(&result);
	return 0;
}