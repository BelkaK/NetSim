#ifndef SIECI_NODES_HPP
#define SIECI_NODES_HPP
#include "package.hpp"
#include <memory>
#include "storage_types.hpp"
#include "package.hpp"
#include <optional>
#include "map"


enum class ReceiverType{
    Ramp,
    Worker,
    Storehouse
};


class IPackageReceiver{
public:
    virtual void receive_package(Package&& p) = 0;
    virtual ElementID get_id() const = 0;
    virtual std::list<Package>::const_iterator cbegin() const = 0;
    virtual std::list<Package>::const_iterator cend() const = 0;
    virtual std::list<Package>::const_iterator begin() const = 0;
    virtual std::list<Package>::const_iterator end() const = 0;
};


class Storehouse: public IPackageReceiver{
public:
    Storehouse(ElementID id, std::unique_ptr<IPackageStockPile> d);
    void receive_package(Package&& p) override;
    ElementID get_id() const override;

    std::list<Package>::const_iterator cbegin() const override;
    std::list<Package>::const_iterator cend() const override;
    std::list<Package>::const_iterator begin() const override;
    std::list<Package>::const_iterator end() const override;

private:
    ElementID id_;
    std::unique_ptr<IPackageStockPile> d_;
};


class ReceiverPreferences{
public:
    using preferences_t = std::map<IPackageReceiver*, double>;
    using const_iterator = preferences_t::const_iterator;

    ReceiverPreferences(ProbabilityGenerator pg);
    void add_receiver(IPackageReceiver* r);
    void remove_receiver(IPackageReceiver* r);
    IPackageReceiver* choose_receiver();
    preferences_t get_preferences() const;

    //nie wiem czy Package czy cos innego
    std::list<Package>::const_iterator cbegin() const;
    std::list<Package>::const_iterator cend() const;
    std::list<Package>::const_iterator begin() const;
    std::list<Package>::const_iterator end() const;

private:
    preferences_t preferences_;
    ProbabilityGenerator pg_;
};


class PackageSender{
public:
    PackageSender(PackageSender&&);
    void send_package();
    std::optional<Package>& get_sending_buffer() const;

private:
    ReceiverPreferences received_preferences_;

protected:
    void push_package(Package&&);
};


class Ramp{
    Ramp(ElementID id, TimeOffset di);
    void deliver_goods(Time t);
    TimeOffset get_delivery_interval() const;
    ElementID get_id() const;
};


class Worker: public IPackageReceiver{
    Worker(ElementID id, TimeOffset pd, std::unique_ptr<IPackageQueue>);
    void receive_package(Package&& p) override;
    ElementID get_id() const override;
    void do_work(Time t);
    TimeOffset get_processing_duration() const;
    Time get_package_processing_start_time() const;

    std::list<Package>::const_iterator cbegin() const override;
    std::list<Package>::const_iterator cend() const override;
    std::list<Package>::const_iterator begin() const override;
    std::list<Package>::const_iterator end() const override;
};



#endif
