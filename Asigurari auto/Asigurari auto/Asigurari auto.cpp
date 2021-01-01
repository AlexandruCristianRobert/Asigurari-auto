#include <iostream>
using namespace std;
// lucruri importante
//stringurile tale nu retin propoziiti, adica nu citest spatii. Deci daca vrei sa dai un nume de genul Ionel Fanel, il scrii Ionel.Fanel sau Ionel_Fanel, sau cu ce orice vrei tu dar nus patiu
// durata, ziua inregistrarii nu au limite, deci nu da si tu ziua inregistrarii 400, si durata 200, limieteaaza-le in zilele anului de la 1 la 365
class Asigurare
{
private:
	// variabile si functii( noi avem doar variabile aici ) private, pot fi folosite doar in clasa curenta( adica aici in clasa Asigurare)
	string nume;
	bool polita = true;// asigurare obligatorie sau casco , o setam default ca true
	int valoare;// pretul/valoare asiguratii
	int zi_inregistrare;
	int durata;
public:// variabile si functii( avem functii noi ) publice , pot fi folosiite oriunde in programm, adica putem sale folosim in alte clase sau in in main
	Asigurare() :valoare(0), durata(0) {}// constructorul, de fiecare data cand se creeaza o asigurare initializam valorile cu 0
	// pentru a accesa sau modifica valorile variabileleor private, folosim functii "set" si functii "get"
	// functiile set schimba valoarea variabilei, 
	//  functiile get returneaza valoarea variabilei
	void set_valoare(int x)// functie set ,, ii schimba valoarea variabilei valoarea cu valoarea lui x, adica face valoarea =5 daca x e 5. 
	{
		valoare = x;
	}
	int get_valoare()// returneaza valoarea lui valoarea. adica daca valorea = 5 si tu vrei sa afisezi valoarea spui cout<<get_valoare() si iti afiseaza 5
	{
		return valoare;
	}
	void set_durata(int x)
	{
		durata = x;
	}
	friend istream& operator >>(istream& in, Asigurare* a)// suprascrierea citirii, folosim pointeri la input de-aia am  pus * nu &
	{
		cout << "Nume asigurare: ";
		in >> a->nume;// cand folosesti pointeri se scrie -> in loc de .
		cout << "Tip polita Obligatorie( 0 )  sau optionala ( 1 ): ";
		in >> a->polita;
		cout << "Ziua inregistrarii: ";
		in >> a->zi_inregistrare;
		return in;
	}
	friend ostream& operator <<(ostream& on, Asigurare* a)// suprascrierea afisarii
	{
		on << a->nume << endl;
		if (a->polita)
			on << "Tip polita: optionala" << endl;
		else
			on << "Tip Polita: obligatorie" << endl;
		on << "Ziua inregistrarii: " << a->zi_inregistrare << endl;
		on << "Durata zile: " << a->durata << endl;
		on << "Pret platit: " << a->valoare << endl;
		return on;
	}
};
class Client
{
	int id;
	static int adauga;// variabila statica , apartine clasei nu instantei, de ex faci un client , adauga = 1 de inceput, faci adauga ++ devine 2, faci alt client, adauga inca are valoarea 2, nu s-a resetat la 1. faci adauga++ devine 3 si tot asa
	string nume;
	string automobil;
	Asigurare** va;// pointer de pointeri la asigurari, Adica ai un pointer care arata spre un loc, iar in locul ala tinem toate adresele(toti pointerii) asigurarilor. Asa functioneaza  stl-ul vector, si da, s-a facut la seminar asta
	int na;// numar asigurari
	int valoare_asigurari;
public:
	Client() :na(0), valoare_asigurari(0)
	{
		va = new Asigurare * [0];// se initializeaza vectorul de dimensiune 0 la inceput
		id = adauga++;// incrementam id-ul clientului. Adica faci client id=1, faci client id=2, ...
	}
	void set_valoare()
	{
		valoare_asigurari = 0;// daca apelezi de mai multe ori set valoare vrem sa fie mereu valoarea normala, nu sa se adune intr-una o sa vezi in int main
		for (int i = 0;i < na;i++)// seteaza pentru fiecare asigurare a clientului valoarea sa 
		{
			valoare_asigurari += va[i]->get_valoare();// exemplu de apelare a lui get_valoare, deoarece nu putem accesa valoarea unei asigurari, apelam functia publica get_valoare pentru a folosi valoarea
		}
	}
	int get_id()
	{
		return id;
	}
	int get_val()
	{
		return valoare_asigurari;
	}
	void Add_asig(Asigurare* a)//  adauga o asigurare in vectorul de asigurari al clientului
	{
		Asigurare** copie = new Asigurare * [na + 1];// facem un alt vector, cu 1 loc mai mult decat cel pe care il are deja clientul
		for (int i = 0;i < na;i++)
		{
			*(copie + i) = *(va + i);//  copiem in vectorul nou fiecare element din vectorul clientului, unu cate unu
		}
		*(copie + na) = a;// la ultima pozitie a vectorului nou adaugam asigurarea noua, aia din parametru
		delete[] va;// stergem vectorul clientului
		va = copie;// alocam vectorul nou ca vectorul clientului
		na++;//  na++,  adica numar asigurari
	}
	Asigurare* get_asig(int i)//  returneaza un pointer  la o asigurare
	{
		return *(va + i);
	}
	friend istream& operator >>(istream& in, Client* c)// suprascierea citirii unui client
	{
		cout << "Nume: ";
		in >> c->nume;
		cout << "Masina: ";
		in >> c->automobil;
		return in;
	}
	friend ostream& operator <<(ostream& on, Client* c)//suprascrierea afisarii unui client. Programul stie pe care suprascriere sa o aleaga in functie de ce urmeaza dupa << sau >>/ Daca urmeaza o asigurare foloseste suprascrierea de la asigurare, daca urmeaza un client foloseste suprascrierea de la client.
	{
		on << "Id client: " << c->id << endl;
		on << "Nume: " << c->nume << endl;
		on << "Masina: " << c->automobil << endl;
		on << "Asigurari: ";
		for (int j = 0;j < c->na;j++)//  aici o sa  afiseze toate asigurarile
		{
			on << c->get_asig(j);//foloseste suprascrierea de la asigurare.  Deci e o serie de suprascrieri intr-o suprascriere
		}
		on << endl;
		return on;
	}

};
int Client::adauga = 1;// initializarea valorii statice cu 1, normal incepea de la0 , dar vrem id client sa inceapa dela 1
class Societate
{
	int id;
	static int a;
	string denumire;
	Client** vc;
	int nc;
	int total_val_societate;
public:
	string get_nume()
	{
		return denumire;
	}
	void set_val()
	{
		for (int i = 0;i < nc;i++)
		{
			total_val_societate += vc[i]->get_val();
		}
	}
	int get_val()
	{
		return total_val_societate;
	}
	Societate() :id(a++)// chit ca intre acolade id=a++ sau scrii aici sus :id(a++) e aceeasi chestie
	{
		nc = 0;
		vc = new Client * [0];
	}
	friend istream& operator >>(istream& in, Societate& s)
	{
		cout << "Nume societate: ";
		in >> s.denumire;
		return in;
	}
	friend ostream& operator <<(ostream& on, Societate& s)
	{
		for (int j = 0;j < s.nc;j++)
			on << s.get_client(j);
		return on;
	}
	void Add_client(Client* c)// acelasi lucru , doar ca aici adaugam clienti in asociatie
	{
		Client** copie = new Client * [nc + 1];
		for (int i = 0;i < nc;i++)
		{
			*(copie + i) = *(vc + i);
		}
		*(copie + nc) = c;
		delete[] vc;
		vc = copie;
		nc++;
	}
	void adauga_asig(int i, Asigurare* a)// adauga o asigurare la clientul cu id i
	{
		get_client(i-1)->Add_asig(a);//  explic mai jos de ce i-1
	}
	Client* get_client(int i)
	{
		return *(vc + i);// noi incepem de la pozitia vc, daca pui id 1 si returnezei vc+1 iti da clientul 2 nu 1. normal trebuie sa fie vc+0 primul.
	}

};
int Societate::a = 1;
int main()
{
	Societate s;// creaza o societate
	cin >> s;// o citim, numele ei mai exact
	bool y = true;
	while (y)// cat timp y e adevarat
	{
		int x;
		cout << endl;
		cout << "Societatea: " << s.get_nume() << endl;
		cout << "1) Adauga client " << endl;
		cout << "2) Adauga asigurare " << endl;
		cout << "3) Afisare pret asigurari client " << endl;
		cout << "4) Afisare clienti" << endl;
		cout << "5) Afisare incasari societate" << endl;
		cout << "6) Iesire" << endl;
		cin >> x;
		switch (x)// functie switch, in functie de ce valoare are x, ruleaza un cod
		{
		case 1:
		{
			Client* c = new Client();// faci un pointer la un client si creezi un client la adresa aia
			cin >> c;// citesti clientul
			s.Add_client(c);// adaugi clientul la societate
			break;// functie break, opreste un for/while/case. In cazul nostru case -ul 1
		}
		case 2:
		{
			cout << "Id client: ";
			int id;
			cin >> id;
			Asigurare* as = new Asigurare();
			cin >> as;
			cout << "Durata: ";
			int durata;
			cin >> durata;
			int valoare = 7 * durata;// o functie sa ii dea lui valoare o valoare in functie de durata
			as->set_durata(durata); // setam durata asigurarii
			as->set_valoare(valoare);// setam valoarea asigurarii
			s.adauga_asig(id, as);// adaugam asigurarea la clientul cu id-ul id din societate
			break;
		}
		case 3:
		{
			cout << "Id client: ";
			int id;
			cin >> id;
			s.get_client(id-1)->set_valoare();//nu am setat valoarea pana acum, deci trebuie setata cand vrei sa vezi clientul
			cout << "Valoare asigurarilor clientului este de :" << s.get_client(id-1)->get_val();
			break;
		}
		case 4:
		{
			cout << "Lista clienti: " << endl;
			cout << s << endl;
			break;
		}
		case 5:
		{
			s.set_val();
			cout << "Total bani incasati: " << s.get_val() << endl;// valoarea tuturor asigurarilor vandute de societate
			break;
		}
		case 6:
		{
			y = false;// y = false, deci iese din while, end.
			break;
		}
		}
	}
	return 0;
}
