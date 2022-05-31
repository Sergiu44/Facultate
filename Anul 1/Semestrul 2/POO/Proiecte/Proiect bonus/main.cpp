#include <iostream>
#include <vector>

using namespace std;

class Interface {
public:
    virtual istream& citire(istream& in) = 0;
    virtual ostream& afisare(ostream& out) const = 0;
};

class BadCast: public exception {
public:
    virtual const char* what() {
        return "Cast-ul pe care incerci sa il faci nu se poate realiza";
    }
}badCast;

class Vaccin: public Interface {
private:
    float pret;
    float temp;
    string numeProducator;
    vector<string>substante;

public:
    Vaccin(float pret = 100, float temp = 15, string numeProducator = "ProducatorX", vector<string>substante = {"subs1", "subs2"});
    Vaccin(const Vaccin& vaccin);
    Vaccin& operator=(const Vaccin& vaccin);
    virtual ~Vaccin() = 0;

    virtual istream& citire(istream& in);
    virtual ostream& afisare(ostream& out) const;

    friend istream& operator>>(istream& in, Vaccin& vaccin);
    friend ostream& operator<<(ostream& out, const Vaccin& vaccin);
};
Vaccin::Vaccin(float pret, float temp, string numeProducator, vector <string> substante) {
    this->pret = pret;
    this->temp = temp;
    this->numeProducator = numeProducator;
    this->substante = substante;
}
Vaccin::Vaccin(const Vaccin &vaccin) {
    this->pret = vaccin.pret;
    this->temp = vaccin.temp;
    this->numeProducator = vaccin.numeProducator;
    this->substante = vaccin.substante;
}
Vaccin& Vaccin::operator=(const Vaccin &vaccin) {
    if(this != &vaccin) {
        this->pret = vaccin.pret;
        this->temp = vaccin.temp;
        this->numeProducator = vaccin.numeProducator;
        this->substante = vaccin.substante;
    }
    return *this;
}
Vaccin::~Vaccin() {
    cout<<"Destructor vaccin"<<endl;
    if(!this->substante.empty())
        this->substante.clear();
}
istream& Vaccin::citire(istream &in) {
    cout<<"Pret: "; in>>this->pret;
    cout<<"Temperatura: "; in>>this->temp;
    cout<<"Nume producator: "; in.get();
    getline(in, this->numeProducator);
    unsigned int number;
    cout<<"Numarul de substante: "; in>>number;
    for(int i = 0 ; i<number; ++i) {
        cout<<"Substanta "<<i+1<<": "; in.get();
        getline(in, this->substante[i]);
    }
    return in;
}
ostream& Vaccin::afisare(ostream &out) const {
    out<<"Pret: "<<this->pret<<endl;
    out<<"Temperatura: "<<this->temp<<endl;
    out<<"Nume producator: "<<this->numeProducator<<endl;
    cout<<"Substante: "<<endl;
    for(int i = 0 ; i<this->substante.size(); ++i) {
        cout<<"Substanta "<<i+1<<": "<<this->substante[i]<<endl;
    }
    return out;
}
istream& operator>>(istream& in, Vaccin& vaccin) {
    return vaccin.citire(in);
}
ostream& operator<<(ostream& out, const Vaccin& vaccin) {
    return vaccin.afisare(out);
}

class Antigripal: public Vaccin {
private:
    string tip;
    bool isValid;
    string descriere;
public:
    Antigripal(float pret = 100, float temp = 15, string numeProducator = "ProducatorX", vector<string>substante = {"subs1", "subs2"}, string tip = "A-H1N1", bool isValid = true);
    Antigripal(const Antigripal& antigripal);
    Antigripal& operator=(const Antigripal& antigripal);
    ~Antigripal() {
        cout<<"Destructor antigripal"<<endl;
    };

    virtual istream& citire(istream& in);
    virtual ostream& afisare(ostream& out) const;

    friend istream& operator>>(istream& in, Antigripal& antigripal);
    friend ostream& operator<<(ostream& out, const Antigripal& antigripal);
};
Antigripal::Antigripal(float pret, float temp, string numeProducator, vector <string> substante, string tip, bool isValid): Vaccin(pret, temp, numeProducator, substante) {
    this->tip = tip;
    this->isValid = isValid;
    this->descriere = "...";
}
Antigripal::Antigripal(const Antigripal &antigripal): Vaccin(antigripal) {
    this->tip = antigripal.tip;
    this->isValid = antigripal.isValid;
    this->descriere = antigripal.descriere;
}
Antigripal& Antigripal::operator=(const Antigripal &antigripal) {
    if(this != &antigripal) {
        Vaccin::operator=(antigripal);
        this->tip = antigripal.tip;
        this->isValid = antigripal.isValid;
        this->descriere = antigripal.descriere;
    }
    return *this;
}
istream& Antigripal::citire(istream &in) {
    Vaccin::citire(in);
    cout<<"Tip vaccin: "; in.get();
    getline(in, this->tip);
    cout<<"Este valid acest vaccin antigripal(DA/NU): "; in.get();
    string answer;
    getline(in, answer);
    if(!answer.compare("DA")) {
        this->isValid = true;
    } else {
        this->isValid = false;
    }
    return in;
}
ostream& Antigripal::afisare(ostream &out) const {
    Vaccin::afisare(out);
    out<<"Pret: "<<this->tip<<endl;
    out<<"Valid: "<<(this->isValid ? "DA" : "NU")<<endl;
    out<<"Descriere: "<<this->descriere<<endl;
    return out;
}
istream& operator>>(istream& in, Antigripal& antigripal) {
    return antigripal.citire(in);
}
ostream& operator<<(ostream& out, const Antigripal& antigripal) {
    return antigripal.afisare(out);
}


class SarsCov2: public Vaccin {
private:
    vector<string>reactii;
    unsigned int eficienta;
    vector<string>medicamente;
    string descriere;
public:
    SarsCov2(float pret = 100, float temp = 15, string numeProducator = "ProducatorX", vector<string>substante = {"subs1", "subs2"}, vector<string>reactii = {"voma"}, unsigned int eficienta = 75, vector<string>medicamente = {"Paracetamol"});
    SarsCov2(const SarsCov2& sarsCov2);
    SarsCov2& operator=(const SarsCov2& sarsCov2);
    ~SarsCov2() {
        cout<<"Destructor sarsCov2"<<endl;
    };

    virtual istream& citire(istream& in);
    virtual ostream& afisare(ostream& out) const;

    friend istream& operator>>(istream& in, SarsCov2& sarsCov2);
    friend ostream& operator<<(ostream& out, const SarsCov2& sarsCov2);
};
SarsCov2::SarsCov2(float pret, float temp, string numeProducator, vector <string> substante, vector<string>reactii, unsigned int eficienta, vector<string>medicamente): Vaccin(pret, temp, numeProducator, substante) {
    this->reactii = reactii;
    this->eficienta = eficienta;
    this->medicamente = medicamente;
    this->descriere = "...";
}
SarsCov2::SarsCov2(const SarsCov2 &sarsCov2): Vaccin(sarsCov2) {
    this->reactii = sarsCov2.reactii;
    this->eficienta = sarsCov2.eficienta;
    this->medicamente = sarsCov2.medicamente;
    this->descriere = sarsCov2.descriere;
}
SarsCov2& SarsCov2::operator=(const SarsCov2 &sarsCov2) {
    if(this != &sarsCov2) {
        Vaccin::operator=(sarsCov2);
        this->reactii = sarsCov2.reactii;
        this->eficienta = sarsCov2.eficienta;
        this->medicamente = sarsCov2.medicamente;
        this->descriere = sarsCov2.descriere;
    }
    return *this;
}
istream& SarsCov2::citire(istream &in) {
    Vaccin::citire(in);
    unsigned int number;
    cout<<"Numarul de reactii adverse: "; in>>number;
    for(int i = 0 ; i<number; ++i) {
        cout<<"Reactie "<<i+1<<": "; in.get();
        string reactie;
        getline(in, reactie);
        this->reactii.push_back(reactie);
    }

    cout<<"Numarul de medicamente recomandate: "; in>>number;
    for(int i = 0 ; i<number; ++i) {
        cout<<"Medicament "<<i+1<<": "; in.get();
        string medicament;
        getline(in, medicament);
        this->medicamente.push_back(medicament);
    }
    cout<<"Eficienta acestui vaccin sarsCov2: "; in>>this->eficienta;
    return in;
}
ostream& SarsCov2::afisare(ostream &out) const {
    Vaccin::afisare(out);
    for(int i = 0 ; i<this->reactii.size(); ++i) {
        cout<<"Reactie "<<i+1<<": "<<this->reactii[i]<<endl;
    }

    for(int i = 0 ; i<this->medicamente.size(); ++i) {
        cout<<"Medicament "<<i+1<<": "<<this->medicamente[i]<<endl;
    }
    cout<<"Eficienta acestui vaccin sarsCov2: "<<this->eficienta<<endl;
    return out;
}
istream& operator>>(istream& in, SarsCov2& sarsCov2) {
    return sarsCov2.citire(in);
}
ostream& operator<<(ostream& out, const SarsCov2& sarsCov2) {
    return sarsCov2.afisare(out);
}

class Hepatita: public Vaccin {
private:
    string tip;
    string modVaccinare;
    string descriere;
public:
    Hepatita(float pret = 100, float temp = 15, string numeProducator = "ProducatorX", vector<string>substante = {"subs1", "subs2"}, string tip = "A", string modVaccinare = "intramuscular");
    Hepatita(const Hepatita& hepatita);
    Hepatita& operator=(const Hepatita& hepatita);
    ~Hepatita() {
        cout<<"Destructor hepatita"<<endl;
    };

    virtual istream& citire(istream& in);
    virtual ostream& afisare(ostream& out) const;

    friend istream& operator>>(istream& in, Hepatita& hepatita);
    friend ostream& operator<<(ostream& out, const Hepatita& hepatita);
};
Hepatita::Hepatita(float pret, float temp, string numeProducator, vector <string> substante, string tip, string modVaccinare): Vaccin(pret, temp, numeProducator, substante) {
    this->tip = tip;
    this->modVaccinare = modVaccinare;
    this->descriere = "...";
}
Hepatita::Hepatita(const Hepatita &hepatita): Vaccin(hepatita) {
    this->tip = hepatita.tip;
    this->modVaccinare = hepatita.modVaccinare;
    this->descriere = hepatita.descriere;
}
Hepatita& Hepatita::operator=(const Hepatita &hepatita) {
    if(this != &hepatita) {
        Vaccin::operator=(hepatita);
        this->tip = hepatita.tip;
        this->modVaccinare = hepatita.modVaccinare;
        this->descriere = hepatita.descriere;
    }
    return *this;
}
istream& Hepatita::citire(istream &in) {
    Vaccin::citire(in);
    cout<<"Tipul vaccinului hepatic: "; in.get();
    getline(in, this->tip);

    cout<<"Mod vaccinare: "; in.get();
    getline(in, this->modVaccinare);
    return in;
}
ostream& Hepatita::afisare(ostream &out) const {
    Vaccin::afisare(out);
    cout<<"Tipul acestui vaccin hepatic: "<<this->tip<<endl;
    cout<<"Mod vaccin: "<<this->modVaccinare<<endl;
    return out;
}
istream& operator>>(istream& in, Hepatita& hepatita) {
    return hepatita.citire(in);
}
ostream& operator<<(ostream& out, const Hepatita& hepatita) {
    return hepatita.afisare(out);
}

class Comanda: public Interface {
private:
    static int contorId;
    const int idComanda;

    string data;
    string numeClient;

    vector<Vaccin*> vaccinuri;
    vector<unsigned int> cantitate;

public:
    Comanda(string data = "28/05/2022", string numeClient = "Client", vector<Vaccin*> vaccinuri = {}, vector<unsigned int>cantitate = {});
    Comanda(const Comanda& comanda);
    Comanda& operator=(const Comanda& comanda);
    ~Comanda() {
        if(!this->vaccinuri.empty())
            this->vaccinuri.clear();
        if(!this->cantitate.empty())
            this->cantitate.clear();
        cout<<"Destructor comanda"<<endl;
    }

    virtual istream& citire(istream& in);
    virtual ostream& afisare(ostream& out) const;

    friend istream& operator>>(istream& in, Comanda& comanda);
    friend ostream& operator<<(ostream& out, const Comanda& comanda);

};
Comanda::Comanda(string data, string numeClient, vector<Vaccin *> vaccinuri, vector<unsigned int> cantitate):idComanda(contorId++) {
    this->data = data;
    this->numeClient = numeClient;
    this->vaccinuri = vaccinuri;
    this->cantitate = cantitate;
}
Comanda::Comanda(const Comanda &comanda):idComanda(comanda.idComanda) {
    this->data = comanda.data;
    this->numeClient = comanda.numeClient;
    this->vaccinuri = comanda.vaccinuri;
    this->cantitate = comanda.cantitate;
}
Comanda& Comanda::operator=(const Comanda &comanda) {
    if(this != &comanda) {
        this->data = comanda.data;
        this->numeClient = comanda.numeClient;
        this->vaccinuri = comanda.vaccinuri;
        this->cantitate = comanda.cantitate;
    }
    return *this;
}
istream& Comanda::citire(istream& in) {
    cout<<"Data comenzii(format: ZZ/LL/AAAA): "; in>>this->data;
    cout<<"Numele clientului: "; in.get();
    getline(in, this->numeClient);
    int number;
    cout<<"Numarul de vaccinuri: "; in>>number;
    for(int i = 0; i<number; ++i) {
        cout<<"Alegeti tipul de vaccin:\n1.Antigripal\n2.SarsCov2\n3.Hepatita\n";
        int comandaVaccin;
        int cantitate;
        in>>comandaVaccin;
        switch (comandaVaccin) {
            case 1: {
                Antigripal* antigripal = new Antigripal();
                antigripal->citire(in);
                cout<<"Cantitatea acestui vaccin este: "; in>>cantitate;
                this->cantitate.push_back(cantitate);
                this->vaccinuri.push_back(antigripal);
                break;
            }
            case 2: {
                SarsCov2* sarsCov2 = new SarsCov2();
                sarsCov2->citire(in);
                cout<<"Cantitatea acestui vaccin este: "; in>>cantitate;
                this->cantitate.push_back(cantitate);
                this->vaccinuri.push_back(sarsCov2);
                break;
            }
            case 3: {
                Hepatita* hepatita = new Hepatita();
                hepatita->citire(in);
                cout<<"Cantitatea acestui vaccin este: "; in>>cantitate;
                this->cantitate.push_back(cantitate);
                this->vaccinuri.push_back(hepatita);
                break;
            }
            default: {
                --i;
                cout<<"Indexul introdus nu este bun!"<<endl;
            }
        }

    }
    return in;
}
ostream& Comanda::afisare(ostream &out) const {
    out<<"Data comenzii este: "<<this->data<<endl;
    out<<"Numele clientului: "<<this->numeClient<<endl;
    out<<"Vaccinurile: "<<endl;

    for(int i =0; i<this->vaccinuri.size(); ++i) {
        try {
            out << i + 1 << ". ";
            if (dynamic_cast<Antigripal*>(this->vaccinuri[i])) {
                this->vaccinuri[i]->afisare(cout);
                out<<"Cantitatea acestui vaccin este: "<<this->cantitate[i]<<endl;

            } else if (dynamic_cast<SarsCov2*>(this->vaccinuri[i])) {
                this->vaccinuri[i]->afisare(cout);
                out<<"Cantitatea acestui vaccin este: "<<this->cantitate[i]<<endl;

            } else if (dynamic_cast<Hepatita*>(this->vaccinuri[i])) {
                this->vaccinuri[i]->afisare(cout);
                out<<"Cantitatea acestui vaccin este: "<<this->cantitate[i]<<endl;

            } else {
                throw badCast;
            }
        }catch(BadCast& exception) {
            cout<<exception.what()<<endl;
        }
    }
    return out;
}
int Comanda::contorId = 0;


class MenuCRUD {
private:
    static MenuCRUD* obiect;
    MenuCRUD() {};
    ~MenuCRUD() {
        if(obiect != NULL)
            delete obiect;
    }

public:
    static MenuCRUD* getInstance() {
        if(!obiect)
            obiect = new MenuCRUD();
        return obiect;
    }
    void meniuInteractiv();
};
MenuCRUD* MenuCRUD::obiect = 0;

int main() {
    Comanda* comanda = new Comanda();
    comanda->citire(cin);
    comanda->afisare(cout);
    return 0;
}