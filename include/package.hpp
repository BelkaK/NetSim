#ifndef NETSIM_PACKAGE_HPP
#define NETSIM_PACKAGE_HPP

#include "types.hpp"
#include <set>


class Package{
public:
    static std::set<ElementID> freed_IDs_;
    static std::set<ElementID> assigned_IDs_;
    Package();
    Package(ElementID id) : id_(id) {}
    Package(Package&& other) noexcept;

    ElementID get_id() const { return id_; }
    Package& operator=(Package&&) = default;
    ~Package();

protected:

    ElementID id_;
};


#endif //NET_SIM_PACKAGE_HPP
