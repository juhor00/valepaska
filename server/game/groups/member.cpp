#include "member.h"

Member::Member(id id):
    id_(id)
{
}

Member::~Member()
{

}

id Member::getId()
{
    return id_;
}
