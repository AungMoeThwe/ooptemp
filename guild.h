

#ifndef SENECA_GUILD_H
#define SENECA_GUILD_H

#include <string>
#include "character.h"

namespace seneca {

class Guild {
    size_t m_capacity = 0, m_size = 0;
    std::string m_name;
    Character **m_characters;

    void resize();
    public:
    // default constructor
    Guild() = default;

    // constructor with args
    Guild(const char* name);

    // copy constructor
    Guild(const Guild& other);

    // copy assignment
    Guild& operator=(const Guild& other);

    // move constructor
    Guild(Guild&& other) noexcept;

    // move assignment
    Guild& operator=(Guild&& other) noexcept;

    // destructor
    ~Guild();

    void addMember(Character* c);

    void removeMember(const std::string& c);

    Character* operator[](size_t idx) const;

    void showMembers() const;


};

} // seneca

#endif //SENECA_GUILD_H
