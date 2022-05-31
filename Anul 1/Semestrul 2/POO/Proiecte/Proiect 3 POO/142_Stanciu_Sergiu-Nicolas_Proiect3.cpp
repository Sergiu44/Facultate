#include <iostream>
#include <cstring>
#include <vector>
#include <list>
#include <map>
#include <typeinfo>
#include <set>

using namespace std;

class IOInterface {
public:
    virtual ostream &read(ostream &) const = 0;

    virtual istream &write(istream &) = 0;
};

class indexException : public exception {
public:
    virtual const char *what() {
        return "Input-ul introdus nu este bun.";
    }
} indexEx;

class sumException : public exception {
public:
    virtual const char *what() {
        return "Valoarea trebuie sa fie maxim 100, vom seta implicit rezultatul la 100";
    }
} sumEx;

class typeException : public exception {
public:
    virtual const char *what() {
        return "Cuvantul introdus nu este corect!";
    }
} typeEx;

class badCast : public exception {
public:
    virtual const char *what() {
        return "Bad cast!";
    }
} badCastEx;

template<class V, class U>
V adunare(V nr1, U nr2) {
    try {
        if (nr1 + nr2 > 100) {
            throw sumEx;
        } else {
            return nr1 + nr2;
        }
    } catch (sumException &e) {
        cout << e.what() << endl;
        return 100;
    }
}

template<class V>
V inmultire(V nr1, V nr2) {
    return nr1 * nr2;
}

class Player {
protected:
    string firstName;
    string lastName;
    unsigned int age;
    string mainFoot;

    bool injured;
    unsigned int pace;
    unsigned int shooting;
    unsigned int physical;

    unsigned int stamina;

public:
    Player(string firstName = "John", string lastName = "Stuard", unsigned int age = 18, string mainFoot = "drept",
           bool injured = false, unsigned int pace = 75, unsigned int shooting = 75, unsigned int physical = 75,
           unsigned int stamina = 75);

    Player(const Player &player);

    Player &operator=(const Player &player);

    ~Player();

    virtual ostream &read(ostream &) const;

    virtual istream &write(istream &);

    friend istream &operator>>(istream &, Player &player);

    friend ostream &operator<<(ostream &, const Player &player);

    virtual void increaseStats() = 0;
};

Player::Player(string firstName, string lastName, unsigned int age, string mainFoot, bool injured, unsigned int pace,
               unsigned int shooting, unsigned int physical, unsigned int stamina) {
    this->firstName = firstName;
    this->lastName = lastName;
    this->age = age;
    this->mainFoot = mainFoot;
    this->injured = injured;
    this->pace = pace;
    this->shooting = shooting;
    this->physical = physical;
    this->stamina = stamina;
}

Player::Player(const Player &player) {
    this->firstName = player.firstName;
    this->lastName = player.lastName;
    this->age = player.age;
    this->mainFoot = player.mainFoot;
    this->injured = player.injured;
    this->pace = player.pace;
    this->shooting = player.shooting;
    this->physical = player.physical;
    this->stamina = player.stamina;
}

Player &Player::operator=(const Player &player) {
    if (this != &player) {
        this->firstName = player.firstName;
        this->lastName = player.lastName;
        this->age = player.age;
        this->mainFoot = player.mainFoot;
        this->injured = player.injured;
        this->pace = player.pace;
        this->shooting = player.shooting;
        this->physical = player.physical;
        this->stamina = player.stamina;
    }
    return *this;
}

Player::~Player() {
    cout << "Destructor Player" << endl;
}

ostream &Player::read(ostream &out) const {
    out << "Prenume: " << this->firstName << "     ";
    out << "Nume de familie: " << this->lastName << "     ";
    out << "Varsta: " << this->age << endl;
    out << "Piciorul de baza: " << this->mainFoot << "       ";
    out << "Accidentat: " << (this->injured ? "DA" : "NU") << "     ";
    out << "Pace: " << this->pace << "     ";
    out << "Physical: " << this->physical << endl;
    out << "Shooting: " << this->shooting << "     ";
    out << "Stamina: " << this->stamina << endl;
    return out;
}

istream &Player::write(istream &in) {
    cout << "Prenume: ";
    in >> this->firstName;
    cout << "Nume de familie: ";
    in >> this->lastName;
    cout << "Varsta: ";
    in >> this->age;
    cout << "Piciorul de baza: ";
    in >> this->mainFoot;
    string str;
    this->injured = false;
    cout << "Accidentat(DA/NU): ";
    in >> str;
    if (str == "DA") {
        this->injured = true;
    }
    cout << "Pace: ";
    in >> this->pace;
    this->pace = adunare(this->pace, 0);
    cout << "Physical: ";
    in >> this->physical;
    this->physical = adunare(0, this->physical);
    cout << "Shooting: ";
    in >> this->shooting;
    this->physical = adunare(0, this->shooting);
    cout << "Stamina: ";
    in >> this->stamina;
    this->stamina = adunare(0, this->stamina);
    return in;
}

istream &operator>>(istream &in, Player &player) {
    return player.write(in);
}

ostream &operator<<(ostream &out, const Player &player) {
    return player.read(out);
}

class Striker : virtual public Player {
protected:
    unsigned int shotPower;
    unsigned int penalty;
    unsigned int heading;

public:
    Striker(string firstName = "John", string lastName = "Stuard", unsigned int age = 18, string mainFoot = "drept",
            bool injured = false, unsigned int pace = 75, unsigned int shooting = 75, unsigned int physical = 75,
            unsigned int stamina = 75,
            unsigned int shotPower = 75, unsigned int penalty = 75, unsigned int heading = 75);

    Striker(const Striker &striker);

    Striker &operator=(const Striker &striker);

    ~Striker();

    friend istream &operator>>(istream &, Striker &striker);

    friend ostream &operator<<(ostream &, const Striker &striker);

    ostream &read(ostream &) const;

    istream &write(istream &);

    void increaseStats();

};

Striker::Striker(string firstName, string lastName, unsigned int age, string mainFoot, bool injured, unsigned int pace,
                 unsigned int shooting, unsigned int physical, unsigned int stamina, unsigned int shotPower,
                 unsigned int penalty, unsigned int heading) : Player(firstName, lastName, age, mainFoot, injured, pace,
                                                                      shooting, physical, stamina) {
    this->shotPower = shotPower;
    this->penalty = penalty;
    this->heading = heading;
}

Striker::Striker(const Striker &striker) : Player(striker) {
    this->shotPower = striker.shotPower;
    this->penalty = striker.penalty;
    this->heading = striker.heading;
}

Striker &Striker::operator=(const Striker &striker) {
    if (this != &striker) {
        Player::operator=(striker);
        this->shotPower = striker.shotPower;
        this->penalty = striker.penalty;
        this->heading = striker.heading;
    }
    return *this;
}

Striker::~Striker() {
    cout << "Destructor striker" << endl;
}

istream &operator>>(istream &in, Striker &striker) {
    in >> (Player &) striker;
    return in;
}

ostream &operator<<(ostream &out, const Striker &striker) {
    out << (Player &) striker << endl;
    return out;
}

istream &Striker::write(istream &in) {
    Player::write(in);
    cout << "Shot power: ";
    in >> this->shotPower;
    this->shotPower = adunare(0, this->shotPower);
    cout << "Penalty: ";
    in >> this->penalty;
    this->penalty = adunare(0, this->penalty);
    cout << "Heading: ";
    in >> this->heading;
    this->heading = adunare(0, this->heading);
    return in;
}

ostream &Striker::read(ostream &out) const {
    Player::read(out);
    out << "Shot power: " << this->shotPower << "     ";
    out << "Penalty: " << this->penalty << "     ";
    out << "Heading: " << this->heading << "     " << endl;
    return out;
}

void Striker::increaseStats() {
    if (this->stamina < 5 || this->injured) {
        cout << "Jucatorul nu are destula stamina pentru a se antrena sau este accidentat" << endl;
    } else {
        cout << "Acest jucator are " << this->stamina
             << " stamina disponibila pentru antrenament.\n\nAlege exercitiile pentru antrenament(poti alege acelasi exercitiu de mai multe ori):\n";
        int command;
        vector <string> exercises;
        int fr[6] = {0, 0, 0, 0, 0, 0};
        cout
                << "1.Fast counter-attack (-12 stamina)\n2.Pass, go & shoot (-10 stamina)\n3.Slalom dribble (-7 stamina)\n4.Shuttle Run (-5 stamina)\n5.Penalties (-3 stamina)\n6.Finish with header (-7 stamina)\n7.Start training\n";
        cin >> command;
        int totalStamina = 0;
        while (command != 7) {
            try {
                if (command < 7 && command > 0) {
                    int aux = 0;
                    fr[command - 1]++;
                    switch (command) {
                        case 0: {
                            aux += fr[command] * 12;
                            exercises.push_back("Fast counter-attack");
                            break;
                        }
                        case 1: {
                            aux += fr[command] * 10;
                            exercises.push_back("Pass, go & shoot");
                            break;
                        }
                        case 2: {
                            aux += fr[command] * 7;
                            exercises.push_back("Slalom dribble");
                            break;
                        }
                        case 3: {
                            aux += fr[command] * 5;
                            exercises.push_back("Shuttle run");
                            break;
                        }
                        case 4: {
                            aux += fr[command] * 3;
                            exercises.push_back("Penalties");
                            break;
                        }
                        case 5: {
                            aux += fr[command] * 7;
                            exercises.push_back("Finish with header");
                            break;
                        }
                        default:
                            break;
                    }
                    totalStamina = aux;
                    cout << "\nStamina ce va fi folosita: " << totalStamina << endl;
                    cout
                            << "1.Fast counter-attack (-12 stamina)\n2.Pass, go & shoot (-10 stamina)\n3.Slalom dribble (-7 stamina)\n4.Shuttle Run (-5 stamina)\n5.Penalties (-3 stamina)\n6.Finish with header (-7 stamina)\n7.Start training\n";
                    cin >> command;
                } else if (command > 7 || command < 1) {
                    throw indexEx;
                }
            } catch (indexException &e) {
                cout << e.what() << endl << endl;
                cout
                        << "1.Fast counter-attack (-12 stamina)\n2.Pass, go & shoot (-10 stamina)\n3.Slalom dribble (-7 stamina)\n4.Shuttle Run (-5 stamina)\n5.Stretch (-3 stamina)\n6.Video analysis (-5 stamina)\n7.Start training\n";
                cin >> command;
            }
        }
        if (command == 7) {
            if (totalStamina > this->stamina) {
                cout << "Antrenamentul necesita mai multa stamina decat are jucatorul deja" << endl;
            } else {
                int pace = 0, physical = 0, shooting = 0, shotPower = 0, penalty = 0, heading = 0;
                this->stamina -= totalStamina;
                if (this->stamina < 10) {
                    this->injured = true;
                }
                for (int i = 0; i < 6; ++i) {
                    if (fr[i]) {
                        switch (i) {
                            case 0: {
                                physical += inmultire(1, fr[i]);
                                shooting += inmultire(2, fr[i]);
                                break;
                            }
                            case 1: {
                                shotPower += inmultire(1, fr[i]);
                                pace += inmultire(1, fr[i]);
                                break;
                            }
                            case 2: {
                                pace += inmultire(2, fr[i]);
                                break;
                            }
                            case 3: {
                                pace += inmultire(1, fr[i]);
                                physical += inmultire(1, fr[i]);
                                break;
                            }
                            case 4: {
                                penalty += inmultire(2, fr[i]);
                                shotPower += inmultire(1, fr[i]);
                                break;
                            }
                            case 5: {
                                heading += inmultire(2, fr[i]);
                                break;
                            }
                            default:
                                break;
                        }
                    }
                }
                if (penalty) {
                    cout << "Penalty: " << this->penalty << " + " << penalty << endl;
                    this->penalty = (this->penalty + penalty > 100) ? 100 : adunare(this->penalty, penalty);
                }
                if (shotPower) {
                    cout << "Shotpower: " << this->shotPower << " + " << shotPower << endl;
                    this->shotPower = (this->shotPower + shotPower > 100) ? 100 : adunare(this->shotPower, shotPower);
                }
                if (heading) {
                    cout << "Heading: " << this->heading << " + " << heading << endl;
                    this->heading = (this->heading + heading > 100) ? 100 : adunare(this->heading, heading);
                }
                if (shooting) {
                    cout << "Shooting: " << this->shooting << " + " << shooting << endl;
                    this->shooting = (this->shooting + shooting > 100) ? 100 : adunare(this->shooting, shooting);
                }
                if (pace) {
                    cout << "Pace: " << this->pace << " + " << pace << endl;
                    this->pace = (this->pace + pace > 100) ? 100 : adunare(this->pace, pace);
                }
                if (physical) {
                    cout << "Physical: " << this->physical << " + " << physical << endl;
                    this->physical = (this->physical + physical > 100) ? 100 : adunare(this->physical, physical);
                }
            }
        }
    }
}

class Defender : virtual public Player {
protected:
    unsigned int slideTackle;
    unsigned int balance;
    unsigned int strength;

public:
    Defender(string firstName = "John", string lastName = "Stuard", unsigned int age = 18,
             string mainFoot = "drept", bool injured = false, unsigned int pace = 75, unsigned int shooting = 75,
             unsigned int physical = 75, unsigned int stamina = 100,
             unsigned int slideTackle = 75, unsigned int balance = 75, unsigned int strength = 75);

    Defender(const Defender &defender);

    Defender &operator=(const Defender &defender);

    ~Defender();

    friend ostream &operator<<(ostream &, const Defender &defender);

    friend istream &operator>>(istream &, Defender &defender);

    ostream &read(ostream &) const;

    istream &write(istream &);

    virtual void increaseStats();
};

Defender::Defender(string firstName, string lastName, unsigned int age, string mainFoot, bool injured,
                   unsigned int pace, unsigned int shooting, unsigned int physical, unsigned int stamina,
                   unsigned int slideTackle, unsigned int balance, unsigned int strength) : Player(firstName, lastName,
                                                                                                   age, mainFoot,
                                                                                                   injured, pace,
                                                                                                   shooting, physical,
                                                                                                   stamina) {
    this->slideTackle = slideTackle;
    this->balance = balance;
    this->strength = strength;
}

Defender::Defender(const Defender &defender) : Player(defender) {
    this->slideTackle = defender.slideTackle;
    this->balance = defender.balance;
    this->strength = defender.strength;
}

Defender &Defender::operator=(const Defender &defender) {
    if (this != &defender) {
        Player::operator=(defender);
        this->slideTackle = defender.slideTackle;
        this->balance = defender.balance;
        this->strength = defender.strength;
    }
    return *this;
}

Defender::~Defender() {
    cout << "Destructor fundas" << endl;
}

istream &operator>>(istream &in, Defender &defender) {
    in >> (Player &) defender;
    return in;
}

ostream &operator<<(ostream &out, const Defender &defender) {
    out << (Player &) defender << endl;
    return out;
}

istream &Defender::write(istream &in) {
    Player::write(in);
    cout << "Slide tackle: ";
    in >> this->slideTackle;
    this->slideTackle = adunare(this->slideTackle, 0);
    cout << "Balance: ";
    in >> this->balance;
    this->balance = adunare(this->balance, 0);
    cout << "Strength: ";
    in >> this->strength;
    this->strength = adunare(this->strength, 0);
    return in;
}

ostream &Defender::read(ostream &out) const {
    Player::read(out);
    out << "Slide tackle: " << this->slideTackle << "     ";
    out << "Balance: " << this->balance << "     ";
    out << "Strength: " << this->strength << "     " << endl;
    return out;
}

void Defender::increaseStats() {
    if (this->stamina < 5 || this->injured) {
        cout << "Jucatorul nu are destula stamina pentru a se antrena sau este accidentat" << endl;
    } else {
        cout << "Acest jucator are " << this->stamina
             << " stamina disponibila pentru antrenament.\n\nAlege exercitiile pentru antrenament(poti alege acelasi exercitiu de mai multe ori):\n";
        int command;
        vector <string> exercises;
        int fr[6] = {0, 0, 0, 0, 0, 0};
        cout
                << "1.Gym (-12 stamina)\n2.Press the play (-10 stamina)\n3.Hurdle jumps (-7 stamina)\n4.Shuttle Run (-5 stamina)\n5.Guarding crosses (-10 stamina)\n6.Stretching (-5 stamina)\n7.Start training\n";
        cin >> command;
        int totalStamina = 0;
        while (command != 7) {
            try {
                if (command < 7 && command > 0) {
                    fr[command-1]++;
                    int aux = 0;
                    switch (command) {
                        case 1: {
                            aux += 12;
                            exercises.push_back("Gym");
                            break;
                        }
                        case 2: {
                            aux += 10;
                            exercises.push_back("Press the play");
                            break;
                        }
                        case 3: {
                            aux += 7;
                            exercises.push_back("Hurdle jumps");
                            break;
                        }
                        case 4: {
                            aux += 5;
                            exercises.push_back("Shuttle run");
                            break;
                        }
                        case 5: {
                            aux += 10;
                            exercises.push_back("Guarding crosses");
                            break;
                        }
                        case 6: {
                            aux += 5;
                            exercises.push_back("Stretching");
                            break;
                        }
                        default:
                            break;
                    }
                    for (vector<string>::iterator it = exercises.begin(); it != exercises.end(); ++it) {
                        if (it != end(exercises))
                            cout << *it << " -> ";
                    }
                    totalStamina = aux;
                    cout << "\nStamina ce va fi folosita: " << totalStamina << endl;
                    cout
                            << "1.Gym (-12 stamina)\n2.Press the play (-10 stamina)\n3.Hurdle jumps (-7 stamina)\n4.Shuttle Run (-5 stamina)\n5.Guarding crosses (-10 stamina)\n6.Stretch (-5 stamina)\n7.Start training\n";
                    cin >> command;
                } else if (command > 7 || command < 1) {
                    throw indexEx;
                }
            } catch (indexException &e) {
                cout << e.what() << endl << endl;
                cout
                        << "1.Gym (-12 stamina)\n2.Press the play (-10 stamina)\n3.Hurdle jumps (-7 stamina)\n4.Shuttle Run (-5 stamina)\n5.Guarding crosses (-10 stamina)\n6.Stretch (-5 stamina)\n7.Start training\n";
                cin >> command;
            }
        }
        if (command == 7) {
            if (totalStamina > this->stamina) {
                cout << "Antrenamentul necesita mai multa stamina decat are jucatorul deja" << endl;
            } else {
                int pace = 0, physical = 0, balance = 0, strength = 0, slideTackle = 0;
                this->stamina -= totalStamina;
                if (this->stamina < 10) {
                    this->injured = true;
                }
                for (int i = 0; i < 6; ++i) {
                    if (fr[i]) {
                        switch (i) {
                            case 0: {
                                physical += 1 * fr[i];
                                strength += 2 * fr[i];
                                break;
                            }
                            case 1: {
                                slideTackle += 2 * fr[i];
                                pace += 2 * fr[i];
                                break;
                            }
                            case 2: {
                                balance += 2 * fr[i];
                                break;
                            }
                            case 3: {
                                pace += 1 * fr[i];
                                physical += 1 * fr[i];
                                break;
                            }
                            case 4: {
                                physical += 1 * fr[i];
                                balance += 1 * fr[i];
                                break;
                            }
                            case 5: {
                                balance += 1 * fr[i];
                                break;
                            }
                            default:
                                break;
                        }
                    }
                }
                if (balance) {
                    cout << "Balance: " << this->balance << " + " << balance << endl;
                    this->balance = (this->balance + balance > 100) ? 100 : this->balance + balance;
                }
                if (strength) {
                    cout << "Strength: " << this->strength << " + " << strength << endl;
                    this->strength = (this->strength + strength > 100) ? 100 : this->strength + strength;
                }
                if (slideTackle) {
                    cout << "Slide tackle: " << this->slideTackle << " + " << slideTackle << endl;
                    this->slideTackle = (this->slideTackle + slideTackle > 100) ? 100 : this->slideTackle + slideTackle;
                }
                if (pace) {
                    cout << "Pace: " << this->pace << " + " << pace << endl;
                    this->pace = (this->pace + pace > 100) ? 100 : this->pace + pace;
                }
                if (physical) {
                    cout << "Physical: " << this->physical << " + " << physical << endl;
                    this->physical = (this->physical + physical > 100) ? 100 : this->physical + physical;
                }
            }
        }
    }
}

class Goalkeeper : virtual public Player {
protected:
    unsigned int reflexes;
    unsigned int diving;
    unsigned int handling;

public:
    Goalkeeper(string firstName = "John", string lastName = "Stuard", unsigned int age = 18,
               string mainFoot = "right", bool injured = false, unsigned int pace = 75, unsigned int shooting = 75,
               unsigned int physical = 75, unsigned int stamina = 100,
               unsigned int reflexes = 75, unsigned int diving = 75, unsigned int handling = 75);

    Goalkeeper(const Goalkeeper &goalkeeper);

    Goalkeeper &operator=(const Goalkeeper &goalkeeper);

    ~Goalkeeper();

    friend istream &operator>>(istream &, Goalkeeper &goalkeeper);

    friend ostream &operator<<(ostream &, const Goalkeeper &goalkeeper);

    istream &write(istream &);

    ostream &read(ostream &) const;

    virtual void increaseStats();
};

Goalkeeper::Goalkeeper(string firstName, string lastName, unsigned int age, string mainFoot, bool injured,
                       unsigned int pace, unsigned int shooting, unsigned int physical, unsigned int stamina,
                       unsigned int reflexes, unsigned int diving, unsigned int handling) : Player(firstName, lastName,
                                                                                                   age, mainFoot,
                                                                                                   injured, pace,
                                                                                                   shooting, physical,
                                                                                                   stamina) {
    this->reflexes = reflexes;
    this->diving = diving;
    this->handling = handling;
}

Goalkeeper::Goalkeeper(const Goalkeeper &goalkeeper) : Player(goalkeeper) {
    this->reflexes = goalkeeper.reflexes;
    this->diving = goalkeeper.diving;
    this->handling = goalkeeper.handling;
}

Goalkeeper &Goalkeeper::operator=(const Goalkeeper &goalkeeper) {
    if (this != &goalkeeper) {
        Player::operator=(goalkeeper);
        this->reflexes = goalkeeper.reflexes;
        this->diving = goalkeeper.diving;
        this->handling = goalkeeper.handling;
    }
    return *this;
}

Goalkeeper::~Goalkeeper() {
    cout << "Destructor portar" << endl;
}

istream &operator>>(istream &in, Goalkeeper &goalkeeper) {
    in >> (Player &) goalkeeper;
    return in;
}

ostream &operator<<(ostream &out, const Goalkeeper &goalkeeper) {
    out << (Player &) goalkeeper << endl;
    return out;
}

istream &Goalkeeper::write(istream &in) {
    Player::write(in);
    cout << "Reflexes: ";
    in >> this->reflexes;
    this->reflexes = adunare(this->reflexes, 0);
    cout << "Diving: ";
    in >> this->diving;
    this->diving = adunare(this->diving, 0);
    cout << "Handling: ";
    in >> this->handling;
    this->handling = adunare(this->handling, 0);
    return in;
}

ostream &Goalkeeper::read(ostream &out) const {
    Player::read(out);
    out << "Reflexes: " << this->reflexes << "     ";
    out << "Diving: " << this->diving << "     ";
    out << "Handling: " << this->handling << "     " << endl;
    return out;
}

void Goalkeeper::increaseStats() {
    if (this->stamina < 5 || this->injured) {
        cout << "Jucatorul nu are destula stamina pentru a se antrena sau este accidentat" << endl;
    } else {
        cout << "Acest jucator are " << this->stamina
             << " stamina disponibila pentru antrenament.\n\nAlege exercitiile pentru antrenament(poti alege acelasi exercitiu de mai multe ori):\n";
        int command;
        vector <string> exercises;
        int fr[6] = {0, 0, 0, 0, 0, 0};
        cout
                << "1. 1-on-1 ending (-10 stamina)\n2.Carioca with ladunareers (-10 stamina)\n3.Long run (-5 stamina)\n4.Penalties (-7 stamina)\n5.Guarding crosses (-7 stamina)\n6.Stretching (-3 stamina)\n7.Start training\n";
        cin >> command;
        int totalStamina = 0;
        int aux = 0;
        while (command != 7) {
            try {
                if (command < 7 && command > 0) {
                    fr[command - 1]++;
                    switch (command) {
                        case 0: {
                            aux += fr[command] * 10;
                            exercises.push_back("1-on-1 ending");
                            break;
                        }
                        case 1: {
                            aux += fr[command] * 10;
                            exercises.push_back("Carioca with ladunareers");
                            break;
                        }
                        case 2: {
                            aux += fr[command] * 5;
                            exercises.push_back("Long run");
                            break;
                        }
                        case 3: {
                            aux += fr[command] * 7;
                            exercises.push_back("Penalties");
                            break;
                        }
                        case 4: {
                            aux += fr[command] * 7;
                            exercises.push_back("Guarding crosses");
                            break;
                        }
                        case 5: {
                            aux += fr[command] * 3;
                            exercises.push_back("Stretching");
                            break;
                        }
                        default:
                            break;
                    }
                    for (vector<string>::iterator it = begin(exercises); it != end(exercises); ++it) {
                        if (it + 1 != end(exercises))
                            cout << *it << " -> ";
                    }
                    totalStamina = aux;
                    cout << "\nStamina ce va fi folosita: " << totalStamina << endl;
                    cout
                            << "1. 1-on-1 ending (-10 stamina)\n2.Carioca with ladunareers (-10 stamina)\n3.Long run (-5 stamina)\n4.Penalties (-7 stamina)\n5.Guarding crosses (-7 stamina)\n6.Stretch (-3 stamina)\n7.Start training\n";
                    cin >> command;
                } else if (command > 7 || command < 1) {
                    throw indexEx;
                }
            } catch (indexException &e) {
                cout << e.what() << endl << endl;
                cout
                        << "1. 1-on-1 ending (-10 stamina)\n2.Carioca with ladunareers (-10 stamina)\n3.Long run (-5 stamina)\n4.Penalties (-7 stamina)\n5.Guarding crosses (-7 stamina)\n6.Stretch (-3 stamina)\n7.Start training\n";
                cin >> command;
            }
        }
        if (command == 7) {
            if (totalStamina > this->stamina) {
                cout << "Antrenamentul necesita mai multa stamina decat are jucatorul deja" << endl;
            } else {
                int pace = 0, physical = 0, reflexes = 0, diving = 0, handling = 0;
                this->stamina -= totalStamina;
                if (this->stamina < 10) {
                    this->injured = true;
                }
                for (int i = 0; i < 6; ++i) {
                    if (fr[i]) {
                        switch (i) {
                            case 0: {
                                reflexes += 2 * fr[i];
                                handling += 1 * fr[i];
                                break;
                            }
                            case 1: {
                                physical += 2 * fr[i];
                                reflexes += 1 * fr[i];
                                break;
                            }
                            case 2: {
                                physical += 1 * fr[i];
                                pace += 1 * fr[i];
                                break;
                            }
                            case 3: {
                                diving += 2 * fr[i];
                                break;
                            }
                            case 4: {
                                reflexes += 1 * fr[i];
                                handling += 1 * fr[i];
                                break;
                            }
                            case 5: {
                                physical += 1 * fr[i];
                                break;
                            }
                            default:
                                break;
                        }
                    }
                }
                if (handling) {
                    cout << "Handling: " << this->handling << " + " << handling << endl;
                    this->handling = (this->handling + handling > 100) ? 100 : this->handling + handling;
                }
                if (diving) {
                    cout << "Diving: " << this->diving << " + " << diving << endl;
                    this->diving = (this->diving + diving > 100) ? 100 : this->diving + diving;
                }
                if (reflexes) {
                    cout << "Reflexes: " << this->reflexes << " + " << reflexes << endl;
                    this->reflexes = (this->reflexes + reflexes > 100) ? 100 : this->reflexes + reflexes;
                }
                if (pace) {
                    cout << "Pace: " << this->pace << " + " << pace << endl;
                    this->pace = (this->pace + pace > 100) ? 100 : this->pace + pace;
                }
                if (physical) {
                    cout << "Physical: " << this->physical << " + " << physical << endl;
                    this->physical = (this->physical + physical > 100) ? 100 : this->physical + physical;
                }
            }
        }
    }
}

class Midfielder : virtual public Defender, virtual public Striker {
private:
    unsigned int positioning;
    unsigned int passing;
    unsigned int vision;

public:
    Midfielder(string firstName = "John", string lastName = "Stuard", unsigned int age = 18,
               string mainFoot = "right", bool injured = false, unsigned int pace = 75, unsigned int shooting = 75,
               unsigned int physical = 75, unsigned int stamina = 100,
               unsigned int shotPower = 75, unsigned int penalty = 75, unsigned int heading = 75,
               unsigned int slideTackle = 75, unsigned int balance = 75, unsigned int strength = 75,
               unsigned int positioning = 75, unsigned int passing = 75, unsigned int vision = 75);

    Midfielder(const Midfielder &midfielder);

    Midfielder &operator=(const Midfielder &midfielder);

    ~Midfielder();

    friend istream &operator>>(istream &, Midfielder &midfielder);

    friend ostream &operator<<(ostream &, const Midfielder &midfielder);

    istream &write(istream &);

    ostream &read(ostream &) const;

    virtual void increaseStats();
};

Midfielder::Midfielder(string firstName, string lastName, unsigned int age, string mainFoot, bool injured,
                       unsigned int pace, unsigned int shooting, unsigned int physical, unsigned int stamina,
                       unsigned int shotPower, unsigned int penalty, unsigned int heading, unsigned int slideTackle,
                       unsigned int balance, unsigned int strength, unsigned int positioning, unsigned int passing,
                       unsigned int vision) : Defender(firstName, lastName, age, mainFoot,
                                                       injured, pace, shooting, physical,
                                                       stamina, slideTackle, balance, strength),
                                              Striker(firstName, lastName, age, mainFoot,
                                                      injured, pace, shooting, physical,
                                                      stamina, shotPower, penalty, heading) {
    this->positioning = positioning;
    this->passing = passing;
    this->vision = vision;
}

Midfielder::Midfielder(const Midfielder &midfielder) : Defender(midfielder), Striker(midfielder) {
    this->positioning = midfielder.positioning;
    this->passing = midfielder.passing;
    this->vision = midfielder.vision;
}

Midfielder &Midfielder::operator=(const Midfielder &midfielder) {
    if (this != &midfielder) {
        Defender::operator=(midfielder);
        Striker::operator=(midfielder);
        this->positioning = midfielder.positioning;
        this->passing = midfielder.passing;
        this->vision = midfielder.vision;
    }
    return *this;
}

Midfielder::~Midfielder() {
    cout << "Destructor miljlocas" << endl;
}

istream &operator>>(istream &in, Midfielder &midfielder) {
    in >> (Defender &) midfielder;
    return in;
}

ostream &operator<<(ostream &out, const Midfielder &midfielder) {
    out << (Defender &) midfielder << endl;
    return out;
}

istream &Midfielder::write(istream &in) {
    Defender::write(in);
    cout << "Shot power: ";
    in >> this->shotPower;
    this->shotPower = adunare(this->shotPower, 0);
    cout << "Penalty: ";
    in >> this->penalty;
    this->penalty = adunare(this->penalty, 0);
    cout << "Heading: ";
    in >> this->heading;
    this->heading = adunare(this->heading, 0);
    cout << "Positioning: ";
    in >> this->positioning;
    this->positioning = adunare(this->positioning, 0);
    cout << "Passing: ";
    in >> this->passing;
    this->passing = adunare(this->passing, 0);
    cout << "Vision: ";
    in >> this->vision;
    this->vision = adunare(this->vision, 0);
    return in;
}

ostream &Midfielder::read(ostream &out) const {
    Defender::read(out);
    out << "Shot power: " << this->shotPower << "    ";
    out << "Penalty: " << this->penalty << "    ";
    out << "Heading: " << this->heading << endl;
    out << "Positioning: " << this->positioning << "    ";
    out << "Passing: " << this->passing << "    ";
    out << "Vision: " << this->vision << endl;
    return out;
}

void Midfielder::increaseStats() {
    if (this->stamina < 5 || this->injured) {
        cout << "Jucatorul nu are destula stamina pentru a se antrena sau este accidentat" << endl;
    } else {
        cout << "Acest jucator are " << this->stamina
             << " stamina disponibila pentru antrenament.\n\nAlege exercitiile pentru antrenament(poti alege acelasi exercitiu de mai multe ori):\n";
        int command;
        vector <string> exercises;
        int fr[6] = {0, 0, 0, 0, 0, 0};
        cout
                << "1.Piggy in the middle (-15 stamina)\n2.Pass, go & shoot (-7 stamina)\n3.Sprints (-7 stamina)\n4.Press the play (-10 stamina)\n5.Penalties (-3 stamina)\n6.Hold the line (-5 stamina)\n7.Start training\n";
        cin >> command;
        int aux = 0;
        int totalStamina = 0;
        while (command != 7) {
            try {
                if (command < 7 && command > 0) {

                    fr[command - 1]++;
                    switch (command) {
                        case 0: {
                            aux += inmultire(fr[command], 15);
                            exercises.push_back("Piggy in the middle");
                            break;
                        }
                        case 1: {
                            aux += inmultire(fr[command], 10);
                            exercises.push_back("Pass, go & shoot");
                            break;
                        }
                        case 2: {
                            aux += inmultire(fr[command], 7);
                            exercises.push_back("Sprints");
                            break;
                        }
                        case 3: {
                            aux += inmultire(fr[command], 7);
                            exercises.push_back("Press the play");
                            break;
                        }
                        case 4: {
                            aux += inmultire(fr[command], 3);
                            exercises.push_back("Penalties");
                            break;
                        }
                        case 5: {
                            aux += inmultire(fr[command], 5);
                            exercises.push_back("Hold the line");
                            break;
                        }
                        default:
                            break;
                    }
                    for (vector<string>::iterator it = begin(exercises); it != end(exercises); ++it) {
                        if (it + 1 != end(exercises))
                            cout << *it << " -> ";
                    }
                    totalStamina = aux;
                    cout << "\nStamina ce va fi folosita: " << totalStamina << endl;
                    cout
                            << "1.Piggy in the middle (-15 stamina)\n2.Pass, go & shoot (-7 stamina)\n3.Sprints (-7 stamina)\n4.Press the play (-10 stamina)\n5.Penalties (-3 stamina)\n6.Hold the line (-5 stamina)\n7.Start training\n";
                    cin >> command;
                } else if (command > 7 || command < 1) {
                    throw indexEx;
                }
            } catch (indexException &e) {
                cout << e.what() << endl << endl;
                cout
                        << "1.Piggy in the middle (-15 stamina)\n2.Pass, go & shoot (-7 stamina)\n3.Sprints (-7 stamina)\n4.Press the play (-10 stamina)\n5.Penalties (-3 stamina)\n6.Hold the line (-5 stamina)\n7.Start training\n";
                cin >> command;
            }
        }
        if (command == 7) {
            if (totalStamina > this->stamina) {
                cout << "Antrenamentul necesita mai multa stamina decat are jucatorul deja" << endl;
            } else {
                int pace = 0, physical = 0, shooting = 0, slideTackle = 0, balance = 0, strength = 0;
                int shotPower = 0, penalty = 0, heading = 0;
                int positioning = 0, passing = 0, vision = 0;
                this->stamina -= totalStamina;
                if (this->stamina < 10) {
                    this->injured = true;
                }
                for (int i = 0; i < 6; ++i) {
                    if (fr[i]) {
                        switch (i) {
                            case 0: {
                                slideTackle = adunare(slideTackle, inmultire(1, fr[i]));
                                balance = adunare(balance, inmultire(1, fr[i]));
                                vision = adunare(vision, inmultire(1, fr[i]));
                                positioning = adunare(positioning, inmultire(2, fr[i]));
                                break;
                            }
                            case 1: {
                                shooting = adunare(shooting, inmultire(1, fr[i]));
                                physical = adunare(physical, inmultire(1, fr[i]));
                                passing = adunare(passing, inmultire(1, fr[i]));
                                break;
                            }
                            case 2: {
                                pace = adunare(pace, inmultire(1, fr[i]));
                                physical = adunare(physical, inmultire(2, fr[i]));
                                balance = adunare(balance, inmultire(1, fr[i]));
                                break;
                            }
                            case 3: {
                                strength = adunare(strength, inmultire(1, fr[i]));
                                slideTackle = adunare(slideTackle, inmultire(1, fr[i]));
                                physical = adunare(physical, inmultire(1, fr[i]));
                                break;
                            }
                            case 4: {
                                shotPower = adunare(shotPower, inmultire(1, fr[i]));
                                penalty = adunare(penalty, inmultire(1, fr[i]));
                                break;
                            }
                            case 5: {
                                vision = adunare(vision, inmultire(1, fr[i]));
                                balance = adunare(balance, inmultire(1, fr[i]));
                                positioning = adunare(positioning, inmultire(2, fr[i]));
                                break;
                            }
                            default:
                                break;
                        }
                    }
                }
                if (positioning) {
                    cout << "Positioning: " << this->positioning << " + " << positioning << endl;
                    this->positioning = (this->positioning + positioning > 100) ? 100 : this->positioning +
                                                                                        positioning;
                }
                if (passing) {
                    cout << "Passing: " << this->passing << " + " << passing << endl;
                    this->passing = (this->passing + passing > 100) ? 100 : this->passing + passing;
                }
                if (vision) {
                    cout << "Vision: " << this->vision << " + " << vision << endl;
                    this->vision = (this->vision + vision > 100) ? 100 : this->vision + vision;
                }
                if (shooting) {
                    cout << "Shooting: " << this->shooting << " + " << shooting << endl;
                    this->shooting = (this->shooting + shooting > 100) ? 100 : this->shooting + shooting;
                }
                if (pace) {
                    cout << "Pace: " << this->pace << " + " << pace << endl;
                    this->pace = (this->pace + pace > 100) ? 100 : this->pace + pace;
                }
                if (physical) {
                    cout << "Physical: " << this->physical << " + " << physical << endl;
                    this->physical = (this->physical + physical > 100) ? 100 : this->physical + physical;
                }
                if (slideTackle) {
                    cout << "Slide tackle: " << this->slideTackle << " + " << slideTackle << endl;
                    this->slideTackle = (this->slideTackle + slideTackle > 100) ? 100 : this->slideTackle + slideTackle;
                }
                if (balance) {
                    cout << "Balance: " << this->balance << " + " << balance << endl;
                    this->balance = (this->balance + balance > 100) ? 100 : this->balance + balance;
                }
                if (strength) {
                    cout << "Strength: " << this->strength << " + " << strength << endl;
                    this->strength = (this->strength + strength > 100) ? 100 : this->strength + strength;
                }
            }
        }
    }
}

class menuCRUD {
private:
    static menuCRUD *obiect;

    menuCRUD() {};

public:
    static menuCRUD *getInstance() {
        if (!obiect) {
            obiect = new menuCRUD();
        }
        return obiect;
    }

    void meniu();
};

menuCRUD *menuCRUD::obiect = 0;


vector <map<string, set < Player * >>>
teams;
vector <string> nameTeams;

int main() {
    menuCRUD *meniu = meniu->getInstance();
    meniu->meniu();
    return 0;
}


void menuCRUD::meniu() {
    teams.resize(teams.size() + 1);
    cout
            << "Nu ai nicio echipa pana in momentul de fata. Hai sa cream una.\nMai intai de toate alege un nume pentru aceasta echipa:\n";
    char numeEchipa[100];
    cout << "Nume echipa: ";
    cin.getline(numeEchipa, 100);
    nameTeams.push_back(numeEchipa);
    cout << "Acum e timpul sa alegi cine ai vrea sa fie capitan in aceasta echipa:\n";
    bool valid = false;
    do {
        cout
                << "1.Ronaldo - Striker; 90 shooting, 94 - heading, 88 - pace\n2.Sergio Ramos - Defender; 96 - slideTackle, 94 - strength, 92 - balance\n3.Iker Casillar - Goalkeeper; 90 - diving, 98 - reflexes, 87 - handling\n";
        int k;
        cout << "Alege capitanul: ";
        cin >> k;
        try {
            switch (k) {
                case 1: {
                    Striker *striker = new Striker("Ronaldo", "Cristiano", 34, "both", false, 88, 90, 88,
                                                   100, 88, 84, 94);
                    teams[0]["atacanti"].insert(striker);
                    valid = true;
                    break;
                }
                case 2: {
                    Defender *defender = new Defender("Ramos", "Sergio", 27, "left", false, 96, 89, 82, 100, 96, 92,
                                                      94);
                    teams[0]["fundasi"].insert(defender);
                    valid = true;
                    break;
                }
                case 3: {
                    Goalkeeper *goalkeeper = new Goalkeeper("Casillas", "Iker", 31, "right", false, 82, 81, 85, 100, 98,
                                                            90,
                                                            87);
                    teams[0]["portari"].insert(goalkeeper);
                    valid = true;
                    break;
                }
                default: {
                    throw indexEx;
                    break;
                }
            }
        } catch (indexException &e) {
            cout << e.what() << endl;
        }
    } while (!valid);
    cout
            << "Acum ca avem o echipa si avem si capitan, iti poti alege sa iti cresti in continuare aceasta echipa, sa o modelezi cum vrei, sa iti aduci alti jucatori sau ai putea sa iti faci alta echipa noua.\n\n";

    int comanda;
    do {
        cout << "Alege cu ce echipa vrei sa lucrezi:\n";
        int i = 0;
        for (int i = 0; i < nameTeams.size(); i++) {
            cout << i + 1 << ". " << nameTeams[i] << endl;
        }
        cout << nameTeams.size() + 1 << " -> creeaza o noua echipa\n";
        cout << nameTeams.size() + 2 << " -> iesi din meniu\n";

        cin >> comanda;
        if (comanda == nameTeams.size() + 1) {
            teams.resize(teams.size() + 1);
            cout << "Nume echipa: ";
            cin >> numeEchipa;
            nameTeams.push_back(numeEchipa);
            cout << "Acum e timpul sa alegi cine ai vrea sa fie capitan in aceasta echipa:\n";
            do {
                cout
                        << "1.Ronaldo - Striker; 90 shooting, 94 - heading, 88 - pace\n2.Sergio Ramos - Defender; 96 - slideTackle, 94 - strength, 92 - balance\n3.Iker Casillar - Goalkeeper; 90 - diving, 98 - reflexes, 87 - handling\n";
                int k;
                cout << "Alege capitanul: ";
                cin >> k;
                try {
                    switch (k) {
                        case 1: {
                            Striker *striker = new Striker("Ronaldo", "Cristiano", 34, "both", false, 88, 90, 88,
                                                           100, 88, 84, 94);
                            teams[teams.size() - 1]["atacanti"].insert(striker);
                            valid = true;
                            break;
                        }
                        case 2: {
                            Defender *defender = new Defender("Ramos", "Sergio", 27, "left", false, 96, 89, 82, 100, 96,
                                                              92,
                                                              94);
                            teams[teams.size() - 1]["fundasi"].insert(defender);
                            valid = true;
                            break;
                        }
                        case 3: {
                            Goalkeeper *goalkeeper = new Goalkeeper("Casillas", "Iker", 31, "right", false, 82, 81, 85,
                                                                    100, 98,
                                                                    90,
                                                                    87);
                            teams[teams.size() - 1]["portari"].insert(goalkeeper);
                            valid = true;
                            break;
                        }
                        default: {
                            throw indexEx;
                            break;
                        }
                    }
                } catch (indexException &e) {
                    cout << e.what() << endl;
                }
            } while (!valid);
        } else if (comanda <= nameTeams.size()) {
            int index = comanda - 1;
            int comanda_echipa = 0;
            cout << "Alege ce schimbari vrei sa faci:\n\n";
            while (comanda_echipa != 9) {
                cout
                        << "1.Adauga jucator\n2.Sterge un jucator\n3.Imbunatateste un jucator\n4.Sterge echipa\n5.Arata toti fundasii\n6.Arata toti atacantii\n7.Arata toti portarii\n8.Arata toti mijlocasii\n9.Inapoi\n";
                cout << "Comanda: ";
                cin >> comanda_echipa;
                switch (comanda_echipa) {
                    case 1: {
                        int tip_jucator;
                        cout
                                << "Alege ce fel de jucator vrei sa adaugi:\n1.Atacant\n2.Fundas\n3.Portar\n4.Mijlocas\n5.Inapoi\n";
                        cout << "Comanda fel jucator: ";
                        cin >> tip_jucator;
                        cout << endl;
                        try {
                            switch (tip_jucator) {
                                case 1: {
                                    Striker striker;
                                    striker.write(cin);
                                    Striker *aux = new Striker(striker);
                                    teams[index]["atacanti"].insert(aux);
                                    break;
                                }
                                case 2: {
                                    Defender defender;
                                    defender.write(cin);
                                    Defender *aux = new Defender(defender);
                                    teams[index]["fundasi"].insert(aux);
                                    break;
                                }
                                case 3: {
                                    Goalkeeper goalkeeper;
                                    goalkeeper.write(cin);
                                    Goalkeeper *aux = new Goalkeeper(goalkeeper);
                                    teams[index]["portari"].insert(aux);
                                    break;
                                }
                                case 4: {
                                    Midfielder midfielder;
                                    midfielder.write(cin);
                                    Midfielder *aux = new Midfielder(midfielder);
                                    teams[index]["mijlocasi"].insert(aux);
                                    break;
                                }
                                case 5: {
                                    break;
                                }
                                default: {
                                    throw indexEx;
                                    break;
                                }
                            }
                        } catch (indexException &e) {
                            cout << e.what() << endl;
                        }
                        break;
                    }
                    case 2: {
                        int index_jucator;
                        string type;
                        try {
                            cout << "Ce fel de jucator ati vrea sa stergeti? (fundasi/atacanti/portari/mijlocasi):  ";
                            cin >> type;
                            if (type.compare("fundasi") != 0 || type.compare("atacanti") != 0 ||
                                type.compare("portari") != 0 || type.compare("mijlocasi") != 0) {
                                throw typeEx;
                            }
                        } catch (typeException &e) {
                            cout << e.what() << endl;
                        }
                        cout << "Alege al catelea jucator din echipa vrei sa il stergi.\n";
                        cout << "Index: ";
                        cin >> index_jucator;
                        index_jucator--;
                        if (index_jucator + 1 > teams[index][type].size()) {
                            cout << "Nu exista acest jucator.\n";
                        } else {
                            set<Player *>::iterator itr = teams[index][type].begin();
                            while (index_jucator) {
                                itr++;
                                index_jucator--;
                            }
                            teams[index][type].erase(itr);
                        }
                        break;
                    }
                    case 3: {
                        int index_jucator;
                        string type;
                        try {
                            cout
                                    << "Ce fel de jucator ati vrea sa il imbunatatiti? (fundasi/atacanti/portari/mijlocasi):  ";
                            cin >> type;
                            if (type.compare("fundasi") != 0 || type.compare("atacanti") != 0 ||
                                type.compare("portari") != 0 || type.compare("mijlocasi") != 0) {
                                throw typeEx;
                            }
                        } catch (typeException &e) {
                            cout << e.what() << endl;
                        }
                        cout << "Alege al catelea jucator din echipa vrei sa il imbunatatesti.\n";
                        cout << "Index: ";
                        cin >> index_jucator;
                        index_jucator--;
                        cout << teams[index][type].size();
                        if (index_jucator + 1 > teams[index][type].size()) {
                            cout << "Nu exista acest jucator.\n";
                        } else {
                            set<Player *>::iterator itr = teams[index][type].begin();
                            while (index_jucator) {
                                itr++;
                                index_jucator--;
                            }
                            try {
                                if (type == "fundasi") {
                                    Defender *aux = dynamic_cast<Defender *>(*itr);
                                    aux->increaseStats();
                                } else if (type == "atacanti") {
                                    Striker *aux = dynamic_cast<Striker *>(*itr);;
                                    aux->increaseStats();
                                } else if (type == "portari") {
                                    Goalkeeper *aux = dynamic_cast<Goalkeeper *>(*itr);
                                    aux->increaseStats();
                                } else if (type == "mijlocasi") {
                                    Midfielder *aux = dynamic_cast<Midfielder *>(*itr);
                                    aux->increaseStats();
                                } else {
                                    throw typeEx;
                                }
                            } catch (typeException &e) {
                                cout << e.what() << endl;
                            }

                        }
                        break;
                    }
                    case 4: {
                        if (teams.size() == 1) {
                            cout << "Nu putem sterge singura echipa pe care o ai!\n";
                            break;
                        }
                        cout << "Esti sigur ca vrei sa stergi aceasta echipa?(DA/NU)";
                        string answer;
                        cin >> answer;
                        if (answer == "DA" || answer == "Da" || answer == "da") {
                            teams.erase(teams.begin() + index - 1);
                            nameTeams.erase(nameTeams.begin() + index - 1);
                        }
                        break;
                    }
                    case 5: {
                        set<Player *>::iterator itr;
                        for (itr = teams[index]["fundasi"].begin(); itr != teams[index]["fundasi"].end(); itr++) {
                            try {
                                if (Defender *aux = dynamic_cast<Defender *>(*itr)) {
                                    (*itr)->read(cout);
                                    cout << endl;
                                } else {
                                    throw badCastEx;
                                }
                            } catch (badCast &e) {
                                cout << e.what() << endl;
                            }
                        }
                        break;
                    }
                    case 6: {
                        set<Player *>::iterator itr;
                        for (itr = teams[index]["atacanti"].begin(); itr != teams[index]["atacanti"].end(); itr++) {
                            try {
                                if (Striker *aux = dynamic_cast<Striker *>(*itr)) {
                                    (*itr)->read(cout);
                                    cout << endl;
                                } else {
                                    throw badCastEx;
                                }
                            } catch (badCast &e) {
                                cout << e.what() << endl;
                            }
                        }
                        break;
                    }
                    case 7: {
                        set<Player *>::iterator itr;
                        for (itr = teams[index]["portari"].begin(); itr != teams[index]["portari"].end(); itr++) {
                            try {
                                if (Goalkeeper *aux = dynamic_cast<Goalkeeper *>(*itr)) {
                                    (*itr)->read(cout);
                                    cout << endl;
                                } else {
                                    throw badCastEx;
                                }
                            } catch (bad_cast &e) {
                                cout << e.what() << endl;
                            }
                        }
                        break;
                    }
                    case 8: {
                        set<Player *>::iterator itr;
                        for (itr = teams[index]["mijlocasi"].begin(); itr != teams[index]["mijlocasi"].end(); itr++) {
                            try {
                                if (Midfielder *aux = dynamic_cast<Midfielder *>(*itr)) {
                                    (*itr)->read(cout);
                                    cout << endl;
                                } else {
                                    throw badCastEx;
                                }
                            } catch (badCast &e) {
                                cout << e.what() << endl;
                            }
                        }
                        break;
                    }
                }
            }
        }
    } while (comanda != nameTeams.

            size()

                        + 2);
    cout << "Va multumim! O zi nemaipomenita!";
}
