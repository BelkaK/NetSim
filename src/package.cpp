#include "package.hpp"



std::set<ElementID> Package::freed_IDs_;
std::set<ElementID> Package::assigned_IDs_;


Package::Package() {
    if (!freed_IDs_.empty()) {
        id_ = *freed_IDs_.begin();
        assigned_IDs_.insert(id_);    /* dodanie nowego id  do zbioru przypsanych */
        freed_IDs_.erase(id_);    /* usunięcie przypisanego ze zbioru wolnych */
    }
    else if (!assigned_IDs_.empty()) {  //tutaj brakowało elsa po prostu
        id_ = *(assigned_IDs_.rbegin()) + 1;        /* inkrementacja */
        assigned_IDs_.insert(id_);
    }
    else {
        id_ = 1;
        assigned_IDs_.insert(id_);
    }
}

Package::~Package() {
    assigned_IDs_.erase(id_);   // usuwamm stary
    freed_IDs_.insert(id_);   // dodaje do wolnych do uzycia

}

Package::Package(Package&& other) noexcept
{
    id_ = other.id_;
}