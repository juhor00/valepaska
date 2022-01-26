#ifndef GROUP_H
#define GROUP_H

#include <vector>
#include <algorithm>

using id = int;

class Group
{
public:

    Group();
    virtual  ~Group();
    virtual void transferTo(Group* other);
    int size();

protected:


    virtual bool add(id member);
    virtual bool remove(id member);
    virtual bool hasMember(id member);


    static const int MAX_SIZE = 5;

private:

    std::vector<id> members_;


};

#endif // GROUP_H
