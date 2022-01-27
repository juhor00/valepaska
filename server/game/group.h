#ifndef GROUP_H
#define GROUP_H

#include <vector>
#include <algorithm>

using id = unsigned long long;

class Group
{
public:

    Group();
    virtual  ~Group();

    virtual bool add(id member);
    virtual bool remove(id member);

    virtual bool hasMember(id member);
    std::vector<id> getMembers();

    int size();
    bool isFull();
    bool isEmpty();

    virtual void transferTo(Group* other);


protected:

    static const int MAX_SIZE = 5;

private:

    std::vector<id> members_;


};

#endif // GROUP_H
