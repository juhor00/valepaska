#include "member.h"

Member::Member(id id):
    id_(id)
{
}

id Member::getId()
{
    return id_;
}
