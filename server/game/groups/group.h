#ifndef GROUP_H
#define GROUP_H

#include <unordered_map>
#include <algorithm>
#include <vector>

#include "member.h"

class Group
{
public:

    Group();
    virtual  ~Group();

    virtual bool add(id id);
    virtual bool remove(id id);

    virtual bool hasMember(id id);
    std::vector<id> getIds();

    int size();
    bool isFull();
    bool isEmpty();

    virtual void transferTo(Group* other);


protected:


    virtual bool add(Member* member);
    virtual bool remove(Member* member);
    virtual bool hasMember(Member* member);
    virtual Member *getMember(id id);
    virtual std::vector<Member*> getMembers();

    static const int MAX_SIZE = 5;

private:

    std::unordered_map<id, Member*> members_;


};

#endif // GROUP_H
