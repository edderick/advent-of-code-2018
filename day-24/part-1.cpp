#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <map>
#include <regex>
#include <set>
#include <cmath>

using namespace std;

struct Army {
// 17 units each with 5390 hit points (weak to radiation, bludgeoning) with
// an attack that does 4507 fire damage at initiative 2

    Army(int units, 
         int hitpoints, 
         const set<string>& weaknesses, 
         const set<string>& immunities, 
         int attack, 
         const string& attackType,
         int initiative,
         bool immuneSystem, 
         int groupNumber)
    : d_id(rand())
    , d_units(new int)
    , d_hitpoints(hitpoints)
    , d_weaknesses(weaknesses)
    , d_immunities(immunities)
    , d_attack(attack)
    , d_attackType(attackType)
    , d_initiative(initiative)
    , d_immuneSystem(immuneSystem)
    , d_groupNumber(groupNumber)
    {
        *d_units = units;
    }

    int d_id;

    int* d_units;
    int d_hitpoints;
    set<string> d_weaknesses;
    set<string> d_immunities;
    int d_attack;
    string d_attackType;
    int d_initiative;

    bool d_immuneSystem;
    int d_groupNumber;

    int effectivePower() const
    {
        return *d_units * d_attack; 
    }

    int damage(const Army& other) const
    {
        if (other.d_immunities.count(d_attackType) != 0)
        {
            return 0;
        }
        
        const int damage = effectivePower();

        if (other.d_weaknesses.count(d_attackType) != 0)
         {
            return 2 * damage;
        }

        return damage;
    }

    void takeDamage(int damage)
    {
        *d_units -= damage / d_hitpoints;
        if (*d_units < 0)
        {
            *d_units = 0; 
        }
    }

    friend ostream& operator<<(ostream& out, const Army& army);
    
    bool operator<(const Army& other) const
    {
        return d_id < other.d_id;
    }

    bool operator==(const Army& other) const
    {
        return d_id == other.d_id;
    }
    
    bool operator!=(const Army& other) const
    {
        return !(other == *this);
    }
};

struct ArmyComp {
    bool operator()(const Army& lhs, const Army& rhs) const
    {
        if (lhs.effectivePower() == rhs.effectivePower())
        {
            return lhs.d_initiative > rhs.d_initiative;
        }
        return lhs.effectivePower() > rhs.effectivePower();
        //TODO:
    }
};

struct BattleComp {
    bool operator()(const Army& lhs, const Army& rhs) const
    {
        return lhs.d_initiative > rhs.d_initiative;
    }
};


ostream& operator<<(ostream& out, const Army& army)
{
    out << "Group " << army.d_groupNumber << " ";
    out << "contains " << *army.d_units << " units";
    return out;
}

vector<string> getInput()
{
    vector<string> input;
    for (string line; getline(cin, line); ) {
        input.push_back(line);
    }
    return input;
}

Army parseLine(const string& entry, bool immuneSystem, int groupNumber)
{        
    regex lineRegex("(\\d+) units each with (\\d+) hit points \\((.+)\\) with an attack that does (\\d+) (.+) damage at initiative (\\d+)");
    regex weaknessRegex("(weak to (\\w+),? ?(\\w+)?)");
    regex immunityRegex("(immune to (\\w+)+ ?; ?)");

    cout << entry << endl;

    auto words_begin = sregex_iterator(entry.begin(), entry.end(), lineRegex);
    
    auto it = words_begin;
    
    const int numUnits = stoi((*it)[1]);
    const int hitpoints = stoi((*it)[2]);
    const string abilitiesStr((*it)[3]); 
    const int damage = stoi((*it)[4]);
    const string damageType((*it)[5]);
    const int initiative = stoi((*it)[6]);

    set<string> weaknesses;
    auto words_begin2 = sregex_iterator(abilitiesStr.begin(), abilitiesStr.end(), weaknessRegex);
    for (auto it2 = words_begin2; it2 != sregex_iterator(); it2++)
    {
        auto it3 = it2->begin();
        ++it3;
        for (; it3 != it2->end(); ++it3)
        { 
            weaknesses.insert(*it3);
        }
    }

    set<string> immunities;
    auto words_begin3 = sregex_iterator(abilitiesStr.begin(), abilitiesStr.end(), immunityRegex);
    for (auto it2 = words_begin3; it2 != sregex_iterator(); it2++)
    {
        auto it3 = it2->begin();
        ++it3;
        for (; it3 != it2->end(); ++it3)
        { 
            immunities.insert(*it3);
        }
    }

    return {numUnits, hitpoints, weaknesses, immunities, damage, damageType, initiative, immuneSystem, groupNumber};
}

int main(int argc, char* argv[])
{
    set<Army, ArmyComp> immuneSystemArmies;
    set<Army, ArmyComp> infectionArmies;
    vector<string> inputs = getInput();
    auto it = inputs.begin();
    ++it;
    bool immuneSystem = true;
    int immuneGroup = 1;
    int infectionGroup = 1;
    for (; it != inputs.end(); ++it )
    {
        if (it->empty())
        {
            ++it; // Skip next line too
            immuneSystem = false;
            continue;
        }
        if (immuneSystem)
        {
            immuneSystemArmies.insert(parseLine(*it, immuneSystem, immuneGroup++));
        }
        else 
        {
            infectionArmies.insert(parseLine(*it, immuneSystem, infectionGroup++));
        }
    }

    for (const auto& army : immuneSystemArmies)
    {
        cout << army << "\n";
    }
    
    cout << "\n";

    for (const auto& army : infectionArmies)
    {
        cout << army << "\n";
    }

    cout << "\n";


    for (int i = 0; i < 2000; i++)
    {
        cout << "=================================================================================\n";
        cout << "Round " << i + 1 <<  "\n\n"; 


        int immuneSum = 0;
        for (const auto& army : immuneSystemArmies)
        {
            immuneSum += *army.d_units;    
        }

        int infectionSum = 0;
        for (const auto& army : infectionArmies)
        {
            infectionSum += *army.d_units;    
        }
        
        cout << "\n" << infectionSum << ", " << immuneSum << "\n";
        
        // Target Selection
        map<Army, const Army*, BattleComp> battles;
        set<Army> targets;

        for (const auto& army : infectionArmies)
        {
            for (const auto& target : immuneSystemArmies)
            {
                if (targets.find(target) != targets.end())
                {
                    continue;
                }
                cout << "Infection " << army.d_groupNumber 
                     << " -- " << target.d_groupNumber 
                     << " = " << army.damage(target) << "\n";

                auto it = battles.find(army);
                if (it == battles.end())
                {
                    targets.insert(target);
                    battles[army] = &target;
                }
                else if (army.damage(target) > army.damage(*it->second)) 
                {
                    targets.erase(*it->second);
                    targets.insert(target);
                    battles[army] = &target;
                }
                else if (army.damage(target) == army.damage(*it->second) && 
                         target.effectivePower() > it->second->effectivePower())
                {
                    targets.erase(*it->second);
                    targets.insert(target);
                    battles[army] = &target;
                }
                else if (army.damage(target) == army.damage(*it->second) && 
                         target.effectivePower() == it->second->effectivePower() &&
                         target.d_initiative > it->second->d_initiative)
                {
                    targets.erase(*it->second);
                    targets.insert(target);
                    battles[army] = &target;
                }
            }
        }

        for (const auto& army : immuneSystemArmies)
        {
            for (const auto& target : infectionArmies)
            {
                if (targets.count(target) == 1)
                {
                    continue;
                }

                cout << "Immune System " << army.d_groupNumber 
                     << " -- " << target.d_groupNumber 
                     << " = " << army.damage(target) << "\n";

                auto it = battles.find(army);
                if (it == battles.end())
                {
                    targets.insert(target);
                    battles[army] = &target;
                }
                else if (army.damage(target) > army.damage(*it->second)) 
                {
                    targets.erase(*it->second);
                    targets.insert(target);
                    battles[army] = &target;
                }
                else if (army.damage(target) == army.damage(*it->second) && 
                         target.effectivePower() > it->second->effectivePower())
                {
                    targets.erase(*it->second);
                    targets.insert(target);
                    battles[army] = &target;
                }
                else if (army.damage(target) == army.damage(*it->second) && 
                         target.effectivePower() == it->second->effectivePower() &&
                         target.d_initiative > it->second->d_initiative)
                {
                    targets.erase(*it->second);
                    targets.insert(target);
                    battles[army] = &target;
                }
            }
        }

        cout << "\n";

        for (auto battle : battles)
        {
            cout << "Battle " << (battle.first.d_immuneSystem ? "Immune System " : "Infection ") 
                 << battle.first.d_groupNumber  
                 << " -- " << battle.second->d_groupNumber; 

            if (battle.first.d_immuneSystem)
            {
                int before = *battle.second->d_units;

                const auto damage = battle.first.damage(*battle.second);
                auto it = infectionArmies.find(*battle.second);
                Army copy = *it;
                infectionArmies.erase(it);
                copy.takeDamage(damage);
                if (*copy.d_units > 0)
                {
                    infectionArmies.insert(copy);
                }
                cout << " HP: "<< before - *copy.d_units << "\n";
            }
            else
            {
                int before = *battle.second->d_units;

                const auto damage = battle.first.damage(*battle.second);
                auto it = immuneSystemArmies.find(*battle.second);
                Army copy = *it;
                immuneSystemArmies.erase(it);
                copy.takeDamage(damage);
                if (*copy.d_units > 0)
                {
                    immuneSystemArmies.insert(copy);
                }
                cout << " HP: "<< before - *copy.d_units << "\n";
            }
        }
        if (immuneSystemArmies.empty() || infectionArmies.empty())
        {
            break;
        }
    }

    int immuneSum = 0;
    for (const auto& army : immuneSystemArmies)
    {
        immuneSum += *army.d_units;    
    }

    int infectionSum = 0;
    for (const auto& army : infectionArmies)
    {
        infectionSum += *army.d_units;    
    }
    
    cout << "\n" << infectionSum << ", " << immuneSum << "\n";


    return 0;
}
