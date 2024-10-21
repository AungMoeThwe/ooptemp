#ifndef SENECA_CHARACTERTPL_H
#define SENECA_CHARACTERTPL_H
#include "character.h"

namespace seneca {
    template <typename T>
class CharacterTpl : public Character{
        int m_healthMax; // represents max health of a char
        T m_health; // represents current health

    public:
        CharacterTpl(const char* name, int healthMax): Character(name), m_healthMax(healthMax)
        {
            m_health =static_cast<int>(m_healthMax);
        }

        // Copy Constructor
        CharacterTpl(const CharacterTpl& other) : Character(other.getName().c_str()), m_healthMax(other.m_healthMax)
        {
            m_health = static_cast<int>(other.m_healthMax);
        }

        void takeDamage(int dmg) override
        {
            m_health -= dmg;
            if (m_health <= 0)
            {
                m_health = 0;
            }

            if (Character::isAlive())
            {
                std::cout << "    " << Character::getName() << " took " << dmg << " damage, " << getHealth() << " health remaining." << std::endl;
            } else
            {
                std::cout << "    " << Character::getName() << " has been defeated!" << std::endl;
            }
        }

        int getHealth() const override{return static_cast<int>(m_health);}

        int getHealthMax() const override {return m_healthMax;}

        void setHealth(int health) override{m_health = health;}

        void setHealthMax(int health) override{m_healthMax = health;}
};

} // seneca

#endif //SENECA_CHARACTERTPL_H
