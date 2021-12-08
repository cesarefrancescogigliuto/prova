#include <iostream>
using namespace std;

//Creazione classe Veicolo
class Veicolo{
public:
	string marca;
	int cavalli;

	Veicolo(string marca, int cavalli){
		this->marca=marca; //copiamo i valori nel costruttore
		this->cavalli=cavalli;
	}
};

//Creazione classe Auto
class Auto: public Veicolo{
public:
	Auto(string marca, int cavalli): Veicolo(marca, cavalli) {};
};

//Creazione della classe Moto
class Moto: public Veicolo{
public:
	Moto(string marca, int cavalli): Veicolo(marca, cavalli) {};
};

//Creazione della classe Barca
class Barca: public Veicolo{
public:
	Barca(string marca, int cavalli): Veicolo(marca, cavalli) {};
};

//Creazione del nodo
class Nodo{
public:
    Veicolo* v; //Non usiamo un valore ma un puntatore a Veicolo che copia in v
    Nodo* succ;
    Nodo(Veicolo *veicolo){
		v=veicolo;
	}
};

//Creazione della struttura coda
class Queue{
    Nodo *fronte, *fine;
public:
    Queue() {
        cout << "costruttore coda"<<endl;
        fronte = fine = NULL;
        }
    void enQueue(Veicolo* x); //Passiamo un puntatore a veicolo
    Veicolo* deQueue();//Ci facciamo tornare un puntatore a veicolo
    bool isEmpty()const { return fine == NULL;}//controlla se la coda e' vuota
    friend
    ostream& operator<<(ostream& out, const Queue& q);
    void stampa();
};

//Inserimento
void Queue::enQueue(Veicolo* x){
    cout <<"enQueue"<<endl;
    Nodo* tmp = new Nodo(x); //non usiamo l'inserimento esplicitamente
    if(fine == NULL){
        fronte = fine = tmp;
    }
    else // inserimento in coda...
    {
        fine->succ = tmp;
        fine = tmp; //la fine deve puntare ad un nuovo nodo
    }
}

Veicolo* Queue::deQueue(){
    cout << "dequeue " << fronte << " " <<fine <<endl;
    // se e' vuota...
    //if(fronte == NULL)
        if(fronte == NULL )
        //if(fine == NULL)
        return NULL;
        cout << "ci arrivo 1" <<endl;
    Nodo* tmp = fronte;

    if (fronte!=fine)    {

     fronte = fronte->succ;
    }
    else {
        fronte=NULL;
    }
    cout << "ci arrivo 2" <<endl;
    // se ho svuotato la coda aggiorno 'fine'
    if(fronte == NULL)
        fine = NULL;
     cout << "ci arrivo 3" <<endl;
    Veicolo* aux = tmp->v;
    delete tmp;
    return aux;
}

void Queue::stampa(){
    cout << "stampa " << fronte << " " <<fine <<endl;
     Nodo* tmp = fronte;
     while (tmp != NULL && tmp<=fine) { ///scorriamo al successivo finche' non arriviamo a NULL
            cout <<"tmp-> " << tmp->v->marca<< " " << tmp->v->cavalli<<endl;
            tmp=tmp->succ;
     }

    /*
    // se e' vuota...
    //if(fronte == NULL)
        if(fronte == NULL)
        //if(fine == NULL)
        return NULL;
        cout << "ci arrivo 1" <<endl;
    Nodo* tmp = fronte;

    fronte = fronte->succ;
    cout << "ci arrivo 2" <<endl;
    // se ho svuotato la coda aggiorno 'fine'
    if(fronte == NULL)
        fine = NULL;
     cout << "ci arrivo 3" <<endl;
    Veicolo* aux = tmp->v;
    delete tmp;
    return aux;
    */
}


//Creazione di albero
class NodoAlbero{
public:
    Veicolo* veicolo; //Non usiamo un valore ma una classe ovvero un puntatore a Veicolo
    NodoAlbero *left, *right, *padre;
};

class Albero{
    NodoAlbero *radice;
    int num_elementi=0;
    void inOrder(NodoAlbero* p) const; //Usiamo l'inorder per la visita ordinata
public:
    Albero(): radice(NULL) {}
    void inserisci(Veicolo*);
    void inOrder() const{inOrder(radice); cout << endl;}
    void cancella(NodoAlbero* z);
    void trapianta(NodoAlbero* u, NodoAlbero *v);
    NodoAlbero* minimo(NodoAlbero* x);
    void cancellaMinori(int valore);

    friend
    ostream& operator<<(ostream& out, const Albero&t);
};

//Inserimento in cui passiamo il puntatore a veicolo
void Albero::inserisci(Veicolo* v){
	NodoAlbero* nuovo = new NodoAlbero;
    NodoAlbero* x=radice, *y=NULL;
    int cav = v->cavalli; 

    nuovo->veicolo = v;
    nuovo->left = NULL;
    nuovo->right = NULL;
    while(x!=NULL){
        y = x;// y tiene traccia del padre di x
        if(cav < x->veicolo->cavalli) //ordinamento in base al numero di cavalli
            x = x->left;
        else
            x = x->right;
    }
    nuovo->padre = y;
    if(y==NULL)
        radice = nuovo;
    else if(cav < y->veicolo->cavalli)
        y->left = nuovo;
    else
        y->right = nuovo;

    num_elementi++;
}


void Albero::inOrder(NodoAlbero* p) const{
	cout<<"INORDER"<<endl;
    if(p!=NULL){
        inOrder(p->left); //figlio sx
        cout << p->veicolo->marca <<" "<<p->veicolo->cavalli<< "\t"; //padre
        inOrder(p->right); //figlio dx
    }
}

//Metodo trapianta per spostare pezzi di un sottoalbero
void Albero::trapianta(NodoAlbero* u, NodoAlbero *v){
    if(u->padre==NULL)
        radice = v;
    else if(u==u->padre->left)
        u->padre->left = v;
    else
        u->padre->right = v;

    if(v!=NULL)
        v->padre = u->padre;
}


NodoAlbero* Albero::minimo(NodoAlbero* x){
    NodoAlbero* nMin = x;
    while(nMin->left!=NULL)
        nMin = nMin->left;
    return nMin;
}

void Albero::cancella(NodoAlbero* z){
    NodoAlbero *y;
    // Caso 2: z ha un solo figlio
    if(z->left == NULL)
        trapianta(z,z->right);
    else if(z->right==NULL)
        trapianta(z,z->left);

    // Caso 3: ha entrambi i figli
    else{
        y = minimo(z->right); // y <- successore di z
        if(y->padre!=z){
            trapianta(y, y->right); // y->right corrisponde ad 'x' nelle slides
            y->right = z->right; // z->right <==> 'r' nelle slides
            y->right->padre = y;
        }
        //non ci resta altro che trapiantare y in z
        trapianta(z,y);
        y->left = z->left; // z->left <==> 'l' nelle slides
        y->left->padre = y;
    }
    delete z;
}

void Albero::cancellaMinori(int valore){
	NodoAlbero* tmp=minimo(radice);
	while(tmp->veicolo->cavalli<valore) {
		cancella(tmp);
	}


}

int main()
{
	int N;
	cout<<"Numero di oggetti Veicolo da inserire A/B/M?"<<endl;
	cin>>N;

	Queue qAuto;  //coda auto
	Queue qMoto;  //coda moto
	Queue qBarca; //coda barca

    system("PAUSE");
	
	//Setto da tastiera tipo, marca e cavalli
	for(int i=0;i<N;i++){
		string tipo, marca;
		int cavalli;

		cout<<"Inserire tipo elemento \t"<<i<<endl;
		cin>>tipo;
		cout<<"Inserire la marca \t"<<endl;
		cin>>marca;
		cout<<"Inserire i cavalli\t"<<endl;
		cin>>cavalli;
		Veicolo* v; //inizializza l'oggetto di tipo tipo -> mi serve per crearmi l'oggetto di tipo A, B, M

		if(tipo=="A") {
			v= new Auto(marca,cavalli);
			qAuto.enQueue(v);
		}
		else if(tipo=="B"){
			v= new Barca(marca,cavalli);
			qBarca.enQueue(v);
		}
		else if(tipo=="M"){
			v= new Moto(marca,cavalli);
			qMoto.enQueue(v);
		}
		else{
			cout<<"Tipo non valido"<<endl;
			i--;
		}
	}
	system("PAUSE");

	qAuto.stampa();
	qMoto.stampa();
	qBarca.stampa();

	cout << "fine stampa" <<endl;
	system("PAUSE");
	//cout<<"DEQUEUE: "<<qAuto.deQueue()->marca<<endl;

    cout<<"CONTROLLO"<<endl;
	Veicolo* au=qAuto.deQueue();;
	Albero aAuto;
	while(au!=NULL){ //Estraggo dalla coda dell'auto e in parallelo li inserisco nel relativo BST 
		//if(au!=NULL){
		//	cout<<"Leggo: "<<au->marca<<endl;
			aAuto.inserisci(au);
		//	cout<<"Inserito"<<endl;
		//}
		//cout<<"CONTROLLO"<<endl;
		au=qAuto.deQueue();
		//cout<<"CONTROLLATO"<<endl;
	}

  // cout << "ci arrivo finale" <<endl;


	au=qMoto.deQueue();
	Albero aMoto;
	while(au!=NULL){

		//if(au!=NULL){
			aMoto.inserisci(au);
		//}
		au=qMoto.deQueue();
	}

	au=qBarca.deQueue();
	Albero aBarca;
	while(au!=NULL){

		//if(au!=NULL){
			aBarca.inserisci(au);
		//}
		au=qBarca.deQueue();
	}
	//Stampa inorder dei vari sottoalberi
	cout<<"Auto:"<<endl;
	aAuto.inOrder();
	cout<<"Moto:"<<endl;
	aMoto.inOrder();
	cout<<"Barca:"<<endl;
	aBarca.inOrder();

	//aAuto.cancellaMinori(2);
	//aAuto.inOrder();


}
