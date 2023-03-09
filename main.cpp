/*
3/8/2023

This is a game. In this game we have four different types of creatures: humans, cyberdemons, balrogs, and elves.
*/
#include <iostream>
#include <string>
#include <cstdlib> 

using namespace std;

class Creature
{
private:
    int strength;   // How much damage we can inflict 
    int hitpoints;  // How much damage we can sustain 
public:
    Creature() : strength(10), hitpoints(10) {} // Initialize to human, 10 strength, 10 hit points
    Creature(int newStrength, int newHit) : strength(newStrength), hitpoints(newHit) {}

    int getStrength() const { return strength; }
    int getHitpoints() const { return hitpoints; }
    void setStrength(int newStrength) { strength = newStrength; }
    void setHitpoints(int newHit) { hitpoints = newHit; }

    virtual string getSpecies() const { return "Unknown"; } // Returns type of species, for Creature class returns “Unknown” 
    virtual int getDamage();

    virtual ~Creature() {}
};

/*
The getDamage( ) function outputs and returns the damage this creature can inflict in one round
of combat. The rules for calculating the damage are as follows:
• Every creature inflicts damage that is a random number r, where 0 < r <= strength.
• Demons have a 5% chance of inflicting a demonic attack which is an additional 50
damage points. Balrogs and Cyberdemons are demons.
• With a 10% chance elves inflict a magical attack that doubles the normal amount of
damage.
• Balrogs are very fast, so they get to attack twice.
The function is virtual and overrided in Human, Demon(Cyberdemon, Balrog), Elves.
*/
int Creature::getDamage() 
{
    int damage = (rand() % strength) + 1;

    cout << getSpecies() << " attacks for " << damage << " points!" << endl;

    return damage;
}

/*
Human Class.
*/
class Human : public Creature
{
public:
    Human() : Creature(10, 10) {}
    Human(int newStrength, int newHit) : Creature(newStrength, newHit) {}

    virtual string getSpecies() const override { return "Human"; }
};

/*
Elf Class.
*/
class Elf : public Creature
{
public:
    Elf() : Creature(10, 10) {}
    Elf(int newStrength, int newHit) : Creature(newStrength, newHit) {}

    virtual string getSpecies() const override { return "Elf"; }

    virtual int getDamage() override {
        int damage = (rand() % getStrength()) + 1;

        cout << getSpecies() << " attacks for " << damage << " points!" << endl;

        if ((rand() % 10) == 0)
        {
            cout << "Magical attack inflicts " << damage << " additional damage points!" << endl;
            damage *= 2;
        }

        return damage;
    }
};

/*
Demon Class.
*/
class Demon : public Creature
{
public:
    Demon() : Creature(10, 10) {}
    Demon(int newStrength, int newHit) : Creature(newStrength, newHit) {}

    virtual string getSpecies() const override { return "Demon"; }

    virtual int getDamage() override 
    {
        int damage = (rand() % getStrength()) + 1;

        cout << getSpecies() << " attacks for " << damage << " points!" << endl;

        if ((rand() % 100) < 5)
        {
            damage += 50;
            cout << "Demonic attack inflicts 50 additional damage points!" << endl;
        }

        return damage;
    }
};

/*
Cyberdemon--a type of demon--class.
*/
class Cyberdemon : public Demon
{
public:
    Cyberdemon() : Demon(10, 10) {}
    Cyberdemon(int newStrength, int newHit) : Demon(newStrength, newHit) {}

    virtual string getSpecies() const override { return "Cyberdemon"; }
};

/*
Balrog--a type of demon--class.
*/
class Balrog : public Demon
{
public:
    Balrog() : Demon(20, 20) {}
    Balrog(int newStrength, int newHit) : Demon(newStrength, newHit) {}

    virtual string getSpecies() const override { return "Balrog"; }

    virtual int getDamage() override 
    {
        int damage = Demon::getDamage(); // invoke getDamage() of the base class first to get the basic damage
        int balrog_damage = (rand() % getStrength()) + 1; // Add additional Balrog damage

        cout << "Balrog speed attack inflicts " << balrog_damage <<
            " additional damage points!" << endl;

        damage += balrog_damage;

        // Add second Balrog attack
        if (rand() % 2 == 0) 
        {
            int second_balrog_damage = (rand() % getStrength()) + 1;
            cout << "Balrog demon's fire attack inflicts " << second_balrog_damage <<
                " additional damage points!" << endl;
            damage += second_balrog_damage;
        }

        return damage;
    }
};

/*
This function takes two Creature objects as input. The function calculates the
damage done by creature1, subtract that amount from creature2’s hit points, and vice
versa. At the end of each round, if one creature has positive hit points but the other does
not then the battle is over.
If both creatures end up with zero or less hit points then the battle is a tie. Otherwise,
whoever has hit points less than zero loses.
*/
void battleArena(Creature& creature1, Creature& creature2) {
    int dam1, dam2, hit1, hit2, total1, total2;

    while (true) 
    {
        dam1 = creature1.getDamage();
        dam2 = creature2.getDamage();
        hit1 = creature1.getHitpoints();
        hit2 = creature2.getHitpoints();

        total1 = hit2 - dam1;
        total2 = hit1 - dam2;

        if (total1 < 0) 
        {
            cout << "\nCreature 1 has " << total1 << " hit points."
                << " \n\nCreature 2 wins!\n";
            break;
        }
        else if (total2 < 0) 
        {
            cout << "\nCreature 2 has " << total2 << " hit points."
                << " \n\nCreature 1 wins!\n";
            break;
        }
        else if (total1 == 0 && total2 == 0) 
        {
            cout << "Tie!\n";
            break;
        }
    }
}

int main() {
    srand(static_cast<int>(time(NULL)));

    Human human1(30, 10);
    human1.getDamage();

    cout << endl;

    Elf elf1;
    elf1.getDamage();

    cout << endl;

    Balrog balrog1(50, 50);;
    balrog1.getDamage();

    cout << endl;

    Cyberdemon cdemon(30, 40);
    cdemon.getDamage();

    cout << endl;

    Elf elf2(50, 50);
    Balrog balrog2(50, 50);

    cout << endl;
    
    battleArena(elf2, balrog2);
    return 0;
}

/*
Human attacks for 14 points!

Elf attacks for 5 points!

Balrog attacks for 1 points!
Balrog speed attack inflicts 11 additional damage points!

Cyberdemon attacks for 5 points!


Elf attacks for 27 points!
Balrog attacks for 26 points!
Balrog speed attack inflicts 24 additional damage points!
Elf attacks for 26 points!
Balrog attacks for 21 points!
Balrog speed attack inflicts 48 additional damage points!
Balrog demon's fire attack inflicts 25 additional damage points!

Creature 2 has -44 hit points.

Creature 1 wins!

Press any key to close this window . . .
*/