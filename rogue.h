#ifndef SENECA_ROGUE_H
#define SENECA_ROGUE_H

#include "weapons.h"

namespace seneca {
template <typename T, typename FirstAbility_t, typename SecondAbility_t>
class Rogue : public CharacterTpl<T> {
    int m_baseAttack{};
    int m_baseDefense{};

    FirstAbility_t m_firstAbility;
    SecondAbility_t m_secondAbility;

    seneca::Dagger m_weapon;

public:
    Rogue(const char* name, int healthMax, int baseAttack, int baseDefense):CharacterTpl<T>(name, healthMax), m_baseAttack(baseAttack), m_baseDefense(baseDefense) {}

    Rogue (const Rogue& other) : CharacterTpl<T>(other)
    {
        m_baseAttack = other.m_baseAttack;
        m_baseDefense = other.m_baseDefense;
        m_firstAbility = other.m_firstAbility;
        m_secondAbility = other.m_secondAbility;

        m_weapon = other.m_weapon;
    }

    int getAttackAmnt() const override {return (m_baseAttack + 2 * static_cast<double>(m_weapon));}

    int getDefenseAmnt() const override {return m_baseDefense;}

    Character* clone() const override {return new Rogue(*this);};

    void attack(Character* enemy) override
    {
        std::cout<< CharacterTpl<T>::getName()<< " is attacking " << enemy->getName() << "." <<std::endl;
        m_firstAbility.useAbility(this);
        m_secondAbility.useAbility(this);

        int dmg = getAttackAmnt();
        m_firstAbility.transformDamageDealt(dmg);
        m_secondAbility.transformDamageDealt(dmg);
        std::cout << "Rogue deals " << dmg << " melee damage!\n";
        enemy->takeDamage(dmg);
    }

    void takeDamage(int dmg) override
    {
        std::cout<<CharacterTpl<T>::getName() << " is attacked for " << dmg << " damage." << std::endl;
        std::cout << "    Rogue has a defense of " << getDefenseAmnt() <<". Reducing damage received."<< std::endl;

        dmg = dmg - getDefenseAmnt();
        if (dmg < 0) dmg =0;

        m_firstAbility.transformDamageReceived(dmg);
        m_secondAbility.transformDamageReceived(dmg);

        CharacterTpl<T>::takeDamage(dmg);
    }

};

} // seneca

#endif //SENECA_ROGUE_H
