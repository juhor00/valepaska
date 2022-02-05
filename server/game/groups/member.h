#ifndef PLAYER_H
#define PLAYER_H

using id = unsigned long long;

class Member
{
public:
    Member(id id);
    id getId();

private:

    id id_;
};

#endif // PLAYER_H
