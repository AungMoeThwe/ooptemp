#include <iostream>
#include <string>

using namespace std;
#include "team.h"


namespace seneca {
    void Team::resize()
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

    Team::Team(const char* name) : m_capacity(2), m_size(0), m_name(name), m_characters(new Character* [m_capacity])
    {
    }

    Team::Team(const Team& other)
    {

        m_name = other.m_name;
        m_size = other.m_size;
        m_capacity = other.m_capacity;
        m_characters = new Character * [m_capacity];
        for (size_t i = 0; i < m_size; i++)
        {
            m_characters[i] = other.m_characters[i]->clone();
        }
    }

    Team& Team::operator=(const Team& other)
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
            m_characters = new Character * [m_capacity];
            for (size_t i = 0; i < m_size; i++)
            {
                m_characters[i] = other.m_characters[i]->clone();
            }
        }
        return *this;
    }

    Team::Team(Team&& other) noexcept
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

    Team& Team::operator=(Team&& other) noexcept
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

    Team::~Team()
    {
        if (m_characters != nullptr)
        {
            for (size_t i = 0; i < m_size; ++i)
            delete m_characters[i];
        }
        delete[] m_characters;


    }

    void Team::addMember(const Character* c)
    {
        // Check if character with the same name already exists
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
        // Add the new member (clone the character)
        m_characters[m_size++] = c->clone();
    }

    void Team::removeMember(const std::string& c)
    {
        for (size_t i = 0; i < m_size; ++i)
        {
            if (m_characters[i]->getName() == c)
            {
                for (size_t j = i; j < m_size - 1; ++j)
                {
                    m_characters[j] = m_characters[j + 1];
                }
                m_size--;
            }
        }
    }

    Character* Team::operator[](size_t idx) const
    {
        if (idx >= m_size) return nullptr;
        return m_characters[idx];
    }

    void Team::showMembers() const
    {
        if (m_capacity > 0)
        {
            cout << "[Team] " << m_name << "\n";
            for (size_t i = 0; i < m_size; ++i)
            {
                cout << "    " << i + 1 << ": " << *m_characters[i] << std::endl;
            }
        }
        else
        {
            cout << "No team." << std::endl;
            return;
        }
    }
} // seneca