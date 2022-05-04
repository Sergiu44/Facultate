#include <iostream>
#include <vector>
#include <typeinfo>
using namespace std;

class IOInterface {
public:
    virtual istream &write(istream &in) = 0;
    virtual ostream &read(ostream &out) = 0;
};

class Player {
protected:
    string firstName;
    string lastName;
    unsigned int age;
    float height;
    string mainFoot;

    unsigned int experience;
    string role;
    bool injured;
    // Basic stats
    unsigned int pace;
    unsigned int shooting;
    unsigned int physical;

    unsigned int stamina;

public:

    Player(string firstName = "John", string lastName = "Stuard", unsigned int age = 18, float height = 180,
           string mainFoot = "right", unsigned int experience = 0, string role = "bench player", bool injured = false,
           unsigned int pace = 75, unsigned int shooting = 75, unsigned int physical = 75, unsigned int stamina = 100);

    Player(const Player &player);

    Player &operator=(const Player &player);

    ~Player();

    virtual ostream &read(ostream &) const;

    virtual istream &write(istream &);

    friend ostream &operator>>(ostream &, Player &player);

    friend istream &operator<<(istream &, const Player &player);

    virtual void increaseStats() = 0;
};

Player::Player(string firstName, string lastName, unsigned int age, float height, string mainFoot,
               unsigned int experience, string role, bool injured, unsigned int pace, unsigned int shooting,
               unsigned int physical, unsigned int stamina) {
    this->firstName = firstName;
    this->lastName = lastName;
    this->age = age;
    this->height = height;
    this->experience = experience;
    this->role = role;
    this->injured = injured;
    this->pace = pace;
    this->physical = physical;
    this->mainFoot = mainFoot;
    this->shooting = shooting;
    this->stamina = stamina;
};

Player::Player(const Player &player) {
    this->firstName = player.firstName;
    this->lastName = player.lastName;
    this->age = player.age;
    this->height = player.height;
    this->experience = player.experience;
    this->role = player.role;
    this->injured = player.injured;
    this->pace = player.pace;
    this->physical = player.physical;
    this->mainFoot = player.mainFoot;
    this->shooting = player.shooting;
    this->stamina = player.stamina;
}

Player &Player::operator=(const Player &player) {
    if (this != &player) {
        this->firstName = player.firstName;
        this->lastName = player.lastName;
        this->age = player.age;
        this->height = player.height;
        this->experience = player.experience;
        this->role = player.role;
        this->injured = player.injured;
        this->pace = player.pace;
        this->physical = player.physical;
        this->mainFoot = player.mainFoot;
        this->shooting = player.shooting;
        this->stamina = player.stamina;
    }
    return *this;
}

Player::~Player() {
    cout << "Destructor jucator" << endl;
}

ostream &Player::read(ostream &out) const {
    out << "Prenume: " << this->firstName << "     ";
    out << "Nume de familie: " << this->lastName << "     ";
    out << "Varsta: " << this->age << endl;
    out << "Inaltime: " << this->height << "     ";
    out << "Experienta(in ani): " << this->experience << "      ";
    out << "Rol: " << this->role << endl;
    out << "Accidentat: " << (this->injured ? "DA" : "NU") << "     ";
    out << "Pace: " << this->pace << "     ";
    out << "Physical: " << this->physical << endl;
    out << "Shooting: " << this->shooting << "     ";
    out << "Piciorul de baza: " << this->mainFoot << "       ";
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
    cout << "Inaltime: ";
    in >> this->height;
    cout << "Experienta(in ani): ";
    in >> this->experience;
    cout << "Rol: ";
    in >> this->role;
    string str;
    this->injured = false;
    cout << "Accidentat(DA/NU): ";
    in >> str;
    if (str == "DA") {
        this->injured = true;
    }
    cout << "Pace: ";
    in >> this->pace;
    cout << "Physical: ";
    in >> this->physical;
    cout << "Shooting: ";
    in >> this->shooting;
    cout << "Piciorul de baza: ";
    in >> this->mainFoot;
    cout << "Stamina: ";
    in >> this->stamina;
    return in;
}

ostream &operator<<(ostream &out, const Player &player) {
    return player.read(out);
}

istream &operator>>(istream &in, Player &player) {
    return player.write(in);
}


class Striker : public virtual Player {
protected:
    unsigned int shotPower;
    unsigned int penalty;
    unsigned int heading;

public:
    Striker(string firstName = "John", string lastName = "Stuard", unsigned int age = 18, float height = 180,
            string mainFoot = "right", unsigned int experience = 0, string role = "bench player", bool injured = false,
            unsigned int pace = 75, unsigned int shooting = 75, unsigned int physical = 75, unsigned int stamina = 100,
            unsigned int shotPower = 75, unsigned int penalty = 75, unsigned int heading = 75);

    Striker(const Striker &);

    Striker &operator=(const Striker &);

    ~Striker();

    friend ostream &operator<<(ostream &out, const Striker &striker);

    friend istream &operator>>(istream &in, Striker &striker);

    ostream &read(ostream &) const;

    istream &write(istream &);

    void increaseStats();
};

Striker::Striker(string firstName, string lastName, unsigned int age, float height, string mainFoot,
                 unsigned int experience, string role, bool injured, unsigned int pace, unsigned int shooting,
                 unsigned int physical, unsigned int stamina, unsigned int shotPower, unsigned int penalty,
                 unsigned int heading) : Player(firstName, lastName, age, height, mainFoot, experience, role, injured,
                                                pace, shooting, physical, stamina) {
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

ostream &operator<<(ostream &out, const Striker &striker) {
    out << (Player &) striker;
    out << "Shot power: " << striker.shotPower << "     ";
    out << "Penalty: " << striker.penalty << "     ";
    out << "Heading: " << striker.heading << "     ";
    return out;
}

istream &operator>>(istream &in, Striker &striker) {
    in >> (Player &) striker;
    cout << "Shot power: ";
    in >> striker.shotPower;
    cout << "Penalty: ";
    in >> striker.penalty;
    cout << "Heading: ";
    in >> striker.heading;
    return in;
}

ostream &Striker::read(ostream &out) const {
    Player::read(out);
    out << "Shot power: " << this->shotPower << "     ";
    out << "Penalty: " << this->penalty << "     ";
    out << "Heading: " << this->heading << "     ";
    return out;
}

istream &Striker::write(istream &in) {
    Player::write(in);
    cout << "Shot power: ";
    in >> this->shotPower;
    cout << "Penalty: ";
    in >> this->penalty;
    cout << "Heading: ";
    in >> this->heading;
    return in;
}

void Striker::increaseStats() {
    if (this->stamina < 5 || this->injured) {
        cout << "Jucatorul nu are destula stamina pentru a se antrena sau este accidentat" << endl;
    } else {
        cout << "Acest jucator are " << this->stamina
             << " stamina disponibila pentru antrenament.\n\nAlege exercitiile pentru antrenament(poti alege acelasi exercitiu de mai multe ori):\n";
        int command;
        int fr[6] = {0, 0, 0, 0, 0, 0};
        cout
                << "1.Fast counter-attack (-12 stamina)\n2.Pass, go & shoot (-10 stamina)\n3.Slalom dribble (-7 stamina)\n4.Shuttle Run (-5 stamina)\n5.Penalties (-3 stamina)\n6.Finish with header (-7 stamina)\n7.Start training\n";
        cin >> command;
        int totalStamina = 0;
        while (command != 7) {
            if (command < 7 && command > 0) {
                int aux = 0;
                fr[command - 1]++;
                for (int i = 0; i < 6; ++i) {
                    if (fr[i]) {
                        switch (i) {
                            case 0: {
                                aux += fr[i] * 12;
                                cout << "Fast counter-attack (" << fr[i] << ")  ->  ";
                                break;
                            }
                            case 1: {
                                aux += fr[i] * 10;
                                cout << "Pass, go & shoot (" << fr[i] << ")  ->  ";
                                break;
                            }
                            case 2: {
                                aux += fr[i] * 7;
                                cout << "Slalom dribble (" << fr[i] << ")  ->  ";
                                break;
                            }
                            case 3: {
                                aux += fr[i] * 5;
                                cout << "Shuttle run (" << fr[i] << ")  ->  ";
                                break;
                            }
                            case 4: {
                                aux += fr[i] * 3;
                                cout << "Penalties  (" << fr[i] << ")  ->  ";
                                break;
                            }
                            case 5: {
                                aux += fr[i] * 7;
                                cout << "Finish with header (" << fr[i] << ")  ->  ";
                                break;
                            }
                            default:
                                break;
                        }
                    }
                }
                totalStamina = aux;
                cout << "\nStamina ce va fi folosita: " << totalStamina << endl;
                cout
                        << "1.Fast counter-attack (-12 stamina)\n2.Pass, go & shoot (-10 stamina)\n3.Slalom dribble (-7 stamina)\n4.Shuttle Run (-5 stamina)\n5.Penalties (-3 stamina)\n6.Finish with header (-7 stamina)\n7.Start training\n";
                cin >> command;
            } else if (command > 7 || command < 1) {
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
                                physical += 1 * fr[i];
                                shooting += 2 * fr[i];
                                break;
                            }
                            case 1: {
                                shotPower += 1 * fr[i];
                                pace += 1 * fr[i];
                                break;
                            }
                            case 2: {
                                pace += 2 * fr[i];
                                break;
                            }
                            case 3: {
                                pace += 1 * fr[i];
                                physical += 1 * fr[i];
                                break;
                            }
                            case 4: {
                                penalty += 2 * fr[i];
                                shotPower += 1 * fr[i];
                                break;
                            }
                            case 5: {
                                heading += 2 * fr[i];
                                break;
                            }
                            default:
                                break;
                        }
                    }
                }
                if (penalty) {
                    cout << "Penalty: " << this->penalty << " + " << penalty << endl;
                    this->penalty = (this->penalty + penalty > 100) ? 100 : this->penalty + penalty;
                }
                if (shotPower) {
                    cout << "Shotpower: " << this->shotPower << " + " << shotPower << endl;
                    this->shotPower = (this->shotPower + shotPower > 100) ? 100 : this->shotPower + shotPower;
                }
                if (heading) {
                    cout << "Heading: " << this->heading << " + " << heading << endl;
                    this->heading = (this->heading + heading > 100) ? 100 : this->heading + heading;
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
            }
        }
    }
}


class Defender : public virtual Player {
protected:
    unsigned int slideTackle;
    unsigned int balance;
    unsigned int strength;

public:
    Defender(string firstName = "John", string lastName = "Stuard", unsigned int age = 18, float height = 180,
             string mainFoot = "right", unsigned int experience = 0, string role = "bench player", bool injured = false,
             unsigned int pace = 75, unsigned int shooting = 75, unsigned int physical = 75, unsigned int stamina = 100,
             unsigned int slideTackle = 75, unsigned int balance = 75, unsigned int strength = 75);

    Defender(const Defender &);

    Defender &operator=(const Defender &);

    ~Defender();

    friend ostream &operator<<(ostream &out, const Defender &defender);

    friend istream &operator>>(istream &in, Defender &defender);

    ostream &read(ostream &) const;

    istream &write(istream &);

    virtual void increaseStats();
};

Defender::Defender(string firstName, string lastName, unsigned int age, float height, string mainFoot,
                   unsigned int experience, string role, bool injured, unsigned int pace, unsigned int shooting,
                   unsigned int physical, unsigned int stamina, unsigned int slideTackle, unsigned int balance,
                   unsigned int strength) : Player(firstName, lastName, age, height, mainFoot, experience, role,
                                                   injured, pace, shooting, physical, stamina) {
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

ostream &operator<<(ostream &out, const Defender &defender) {
    out << (Player &) defender << endl;
    out << "Slide tackle: " << defender.slideTackle << "     ";
    out << "Balance: " << defender.balance << "     ";
    out << "Strength: " << defender.strength << "     ";
    return out;
}

istream &operator>>(istream &in, Defender &defender) {
    in >> (Player &) defender;
    cout << "Slide tackle: ";
    in >> defender.slideTackle;
    cout << "Balance: ";
    in >> defender.balance;
    cout << "Strength: ";
    in >> defender.strength;
    return in;
}

ostream &Defender::read(ostream &out) const {
    Player::read(out);
    out << "Slide tackle: " << this->slideTackle << "     ";
    out << "Balance: " << this->balance << "     ";
    out << "Strength: " << this->strength << "     ";
    return out;
}

istream &Defender::write(istream &in) {
    Player::write(in);
    cout << "Slide tackle: ";
    in >> this->slideTackle;
    cout << "Balance: ";
    in >> this->balance;
    cout << "Strength: ";
    in >> this->strength;
    return in;
}

void Defender::increaseStats() {
    if (this->stamina < 5 || this->injured) {
        cout << "Jucatorul nu are destula stamina pentru a se antrena sau este accidentat" << endl;
    } else {
        cout << "Acest jucator are " << this->stamina
             << " stamina disponibila pentru antrenament.\n\nAlege exercitiile pentru antrenament(poti alege acelasi exercitiu de mai multe ori):\n";
        int command;
        int fr[6] = {0, 0, 0, 0, 0, 0};
        cout
                << "1.Gym (-12 stamina)\n2.Press the play (-10 stamina)\n3.Hurdle jumps (-7 stamina)\n4.Shuttle Run (-5 stamina)\n5.Guarding crosses (-10 stamina)\n6.Stretch (-5 stamina)\n7.Start training\n";
        cin >> command;
        int totalStamina = 0;
        while (command != 7) {
            if (command < 7 && command > 0) {
                int aux = 0;
                fr[command - 1]++;
                for (int i = 0; i < 6; ++i) {
                    if (fr[i]) {
                        switch (i) {
                            case 0: {
                                aux += fr[i] * 12;
                                cout << "Gym (" << fr[i] << ")  ->  ";
                                break;
                            }
                            case 1: {
                                aux += fr[i] * 10;
                                cout << "Press the play (" << fr[i] << ")  ->  ";
                                break;
                            }
                            case 2: {
                                aux += fr[i] * 7;
                                cout << "Hurdle jumps (" << fr[i] << ")  ->  ";
                                break;
                            }
                            case 3: {
                                aux += fr[i] * 5;
                                cout << "Shuttle run (" << fr[i] << ")  ->  ";
                                break;
                            }
                            case 4: {
                                aux += fr[i] * 10;
                                cout << "Guarding crosses  (" << fr[i] << ")  ->  ";
                                break;
                            }
                            case 5: {
                                aux += fr[i] * 5;
                                cout << "Stretch (" << fr[i] << ")  ->  ";
                                break;
                            }
                            default:
                                break;
                        }
                    }
                }
                totalStamina = aux;
                cout << "\nStamina ce va fi folosita: " << totalStamina << endl;
                cout
                        << "1.Gym (-12 stamina)\n2.Press the play (-10 stamina)\n3.Hurdle jumps (-7 stamina)\n4.Shuttle Run (-5 stamina)\n5.Guarding crosses (-10 stamina)\n6.Stretch (-5 stamina)\n7.Start training\n";
                cin >> command;
            } else if (command > 7 || command < 1) {
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


class Goalkeeper : public Player {
protected:
    unsigned int reflexes;
    unsigned int diving;
    unsigned int handling;

public:
    Goalkeeper(string firstName = "John", string lastName = "Stuard", unsigned int age = 18, float height = 180,
               string mainFoot = "right", unsigned int experience = 0, string role = "bench player",
               bool injured = false, unsigned int pace = 75, unsigned int shooting = 75, unsigned int physical = 75,
               unsigned int stamina = 100,
               unsigned int reflexes = 75, unsigned int diving = 75, unsigned int handling = 75);

    Goalkeeper(const Goalkeeper &);

    Goalkeeper &operator=(const Goalkeeper &);

    ~Goalkeeper();

    friend ostream &operator<<(ostream &out, const Goalkeeper &goalkeeper);

    friend istream &operator>>(istream &in, Goalkeeper &goalkeeper);

    ostream &read(ostream &) const;

    istream &write(istream &);

    void increaseStats();
};

Goalkeeper::Goalkeeper(string firstName, string lastName, unsigned int age, float height, string mainFoot,
                       unsigned int experience, string role, bool injured, unsigned int pace, unsigned int shooting,
                       unsigned int physical, unsigned int stamina, unsigned int reflexes, unsigned int diving,
                       unsigned int handling) : Player(firstName, lastName, age, height, mainFoot, experience, role,
                                                       injured, pace, shooting, physical, stamina) {
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

ostream &operator<<(ostream &out, const Goalkeeper &goalkeeper) {
    out << (Player &) goalkeeper << endl;
    return out;
}

istream &operator>>(istream &in, Goalkeeper &goalkeeper) {
    in >> (Player &) goalkeeper;
    return in;
}

ostream &Goalkeeper::read(ostream &out) const {
    Player::read(out);
    out << endl;
    out << "Reflexes: " << this->reflexes << "     ";
    out << "Diving: " << this->diving << "     ";
    out << "Handling: " << this->handling << "     ";
    return out;
}

istream &Goalkeeper::write(istream &in) {
    Player::write(in);
    cout << "Reflexes: ";
    in >> this->reflexes;
    cout << "Diving: ";
    in >> this->diving;
    cout << "Handling: ";
    in >> this->handling;
    return in;
}

void Goalkeeper::increaseStats() {
    if (this->stamina < 5 || this->injured) {
        cout << "Jucatorul nu are destula stamina pentru a se antrena sau este accidentat" << endl;
    } else {
        cout << "Acest jucator are " << this->stamina
             << " stamina disponibila pentru antrenament.\n\nAlege exercitiile pentru antrenament(poti alege acelasi exercitiu de mai multe ori):\n";
        int command;
        int fr[6] = {0, 0, 0, 0, 0, 0};
        cout
                << "1. 1-on-1 ending (-10 stamina)\n2.Carioca with ladders (-10 stamina)\n3.Long run (-5 stamina)\n4.Penalties (-7 stamina)\n5.Guarding crosses (-7 stamina)\n6.Stretch (-3 stamina)\n7.Start training\n";
        cin >> command;
        int totalStamina = 0;
        while (command != 7) {
            if (command < 7 && command > 0) {
                int aux = 0;
                fr[command - 1]++;
                for (int i = 0; i < 6; ++i) {
                    if (fr[i]) {
                        switch (i) {
                            case 0: {
                                aux += fr[i] * 10;
                                cout << "1-on-1 ending (" << fr[i] << ")  ->  ";
                                break;
                            }
                            case 1: {
                                aux += fr[i] * 10;
                                cout << "Carioca with ladders (" << fr[i] << ")  ->  ";
                                break;
                            }
                            case 2: {
                                aux += fr[i] * 5;
                                cout << "Long run (" << fr[i] << ")  ->  ";
                                break;
                            }
                            case 3: {
                                aux += fr[i] * 7;
                                cout << "Penalties (" << fr[i] << ")  ->  ";
                                break;
                            }
                            case 4: {
                                aux += fr[i] * 7;
                                cout << "Guarding crosses  (" << fr[i] << ")  ->  ";
                                break;
                            }
                            case 5: {
                                aux += fr[i] * 3;
                                cout << "Stretch (" << fr[i] << ")  ->  ";
                                break;
                            }
                            default:
                                break;
                        }
                    }
                }
                totalStamina = aux;
                cout << "\nStamina ce va fi folosita: " << totalStamina << endl;
                cout
                        << "1. 1-on-1 ending (-10 stamina)\n2.Carioca with ladders (-10 stamina)\n3.Long run (-5 stamina)\n4.Penalties (-7 stamina)\n5.Guarding crosses (-7 stamina)\n6.Stretch (-3 stamina)\n7.Start training\n";
                cin >> command;
            } else if (command > 7 || command < 1) {
                cout
                        << "1. 1-on-1 ending (-10 stamina)\n2.Carioca with ladders (-10 stamina)\n3.Long run (-5 stamina)\n4.Penalties (-7 stamina)\n5.Guarding crosses (-7 stamina)\n6.Stretch (-3 stamina)\n7.Start training\n";
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


class Midfielder : public virtual Player {
protected:
    unsigned int positioning;
    unsigned int passing;
    unsigned int vision;

public:
    Midfielder(string firstName = "John", string lastName = "Stuard", unsigned int age = 18, float height = 180,
               string mainFoot = "right", unsigned int experience = 0, string role = "bench player",
               bool injured = false, unsigned int pace = 75, unsigned int shooting = 75, unsigned int physical = 75,
               unsigned int stamina = 100,
               unsigned int positioning = 75, unsigned int passing = 75, unsigned int vision = 75);

    Midfielder(const Midfielder &);

    Midfielder &operator=(const Midfielder &);

    ~Midfielder();

    friend ostream &operator<<(ostream &out, const Midfielder &midfielder);

    friend istream &operator>>(istream &in, Midfielder &midfielder);

    ostream &read(ostream &) const;

    istream &write(istream &);

    virtual void increaseStats();
};

Midfielder::Midfielder(string firstName, string lastName, unsigned int age, float height, string mainFoot,
                       unsigned int experience, string role, bool injured, unsigned int pace, unsigned int shooting,
                       unsigned int physical, unsigned int stamina, unsigned int positioning, unsigned int passing,
                       unsigned int vision) : Player(firstName, lastName, age, height, mainFoot, experience, role,
                                                     injured, pace, shooting, physical, stamina) {
    this->positioning = positioning;
    this->passing = passing;
    this->vision = vision;
}

Midfielder::Midfielder(const Midfielder &midfielder) : Player(midfielder) {
    this->positioning = midfielder.positioning;
    this->passing = midfielder.passing;
    this->vision = midfielder.vision;
}

Midfielder &Midfielder::operator=(const Midfielder &midfielder) {
    if (this != &midfielder) {
        Player::operator=(midfielder);
        this->positioning = midfielder.positioning;
        this->passing = midfielder.passing;
        this->vision = midfielder.vision;
    }
    return *this;
}

Midfielder::~Midfielder() {
    cout << "Destructor mijlocas" << endl;
}

ostream &operator<<(ostream &out, const Midfielder &midfielder) {
    out << (Player &) midfielder << endl;
    return out;
}

istream &operator>>(istream &in, Midfielder &midfielder) {
    in >> (Player &) midfielder;
    return in;
}

ostream &Midfielder::read(ostream &out) const {
    Player::read(out);
    out << endl;
    out << "Positioning: " << this->positioning << "      ";
    out << "Passing: " << this->passing << "      ";
    out << "Vision: " << this->vision << "       ";
    return out;
}

istream &Midfielder::write(istream &in) {
    Player::write(in);
    cout << "Positioning: ";
    in >> this->positioning;
    cout << "Passing: ";
    in >> this->passing;
    cout << "Vision: ";
    in >> this->vision;
    return in;
}

void Midfielder::increaseStats() {
    if (this->stamina < 5 || this->injured) {
        cout << "Jucatorul nu are destula stamina pentru a se antrena sau este accidentat" << endl;
    } else {
        cout << "Acest jucator are " << this->stamina
             << " stamina disponibila pentru antrenament.\n\nAlege exercitiile pentru antrenament(poti alege acelasi exercitiu de mai multe ori):\n";
        int command;
        int fr[6] = {0, 0, 0, 0, 0, 0};
        cout
                << "1.Long run (-5 stamina)\n2.Pass, go & shoot (-10 stamina)\n3.Piggy in the middle (-12 stamina)\n4.Hold the line (-7 stamina)\n5.Penalties (-3 stamina)\n6.Video analysis (-5 stamina)\n7.Start training\n";
        cin >> command;
        int totalStamina = 0;
        while (command != 7) {
            if (command < 7 && command > 0) {
                int aux = 0;
                fr[command - 1]++;
                for (int i = 0; i < 6; ++i) {
                    if (fr[i]) {
                        switch (i) {
                            case 0: {
                                aux += fr[i] * 5;
                                cout << "Long run (" << fr[i] << ")  ->  ";
                                break;
                            }
                            case 1: {
                                aux += fr[i] * 10;
                                cout << "Pass, go & shoot (" << fr[i] << ")  ->  ";
                                break;
                            }
                            case 2: {
                                aux += fr[i] * 12;
                                cout << "Piggy in the middle (" << fr[i] << ")  ->  ";
                                break;
                            }
                            case 3: {
                                aux += fr[i] * 7;
                                cout << "Hold the line (" << fr[i] << ")  ->  ";
                                break;
                            }
                            case 4: {
                                aux += fr[i] * 3;
                                cout << "Penalties  (" << fr[i] << ")  ->  ";
                                break;
                            }
                            case 5: {
                                aux += fr[i] * 5;
                                cout << "Video analysis (" << fr[i] << ")  ->  ";
                                break;
                            }
                            default:
                                break;
                        }
                    }
                }
                totalStamina = aux;
                cout << "\nStamina ce va fi folosita: " << totalStamina << endl;
                cout
                        << "1.Long run (-5 stamina)\n2.Pass, go & shoot (-10 stamina)\n3.Piggy in the middle (-12 stamina)\n4.Hold the line (-7 stamina)\n5.Penalties (-3 stamina)\n6.Video analysis (-5 stamina)\n7.Start training\n";
                cin >> command;
            } else if (command > 7 || command < 1) {
                cout
                        << "1.Long run (-5 stamina)\n2.Pass, go & shoot (-10 stamina)\n3.Piggy in the middle (-12 stamina)\n4.Hold the line (-7 stamina)\n5.Penalties (-3 stamina)\n6.Video analysis (-5 stamina)\n7.Start training\n";
                cin >> command;
            }
        }
        if (command == 7) {
            if (totalStamina > this->stamina) {
                cout << "Antrenamentul necesita mai multa stamina decat are jucatorul deja" << endl;
            } else {
                int pace = 0, physical = 0, shooting = 0, positioning = 0, passing = 0, vision = 0;
                this->stamina -= totalStamina;
                if (this->stamina < 10) {
                    this->injured = true;
                }
                for (int i = 0; i < 6; ++i) {
                    if (fr[i]) {
                        switch (i) {
                            case 0: {
                                physical += 1 * fr[i];
                                pace += 1 * fr[i];
                                break;
                            }
                            case 1: {
                                passing += 2 * fr[i];
                                shooting += 1 * fr[i];
                                break;
                            }
                            case 2: {
                                pace += 1 * fr[i];
                                vision += 2 * fr[i];
                                positioning += 1 * fr[i];
                                break;
                            }
                            case 3: {
                                positioning += 1 * fr[i];
                                vision += 1 * fr[i];
                                break;
                            }
                            case 4: {
                                shooting += 1 * fr[i];
                                break;
                            }
                            case 5: {
                                vision += 1 * fr[i];
                                positioning += 1 * fr[i];
                                break;
                            }
                            default:
                                break;
                        }
                    }
                }
                if (positioning) {
                    cout << "Positioning: " << this->positioning << " + " << positioning << endl;
                    this->positioning = (this->positioning + positioning > 100) ? 100 : this->positioning + positioning;
                }
                if (vision) {
                    cout << "Vision: " << this->vision << " + " << vision << endl;
                    this->vision = (this->vision + vision > 100) ? 100 : this->vision + vision;
                }
                if (passing) {
                    cout << "Passing: " << this->passing << " + " << passing << endl;
                    this->passing = (this->passing + passing > 100) ? 100 : this->passing + passing;
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
            }
        }
    }
}

class Winger : public virtual Defender, public virtual Striker {
private:
    unsigned int acceleration;
    unsigned int crossing;
    unsigned int footWork;

public:
    Winger(string firstName = "John", string lastName = "Stuard", unsigned int age = 18, float height = 180,
           string mainFoot = "right", unsigned int experience = 0, string role = "bench player", bool injured = false,
           unsigned int pace = 75, unsigned int shooting = 75, unsigned int physical = 75, unsigned int stamina = 100,
           unsigned int slideTackle = 75, unsigned int balance = 75, unsigned int strength = 75,
           unsigned int shotPower = 75, unsigned int penalty = 75, unsigned int heading = 75,
           unsigned int acceleration = 75, unsigned int crossing = 75, unsigned int footWork = 75);

    Winger(const Winger &);

    Winger &operator=(const Winger &);

    ~Winger();

    friend ostream &operator<<(ostream &out, const Winger &winger);

    friend istream &operator>>(istream &in, Winger &winger);

    ostream &read(ostream &) const;

    istream &write(istream &);

    void increaseStats();
};

Winger::Winger(string firstName, string lastName, unsigned int age, float height, string mainFoot,
               unsigned int experience, string role, bool injured, unsigned int pace, unsigned int shooting,
               unsigned int physical, unsigned int stamina, unsigned int slideTackle, unsigned int balance,
               unsigned int strength,
               unsigned int shotPower, unsigned int penalty, unsigned int heading, unsigned int acceleration,
               unsigned int crossing, unsigned int footWork) : Defender(firstName, lastName, age, height, mainFoot,
                                                                        experience, role, injured, pace, shooting,
                                                                        physical, stamina, slideTackle, balance,
                                                                        strength),
                                                               Striker(firstName, lastName, age, height, mainFoot,
                                                                       experience, role, injured, pace, shooting,
                                                                       physical, stamina, shotPower, penalty, heading),
                                                               Player(firstName, lastName, age, height, mainFoot,
                                                                      experience, role, injured, pace, shooting,
                                                                      physical, stamina) {
    this->acceleration = acceleration;
    this->crossing = crossing;
    this->footWork = footWork;
}

Winger::Winger(const Winger &winger) : Defender(winger), Striker(winger), Player(winger) {
    this->acceleration = winger.acceleration;
    this->crossing = winger.crossing;
    this->footWork = winger.footWork;
}

Winger &Winger::operator=(const Winger &winger) {
    if (this != &winger) {
        Defender::operator=(winger);
        Striker::operator=(winger);
        Player::operator=(winger);
        this->acceleration = winger.acceleration;
        this->crossing = winger.crossing;
        this->footWork = winger.footWork;
    }
    return *this;
}

Winger::~Winger() {
    cout << "Destructor extrema" << endl;
}

ostream &operator<<(ostream &out, const Winger &winger) {
    out << (Defender &) winger << endl;
    return out;
}

istream &operator>>(istream &in, Winger &winger) {
    in >> (Defender &) winger;
    cout << "Shot power: ";
    in >> winger.shotPower;
    cout << "Penalty: ";
    in >> winger.penalty;
    cout << "Heading: ";
    in >> winger.heading;
    cout << "Acceleration: ";
    in >> winger.acceleration;
    cout << "Crossing: ";
    in >> winger.crossing;
    cout << "Footwork: ";
    in >> winger.footWork;
    return in;
}

ostream &Winger::read(ostream &out) const {
    Defender::read(out);
    out << endl;
    out << "Shot power: " << this->shotPower << "    ";
    out << "Penalty: " << this->penalty << "    ";
    out << "Heading: " << this->heading << endl;
    out << "Acceleration: " << this->acceleration << "    ";
    out << "Crossing: " << this->crossing << "    ";
    out << "Footwork: " << this->footWork << endl;
    return out;
}

istream &Winger::write(istream &in) {
    Defender::write(in);
    cout << "Shot power: ";
    in >> this->shotPower;
    cout << "Penalty: ";
    in >> this->penalty;
    cout << "Heading: ";
    in >> this->heading;
    cout << "Acceleration: ";
    in >> this->acceleration;
    cout << "Crossing: ";
    in >> this->crossing;
    cout << "Footwork: ";
    in >> this->footWork;
    return in;
}

void Winger::increaseStats() {
    if (this->stamina < 5 || this->injured) {
        cout << "Jucatorul nu are destula stamina pentru a se antrena sau este accidentat" << endl;
    } else {
        cout << "Acest jucator are " << this->stamina
             << " stamina disponibila pentru antrenament.\n\nAlege exercitiile pentru antrenament(poti alege acelasi exercitiu de mai multe ori):\n";
        int command;
        int fr[6] = {0, 0, 0, 0, 0, 0};
        cout
                << "1.Wing play (-15 stamina)\n2.Pass, go & shoot (-7 stamina)\n3.Sprints (-7 stamina)\n4.Press the play (-10 stamina)\n5.Crosses (-3 stamina)\n6.Slalom dribble (-5 stamina)\n7.Start training\n";
        cin >> command;
        int totalStamina = 0;
        while (command != 7) {
            if (command < 7 && command > 0) {
                int aux = 0;
                fr[command - 1]++;
                for (int i = 0; i < 6; ++i) {
                    if (fr[i]) {
                        switch (i) {
                            case 0: {
                                aux += fr[i] * 15;
                                cout << "Wing play (" << fr[i] << ")  ->  ";
                                break;
                            }
                            case 1: {
                                aux += fr[i] * 10;
                                cout << "Pass, go & shoot (" << fr[i] << ")  ->  ";
                                break;
                            }
                            case 2: {
                                aux += fr[i] * 7;
                                cout << "Sprints (" << fr[i] << ")  ->  ";
                                break;
                            }
                            case 3: {
                                aux += fr[i] * 7;
                                cout << "Fast counter-attack (" << fr[i] << ")  ->  ";
                                break;
                            }
                            case 4: {
                                aux += fr[i] * 3;
                                cout << "Crosses  (" << fr[i] << ")  ->  ";
                                break;
                            }
                            case 5: {
                                aux += fr[i] * 5;
                                cout << "Slalom dribble (" << fr[i] << ")  ->  ";
                                break;
                            }
                            default:
                                break;
                        }
                    }
                }
                totalStamina = aux;
                cout << "\nStamina ce va fi folosita: " << totalStamina << endl;
                cout
                        << "1.Wing play (-15 stamina)\n2.Pass, go & shoot (-7 stamina)\n3.Sprints (-7 stamina)\n4.Press the play (-10 stamina)\n5.Crosses (-3 stamina)\n6.Slalom dribble (-5 stamina)\n7.Start training\n";
                cin >> command;
            } else if (command > 7 || command < 1) {
                cout
                        << "1.Wing play (-15 stamina)\n2.Pass, go & shoot (-7 stamina)\n3.Sprints (-7 stamina)\n4.Press the play (-10 stamina)\n5.Crosses (-3 stamina)\n6.Slalom dribble (-5 stamina)\n7.Start training\n";
                cin >> command;
            }
        }
        if (command == 7) {
            if (totalStamina > this->stamina) {
                cout << "Antrenamentul necesita mai multa stamina decat are jucatorul deja" << endl;
            } else {
                int pace = 0, physical = 0, shooting = 0, slideTackle = 0, balance = 0, strength = 0;
                int heading = 0, acceleration = 0, crossing = 0, footWork = 0;
                this->stamina -= totalStamina;
                if (this->stamina < 10) {
                    this->injured = true;
                }
                for (int i = 0; i < 6; ++i) {
                    if (fr[i]) {
                        switch (i) {
                            case 0: {
                                crossing += 1 * fr[i];
                                acceleration += 1 * fr[i];
                                pace += 1 * fr[i];
                                footWork += 1 * fr[i];
                                shooting += 1 * fr[i];
                                break;
                            }
                            case 1: {
                                shooting += 1 * fr[i];
                                physical += 1 * fr[i];
                                break;
                            }
                            case 2: {
                                pace += 1 * fr[i];
                                acceleration += 2 * fr[i];
                                balance += 1 * fr[i];
                                break;
                            }
                            case 3: {
                                strength += 1 * fr[i];
                                slideTackle += 1 * fr[i];
                                physical += 1 * fr[i];
                                break;
                            }
                            case 4: {
                                crossing += 1 * fr[i];
                                heading += 1 * fr[i];
                                break;
                            }
                            case 5: {
                                balance += 1 * fr[i];
                                acceleration += 1 * fr[i];
                                footWork += 1 * fr[i];
                                break;
                            }
                            default:
                                break;
                        }
                    }
                }
                if (acceleration) {
                    cout << "Acceleration: " << this->acceleration << " + " << acceleration << endl;
                    this->acceleration = (this->acceleration + acceleration > 100) ? 100 : this->acceleration +
                                                                                           acceleration;
                }
                if (crossing) {
                    cout << "Crossing: " << this->crossing << " + " << crossing << endl;
                    this->crossing = (this->crossing + crossing > 100) ? 100 : this->crossing + crossing;
                }
                if (footWork) {
                    cout << "Footwork: " << this->footWork << " + " << footWork << endl;
                    this->footWork = (this->footWork + footWork > 100) ? 100 : this->footWork + footWork;
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
                if (heading) {
                    cout << "Heading: " << this->heading << " + " << heading << endl;
                    this->heading = (this->heading + heading > 100) ? 100 : this->heading + heading;
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

class DefensiveMidfielder : public virtual Defender, public virtual Midfielder {
private:
    unsigned int aggressiveness;
    unsigned int interceptions;
    unsigned int marking;

public:
    DefensiveMidfielder(string firstName = "John", string lastName = "Stuard", unsigned int age = 18,
                        float height = 180, string mainFoot = "right", unsigned int experience = 0,
                        string role = "bench player", bool injured = false, unsigned int pace = 75,
                        unsigned int shooting = 75, unsigned int physical = 75, unsigned int stamina = 100,
                        unsigned int slideTackle = 75, unsigned int balance = 75, unsigned int strength = 75,
                        unsigned int positioning = 75, unsigned int passing = 75, unsigned int vision = 75,
                        unsigned int aggressiveness = 75, unsigned int interceptions = 75, unsigned int marking = 75);

    DefensiveMidfielder(const DefensiveMidfielder &);

    DefensiveMidfielder &operator=(const DefensiveMidfielder &);

    ~DefensiveMidfielder();

    friend ostream &operator<<(ostream &out, const DefensiveMidfielder &defMidfielder);

    friend istream &operator>>(istream &in, DefensiveMidfielder &defMidfielder);

    ostream &read(ostream &) const;

    istream &write(istream &);

    void increaseStats();
};

DefensiveMidfielder::DefensiveMidfielder(string firstName, string lastName, unsigned int age, float height,
                                         string mainFoot,
                                         unsigned int experience, string role, bool injured, unsigned int pace,
                                         unsigned int shooting,
                                         unsigned int physical, unsigned int stamina, unsigned int slideTackle,
                                         unsigned int balance, unsigned int strength,
                                         unsigned int positioning, unsigned int passing, unsigned int vision,
                                         unsigned int aggressiveness, unsigned int interceptions, unsigned int marking)
        : Defender(firstName, lastName, age, height, mainFoot, experience, role, injured, pace, shooting, physical,
                   stamina, slideTackle, balance, strength),
          Midfielder(firstName, lastName, age, height, mainFoot, experience, role, injured, pace, shooting, physical,
                     stamina, positioning, passing, vision),
          Player(firstName, lastName, age, height, mainFoot, experience, role, injured, pace, shooting, physical,
                 stamina) {
    this->aggressiveness = aggressiveness;
    this->interceptions = interceptions;
    this->marking = marking;
}

DefensiveMidfielder::DefensiveMidfielder(const DefensiveMidfielder &defMidfielder) : Defender(defMidfielder),
                                                                                     Midfielder(defMidfielder),
                                                                                     Player(defMidfielder) {
    this->aggressiveness = defMidfielder.aggressiveness;
    this->interceptions = defMidfielder.interceptions;
    this->marking = defMidfielder.marking;
}

DefensiveMidfielder &DefensiveMidfielder::operator=(const DefensiveMidfielder &defMidfielder) {
    if (this != &defMidfielder) {
        Defender::operator=(defMidfielder);
        Midfielder::operator=(defMidfielder);
        Player::operator=(defMidfielder);
        this->aggressiveness = defMidfielder.aggressiveness;
        this->interceptions = defMidfielder.interceptions;
        this->marking = defMidfielder.marking;
    }
    return *this;
}

DefensiveMidfielder::~DefensiveMidfielder() {
    cout << "Destructor mijlocas defensiv" << endl;
}

ostream &operator<<(ostream &out, const DefensiveMidfielder &defMidfielder) {
    out << (Defender &) defMidfielder << endl;
    out << "Positioning: " << defMidfielder.positioning << "    ";
    out << "Passing: " << defMidfielder.passing << "    ";
    out << "Vision: " << defMidfielder.vision << endl;
    out << "Aggressiveness: " << defMidfielder.aggressiveness << "    ";
    out << "Interceptions: " << defMidfielder.interceptions << "    ";
    out << "Marking: " << defMidfielder.marking << endl;
    return out;
}

istream &operator>>(istream &in, DefensiveMidfielder &defMidfielder) {
    in >> (Defender &) defMidfielder;
    cout << "Positioning: ";
    in >> defMidfielder.positioning;
    cout << "Passing: ";
    in >> defMidfielder.passing;
    cout << "Vision: ";
    in >> defMidfielder.vision;
    cout << "Aggressiveness: ";
    in >> defMidfielder.aggressiveness;
    cout << "Interceptions: ";
    in >> defMidfielder.interceptions;
    cout << "Marking: ";
    in >> defMidfielder.marking;
    return in;
}

ostream &DefensiveMidfielder::read(ostream &out) const {
    Defender::read(out);
    out << endl;
    out << "Positioning: " << this->positioning << "    ";
    out << "Passing: " << this->passing << "    ";
    out << "Vision: " << this->vision << endl;
    out << "Aggressiveness: " << this->aggressiveness << "    ";
    out << "Interceptions: " << this->interceptions << "    ";
    out << "Marking: " << this->marking << endl;
    return out;
}

istream &DefensiveMidfielder::write(istream &in) {
    Defender::write(in);
    cout << "Positioning: ";
    in >> this->positioning;
    cout << "Passing: ";
    in >> this->passing;
    cout << "Vision: ";
    in >> this->vision;
    cout << "Aggressiveness: ";
    in >> this->aggressiveness;
    cout << "Interceptions: ";
    in >> this->interceptions;
    cout << "Marking: ";
    in >> this->marking;
    return in;
}

void DefensiveMidfielder::increaseStats() {
    if (this->stamina < 5 || this->injured) {
        cout << "Jucatorul nu are destula stamina pentru a se antrena sau este accidentat" << endl;
    } else {
        cout << "Acest jucator are " << this->stamina
             << " stamina disponibila pentru antrenament.\n\nAlege exercitiile pentru antrenament(poti alege acelasi exercitiu de mai multe ori):\n";
        int command;
        int fr[6] = {0, 0, 0, 0, 0, 0};
        cout
                << "1.Piggy in the middle (-12 stamina)\n2.Pass, go & shoot (-7 stamina)\n3.Carioca with ladders (-7 stamina)\n4.Press the play (-15 stamina)\n5.Stop the attacker (-7 stamina)\n6.Video analysis (-3 stamina)\n7.Start training\n";
        cin >> command;
        int totalStamina = 0;
        while (command != 7) {
            if (command < 7 && command > 0) {
                int aux = 0;
                fr[command - 1]++;
                for (int i = 0; i < 6; ++i) {
                    if (fr[i]) {
                        switch (i) {
                            case 0: {
                                aux += fr[i] * 12;
                                cout << "Piggy in the middle (" << fr[i] << ")  ->  ";
                                break;
                            }
                            case 1: {
                                aux += fr[i] * 7;
                                cout << "Pass, go & shoot (" << fr[i] << ")  ->  ";
                                break;
                            }
                            case 2: {
                                aux += fr[i] * 7;
                                cout << "Carioca with ladders (" << fr[i] << ")  ->  ";
                                break;
                            }
                            case 3: {
                                aux += fr[i] * 15;
                                cout << "Press the play (" << fr[i] << ")  ->  ";
                                break;
                            }
                            case 4: {
                                aux += fr[i] * 7;
                                cout << "Stop the attacker (" << fr[i] << ")  ->  ";
                                break;
                            }
                            case 5: {
                                aux += fr[i] * 3;
                                cout << "Video analysis (" << fr[i] << ")  ->  ";
                                break;
                            }
                            default:
                                break;
                        }
                    }
                }
                totalStamina = aux;
                cout << "\nStamina ce va fi folosita: " << totalStamina << endl;
                cout
                        << "1.Piggy in the middle (-12 stamina)\n2.Pass, go & shoot (-7 stamina)\n3.Carioca with ladders (-7 stamina)\n4.Press the play (-15 stamina)\n5.Stop the attacker (-7 stamina)\n6.Video analysis (-3 stamina)\n7.Start training\n";
                cin >> command;
            } else if (command > 7 || command < 1) {
                cout
                        << "1.Piggy in the middle (-15 stamina)\n2.Pass, go & shoot (-7 stamina)\n3.Carioca with ladders (-7 stamina)\n4.Press the play (-15 stamina)\n5.Stop the attacker (-7 stamina)\n6.Video analysis (-3 stamina)\n7.Start training\n";
                cin >> command;
            }
        }
        if (command == 7) {
            if (totalStamina > this->stamina) {
                cout << "Antrenamentul necesita mai multa stamina decat are jucatorul deja" << endl;
            } else {
                int pace = 0, physical = 0, shooting = 0, slideTackle = 0, balance = 0, strength = 0;
                int positioning = 0, vision = 0, passing = 0, interceptions = 0, marking = 0, aggressiveness = 0;
                this->stamina -= totalStamina;
                if (this->stamina < 10) {
                    this->injured = true;
                }
                for (int i = 0; i < 6; ++i) {
                    if (fr[i]) {
                        switch (i) {
                            case 0: {
                                interceptions += 2 * fr[i];
                                aggressiveness += 1 * fr[i];
                                positioning += 1 * fr[i];
                                slideTackle += 1 * fr[i];
                                break;
                            }
                            case 1: {
                                shooting += 1 * fr[i];
                                passing += 2 * fr[i];
                                break;
                            }
                            case 2: {
                                balance += 1 * fr[i];
                                physical += 1 * fr[i];
                                break;
                            }
                            case 3: {
                                strength += 1 * fr[i];
                                slideTackle += 1 * fr[i];
                                physical += 1 * fr[i];
                                interceptions += 1 * fr[i];
                                break;
                            }
                            case 4: {
                                aggressiveness += 1 * fr[i];
                                strength += 1 * fr[i];
                                positioning += 1 * fr[i];
                                break;
                            }
                            case 5: {
                                vision += 1 * fr[i];
                                positioning += 1 * fr[i];
                                break;
                            }
                            default:
                                break;
                        }
                    }
                }
                if (interceptions) {
                    cout << "Interceptions: " << this->interceptions << " + " << interceptions << endl;
                    this->interceptions = (this->interceptions + interceptions > 100) ? 100 : this->interceptions +
                                                                                              interceptions;
                }
                if (marking) {
                    cout << "Marking: " << this->marking << " + " << marking << endl;
                    this->marking = (this->marking + marking > 100) ? 100 : this->marking + marking;
                }
                if (aggressiveness) {
                    cout << "Aggressiveness: " << this->aggressiveness << " + " << aggressiveness << endl;
                    this->aggressiveness = (this->aggressiveness + aggressiveness > 100) ? 100 : this->aggressiveness +
                                                                                                 aggressiveness;
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
                if (positioning) {
                    cout << "Positioning: " << this->positioning << " + " << positioning << endl;
                    this->positioning = (this->positioning + positioning > 100) ? 100 : this->positioning + positioning;
                }
                if (passing) {
                    cout << "Passing: " << this->passing << " + " << passing << endl;
                    this->passing = (this->passing + passing > 100) ? 100 : this->passing + passing;
                }
                if (vision) {
                    cout << "Vision: " << this->vision << " + " << vision << endl;
                    this->vision = (this->vision + vision > 100) ? 100 : this->vision + vision;
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


class AttackingMidfielder : public virtual Striker, public virtual Midfielder {
private:
    unsigned int skillMoves;
    unsigned int ballControl;
    unsigned int composure;

public:
    AttackingMidfielder(string firstName = "John", string lastName = "Stuard", unsigned int age = 18,
                        float height = 180, string mainFoot = "right", unsigned int experience = 0,
                        string role = "bench player", bool injured = false, unsigned int pace = 75,
                        unsigned int shooting = 75, unsigned int physical = 75, unsigned int stamina = 100,
                        unsigned int shotPower = 75, unsigned int penalty = 75, unsigned int heading = 75,
                        unsigned int positioning = 75, unsigned int passing = 75, unsigned int vision = 75,
                        unsigned int skillMoves = 75, unsigned int ballControl = 75, unsigned int composure = 75);

    AttackingMidfielder(const AttackingMidfielder &);

    AttackingMidfielder &operator=(const AttackingMidfielder &);

    ~AttackingMidfielder();

    friend ostream &operator<<(ostream &out, const AttackingMidfielder &attMidfielder);

    friend istream &operator>>(istream &in, AttackingMidfielder &attMidfielder);

    ostream &read(ostream &) const;

    istream &write(istream &);

    void increaseStats();
};

AttackingMidfielder::AttackingMidfielder(string firstName, string lastName, unsigned int age, float height,
                                         string mainFoot,
                                         unsigned int experience, string role, bool injured, unsigned int pace,
                                         unsigned int shooting,
                                         unsigned int physical, unsigned int stamina, unsigned int shotPower,
                                         unsigned int penalty, unsigned int heading,
                                         unsigned int positioning, unsigned int passing, unsigned int vision,
                                         unsigned int skillMoves, unsigned int ballControl, unsigned int composure)
        : Striker(firstName, lastName, age, height, mainFoot, experience, role, injured, pace, shooting, physical,
                  stamina, shotPower, penalty, heading),
          Midfielder(firstName, lastName, age, height, mainFoot, experience, role, injured, pace, shooting, physical,
                     stamina, positioning, passing, vision),
          Player(firstName, lastName, age, height, mainFoot, experience, role, injured, pace, shooting, physical,
                 stamina) {
    this->skillMoves = skillMoves;
    this->ballControl = ballControl;
    this->composure = composure;
}

AttackingMidfielder::AttackingMidfielder(const AttackingMidfielder &attMidfielder) : Striker(attMidfielder),
                                                                                     Midfielder(attMidfielder),
                                                                                     Player(attMidfielder) {
    this->skillMoves = attMidfielder.skillMoves;
    this->ballControl = attMidfielder.ballControl;
    this->composure = attMidfielder.composure;
}

AttackingMidfielder &AttackingMidfielder::operator=(const AttackingMidfielder &attMidfielder) {
    if (this != &attMidfielder) {
        Striker::operator=(attMidfielder);
        Midfielder::operator=(attMidfielder);
        Player::operator=(attMidfielder);
        this->skillMoves = attMidfielder.skillMoves;
        this->ballControl = attMidfielder.ballControl;
        this->composure = attMidfielder.composure;
    }
    return *this;
}

AttackingMidfielder::~AttackingMidfielder() {
    cout << "Destructor mijlocas ofensiv" << endl;
}

ostream &operator<<(ostream &out, const AttackingMidfielder &attMidfielder) {
    out << (Striker &) attMidfielder << endl;
    out << "Positioning: " << attMidfielder.positioning << "    ";
    out << "Passing: " << attMidfielder.passing << "    ";
    out << "Vision: " << attMidfielder.vision << endl;
    out << "Skill moves: " << attMidfielder.skillMoves << "    ";
    out << "Ball control: " << attMidfielder.ballControl << "    ";
    out << "Composure: " << attMidfielder.composure << endl;
    return out;
}

istream &operator>>(istream &in, AttackingMidfielder &attMidfielder) {
    in >> (Striker &) attMidfielder;
    cout << "Positioning: ";
    in >> attMidfielder.positioning;
    cout << "Passing: ";
    in >> attMidfielder.passing;
    cout << "Vision: ";
    in >> attMidfielder.vision;
    cout << "Skill moves: ";
    in >> attMidfielder.skillMoves;
    cout << "Ball control: ";
    in >> attMidfielder.ballControl;
    cout << "Composure: ";
    in >> attMidfielder.composure;
    return in;
}

ostream &AttackingMidfielder::read(ostream &out) const {
    Striker::read(out);
    out << endl;
    out << "Positioning: " << this->positioning << "    ";
    out << "Passing: " << this->passing << "    ";
    out << "Vision: " << this->vision << endl;
    out << "Skill moves: " << this->skillMoves << "    ";
    out << "Ball control: " << this->ballControl << "    ";
    out << "Composure: " << this->composure << endl;
    return out;
}

istream &AttackingMidfielder::write(istream &in) {
    Striker::write(in);
    cout << "Positioning: ";
    in >> this->positioning;
    cout << "Passing: ";
    in >> this->passing;
    cout << "Vision: ";
    in >> this->vision;
    cout << "Skill moves: ";
    in >> this->skillMoves;
    cout << "Ball control: ";
    in >> this->ballControl;
    cout << "Composure: ";
    in >> this->composure;
    return in;
}

void AttackingMidfielder::increaseStats() {
    if (this->stamina < 5 || this->injured) {
        cout << "Jucatorul nu are destula stamina pentru a se antrena sau este accidentat" << endl;
    } else {
        cout << "Acest jucator are " << this->stamina
             << " stamina disponibila pentru antrenament.\n\nAlege exercitiile pentru antrenament(poti alege acelasi exercitiu de mai multe ori):\n";
        int command;
        int fr[6] = {0, 0, 0, 0, 0, 0};
        cout
                << "1.Slalom dribble (-10 stamina)\n2.Pass, go & shoot (-12 stamina)\n3.Fast counter-attack (-10 stamina)\n4.Press the play (-12 stamina)\n5.Gym (-5 stamina)\n6.Penalties (-3 stamina)\n7.Start training\n";
        cin >> command;
        int totalStamina = 0;
        while (command != 7) {
            if (command < 7 && command > 0) {
                int aux = 0;
                fr[command - 1]++;
                for (int i = 0; i < 6; ++i) {
                    if (fr[i]) {
                        switch (i) {
                            case 0: {
                                aux += fr[i] * 10;
                                cout << "Slalom dribble (" << fr[i] << ")  ->  ";
                                break;
                            }
                            case 1: {
                                aux += fr[i] * 12;
                                cout << "Pass, go & shoot (" << fr[i] << ")  ->  ";
                                break;
                            }
                            case 2: {
                                aux += fr[i] * 10;
                                cout << "Fast counter-attack (" << fr[i] << ")  ->  ";
                                break;
                            }
                            case 3: {
                                aux += fr[i] * 12;
                                cout << "Press the play (" << fr[i] << ")  ->  ";
                                break;
                            }
                            case 4: {
                                aux += fr[i] * 5;
                                cout << "Gym (" << fr[i] << ")  ->  ";
                                break;
                            }
                            case 5: {
                                aux += fr[i] * 3;
                                cout << "Penalties (" << fr[i] << ")  ->  ";
                                break;
                            }
                            default:
                                break;
                        }
                    }
                }
                totalStamina = aux;
                cout << "\nStamina ce va fi folosita: " << totalStamina << endl;
                cout
                        << "1.Slalom dribble (-10 stamina)\n2.Pass, go & shoot (-12 stamina)\n3.Fast counter-attack (-10 stamina)\n4.Press the play (-12 stamina)\n5.Gym (-5 stamina)\n6.Penalties (-3 stamina)\n7.Start training\n";
                cin >> command;
            } else if (command > 7 || command < 1) {
                cout
                        << "1.Slalom dribble (-10 stamina)\n2.Pass, go & shoot (-12 stamina)\n3.Fast counter-attack (-10 stamina)\n4.Press the play (-12 stamina)\n5.Gym (-5 stamina)\n6.Penalties (-3 stamina)\n7.Start training\n";
                cin >> command;
            }
        }
        if (command == 7) {
            if (totalStamina > this->stamina) {
                cout << "Antrenamentul necesita mai multa stamina decat are jucatorul deja" << endl;
            } else {
                int pace = 0, physical = 0, shooting = 0, shotPower = 0, penalty = 0;
                int positioning = 0, vision = 0, passing = 0, skillMoves = 0, ballControl = 0, composure = 0;
                this->stamina -= totalStamina;
                if (this->stamina < 10) {
                    this->injured = true;
                }
                for (int i = 0; i < 6; ++i) {
                    if (fr[i]) {
                        switch (i) {
                            case 0: {
                                ballControl += 2 * fr[i];
                                skillMoves += 2 * fr[i];
                                break;
                            }
                            case 1: {
                                shooting += 1 * fr[i];
                                passing += 1 * fr[i];
                                vision += 1 * fr[i];
                                composure += 1 * fr[i];
                                break;
                            }
                            case 2: {
                                composure += 2 * fr[i];
                                physical += 1 * fr[i];
                                pace += 1 * fr[i];
                                break;
                            }
                            case 3: {
                                ballControl += 1 * fr[i];
                                positioning += 1 * fr[i];
                                vision += 1 * fr[i];
                                physical += 1 * fr[i];
                                break;
                            }
                            case 4: {
                                physical += 2 * fr[i];
                                break;
                            }
                            case 5: {
                                shotPower += 1 * fr[i];
                                penalty += 1 * fr[i];
                                shooting += 1 * fr[i];
                                break;
                            }
                            default:
                                break;
                        }
                    }
                }
                if (ballControl) {
                    cout << "Ball control: " << this->ballControl << " + " << ballControl << endl;
                    this->ballControl = (this->ballControl + ballControl > 100) ? 100 : this->ballControl + ballControl;
                }
                if (skillMoves) {
                    cout << "Skill moves: " << this->skillMoves << " + " << skillMoves << endl;
                    this->skillMoves = (this->skillMoves + skillMoves > 100) ? 100 : this->skillMoves + skillMoves;
                }
                if (composure) {
                    cout << "Composure: " << this->composure << " + " << command << endl;
                    this->composure = (this->composure + composure > 100) ? 100 : this->composure + composure;
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
                if (positioning) {
                    cout << "Positioning: " << this->positioning << " + " << positioning << endl;
                    this->positioning = (this->positioning + positioning > 100) ? 100 : this->positioning + positioning;
                }
                if (passing) {
                    cout << "Passing: " << this->passing << " + " << passing << endl;
                    this->passing = (this->passing + passing > 100) ? 100 : this->passing + passing;
                }
                if (vision) {
                    cout << "Vision: " << this->vision << " + " << vision << endl;
                    this->vision = (this->vision + vision > 100) ? 100 : this->vision + vision;
                }
                if (shotPower) {
                    cout << "Shot power: " << this->shotPower << " + " << shotPower << endl;
                    this->shotPower = (this->shotPower + shotPower > 100) ? 100 : this->shotPower + shotPower;
                }
                if (penalty) {
                    cout << "Penalty: " << this->penalty << " + " << penalty << endl;
                    this->penalty = (this->penalty + penalty > 100) ? 100 : this->penalty + penalty;
                }
            }
        }
    }
}

void interactiveMenu();

vector <vector<Player *>> teams;
vector <string> nameTeams;

int main() {

    interactiveMenu();
    return 0;
}

void interactiveMenu() {
    teams.resize(teams.size() + 1);
    cout
            << "Nu ai nicio echipa pana in momentul de fata. Hai sa cream una.\nMai intai de toate alege un nume pentru aceasta echipa:\n";
    char numeEchipa[100];
    cout << "Nume echipa: ";
    cin.getline(numeEchipa, 100);
    nameTeams.push_back(numeEchipa);
    cout << "Acum e timpul sa alegi cine ai vrea sa fie capitan in aceasta echipa:\n";
    cout
            << "1.Ronaldo - Striker; 90 shooting, 94 - heading, 88 - pace\n2.Sterling - Winger; 96 - pace, 91 - footwork, 89 - shooting\n3.Casemiro - Defensive midfielder; 95 - slide tackle, 93 - aggressiveness, 87 - passing\n";
    int k;
    cout << "Alege capitanul: ";
    cin >> k;
    switch (k) {
        case 1: {
            Striker *striker = new Striker("Ronaldo", "Cristiano", 34, 190, "both", 18, "capitan", false, 88, 90, 88,
                                           100, 88, 84, 94);
            teams[0].push_back(striker);
            break;
        }
        case 2: {
            Winger *winger = new Winger("Sterling", "", 27, 186, "left", 10, "capitan", false, 96, 89, 82, 100, 56, 78,
                                        70, 83, 86, 80, 93, 86, 91);
            teams[0].push_back(winger);
            break;
        }
        case 3: {
            DefensiveMidfielder *defensiveMidfielder = new DefensiveMidfielder("Casemiro", "", 31, 186, "right", 13,
                                                                               "capitan", false, 82, 81, 85, 100, 95,
                                                                               87, 90, 84, 87, 87, 93, 89, 80);
            teams[0].push_back(defensiveMidfielder);
            break;
        }
        default: {
            Striker *striker = new Striker("Ronaldo", "Cristiano", 34, 190, "both", 18, "capitan", false, 88, 90, 88,
                                           100, 88, 84, 94);
            teams[0].push_back(striker);
            break;
        }
    }
    cout
            << "Acum ca avem o echipa si avem si capitan, iti poti alege sa iti cresti in continuare aceasta echipa, sa o modelezi cum vrei, sa iti aduci alti jucatori sau ai putea sa iti faci alta echipa noua.\n\n";

    int comanda;
    do {
        cout << "Alege cu ce echipa vrei sa lucrezi:\n";
        for (int i = 0; i < nameTeams.size(); ++i) {
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
            cout
                    << "1.Ronaldo - Striker; 90 shooting, 94 - heading, 88 - pace\n2.Sterling - Winger; 96 - pace, 91 - footwork, 89 - shooting\n3.Casemiro - Defensive midfielder; 95 - slide tackle, 93 - aggressiveness, 87 - passing\n";
            int k;
            cout << "Alege capitanul: ";
            cin >> k;
            switch (k) {
                case 1: {
                    Striker *striker = new Striker("Ronaldo", "Cristiano", 34, 190, "both", 18, "capitan", false, 88,
                                                   90, 88, 100, 88, 84, 94);
                    teams[teams.size() - 1].push_back(striker);
                    break;
                }
                case 2: {
                    Winger *winger = new Winger("Sterling", "", 27, 186, "left", 10, "capitan", false, 96, 89, 82, 100,
                                                56, 78, 70, 83, 86, 80, 93, 86, 91);
                    teams[teams.size() - 1].push_back(winger);
                    break;
                }
                case 3: {
                    DefensiveMidfielder *defensiveMidfielder = new DefensiveMidfielder("Casemiro", "", 31, 186, "right",
                                                                                       13, "capitan", false, 82, 81, 85,
                                                                                       100, 95, 87, 90, 84, 87, 87, 93,
                                                                                       89, 80);
                    teams[teams.size() - 1].push_back(defensiveMidfielder);
                    break;
                }
                default: {
                    Striker *striker = new Striker("Ronaldo", "Cristiano", 34, 190, "both", 18, "capitan", false, 88,
                                                   90, 88, 100, 88, 84, 94);
                    teams[teams.size() - 1].push_back(striker);
                    break;
                }
            }
        } else if (comanda <= nameTeams.size()) {
            int index = comanda-1;
            for (int i = 0; i < teams[index].size(); ++i) {
                cout<<i+1<<".)\n";
                teams[index][i]->read(cout);
                cout<<"Pozitie in teren: ";
                if (typeid(Striker) == typeid(*teams[index][i])) {
                    cout << "ST" << endl << endl;
                }
                if (typeid(Defender) == typeid(*teams[index][i])) {
                    cout << "CB" << endl << endl;
                }
                if (typeid(Midfielder) == typeid(*teams[index][i])) {
                    cout << "CM" << endl << endl;
                }
                if (typeid(Goalkeeper) == typeid(*teams[index][i])) {
                    cout << "GK" << endl << endl;
                }
                if (typeid(Winger) == typeid(*teams[index][i])) {
                    cout << "LW/RW/RB/LB" << endl << endl;
                }
                if (typeid(AttackingMidfielder) == typeid(*teams[index][i])) {
                    cout << "CAM/CF" << endl << endl;
                }
                if (typeid(DefensiveMidfielder) == typeid(*teams[index][i])) {
                    cout << "CDM" << endl << endl;
                }
            }
            int comanda_echipa=0;
            cout<<"Acum ca ai toate datele despre echipa "<<nameTeams[index]<<", alege ce schimbari vrei sa faci:\n\n";
            while(comanda_echipa!=5) {
                cout << "1.Adauga jucator\n2.Sterge un jucator\n3.Imbunatateste un jucator\n4.Sterge echipa\n5.Inapoi\n";
                cout << "Comanda: ";
                cin >> comanda_echipa;
                switch (comanda_echipa) {
                    case 1: {
                        int tip_jucator;
                        cout
                                << "Alege ce fel de jucator vrei sa adaugi:\n1.Atacant\n2.Fundas\n3.Portar\n4.Mijlocas\n5.Extrema\n6.Mijlocas ofensiv\n7.Mijlocas defensiv\n8.Inapoi\n";
                        cout << "Comanda fel jucator: ";
                        cin >> tip_jucator;
                        cout<<endl;
                        switch (tip_jucator) {
                            case 1: {
                                Striker striker;
                                striker.write(cin);
                                Striker *aux = new Striker(striker);
                                teams[index].push_back(aux);
                                break;
                            }
                            case 2: {
                                Defender defender;
                                defender.write(cin);
                                Defender *aux = new Defender(defender);
                                teams[index].push_back(aux);
                                break;
                            }
                            case 3: {
                                Goalkeeper goalkeeper;
                                goalkeeper.write(cin);
                                Goalkeeper *aux = new Goalkeeper(goalkeeper);
                                teams[index].push_back(aux);
                                break;
                            }
                            case 4: {
                                Midfielder midfielder;
                                midfielder.write(cin);
                                Midfielder *aux = new Midfielder(midfielder);
                                teams[index].push_back(aux);
                                break;
                            }
                            case 5: {
                                Winger winger;
                                winger.write(cin);
                                Winger *aux = new Winger(winger);
                                teams[index].push_back(aux);
                                break;
                            }
                            case 6: {
                                AttackingMidfielder attackingMidfielder;
                                attackingMidfielder.write(cin);
                                AttackingMidfielder *aux = new AttackingMidfielder(attackingMidfielder);
                                teams[index].push_back(aux);
                                break;
                            }
                            case 7: {
                                DefensiveMidfielder defensiveMidfielder;
                                defensiveMidfielder.write(cin);
                                DefensiveMidfielder *aux = new DefensiveMidfielder(defensiveMidfielder);
                                teams[index].push_back(aux);
                                break;
                            }
                            case 8: {
                                break;
                            }
                            default: {
                                cout<<"Ati apasat o tasta invalida!!\n\n";
                                break;
                            }
                        }
                        break;
                    }
                    case 2: {
                        int index_jucator;
                        cout<<"Alege al catelea jucator din echipa vrei sa il stergi.\n";
                        cout<<"Index: "; cin>>index_jucator;
                        if(index > teams[index].size()) {
                            cout<<"Nu exista acest jucator.\n";
                        } else {
                            teams[index].erase(teams[index].begin()+index_jucator -1);
                        }
                        break;
                    }
                    case 3: {
                        int index_jucator;
                        cout<<"Alege al catelea jucator din echipa vrei sa il imbunatatesti.\n";
                        cout<<"Index: "; cin>>index_jucator;
                        if(index > teams[index].size()) {
                            cout<<"Nu exista acest jucator.\n";
                        } else {
                            teams[index][index_jucator-1]->increaseStats();
                        }
                        break;
                    }
                    case 4: {
                        if(teams.size() == 1) {
                            cout<<"Nu putem sterge singura echipa pe care o ai!\n";
                            break;
                        }
                        cout<<"Esti sigur ca vrei sa stergi aceasta echipa?(DA/NU)";
                        string answer;
                        cin>>answer;
                        if(answer == "DA" || answer == "Da" || answer == "da") {
                            teams.erase(teams.begin() + index);
                            nameTeams.erase(nameTeams.begin() + index);
                        }
                        break;
                    }
                }
            }
        }
    } while (comanda != nameTeams.size() + 2);
    cout<<"Va multumim! O zi nemaipomenita!";
}