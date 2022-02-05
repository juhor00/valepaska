#ifndef MEMBER_H
#define MEMBER_H

using id = unsigned long long;

class Member
{
public:
    Member(id id);
    id getId();

private:

    id id_;
};

#endif // MEMBER_H
