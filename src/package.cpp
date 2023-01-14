#include "package.hpp"

Package::Package()
{
    if (freed_IDs.empty())
    {
        ElementID value = -1;
        if (assigned_IDs.empty())
            value = 1;
        else
            value = *(assigned_IDs.rbegin()) + 1;

        assigned_IDs.insert(value);
        id = value;
    }
    else
    {
        id = *(freed_IDs.begin());
        assigned_IDs.insert(id);
        freed_IDs.erase(id);
    }
}

Package::Package(ElementID id_)
{
    bool found = std::find(assigned_IDs.begin(), assigned_IDs.end(), id_) == assigned_IDs.end();
    if (found)
    {
        std::cout << "ID jest już zajęte" << std::endl;
    }
    else
    {
        id = id_;
        assigned_IDs.insert(id);
    }
}

Package::Package(Package &&old)
{
    id = old.id;
    old.id = -1;
}

Package &Package::operator=(Package &&other) {
    if (this == &other)
        return *this;
    id = other.id;
    other.id = -1;
    return *this;
}

Package::~Package()
{
    if (id != 0)
    {
        freed_IDs.insert(id);
        assigned_IDs.erase(id);
    }
}

std::set<ElementID> Package::assigned_IDs;
std::set<ElementID> Package::freed_IDs;