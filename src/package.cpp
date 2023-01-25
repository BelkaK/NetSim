#include "package.hpp"



std::set<ElementID> Package::freed_IDs_;
std::set<ElementID> Package::assigned_IDs_;


Package::Package(){
    if(!(freed_IDs_.empty())){
        ElementID minID = *freed_IDs_.begin();
        id_ = minID;
        freed_IDs_.erase(minID);
        assigned_IDs_.insert(minID);
    }
    else{
        if(assigned_IDs_.empty()){
            id_ = 1;
            assigned_IDs_.insert(1);
        }
        else{
            ElementID maxID = *(assigned_IDs_.rbegin());
            id_ = maxID + 1;
            assigned_IDs_.insert(maxID + 1);
        }
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