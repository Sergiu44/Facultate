#include <iostream>
#include <cstring>
#include <ctime>
#include <sstream>
#include <list>

using namespace std;

class Shareholder {
private:
    string last_name;
    string first_name;
    char *CNP;
    // whether he/she is a passive or an active investor
    bool passive;
    // the type of stocks the shareholder wants
    string typeOfStocks;

    const int account_id;
    static int count_account_id;

public:
// Functionality
    int checkAge();

//    Setters
    void setLastName(string last_name);

    void setFirstName(string first_name);

    void setCNP(char *CNP);

    void setIsPassive(bool passive);

    void setTypeOfStocks(string typeOfStocks);

//    Getters
    string getLastName();

    string getFirstName();

    const char *getCNP();

    bool getPassive();

    string getTypeOfStocks();

    int getShareholderId();

    static int getCountId();

    //    Constructors | Destructors
    Shareholder(string last_name, string first_name, char *CNP, bool passive, string typeOfStocks);

    Shareholder(string last_name, string first_name, char *CNP);

    Shareholder(char *CNP);

    Shareholder();

    Shareholder(const Shareholder &shareholder);

    ~Shareholder();

    // Overloading operators
    Shareholder &operator=(const Shareholder &shareholder);

    friend istream &operator>>(istream &in, Shareholder &S);

    friend ostream &operator<<(ostream &out, const Shareholder &S);

    char operator[](int index);

    const Shareholder &operator--();

    const Shareholder operator--(int);

    Shareholder operator+(string name);

    friend Shareholder operator+(string name, Shareholder shareholder);

    Shareholder operator-(int size);

    friend Shareholder operator-(int size, Shareholder shareholder);

    explicit operator string() {
        if (this->CNP != NULL) {
            std::string str(this->CNP);
            return str;
        }
        return "";
    }

    bool operator<(Shareholder shareholder);

    bool operator==(Shareholder shareholder);
};

// Functionality
int Shareholder::checkAge() {
    // Calculating the year in which the shareholder was born and returning a corresponding string based on his/her age
    // Getting the current year
    time_t now = time(0);
    tm *localTime = localtime(&now);

    // In order to get the 2022 year, it is needed to be added 1900
    const string local_year = to_string(1900 + localTime->tm_year);

    // Parsing the current year from string to int
    stringstream geek(local_year);
    int value = 0;
    geek >> value;

    // Creating an array of char element for the year in which the used was born
    char *birth_year = new char[5];
    // -48 from converting from char to int
    if (int(this->CNP[1]) - 48 >= 3) {
        // The person is born before 2000
        strcpy(birth_year, "19");
        birth_year[2] = this->CNP[1];
        birth_year[3] = this->CNP[2];
    } else {
        // The person is born after 2000
        strcpy(birth_year, "20");
        birth_year[2] = this->CNP[1];
        birth_year[3] = this->CNP[2];
    }

    // Convert the year the user was born into an int value
    int birthYear = 0;
    int p = 1000;

    for (int i = 0; i < strlen(birth_year); ++i) {
        birthYear += (birth_year[i] - '0') * p;
        p = p / 10;
    }

    // Check if the user is major or not
    // value - the current year parsed into int
    // birthYear - the year in which the user was born converted to int
    if (value - birthYear >= 18) {
        cout<<"Aveti varsta necesara pentru a tranzactiona pe platforma noastra!"<<endl;
        delete[] birth_year;
        return value - birthYear;
    } else {
        cout<<"Ne pare rau, dar nu aveti varsta necasara pentru a tranzactiona pe platforma noastra!"<<endl;
        delete[] birth_year;
        return value - birthYear;
    }
};

// Setters and Getter
void Shareholder::setLastName(string last_name) {
    this->last_name = last_name;
};

void Shareholder::setFirstName(string first_name) {
    this->first_name = first_name;
};

void Shareholder::setCNP(char *CNP) {
    if (this->CNP != NULL)
        delete[] this->CNP;
    this->CNP = new char[14]; // CNP has 13 + 1 digits
    strcpy(this->CNP, CNP);
};

void Shareholder::setIsPassive(bool passive) {
    this->passive = passive;
};

void Shareholder::setTypeOfStocks(string typeOfStocks) {
    this->typeOfStocks = typeOfStocks;
};

string Shareholder::getLastName() {
    return this->last_name;
};

string Shareholder::getFirstName() {
    return this->first_name;
};

const char *Shareholder::getCNP() {
    return this->CNP;
};

int Shareholder::getCountId() {
    return Shareholder::count_account_id;
};

int Shareholder::getShareholderId() {
    return this->account_id;
};

bool Shareholder::getPassive() {
    return this->passive;
};

string Shareholder::getTypeOfStocks() {
    return this->typeOfStocks;
};


// Constructors / Destructors
Shareholder::Shareholder(string last_name, string first_name, char *CNP, bool passive, string typeOfStocks)
        : account_id(++count_account_id) {
    this->last_name = last_name;
    this->first_name = first_name;
    this->CNP = new char[strlen(CNP) + 1];
    strcpy(this->CNP, CNP);
    this->passive = passive;
    this->typeOfStocks = typeOfStocks;
};

Shareholder::Shareholder(string last_name, string first_name, char *CNP) : account_id(++count_account_id) {
    this->last_name = last_name;
    this->first_name = first_name;
    this->CNP = new char[strlen(CNP) + 1];
    strcpy(this->CNP, CNP);
    this->passive = false;
    this->typeOfStocks = "Dividend";
};

Shareholder::Shareholder(char *CNP) : account_id(++count_account_id) {
    this->last_name = "Stanciu";
    this->first_name = "Sergiu-Nicolas";
    this->CNP = new char[strlen(CNP) + 1];
    strcpy(this->CNP, CNP);
    this->passive = false;
    this->typeOfStocks = "Dividend";
}

Shareholder::Shareholder() : account_id(++count_account_id) {
    this->last_name = "Stanciu";
    this->first_name = "Sergiu-Nicolas";
    this->CNP = new char[strlen("7980304331049") + 1];
    strcpy(this->CNP, "7980304331049");
    this->passive = false;
    this->typeOfStocks = "Dividend";
}

Shareholder::Shareholder(const Shareholder &shareholder) : account_id(++count_account_id) {
    this->last_name = shareholder.last_name;
    this->first_name = shareholder.first_name;
    this->CNP = new char[strlen(shareholder.CNP) + 1];
    strcpy(this->CNP, shareholder.CNP);
    this->passive = shareholder.passive;
    this->typeOfStocks = shareholder.typeOfStocks;
}

Shareholder::~Shareholder() {
    if (this->CNP != NULL)
        delete[] this->CNP;
}

Shareholder &Shareholder::operator=(const Shareholder &shareholder) {
    if (this != &shareholder) {
        if (this->CNP != NULL)
            delete[] this->CNP;

        this->last_name = shareholder.last_name;
        this->first_name = shareholder.first_name;
        this->CNP = new char[strlen(shareholder.CNP) + 1];
        strcpy(this->CNP, shareholder.CNP);
        this->passive = shareholder.passive;
        this->typeOfStocks = shareholder.typeOfStocks;
    }
    return *this;

}

istream &operator>>(istream &in, Shareholder &S) {
    // Declarations
    int tasta;
    char *check = new char[9];
    strcpy(check, "ACCEPTED");
    char *CNP = new char[14];

    cout << "Introduceti datele unui actionar:" << endl;
    cout << "Numele de familie: ";
    in >> S.last_name;
    cout << "Prenumele complet: ";
    in >> S.first_name;
    if (S.CNP != NULL) {
        delete[] S.CNP;
    }
    S.CNP = new char[14];
    cout << "Introduceti CNP-ul(14 caractere): ";
    in >> CNP;
    while(strlen(CNP) != 13) {
        cout << "CNP-ul nu este valid, incercati din nou!";
        in >> CNP;
    }
    strcpy(S.CNP, CNP);
    if(S.checkAge() < 18) {
        cout<<"O zi buna!";
        return in;
    }
    cout << "Ce fel de investitor sunteti? (1 - pasiv | 2 - activ)\n";
    in >> tasta;
    switch (tasta) {
        case 1: {
            S.passive = true;
            break;
        }
        case 2: {
            S.passive = false;
            break;
        }
        default: {
            S.passive = false;
            cout << "Ati apasat alta tasta, ca urmare presupunem ca sunteti un investitor activ" << endl;
            break;
        }
    }
    cout << "Care sunt actiunile care va intereseaza cel mai mult?\n";
    in >> S.typeOfStocks;
    return in;
}

ostream &operator<<(ostream &out, const Shareholder &S) {
    out << "Vom dispune datele unui actioanr, asa cum ne-ati cerut.\n";
    out << "Nume de familie: " << S.last_name << endl;
    out << "Prenumele complet: " << S.first_name << endl;
    out << "CNP: " << S.CNP << endl;
    out << "Modul in care actioneaza investitorul: " << (S.passive ? "pasiv" : "activ") << endl;
    out << "Tipul de stocuri care il intereseaza cel mai mult: " << S.typeOfStocks << endl;
    return out;
}

char Shareholder::operator[](int index) {
    if (index >= 0 && index <= 13) {
        return this->CNP[index];
    }
    cout << "Indexul introdus nu este corect!" << endl;
    return '\0';
}

const Shareholder &Shareholder::operator--() {
    cout<<strlen(this->CNP)<<endl<<endl;
    char *CNP = new char[strlen(this->CNP)-2];
    for(int i=0; i<strlen(this->CNP)-1; ++i) {
        CNP[i] = this->CNP[i];
    }
    CNP[strlen(this->CNP)] = '\0';
    cout<<strlen(CNP);
    if(this->CNP != NULL)
        delete[] this->CNP;
    this->CNP = new char[strlen(CNP)];
    strcpy(this->CNP, CNP);
    delete[] CNP;
    return *this;
}

const Shareholder Shareholder::operator--(int) {
    cout<<strlen(this->CNP)<<endl<<endl;
    Shareholder S = *this;
    char *CNP = new char[strlen(this->CNP)-2];
    for(int i=0; i<strlen(this->CNP)-1; ++i) {
        CNP[i] = this->CNP[i];
    }
    CNP[strlen(this->CNP)] = '\0';
    cout<<strlen(CNP);
    if(this->CNP != NULL)
        delete[] this->CNP;
    this->CNP = new char[strlen(CNP)];
    strcpy(this->CNP, CNP);
    delete[] CNP;
    return S;
}

Shareholder Shareholder::operator+(string name) {
    Shareholder aux(*this);
    aux.first_name = aux.first_name + " " + name;
    return aux;
};

Shareholder operator+(string name, Shareholder shareholder) {
    shareholder.first_name = name + " " + shareholder.first_name;
    return shareholder;
}

Shareholder Shareholder::operator-(int size) {
    Shareholder aux(*this);
    char *CNP = new char[strlen(aux.CNP) + 1];
    for (int i = 0; i < strlen(aux.CNP) + 1; ++i) {
        CNP[i] = aux.CNP[i];
    }
    if (aux.CNP != NULL)
        delete[] aux.CNP;
    aux.CNP = new char[strlen(CNP) + 1 - size];
    for (int i = 0; i < strlen(CNP) - size; ++i) {
        aux.CNP[i] = CNP[i];
    }
    if (CNP != NULL)
        delete[] CNP;
    return aux;
}

Shareholder operator-(int size, Shareholder shareholder) {
    char *CNP = new char[strlen(shareholder.CNP) + 1];
    for (int i = 0; i < strlen(shareholder.CNP) + 1; ++i)
        CNP[i] = shareholder.CNP[i];
    if (shareholder.CNP != NULL)
        delete[] shareholder.CNP;
    shareholder.CNP = new char[strlen(CNP) + 1 - size];
    for (int i = 0; i < strlen(CNP) - size; ++i) {
        shareholder.CNP[i] = CNP[i];
    }
    if (CNP != NULL)
        delete[] CNP;
    return shareholder;
}

bool Shareholder::operator<(Shareholder shareholder) {
    return this->checkAge() < shareholder.checkAge();
}

bool Shareholder::operator==(Shareholder shareholder) {
    return this->checkAge() == shareholder.checkAge();
}
int Shareholder::count_account_id = 0;

class Stock {
private:
    string name;
    double revenue;
    int numberOfDirectors;
    string *staff;
    float *prices;

    const string currency;
    const string country;

    // The market is open or not
    bool available;

    // Growth, dividend, ...
    char *type;
    const int stock_id;
    static int counter_stock_id;

public:
    // Functionality
    string ratingStock(Shareholder &shareholder);

    // Setters
    void setName(string name);

    void setRevenue(double revenue);

    void setNumDirectors(int numberOfDirectors);

    void setStaff(string *staff);

    void setCurrentPrice(float *prices);

    void setAvailable(bool available);

    void setType(char *type);

//    Gettters
    string getName();

    double getRevenue();

    int getNumDirectors();

    const string *getStaff() const;

    const float *getCurrentPrice() const;

    string getCurrency();

    string getCountry();

    bool getAvailability();

    const char *getType();

    int getStockId();

//    Constructors | Destructors | Overloading operators
    Stock(string name, double revenue, int numberOfDirectors, string *staff, float *prices, string currency,
          string country, bool available, char *type);

    Stock(string name, double revenue, string currency, string country, char *type);

    Stock(string name, double revenue, float *prices);

    Stock();

    Stock(const Stock &stock);

    ~Stock();

    Stock &operator=(const Stock &stock);

    friend istream &operator>>(istream &in, Stock &S);

    friend ostream &operator<<(ostream &out, const Stock &S);

    string operator[](int);

    const Stock &operator--();

    const Stock operator--(int);

    Stock operator-(int);

    friend Stock operator-(int, Stock);

    Stock operator+(int);

    friend Stock operator+(int, Stock);

    explicit operator int() {
        int prices[*(&this->prices + 1) - this->prices];
        for (int i = 0; i < *(&this->prices + 1) - this->prices; ++i) {
            prices[i] = (int) this->prices[i];
        }
        return *prices;
    }

    bool operator<(Stock);

    bool operator==(Stock);
};

string Stock::ratingStock(Shareholder &shareholder) {
    if (this->type == NULL || shareholder.getTypeOfStocks() == "") {
        return "Nu se poate verifica compatibilitatea dintre utilizator si actiunea aleasa de el.";
    }
    if (!this->available) {
        return "This stock is not available or the market is not open yet";
    }
    if (!strcmp(this->type, shareholder.getTypeOfStocks().c_str())) {
        return "Acest stock are un rating de 10/10 pentru portofoliul dumneavoastra";
    } else {
        if (!shareholder.getPassive()) {
            if (!strcmp(this->type, "Growth") || !strcmp(this->type, "Value") || !strcmp(this->type, "IPO") ||
                !strcmp(this->type, "Blue chip") || !strcmp(this->type, "Penny")) {
                return "Acest stock are un rating de 7/10 pentru portofoliul dumneavoastra";
            } else if (!strcmp(this->type, "Dividend") || !strcmp(this->type, "Income")) {
                return "Acest stock are un rating de 5/10 pentru portofoliul dumneavoastra";
            } else {
                return "Acest stock are un rating de 3/10 pentru portofoliul dumneavoastra";
            }
        } else {
            if (!strcmp(this->type, "Dividend") || !strcmp(this->type, "Safe") || !strcmp(this->type, "Growth") ||
                !strcmp(this->type, "Large-cap")) {
                return "Acest stock are un rating de 7/10 pentru portofoliul dumneavoastra";
            } else if (!strcmp(this->type, "Value") || !strcmp(this->type, "Income")) {
                return "Acest stock are un rating de 5/10 pentru portofoliul dumneavoastra";
            } else {
                return "Acest stock are un rating de 3/10 pentru portofoliul dumneavoastra";
            }
        }
    }
}

void Stock::setName(string name) {
    this->name = name;
};

void Stock::setRevenue(double revenue) {
    this->revenue = revenue;
};

void Stock::setNumDirectors(int numberOfDirectors) {
    this->numberOfDirectors = numberOfDirectors;
};

void Stock::setStaff(string *staff) {
    if (this->staff != NULL) {
        delete[] this->staff;
    }
    this->staff = new string[this->numberOfDirectors];

    for (int i = 0; i < this->numberOfDirectors; ++i) {
        this->staff[i] = staff[i];
    }
};

void Stock::setCurrentPrice(float *prices) {
    if (this->prices != NULL) {
        delete[] this->prices;
    }
    // I want to set the prices for: now, a week ago, a month ago, a year ago
    this->prices = new float[4];
    for (int i = 0; i < 4; ++i) {
        this->prices[i] = prices[i];
    }
};

void Stock::setAvailable(bool available) {
    this->available = available;
};

void Stock::setType(char *type) {
    if (this->type != NULL) {
        delete[] this->type;
    }
    this->type = new char[strlen(type) + 1];
    strcpy(this->type, type);
};

string Stock::getName() {
    return this->name;
};

double Stock::getRevenue() {
    return this->revenue;
};

int Stock::getNumDirectors() {
    return this->numberOfDirectors;
};

const string *Stock::getStaff() const {
    return this->staff;
};

const float *Stock::getCurrentPrice() const {
    return this->prices;
};

string Stock::getCurrency() {
    return this->currency;
};

string Stock::getCountry() {
    return this->country;
};

bool Stock::getAvailability() {
    return this->available;
};

const char *Stock::getType() {
    return this->type;
};

int Stock::getStockId() {
    return this->stock_id;
};

Stock::Stock(string name, double revenue, int numberOfDirectors, string *staff, float *prices, string currency,
             string country, bool available, char *type) : stock_id(++counter_stock_id), country(country),
                                                           currency(currency) {
    this->name = name;
    this->revenue = revenue;
    this->numberOfDirectors = numberOfDirectors;
    this->staff = new string[numberOfDirectors];
    for (int i = 0; i < numberOfDirectors; ++i) {
        this->staff[i] = staff[i];
    }
    this->prices = new float[4];
    for (int i = 0; i < 4; ++i) {
        this->prices[i] = prices[i];
    }
    this->available = available;

    this->type = new char[strlen(type) + 1];
    strcpy(this->type, type);
};

Stock::Stock(string name, double revenue, string currency, string country, char *type) : stock_id(++counter_stock_id),
                                                                                         country(country),
                                                                                         currency(currency) {
    this->name = name;
    this->revenue = revenue;
    this->numberOfDirectors = 1;

    this->staff = new string[this->numberOfDirectors]{"John Tuesday"};

    this->prices = new float[4];
    this->prices[0] = 50;
    this->prices[1] = 43;
    this->prices[2] = 40.62;
    this->prices[3] = 28.17;

    this->available = true;

    this->type = new char[strlen(type) + 1];
    strcpy(this->type, type);
};

Stock::Stock(string name, double revenue, float *prices) : stock_id(++counter_stock_id), currency("$"),
                                                           country("United States of America") {
    this->name = name;
    this->revenue = revenue;
    this->numberOfDirectors = 1;

    this->staff = new string[this->numberOfDirectors]{"Henry Kennedy"};

    this->prices = new float[3];
    this->prices[0] = prices[0];
    this->prices[1] = prices[1];
    this->prices[2] = prices[2];
    this->prices[3] = prices[3];

    this->available = true;
    this->type = new char[strlen("Dividend") + 1];
    strcpy(this->type, "Dividend");
};

Stock::Stock() : stock_id(++counter_stock_id), currency("$"), country("United States of America") {
    this->name = "Netflix";
    this->revenue = 0;
    this->numberOfDirectors = 0;
    this->staff = NULL;
    this->prices = NULL;
    this->available = true;
    this->type = NULL;
};

Stock::Stock(const Stock &stock) : stock_id(++counter_stock_id), country(stock.country), currency(stock.currency) {
    this->name = stock.name;
    this->revenue = stock.revenue;
    this->numberOfDirectors = stock.numberOfDirectors;

    this->staff = new string[stock.numberOfDirectors];
    for (int i = 0; i < stock.numberOfDirectors; ++i) {
        this->staff[i] = stock.staff[i];
    }

    this->prices = new float[4];
    for (int i = 0; i < 4; ++i) {
        this->prices[i] = stock.prices[i];
    }
    this->available = stock.available;

    this->type = new char[strlen(stock.type) + 1];
    strcpy(this->type, stock.type);
}

Stock::~Stock() {
    if (this->prices != NULL)
        delete[] this->prices;
    if (this->staff != NULL)
        delete[] this->staff;
    if (this->type != NULL)
        delete[] this->type;
}

Stock &Stock::operator=(const Stock &stock) {
    if (this != &stock) {
        // Destructor
        if (this->prices != NULL)
            delete[] this->prices;
        if (this->staff != NULL)
            delete[] this->staff;
        if (this->type != NULL)
            delete[] this->type;

        // Constructor
        this->name = stock.name;
        this->revenue = stock.revenue;
        this->numberOfDirectors = stock.numberOfDirectors;

        this->staff = new string[stock.numberOfDirectors];
        for (int i = 0; i < stock.numberOfDirectors; ++i) {
            this->staff[i] = stock.staff[i];
        }

        this->prices = new float[4];
        for (int i = 0; i < 4; ++i) {
            this->prices[i] = stock.prices[i];
        }
        this->available = stock.available;

        this->type = new char[strlen(stock.type) + 1];
        strcpy(this->type, stock.type);
    }
    return *this;
}

istream &operator>>(istream &in, Stock &S) {
    string answer;
    string da = "Da|DA|da";
    char type[25];
    cout << "Introduceti datele unei actiuni:" << endl;
    cout << "Numele firmei: ";
    in >> S.name;
    cout << "Veniturile firmei: ";
    in >> S.revenue;
    cout << "Numarul de directori: ";
    in >> S.numberOfDirectors;

    if (S.staff != NULL)
        delete[] S.staff;
    S.staff = new string[S.numberOfDirectors];
    cout << "Numele celor " << S.numberOfDirectors << " directori (doar prenumele): " << endl;
    for (int i = 0; i < S.numberOfDirectors; ++i) {
        cout << i + 1 << ". ";
        in >> S.staff[i];
    }
    if (S.prices != NULL)
        delete[] S.prices;
    S.prices = new float[4];
    cout << "Pretul curent al actiunii este: ";
    in >> S.prices[0];
    cout << "Pretul de saptamana trecuta al actiunii este: ";
    in >> S.prices[1];
    cout << "Pretul de luna trecuta al actiunii este: ";
    in >> S.prices[2];
    cout << "Pretul de anul trecut al actiunii este: ";
    in >> S.prices[3];
    cout << "Vreti ca actiunea sa fie valabila? (Da/Nu)\n";
    in >> answer;
    if (strstr(da.c_str(), answer.c_str())) {
        S.available = true;
    } else {
        S.available = false;
    }
    cout << "Ce fel de actiune este?\n";
    in >> type;

    if (S.type != NULL)
        delete[] S.type;
    S.type = new char[strlen(type) + 1];
    strcpy(S.type, type);
    return in;
}

ostream &operator<<(ostream &out, const Stock &S) {
    out << "Vom dispune datele unui actionar, asa cum ne-ati cerut.\n";
    out << "Numele firmei: " << S.name << endl;
    out << "Veniturile firmei: " << S.revenue << endl;
    out << "Numarul de directori: " << S.numberOfDirectors << endl;
    out << "Numele celor " << S.numberOfDirectors << " directori: " << endl;
    for (int i = 0; i < S.numberOfDirectors; ++i) {
        out << i + 1 << ". " << S.staff[i] << endl;
    }
    out << "\nPreturile actiunii: " << endl;
    out << "Curent: " << S.prices[0] << endl;
    out << "Saptamana trecuta: " << S.prices[1] << endl;
    out << "Luna trecuta: " << S.prices[2] << endl;
    out << "Anul trecut: " << S.prices[3] << endl << endl;
    out << "Moneda cu care opereaza firma: " << S.currency << endl;
    out << "Tara in care opereaza firma: " << S.country << endl;
    out << "Actiunea " << (S.available ? "este" : "nu este") << " valabila" << endl;
    out << "Tipul actiunii: " << S.type << endl;
    return out;
}

// More operators
string Stock::operator[](int index) {
    if (index >= 0 && index <= this->numberOfDirectors) {
        return this->staff[index];
    }
    cout << "Indexul introdus nu este corect!" << endl;
    return "\0";
}

const Stock &Stock::operator--() {
    this->numberOfDirectors -= 1;
    string *newStaff = new string[this->numberOfDirectors];
    for (int i = 0; i < this->numberOfDirectors; ++i)
        newStaff[i] = this->staff[i];
    if (this->staff != NULL)
        delete[] this->staff;
    this->staff = new string[this->numberOfDirectors];
    for (int i = 0; i < this->numberOfDirectors; ++i) {
        this->staff[i] = newStaff[i];
    }
    if (newStaff != NULL)
        delete[] newStaff;
    return *this;
}

const Stock Stock::operator--(int) {
    Stock aux(*this);
    this->numberOfDirectors -= 1;
    string *newStaff = new string[this->numberOfDirectors];
    for (int i = 0; i < this->numberOfDirectors; ++i)
        newStaff[i] = this->staff[i];
    if (this->staff != NULL)
        delete[] this->staff;
    this->staff = new string[this->numberOfDirectors];
    for (int i = 0; i < this->numberOfDirectors; ++i) {
        this->staff[i] = newStaff[i];
    }
    if (newStaff != NULL)
        delete[] newStaff;
    return aux;
}

Stock Stock::operator-(int size) {
    Stock aux(*this);
    this->numberOfDirectors -= size;
    string *newStaff = new string[this->numberOfDirectors];
    for (int i = 0; i < this->numberOfDirectors; ++i)
        newStaff[i] = this->staff[i];
    if (this->staff != NULL)
        delete[] this->staff;
    this->staff = new string[this->numberOfDirectors];
    for (int i = 0; i < this->numberOfDirectors; ++i) {
        this->staff[i] = newStaff[i];
    }
    if (newStaff != NULL)
        delete[] newStaff;
    return aux;
}

Stock operator-(int size, Stock stock) {
    stock.numberOfDirectors -= size;
    string *newStaff = new string[stock.numberOfDirectors];
    for (int i = 0; i < stock.numberOfDirectors; ++i)
        newStaff[i] = stock.staff[i];
    if (stock.staff != NULL)
        delete[] stock.staff;
    stock.staff = new string[stock.numberOfDirectors];
    for (int i = 0; i < stock.numberOfDirectors; ++i) {
        stock.staff[i] = newStaff[i];
    }
    if (newStaff != NULL)
        delete[] newStaff;
    return stock;
}

Stock Stock::operator+(int revenue) {
    Stock aux(*this);
    aux.revenue = aux.revenue + (double) revenue;
    return aux;
}

Stock operator+(int revenue, Stock stock) {
    stock.revenue = (double) revenue + stock.revenue;
    return stock;
}

bool Stock::operator<(Stock stock) {
    return this->revenue < stock.revenue;
}

bool Stock::operator==(Stock stock) {
    return this->revenue == stock.revenue;
}

int Stock::counter_stock_id = 0;

class Transaction;

class BankDeposit {

private:
    const int account_id;
    string currency;
    double total_sum;
    int number_of_transactions;
    Transaction *transactions;
    string name;

public:
//    Functionality
    void payTransaction(const Transaction& transaction, double, bool, string);

//    Setters
    void setCurrency(string currency);

    void setTotalSum(double total_sum);

    void setNumOfTransactions(int number_of_transactions);

    void setTransactions(Transaction *transactions);

    void setName(string name);

//    Getters
    int getAccountId() const;

    string getCurrency();

    double getTotalSum();

    int getNumTransactions();

    const Transaction *getTransactions() const;

    string getName();

//    Constructors | Destructors | Overloading operator
    BankDeposit(Shareholder &shareholder, string currency, double total_sum, int number_of_transactions,
                Transaction *transactions, string name);

    BankDeposit(Shareholder &shareholder, string name);

    BankDeposit(Shareholder &shareholder, double total_sum);

    BankDeposit();

    BankDeposit(const BankDeposit &bankDeposit);

    ~BankDeposit();

    BankDeposit &operator=(const BankDeposit &bankDeposit);

    friend istream &operator>>(istream &in, BankDeposit &B);

    friend ostream &operator<<(ostream &out, const BankDeposit &B);

    // More Operators
    const BankDeposit &operator--();

    const BankDeposit operator--(int);

    BankDeposit operator-(int);

    friend BankDeposit operator-(int, BankDeposit);

    BankDeposit operator+(int);

    friend BankDeposit operator+(int, BankDeposit);

    explicit operator int() {
        return int(this->total_sum);
    }

    bool operator<(BankDeposit);

    bool operator==(BankDeposit);

    friend BankDeposit operator+(BankDeposit, const Transaction &);

    friend BankDeposit operator+(const Transaction &, BankDeposit);

    BankDeposit operator+(BankDeposit bankDeposit);
};

// Setters
void BankDeposit::setCurrency(string currency) {
    this->currency = currency;
}

void BankDeposit::setTotalSum(double total_sum) {
    this->total_sum = total_sum;
}

void BankDeposit::setNumOfTransactions(int number_of_transactions) {
    this->number_of_transactions = number_of_transactions;
}

void BankDeposit::setName(string name) {
    this->name = name;
}

// Getters
int BankDeposit::getAccountId() const {
    return this->account_id;
}

int BankDeposit::getNumTransactions() {
    return this->number_of_transactions;
}

string BankDeposit::getCurrency() {
    return this->currency;
}

double BankDeposit::getTotalSum() {
    return this->total_sum;
}

string BankDeposit::getName() {
    return this->name;
}

// More Operators
const BankDeposit &BankDeposit::operator--() {
    this->total_sum -= 1;
    return *this;
}

const BankDeposit BankDeposit::operator--(int) {
    BankDeposit aux(*this);
    this->total_sum -= 1;
    return aux;
}

BankDeposit BankDeposit::operator+(int sum) {
    BankDeposit aux(*this);
    aux.total_sum = aux.total_sum + (double) sum;
    return aux;
}

BankDeposit operator+(int sum, BankDeposit bankDeposit) {
    bankDeposit.total_sum = (double) sum + bankDeposit.total_sum;
    return bankDeposit;
}

bool BankDeposit::operator<(BankDeposit bankDeposit) {
    return this->total_sum < bankDeposit.total_sum;
}

bool BankDeposit::operator==(BankDeposit bankDeposit) {
    return this->total_sum == bankDeposit.total_sum;
}

class Transaction {

private:
    const int account_id;
    const int stock_id;

    float sum;
    // True if the stock and bank_deposit have different currencies
    bool different_currency;
    bool isConfirmed;

    // If different_Currency is true, set the fees attribute
    long fee;
    string transaction_date;

public:
//    Functionality
    double calculateSumOfMoneySpent(Stock &stock, BankDeposit &bankDeposit, float number_shares);

//    Getters
    bool getIsDifferentCurrency();

    bool getIsConfirmed();

    float getSum();

    long getFee();

    string getTransactionDate();

//    Constructors | Destructors | Overloading operators
    Transaction(Shareholder &shareholder, Stock &stock, float sum, bool different_currency, bool isConfirmed, long fee,
                string transaction_date);

    Transaction(Shareholder &shareholder, Stock &stock, BankDeposit &bankDeposit, float sum);

    Transaction(Shareholder &shareholder, bool isConfirmed, string transaction_date);

    Transaction();

    Transaction(const Transaction &transaction);

//     Destructor and Overloading operators
    ~Transaction();

    Transaction &operator=(const Transaction &transaction);

    friend istream &operator>>(istream &in, Transaction &T);

    friend ostream &operator<<(ostream &out, const Transaction &T);

    char operator[](int);

    const Transaction &operator++();

    const Transaction operator++(int);

    Transaction operator+(int);

    friend Transaction operator+(int, Transaction);

    Transaction operator*(int);

    friend Transaction operator*(int, Transaction);

    explicit operator int() {
        return (int) this->sum;
    }

    bool operator<(Transaction);

    bool operator==(Transaction);

    Transaction operator+(Transaction);
};

// Transaction functionality
double Transaction::calculateSumOfMoneySpent(Stock &stock, BankDeposit &bankDeposit, float number_shares) {
    // prices[0] -> current price
    float suma = stock.getCurrentPrice()[0] * number_shares;
    if (strcmp(stock.getCurrency().c_str(), bankDeposit.getCurrency().c_str())) {
        this->different_currency = true;
        this->fee = suma / float(100);
        suma += this->fee;
    } else {
        this->different_currency = false;
    }
    this->sum = suma;
    this->isConfirmed = true;
    return suma;
}

bool Transaction::getIsDifferentCurrency() {
    return this->different_currency;
}

bool Transaction::getIsConfirmed() {
    return this->isConfirmed;
}

long Transaction::getFee() {
    return this->fee;
}

float Transaction::getSum() {
    return this->sum;
}

string Transaction::getTransactionDate() {
    return this->transaction_date;
}

Transaction::Transaction(Shareholder &shareholder, Stock &stock, float sum, bool different_currency, bool isConfirmed,
                         long fee, string transaction_date) : account_id(shareholder.getShareholderId()),
                                                              stock_id(stock.getStockId()) {
    this->sum = sum;
    this->different_currency = different_currency;
    this->isConfirmed = isConfirmed;
    this->fee = fee;
    this->transaction_date = transaction_date;
}

Transaction::Transaction(Shareholder &shareholder, Stock &stock, BankDeposit &bankDeposit, float sum) : account_id(
        shareholder.getShareholderId()), stock_id(stock.getStockId()) {
    this->sum = sum;
    string currency = stock.getCurrency();
    if (currency != bankDeposit.getCurrency()) {
        this->different_currency = true;
    } else {
        this->different_currency = false;
    }
    this->isConfirmed = true;
    this->fee = this->different_currency ? sum / float(100) : 0;
    this->transaction_date = "";
}

Transaction::Transaction(Shareholder &shareholder, bool isConfirmed, string transaction_date) : account_id(
        shareholder.getShareholderId()), stock_id(0) {
    this->sum = 0;
    this->different_currency = false;
    this->isConfirmed = isConfirmed;
    this->fee = 0;
    this->transaction_date = transaction_date;
}

Transaction::Transaction() : account_id(0), stock_id(0) {
    this->sum = 0;
    this->different_currency = false;
    this->isConfirmed = false;
    this->fee = 0;
    this->transaction_date = "";
}

Transaction::Transaction(const Transaction &transaction) : account_id(transaction.account_id),
                                                           stock_id(transaction.stock_id) {
    this->sum = transaction.sum;
    this->different_currency = transaction.different_currency;
    this->isConfirmed = transaction.isConfirmed;
    this->fee = transaction.fee;
    this->transaction_date = transaction.transaction_date;
}

Transaction::~Transaction() {
    this->sum = 0;
    this->different_currency = false;
    this->isConfirmed = false;
    this->fee = 0;
    this->transaction_date = "";
}

Transaction &Transaction::operator=(const Transaction &transaction) {
    if (this != &transaction) {
        this->sum = transaction.sum;
        this->different_currency = transaction.different_currency;
        this->isConfirmed = transaction.isConfirmed;
        this->fee = transaction.fee;
        this->transaction_date = transaction.transaction_date;
    }
    return *this;
}

istream &operator>>(istream &in, Transaction &T) {
    string answer;
    string da = "Da|DA|da";

    cout << "Introduceti datele unei tranzactii:" << endl;
    cout << "Suma initiala ce trebuie achitata: ";
    in >> T.sum;
    cout << "Exista o diferenta intre valutele depozitului unde va tineti banii si cea a actiunii cumparate? (Da/Nu)\n";
    in >> answer;
    if (strstr(da.c_str(), answer.c_str())) {
        T.different_currency = true;
        cout << "Taxa pentru diferenta de valuta intre depozitul bancar si actiunea cumparata: ";
        in >> T.fee;
    } else {
        T.different_currency = false;
        T.fee = 0;
        cout << "Nu exista o taxa pentru diferenta de valuta(valoarea va fi 0)\n";
    }
    cout << "Vreti sa confirmati aceasta tranzactie? (Da/Nu)\n";
    in >> answer;
    if (strstr(da.c_str(), answer.c_str())) {
        T.isConfirmed = true;
    } else {
        T.isConfirmed = false;
    }
    cout << "Data tranzactionarii (MM/DD/YYYY): ";
    in >> T.transaction_date;
    return in;
}

ostream &operator<<(ostream &out, const Transaction &T) {
    out << "Vom dispune datele unei tranzactii, asa cum ne-ati cerut.\n";
    out << "Suma: " << T.sum + T.fee << endl;
    out << "Diferenta intre valute: " << (T.different_currency ? "da" : "nu") << endl;
    out << "Confirmare tranzactie: " << (T.isConfirmed ? "da" : "nu") << endl;
    out << "Din suma initiala " << T.fee << " reprezinta taxa pentru diferenta intre valute" << endl;
    out << "Data tranzactionarii (MM/DD/YYYY): " << T.transaction_date << endl;
    return out;
}

char Transaction::operator[](int index) {
    if (index >= 0 && index <= strlen(this->transaction_date.c_str())) {
        char *transaction_date = new char[strlen(this->transaction_date.c_str()) + 1];
        return transaction_date[index];
    }
    return '\0';
}

const Transaction &Transaction::operator++() {
    this->sum += 1;
    return *this;
}

const Transaction Transaction::operator++(int) {
    Transaction aux(*this);
    this->sum += 1;
    return aux;
}

Transaction Transaction::operator+(int sum) {
    Transaction aux(*this);
    aux.sum = aux.sum + (float) sum;
    return aux;
}

Transaction operator+(int sum, Transaction transaction) {
    transaction.sum = (float) sum + transaction.sum;
    return transaction;
}

Transaction Transaction::operator*(int sum) {
    Transaction aux(*this);
    aux.sum = aux.sum * (float) sum;
    return aux;
}

Transaction operator*(int sum, Transaction transaction) {
    transaction.sum = (float) sum * transaction.sum;
    return transaction;
}

bool Transaction::operator<(Transaction transaction) {
    return this->sum < transaction.sum;
}

bool Transaction::operator==(Transaction transaction) {
    return this->sum == transaction.sum;
}

Transaction Transaction::operator+(Transaction transaction) {
    transaction.sum += this->sum;
    transaction.different_currency = transaction.different_currency || this->different_currency;
    transaction.fee += this->fee;
    transaction.transaction_date = this->transaction_date;
    transaction.isConfirmed = transaction.isConfirmed || this->isConfirmed;
    return transaction;
}


// Continuare BankDepoasit
// Functionality
void BankDeposit::payTransaction(const Transaction& transaction, double sum, bool isConfirmed, string date) {
    this->number_of_transactions++;
    Transaction* transaction_aux = new Transaction[this->number_of_transactions];
    for(int i=0; i< this->number_of_transactions-1; ++i) {
        transaction_aux[i] = this->transactions[i];
    }
    transaction_aux[this->number_of_transactions-1] = transaction;
    if(this->transactions != NULL)
        delete[] this->transactions;

    this->transactions = new Transaction[this->number_of_transactions];
    for(int i=0; i<this->number_of_transactions; ++i) {
        this->transactions[i] = transaction_aux[i];
    }
    if(transaction_aux != NULL)
        delete[] transaction_aux;
    if (isConfirmed) {
        this->total_sum -= sum;
        cout << "A fost efectuata o tranzactie de " << sum << " pe " << date << endl;
        cout << "Banii ramasi pe cont: " << this->total_sum << endl;
    }
}
const Transaction *BankDeposit::getTransactions() const {
    return this->transactions;
}

void BankDeposit::setTransactions(Transaction *transactions) {
    if (this->transactions != NULL) {
        delete[] this->transactions;
    }
    this->transactions = new Transaction[this->number_of_transactions];
    for (int i = 0; i < this->number_of_transactions; ++i)
        this->transactions[i] = transactions[i];
}

// Constructors and Destructors
BankDeposit::BankDeposit(const BankDeposit &bankDeposit) : account_id(bankDeposit.account_id),
                                                           currency(bankDeposit.currency) {
    this->total_sum = bankDeposit.total_sum;
    this->number_of_transactions = bankDeposit.number_of_transactions;
    this->transactions = new Transaction[bankDeposit.number_of_transactions];
    for (int i = 0; i < this->number_of_transactions; ++i)
        this->transactions[i] = bankDeposit.transactions[i];
    this->name = bankDeposit.name;
}

BankDeposit::BankDeposit(Shareholder &shareholder, string currency, double total_sum, int number_of_transactions,
                         Transaction *transactions, string name) : account_id(shareholder.getShareholderId()),
                                                                   currency(currency) {
    this->total_sum = total_sum;
    this->number_of_transactions = number_of_transactions;
    this->transactions = new Transaction[number_of_transactions];
    if (this->transactions != NULL)
        delete[] this->transactions;
    for (int i = 0; i < this->number_of_transactions; ++i) {
        this->transactions[i] = transactions[i];
    }
    this->name = name;
}

BankDeposit::BankDeposit(Shareholder &shareholder, string name) : account_id(shareholder.getShareholderId()),
                                                                  currency("$") {
    this->total_sum = 100000;
    this->number_of_transactions = 0;
    this->transactions = NULL;
    this->name = name;

}

BankDeposit::BankDeposit(Shareholder &shareholder, double total_sum) : account_id(shareholder.getShareholderId()),
                                                                       currency("$") {
    this->total_sum = total_sum;
    this->number_of_transactions = 0;
    this->transactions = NULL;
    this->name = "";
}

BankDeposit::BankDeposit() : account_id(0), currency("$") {
    this->total_sum = 10000;
    this->number_of_transactions = 0;
    this->transactions = NULL;
    this->name = "";
}

BankDeposit::~BankDeposit() {
    this->total_sum = 0;
    this->number_of_transactions = 0;
    if (this->transactions != NULL)
        delete[] this->transactions;
    this->name = "";
    this->currency = "";
}

// Operators
BankDeposit &BankDeposit::operator=(const BankDeposit &bankDeposit) {
    if (this != &bankDeposit) {
        if (this->transactions != NULL)
            delete[] this->transactions;

        this->number_of_transactions = bankDeposit.number_of_transactions;
        this->transactions = new Transaction[bankDeposit.number_of_transactions];
        for (int i = 0; i < this->number_of_transactions; ++i)
            this->transactions[i] = bankDeposit.transactions[i];
        this->total_sum = bankDeposit.total_sum;
        this->name = bankDeposit.name;
        this->currency = bankDeposit.currency;
    }
    return *this;
}

istream &operator>>(istream &in, BankDeposit &B) {
    cout << "Introduceti datele unui depozit bancar:" << endl;
    cout << "Numele depozitului: ";
    in >> B.name;
    cout << "Valuta: ";
    in >> B.currency;
    cout << "Suma valabila in depozit: ";
    in >> B.total_sum;
    B.number_of_transactions = 0;
    B.transactions = NULL;
    return in;
}

ostream &operator<<(ostream &out, const BankDeposit &B) {
    out << "Vom dispune datele unui depozit bancar, asa cum ne-ati cerut.\n";
    out << "Numele depozitului: " << B.name << endl;
    out << "Valuta: " << B.currency << endl;
    out << "Suma valabila in depozit: " << B.total_sum << endl;
    out << "Numarul de tranzactii din istoricul depozitului bancar: " << B.number_of_transactions << endl << endl;
    if (B.number_of_transactions) {
        out << "Cele " << B.number_of_transactions << " tranzactii:" << endl;
    }
    for (int i = 0; i < B.number_of_transactions; ++i) {
        out << i + 1 << ". ";
        out << B.transactions[i] << endl;
    }
    return out;
}

BankDeposit BankDeposit::operator-(int size) {
    BankDeposit aux(*this);
    Transaction *transactions = new Transaction[aux.number_of_transactions];
    for (int i = 0; i < aux.number_of_transactions; ++i) {
        transactions[i] = aux.transactions[i];
    }
    if (aux.transactions != NULL)
        delete[] aux.transactions;
    aux.transactions = new Transaction[*(&transactions + 1) - transactions - size];
    for (int i = 0; i < *(&transactions + 1) - transactions - size; ++i) {
        aux.transactions[i] = transactions[i];
    }
    if (transactions != NULL)
        delete[] transactions;
    return aux;
}

BankDeposit operator-(int size, BankDeposit bankDeposit) {
    Transaction *transactions = new Transaction[bankDeposit.number_of_transactions];
    for (int i = 0; i < bankDeposit.number_of_transactions; ++i) {
        transactions[i] = bankDeposit.transactions[i];
    }
    if (bankDeposit.transactions != NULL)
        delete[] bankDeposit.transactions;
    bankDeposit.transactions = new Transaction[*(&transactions + 1) - transactions - size];
    for (int i = 0; i < *(&transactions + 1) - transactions - size; ++i) {
        bankDeposit.transactions[i] = transactions[i];
    }
    if (transactions != NULL)
        delete[] transactions;
    return bankDeposit;
}

BankDeposit operator+(BankDeposit bankDeposit, const Transaction &transaction) {
    bankDeposit.number_of_transactions += 1;
    Transaction *aux = new Transaction[bankDeposit.number_of_transactions];
    for (int i = 0; i < bankDeposit.number_of_transactions - 1; ++i) {
        aux[i] = bankDeposit.transactions[i];
    }
    aux[bankDeposit.number_of_transactions - 1] = transaction;
    if (bankDeposit.transactions != NULL)
        delete[] bankDeposit.transactions;
    bankDeposit.transactions = new Transaction[bankDeposit.number_of_transactions];
    for (int i = 0; i < bankDeposit.number_of_transactions; ++i) {
        bankDeposit.transactions[i] = aux[i];
    }
    return bankDeposit;
}

BankDeposit operator+(const Transaction &transaction, BankDeposit bankDeposit) {
    bankDeposit.number_of_transactions += 1;
    Transaction *aux = new Transaction[bankDeposit.number_of_transactions];
    for (int i = 0; i < bankDeposit.number_of_transactions - 1; ++i) {
        aux[i] = bankDeposit.transactions[i];
    }
    aux[bankDeposit.number_of_transactions - 1] = transaction;
    if (bankDeposit.transactions != NULL)
        delete[] bankDeposit.transactions;
    bankDeposit.transactions = new Transaction[bankDeposit.number_of_transactions];
    for (int i = 0; i < bankDeposit.number_of_transactions; ++i) {
        bankDeposit.transactions[i] = aux[i];
    }
    return bankDeposit;
}

BankDeposit BankDeposit::operator+(BankDeposit bankDeposit) {
    bankDeposit.total_sum += this->total_sum;
    bankDeposit.name = bankDeposit.name + " " + this->name;
    bankDeposit.number_of_transactions += this->number_of_transactions;
    bankDeposit.currency = this->currency;
    Transaction *transaction = new Transaction[bankDeposit.number_of_transactions];
    for (int i = 0; i < this->number_of_transactions; ++i) {
        transaction[i] = this->transactions[i];
    }
    for (int i = this->number_of_transactions; i < bankDeposit.number_of_transactions; ++i) {
        transaction[i] = bankDeposit.transactions[i];
    }
    for (int i = 0; i < bankDeposit.number_of_transactions; ++i) {
        bankDeposit.transactions[i] = transaction[i];
    }
    if (transaction != NULL)
        delete[] transaction;
    return bankDeposit;
}

list <Transaction> transactions;
list <Shareholder> shareholder;
list <Stock> stock;
list <BankDeposit> bankDeposit;
int comanda;

void createCRUDMenu();

int main() {
    Transaction T;
    BankDeposit B;
    cout<<B+T;
    return 0;
}

void createCRUDMenu() {
    while (comanda != 5) {
        cout
                << "Bun venit in noul meniu al acestei aplicatii. Acest meniu va permite sa folositi operatiile CRUD pentru clasele voastre.\nMai intai de toate trebuie sa alegeti clasa cu care vreti sa lucrati:\n";
        cout << endl << "1.Shareholder\n2.Stock\n3.Transaction\n4.BankDeposit\n5.Exit\n";
        cout << "Tasta: ";
        cin >> comanda;
        switch (comanda) {
            case 1: {
                int comanda_shareholder=0;
                while (comanda_shareholder != 5) {
                    cout << "Acum trebuie sa alegeti ce operatie doriti sa faceti:\n";
                    cout << endl << "1.Create\n2.Read\n3.Update\n4.Delete\n5.Back\n\n";
                    cout << "Comanda:";
                    cin >> comanda_shareholder;
                    switch (comanda_shareholder) {
                        case 1: {
                            int comanda_shareholder_create = 0;
                            while (comanda_shareholder_create != 5) {
                                cout << "Alegeti in ce mod vreti sa creati acest actionar:\n";
                                cout << endl
                                     << "1.Constructorul fara parametri\n2.Constructorul cu toti parametri\n3.Constructorul doar datele de baza(nume, prenume, CNP)\n4.Constructorul doar cu CNP\n5.Back\n\n";
                                cout << "Comanda: ";
                                cin >> comanda_shareholder_create;
                                switch (comanda_shareholder_create) {
                                    case 1: {
                                        Shareholder S;
                                        shareholder.push_back(S);
                                        cout << endl;
                                        break;
                                    }
                                    case 2: {
                                        Shareholder S;
                                        cin >> S;
                                        shareholder.push_back(S);
                                        cout << endl;
                                        break;
                                    }
                                    case 3: {
                                        string nume, prenume;
                                        string CNP_aux;
                                        cout << "Introduceti datele actionarului:\n";
                                        cout << "Nume: ";
                                        cin >> nume;
                                        cout << "Prenume: ";
                                        cin >> prenume;
                                        cout << "CNP: ";
                                        cin >> CNP_aux;
                                        cout << endl;
                                        char *CNP = new char[strlen(CNP_aux.c_str()) + 1];
                                        strcpy(CNP, CNP_aux.c_str());
                                        Shareholder S(nume, prenume, CNP);
                                        shareholder.push_back(S);
                                        cout << endl;
                                        break;
                                    }
                                    case 4: {
                                        string CNP_aux;
                                        cout << "Introduceti datele actionarului:\n";
                                        cout << "CNP: ";
                                        cin >> CNP_aux;
                                        cout << endl;
                                        char *CNP = new char[strlen(CNP_aux.c_str()) + 1];
                                        strcpy(CNP, CNP_aux.c_str());
                                        Shareholder S(CNP);
                                        shareholder.push_back(S);
                                        cout << endl;
                                        break;
                                    }
                                    case 5: {
                                        break;
                                    }
                                    default: {
                                        cout << "Nu exista aceasta comanda!" << endl;
                                        continue;
                                    }
                                }
                            }
                            break;
                        }
                        case 2: {
                            bool comanda_shareholder_read = true;
                            list<Shareholder>::iterator it_shareholder;
                            int index;
                            while (comanda_shareholder_read) {
                                cout << "Alegeti al catelea element din lista de actionari vreti sa fie afisat: ";
                                cin >> index;
                                it_shareholder = shareholder.begin();
                                advance(it_shareholder, index - 1);
                                if (it_shareholder == shareholder.end()) {
                                    cout << "Elementul pe care incercati sa il accesati nu exista!" << endl;
                                    comanda_shareholder_read = false;
                                } else {
                                    cout << *it_shareholder << endl;
                                    string answer;
                                    cout << "Vreti sa continuati? (Da/Nu)";
                                    cin >> answer;
                                    if ("Da" != answer)
                                        comanda_shareholder_read = false;
                                }
                            }
                            comanda_shareholder = 0;
                            break;
                        }
                        case 3: {
                            bool comanda_shareholder_update = true;
                            list<Shareholder>::iterator it_shareholder;
                            int index;
                            while (comanda_shareholder_update) {
                                cout << "Alegeti al catelea element din lista de actionari vreti sa fie updatat: ";
                                cin >> index;
                                it_shareholder = shareholder.begin();
                                advance(it_shareholder, index - 1);
                                if (it_shareholder == shareholder.end()) {
                                    cout << "Elementul pe care incercati sa il accesati nu exista!" << endl;
                                    comanda_shareholder_update = false;
                                } else {
                                    Shareholder shareholder_aux;
                                    cin >> shareholder_aux;
                                    *it_shareholder = shareholder_aux;
                                    cout << endl;
                                    string answer;
                                    cout << "Vreti sa continuati? (Da/Nu)";
                                    cin >> answer;
                                    if ("Da" != answer)
                                        comanda_shareholder_update = false;
                                }
                            }
                            comanda_shareholder = 0;
                            break;
                        }
                        case 4: {
                            bool comanda_shareholder_delete = true;
                            list<Shareholder>::iterator it_shareholder;
                            int index;
                            while (comanda_shareholder_delete) {
                                cout << "Alegeti al catelea element din lista de actionari vreti sa fie sters: ";
                                cin >> index;
                                it_shareholder = shareholder.begin();
                                advance(it_shareholder, index - 1);
                                if (it_shareholder == shareholder.end()) {
                                    cout << "Elementul pe care incercati sa il accesati nu exista!" << endl;
                                    comanda_shareholder_delete = false;
                                } else {
                                    shareholder.erase(it_shareholder);
                                    cout << endl;
                                    string answer;
                                    cout << "Vreti sa continuati? (Da/Nu)";
                                    cin >> answer;
                                    if ("Da" != answer)
                                        comanda_shareholder_delete = false;
                                }
                            }
                            comanda_shareholder = 0;
                            break;
                        }
                        case 5: {
                            break;
                        }
                        default:
                            comanda_shareholder = 0;
                            cout << "Nu exista aceasta comanda!" << endl;
                            continue;
                    }

                }
            }
            case 2: {
                int comanda_stock;
                while (comanda_stock != 5) {
                    cout << "Acum trebuie sa alegeti ce operatie doriti sa faceti:\n";
                    cout << endl << "1.Create\n2.Read\n3.Update\n4.Delete\n5.Back\n\n";
                    cout << "Comanda:";
                    cin >> comanda_stock;
                    switch (comanda_stock) {
                        case 1: {
                            int comanda_stock_create;
                            while (comanda_stock_create != 3) {
                                cout << "Alegeti in ce mod vreti sa creati aceasta actiune:\n";
                                cout << endl
                                     << "1.Constructorul fara parametri\n2.Constructorul cu toti parametri\n3.Back\n\n";
                                cout << "Comanda: ";
                                cin >> comanda_stock_create;
                                switch (comanda_stock_create) {
                                    case 1: {
                                        Stock S;
                                        stock.push_back(S);
                                        cout << endl;
                                        break;
                                    }
                                    case 2: {
                                        Stock S;
                                        cin >> S;
                                        stock.push_back(S);
                                        cout << endl;
                                        break;
                                    }
                                    case 3: {
                                        comanda_stock = 0;
                                        break;
                                    }
                                    default: {
                                        cout << "Nu exista aceasta comanda!" << endl;
                                        continue;
                                    }
                                }
                            }
                            comanda_stock = 0;
                            break;
                        }
                        case 2: {
                            bool comanda_stock_read = true;
                            list<Stock>::iterator it_stock;
                            int index;
                            while (comanda_stock_read) {
                                cout << "Alegeti al catelea element din lista de actiuni vreti sa fie afisat: ";
                                cin >> index;
                                it_stock = stock.begin();
                                advance(it_stock, index - 1);
                                if (it_stock == stock.end()) {
                                    cout << "Elementul pe care incercati sa il accesati nu exista!" << endl;
                                    comanda_stock_read = false;
                                } else {
                                    cout << *it_stock << endl;
                                    string answer;
                                    cout << "Doriti sa continuati? (Da/Nu)";
                                    cin >> answer;
                                    if ("Da" != answer) {
                                        comanda_stock_read = false;
                                    }
                                }
                            }
                            comanda_stock_read = true;
                            break;
                        }
                        case 3: {
                            bool comanda_stock_update = true;
                            list<Stock>::iterator it_stock;
                            int index;
                            while (comanda_stock_update) {
                                cout << "Alegeti al catelea element din lista de actiuni vreti sa fie updatat: ";
                                cin >> index;
                                it_stock = stock.begin();
                                advance(it_stock, index - 1);
                                if (it_stock == stock.end()) {
                                    cout << "Elementul pe care incercati sa il accesati nu exista!" << endl;
                                    comanda_stock_update = false;
                                } else {
                                    Stock stock_aux;
                                    cin >> stock_aux;
                                    *it_stock = stock_aux;
                                    cout << endl;
                                    string answer;
                                    cout << "Vreti sa continuati? (Da/Nu)";
                                    cin >> answer;
                                    if ("Da" != answer)
                                        comanda_stock_update = false;
                                }
                            }
                            comanda_stock_update = true;
                            break;
                        }
                        case 4: {
                            bool comanda_stock_delete = true;
                            list<Stock>::iterator it_stock;
                            int index;
                            while (comanda_stock_delete) {
                                cout << "Alegeti al catelea element din lista de actiuni vreti sa fie sters: ";
                                cin >> index;
                                it_stock = stock.begin();
                                advance(it_stock, index - 1);
                                if (it_stock == stock.end()) {
                                    cout << "Elementul pe care incercati sa il accesati nu exista!" << endl;
                                    comanda_stock_delete = false;
                                } else {
                                    stock.erase(it_stock);
                                    cout << endl;
                                    string answer;
                                    cout << "Vreti sa continuati? (Da/Nu)";
                                    cin >> answer;
                                    if ("Da" != answer)
                                        comanda_stock_delete = false;
                                }
                            }
                            comanda_stock_delete = true;
                            break;
                        }
                        case 5: {
                            break;
                        }
                        default:
                            comanda_stock = 0;
                            cout << "Nu exista aceasta comanda!" << endl;
                            continue;
                    }

                }
            }
            case 3: {
                int comanda_transaction;
                while (comanda_transaction != 5) {
                    cout << "Acum trebuie sa alegeti ce operatie doriti sa faceti:\n";
                    cout << endl << "1.Create\n2.Read\n3.Update\n4.Delete\n5.Back\n\n";
                    cout << "Comanda:";
                    cin >> comanda_transaction;
                    switch (comanda_transaction) {
                        case 1: {
                            int comanda_transaction_create;
                            while (comanda_transaction_create != 5) {
                                cout << "Alegeti in ce mod vreti sa creati aceasta tranzactie:\n";
                                cout << endl
                                     << "1.Constructorul fara parametri\n2.Constructorul cu toti parametri\n3.Constructorul cu parametrul pentru suma.\n4.Constructorul cu parametrul pentru data tranzactionarii\n5.Back\n\n";
                                cout << "Comanda: ";
                                cin >> comanda_transaction_create;
                                switch (comanda_transaction_create) {
                                    case 1: {
                                        Transaction T;
                                        transactions.push_back(T);
                                        cout << endl;
                                        break;
                                    }
                                    case 2: {
                                        Transaction T;
                                        cin >> T;
                                        transactions.push_back(T);
                                        cout << endl;
                                        break;
                                    }
                                    case 3: {
                                        float suma;
                                        cout << "Introduceti suma: ";
                                        cin >> suma;
                                        Shareholder S;
                                        Stock st;
                                        BankDeposit B;
                                        Transaction T(S, st, B, suma);
                                        transactions.push_back(T);
                                        cout << endl;
                                        break;
                                    }
                                    case 4: {
                                        string transaction_date;
                                        cout << "Introduceti data tranzactionarii: ";
                                        cin >> transaction_date;
                                        Shareholder S;
                                        Transaction T(S, true, transaction_date);
                                        transactions.push_back(T);
                                        cout << endl;
                                        break;
                                    }
                                    case 5: {
                                        break;
                                    }
                                    default: {
                                        cout << "Nu exista aceasta comanda!" << endl;
                                        continue;
                                    }
                                }
                            }
                            break;
                        }
                        case 2: {
                            bool comanda_transaction_read = true;
                            list<Transaction>::iterator it_transaction;
                            int index;
                            while (comanda_transaction_read) {
                                cout << "Alegeti al catelea element din lista de tranzactii vreti sa fie afisat: ";
                                cin >> index;
                                it_transaction = transactions.begin();
                                advance(it_transaction, index - 1);
                                if (it_transaction == transactions.end()) {
                                    cout << "Elementul pe care incercati sa il accesati nu exista!" << endl;
                                    comanda_transaction_read = false;
                                } else {
                                    cout << *it_transaction << endl;
                                    string answer;
                                    cout << "Doriti sa continuati? (Da/Nu)";
                                    cin >> answer;
                                    if ("Da" != answer) {
                                        comanda_transaction_read = false;
                                    }
                                }
                            }
                            break;
                        }
                        case 3: {
                            bool comanda_transaction_update = true;
                            list<Transaction>::iterator it_transaction;
                            int index;
                            while (comanda_transaction_update) {
                                cout << "Alegeti al catelea element din lista de tranzactii vreti sa fie updatat: ";
                                cin >> index;
                                it_transaction = transactions.begin();
                                advance(it_transaction, index - 1);
                                if (it_transaction == transactions.end()) {
                                    cout << "Elementul pe care incercati sa il accesati nu exista!" << endl;
                                    comanda_transaction_update = false;
                                } else {
                                    Transaction transaction_aux;
                                    cin >> transaction_aux;
                                    *it_transaction = transaction_aux;
                                    cout << endl;
                                    string answer;
                                    cout << "Vreti sa continuati? (Da/Nu)";
                                    cin >> answer;
                                    if ("Da" != answer)
                                        comanda_transaction_update = false;
                                }
                            }
                            break;
                        }
                        case 4: {
                            bool comanda_transaction_delete = true;
                            list<Transaction>::iterator it_transaction;
                            int index;
                            while (comanda_transaction_delete) {
                                cout << "Alegeti al catelea element din lista de tranzactii vreti sa fie sters: ";
                                cin >> index;
                                it_transaction = transactions.begin();
                                advance(it_transaction, index - 1);
                                if (it_transaction == transactions.end()) {
                                    cout << "Elementul pe care incercati sa il accesati nu exista!" << endl;
                                    comanda_transaction_delete = false;
                                } else {
                                    transactions.erase(it_transaction);
                                    cout << endl;
                                    string answer;
                                    cout << "Vreti sa continuati? (Da/Nu)";
                                    cin >> answer;
                                    if ("Da" != answer)
                                        comanda_transaction_delete = false;
                                }
                            }
                            break;
                        }
                        case 5: {
                            break;
                        }
                        default:
                            comanda_transaction = 0;
                            cout << "Nu exista aceasta comanda!" << endl;
                            continue;
                    }

                }
                comanda_transaction = 0;
                break;
            }
            case 4: {
                int comanda_bankDeposit;
                while (comanda_bankDeposit != 5) {
                    cout << "Acum trebuie sa alegeti ce operatie doriti sa faceti:\n";
                    cout << endl << "1.Create\n2.Read\n3.Update\n4.Delete\n5.Back\n\n";
                    cout << "Comanda:";
                    cin >> comanda_bankDeposit;
                    switch (comanda_bankDeposit) {
                        case 1: {
                            int comanda_bankDeposit_create;
                            while (comanda_bankDeposit_create != 5) {
                                cout << "Alegeti in ce mod vreti sa creati acest actionar:\n";
                                cout << endl
                                     << "1.Constructorul fara parametri\n2.Constructorul cu toti parametri\n3.Constructorul cu parametrul pentru nume\n4.Constructorul cu parametru pentru suma depusa\n5.Back\n\n";
                                cout << "Comanda: ";
                                cin >> comanda_bankDeposit_create;
                                switch (comanda_bankDeposit_create) {
                                    case 1: {
                                        BankDeposit B;
                                        bankDeposit.push_back(B);
                                        cout << endl;
                                        break;
                                    }
                                    case 2: {
                                        BankDeposit B;
                                        cin >> B;
                                        bankDeposit.push_back(B);
                                        cout << endl;
                                        break;
                                    }
                                    case 3: {
                                        Shareholder S;
                                        string name;
                                        cout << "Introduceti numele depozitului: ";
                                        cin >> name;
                                        BankDeposit B(S, name);
                                        bankDeposit.push_back(B);
                                        cout << endl;
                                        break;
                                    }
                                    case 4: {
                                        Shareholder S;
                                        double sum;
                                        cout << "Introduceti suma depozitului: ";
                                        cin >> sum;
                                        BankDeposit B(S, sum);
                                        bankDeposit.push_back(B);
                                        cout << endl;
                                        break;
                                    }
                                    case 5: {
                                        break;
                                    }
                                    default: {
                                        cout << "Nu exista aceasta comanda!" << endl;
                                        continue;
                                    }
                                }
                            }
                            comanda_bankDeposit = 0;
                            break;
                        }
                        case 2: {
                            bool comanda_bankDeposit_read = true;
                            list<BankDeposit>::iterator it_bankDeposit;
                            int index;
                            while (comanda_bankDeposit_read) {
                                cout << "Alegeti al catelea element din lista de depoztie vreti sa fie afisat: ";
                                cin >> index;
                                it_bankDeposit = bankDeposit.begin();
                                advance(it_bankDeposit, index - 1);
                                if (it_bankDeposit == bankDeposit.end()) {
                                    cout << "Elementul pe care incercati sa il accesati nu exista!" << endl;
                                    comanda_bankDeposit_read = false;
                                } else {
                                    cout << *it_bankDeposit << endl;
                                    string answer;
                                    cout << "Doriti sa continuati? (Da/Nu)";
                                    cin >> answer;
                                    if ("Da" != answer) {
                                        comanda_bankDeposit_read = false;
                                    }
                                }
                            }
                            break;
                        }
                        case 3: {
                            bool comanda_bankDeposit_update = true;
                            list<BankDeposit>::iterator it_bankDeposit;
                            int index;
                            while (comanda_bankDeposit_update) {
                                cout << "Alegeti al catelea element din lista de depozite vreti sa fie updatat: ";
                                cin >> index;
                                it_bankDeposit = bankDeposit.begin();
                                advance(it_bankDeposit, index - 1);
                                if (it_bankDeposit == bankDeposit.end()) {
                                    cout << "Elementul pe care incercati sa il accesati nu exista!" << endl;
                                    comanda_bankDeposit_update = false;
                                } else {
                                    BankDeposit bankDeposit_aux;
                                    cin >> bankDeposit_aux;
                                    *it_bankDeposit = bankDeposit_aux;
                                    cout << endl;
                                    string answer;
                                    cout << "Vreti sa continuati? (Da/Nu)";
                                    cin >> answer;
                                    if ("Da" != answer)
                                        comanda_bankDeposit_update = false;
                                }
                            }
                            break;
                        }
                        case 4: {
                            bool comanda_bankDeposit_delete = true;
                            list<BankDeposit>::iterator it_bankDeposit;
                            int index;
                            while (comanda_bankDeposit_delete) {
                                cout << "Alegeti al catelea element din lista de depozitie vreti sa fie sters: ";
                                cin >> index;
                                it_bankDeposit = bankDeposit.begin();
                                advance(it_bankDeposit, index - 1);
                                if (it_bankDeposit == bankDeposit.end()) {
                                    cout << "Elementul pe care incercati sa il accesati nu exista!" << endl;
                                    comanda_bankDeposit_delete = false;
                                } else {
                                    bankDeposit.erase(it_bankDeposit);
                                    cout << endl;
                                    string answer;
                                    cout << "Vreti sa continuati? (Da/Nu)";
                                    cin >> answer;
                                    if ("Da" != answer)
                                        comanda_bankDeposit_delete = false;
                                }
                            }
                            break;
                        }
                        case 5: {
                            break;
                        }
                        default:
                            comanda_bankDeposit = 0;
                            cout << "Nu exista aceasta comanda!" << endl;
                            continue;
                    }

                }
                comanda_bankDeposit = 0;
                break;
            }
            case 5: {
                cout<<"Multumim pentru ca ati folosit aplicatia noastra! O zi buna!"<<endl;
                break;
            }
            default:
                cout<<"Nu exista aceasta comanda!"<<endl;
                continue;
        }
    }

}