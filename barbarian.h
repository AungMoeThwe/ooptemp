
#ifndef SENECA_BARBARIAN_H
#define SENECA_BARBARIAN_H
#include <iostream>
#include "characterTpl.h"

namespace seneca {
template <typename T, typename Ability_t, typename Weapon_t>
class Barbarian: public CharacterTpl<T>{
    int m_baseAttack{};
    int m_baseDefense{};

    Ability_t m_ability{};
    Weapon_t m_weapon[2]{};
    public:

    Barbarian(const char* name, int healthMax, int baseAttack, int baseDefense, Weapon_t primaryWeapon, Weapon_t secondaryWeapon):CharacterTpl<T>(name, healthMax), m_baseAttack(baseAttack), m_baseDefense(baseDefense)
    {
        m_weapon[0] = primaryWeapon;
        m_weapon[1] = secondaryWeapon;
    }

    Barbarian(const Barbarian& other):CharacterTpl<T>(other)
    {
        m_baseDefense = other.m_baseDefense;
        m_baseAttack = other.m_baseAttack;

        m_ability = other.m_ability;

        for (size_t i =0; i < 2; i++)
        {
            m_weapon[i] = other.m_weapon[i];
        }
    }

    int getAttackAmnt() const override {return m_baseAttack + (static_cast<double>(m_weapon[0])/2) + (static_cast<double>(m_weapon[1])/2);}

    int getDefenseAmnt() const override {return m_baseDefense;}

    Character* clone() const override {return new Barbarian(*this);}

    void attack(Character* enemy) override
    {
        std::cout<< CharacterTpl<T>::getName() << " is attacking " << enemy->getName() <<"."<<std::endl;
        m_ability.useAbility(this);
        int damage = getAttackAmnt();
        m_ability.transformDamageDealt(damage);
        std::cout<< "    Barbarian deals " << damage << " melee damage!" << std::endl;
        enemy -> takeDamage(damage);
    }

    void takeDamage(int dmg) override
    {
        std::cout << CharacterTpl<T>::getName() << " is attacked for " << dmg << " damage." << std::endl;
        std::cout << "    Barbarian has a defense of " << getDefenseAmnt() << ". Reducing damage received." << std::endl;

        dmg = dmg - getDefenseAmnt();
        if (dmg < 0) dmg = 0;
        m_ability.transformDamageReceived(dmg);
        CharacterTpl<T>::takeDamage(dmg);
    }

};

} // seneca

#endif //SENECA_BARBARIAN_H
