#ifndef SENECA_TEAM_H
#define SENECA_TEAM_H

#include <string>
#include "character.h"

namespace seneca {

class Team {
    size_t m_capacity = 0, m_size = 0;
    std::string m_name;
    Character **m_characters;

    void resize();
    public:

    // default constructor
    Team() = default;

    // constructor with args
    Team(const char* name);

    // copy constructor
    Team(const Team& other);

    // copy assignment
    Team& operator=(const Team& other);

    // move constructor
    Team(Team&& other) noexcept;

    // move assignment
    Team& operator=(Team&& other) noexcept;

    // destructor
    ~Team();

    void addMember(const Character* c);

    void removeMember(const std::string& c);

    Character* operator[](size_t idx) const;

    void showMembers() const;

};

} // seneca

#endif //SENECA_TEAM_H
