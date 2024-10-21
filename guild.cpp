#include <iostream>
#include <string>
#include "guild.h"

using namespace std;
namespace seneca {
    void Guild::resize()
    {
        // Resize function (doubles the capacity when needed)
        size_t newCapacity = (m_capacity == 0) ? 1 : m_capacity * 2;
        Character** newMembers = new Character * [newCapacity];
        for (size_t i = 0; i < m_size; ++i)
        {
            newMembers[i] = m_characters[i];
        }
        delete[] m_characters;
        m_characters = newMembers;
        m_capacity = newCapacity;
    }


    Guild::Guild(const char* name) : m_capacity(2), m_size(0), m_name(name), m_characters(new Character* [m_capacity])
    {
    }

    Guild::Guild(const Guild& other)
    {
        m_name = other.m_name;
        m_size = other.m_size;
        m_capacity = other.m_capacity;
        m_characters = new Character * [m_capacity];
        for (size_t i = 0; i < m_size; i++)
        {
            m_characters[i] = other.m_characters[i];
        }
    }

    Guild& Guild::operator=(const Guild& other)
    {
        if (this != &other)
        {

            delete[] m_characters; // need to look at this
            m_name = other.m_name;
            m_size = other.m_size;
            m_capacity = other.m_capacity;
            m_characters = new Character * [m_capacity];
            for (size_t i = 0; i < m_size; i++)
            {
                m_characters[i] = other.m_characters[i];
            }
        }
        return *this;
    }

    Guild::Guild(Guild&& other) noexcept
    {
        m_name = other.m_name;
        m_size = other.m_size;
        m_capacity = other.m_capacity;
        m_characters = other.m_characters;

        other.m_characters = nullptr;
        other.m_name = "";
        other.m_size = 0;
        other.m_capacity = 0;
    }

    Guild& Guild::operator=(Guild&& other) noexcept
    {
        if (this != &other)
        {
            for (size_t i = 0; i < m_size; i++)
            {
                delete m_characters[i];
            }
            delete[] m_characters;
            m_name = other.m_name;
            m_size = other.m_size;
            m_capacity = other.m_capacity;
            m_characters = other.m_characters;

            other.m_characters = nullptr;
            other.m_name = "";
            other.m_size = 0;
            other.m_capacity = 0;
        }
        return *this;
    }

    Guild::~Guild()
    {
        if (m_characters != nullptr)
        {
            delete[] m_characters;
        }


    }

    void Guild::addMember(Character* c)
    {
        for (size_t i = 0; i < m_size; ++i)
        {
            if (m_characters[i]->getName() == c->getName())
            {
                return;
            }
        }
        // Resize the array if needed
        if (m_size == m_capacity)
        {
            resize();
        }

        c->setHealthMax(c->getHealthMax() + 300);
        c->setHealth(c->getHealthMax());


        m_characters[m_size++] = c;
    }

    void Guild::removeMember(const std::string& c)
    {
        for (size_t i = 0; i < m_size; ++i)
        {
            if (m_characters[i]->getName() == c)
            {
                m_characters[i]->setHealthMax(m_characters[i]->getHealthMax() - 300);
                m_characters[i]->setHealth(m_characters[i]->getHealthMax());
                for (size_t j = i; j < m_size - 1; ++j)
                {
                    m_characters[j] = m_characters[j + 1];
                }
                m_size--;
            }
        }

    }

    Character* Guild::operator[](size_t idx) const
    {
        if (idx >= m_size) return nullptr;
        return m_characters[idx];
    }

    void Guild::showMembers() const
    {
        if (m_capacity > 0)
        {
            cout << "[Guild] " << m_name << "\n";
            for (size_t i = 0; i < m_size; ++i)
            {
                cout << "    " << i + 1 << ": " << *m_characters[i] << std::endl;
            }
        }
        else
        {
            cout << "No guild." << std::endl;
            return;
        }
    }
} // seneca