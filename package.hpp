#ifndef PACKAGE
#define PACKAGE

#include <list>
#include "types.hpp"

class Package
{
public:
    Package();
    Package(ElementID);
    Package(Package &&);
    Package &operator=(Package &&);
    ElementID get_id() const;
    ~Package();

private:
    ElementID id;
    static std::list<ElementID> assigned_IDs;
    static std::list<ElementID> freed_IDs;
};

#endif