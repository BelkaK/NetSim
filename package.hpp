#ifndef PACKAGE
#define PACKAGE

#include <set>
#include "types.hpp"
#include <algorithm>
#include <iostream>

class Package
{
public:
    Package();
    Package(ElementID id_);
    Package(Package &&old);
    Package &operator=(Package &&other);
    ElementID get_id() const { return id; }
    ~Package();

private:
    ElementID id;
    static std::set<ElementID> assigned_IDs;
    static std::set<ElementID> freed_IDs;
};

#endif