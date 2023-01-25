#ifndef SIECI_NODES_HPP
#define SIECI_NODES_HPP
#include "package.hpp"
#include <memory>
#include "storage_types.hpp"
#include "helpers.hpp"
#include <optional>
#include <map>
#include "types.hpp"

enum class ReceiverType
{
    WORKER,
    STOREHOUSE
};

class IPackageReceiver
{
public:
    virtual void receive_package(Package &&p) = 0;
    virtual ElementID get_id() const = 0;
    virtual ReceiverType get_receiver_type(void) const { return type; }
    virtual IPackageStockpile::const_iterator cbegin() const = 0;
    virtual IPackageStockpile::const_iterator cend() const = 0;
    virtual IPackageStockpile::const_iterator begin() const = 0;
    virtual IPackageStockpile::const_iterator end() const = 0;

    virtual ~IPackageReceiver() = default;

protected:
    ElementID id_;
    ReceiverType type;
};

class Storehouse : public IPackageReceiver
{
private:
    std::unique_ptr<PackageQueue> d_;

public:
    Storehouse(ElementID id, std::unique_ptr<PackageQueue> d = std::make_unique<PackageQueue>(PackageQueue(PackageQueueType::FIFO)));
    ElementID get_id() const override { return id_; }
    void receive_package(Package &&p) override;

    virtual IPackageStockpile::const_iterator cbegin() const override { return d_->cbegin(); }
    virtual IPackageStockpile::const_iterator cend() const override { return d_->cend(); }
    virtual IPackageStockpile::const_iterator begin() const override { return d_->begin(); }
    virtual IPackageStockpile::const_iterator end() const override { return d_->end(); }
};

class ReceiverPreferences
{
public:
    using preferences_t = std::map<IPackageReceiver *, double>;
    using const_iterator = preferences_t::const_iterator;

    ReceiverPreferences(ProbabilityGenerator pg = probability_generator) : gen(std::move(pg)) {}
    void add_receiver(IPackageReceiver *r);
    void remove_receiver(IPackageReceiver *r);
    IPackageReceiver *choose_receiver();
    preferences_t get_preferences() const { return preferences_; }

    // nie wiem czy Package czy cos innego
    const_iterator cbegin() const { return preferences_.cbegin(); }
    const_iterator cend() const { return preferences_.cend(); }
    const_iterator begin() const { return preferences_.begin(); }
    const_iterator end() const { return preferences_.end(); }

    virtual ~ReceiverPreferences() = default;

private:
    ProbabilityGenerator gen;
    preferences_t preferences_;
};

class PackageSender : public ReceiverPreferences
{
public:
    ReceiverPreferences receiver_preferences_;
    PackageSender() : receiver_preferences_(default_probability_generator) {}
    PackageSender(PackageSender &&) = default;
    void send_package();
    std::optional<Package> &get_sending_buffer() { return buffer_; }

protected:
    void push_package(Package &&p);
    std::optional<Package> buffer_ = std::nullopt;
};

class Ramp : public PackageSender
{

public:
    Ramp(ElementID id, TimeOffset di) : id_(id),offset_(di) {}
    void deliver_goods(Time t);

    TimeOffset get_delivery_interval() const { return offset_; }
    ElementID get_id() const { return id_; }
    Ramp &operator=(Ramp &&other);
    Ramp(Ramp &&) = default;

private:
    ElementID id_;
    TimeOffset offset_;
    unsigned long long start_time_ = UINTMAX_MAX;
};

class Worker : public IPackageReceiver, public PackageSender
{
private:
    TimeOffset offset;
    Time start_time;
    std::unique_ptr<IPackageQueue> queue;
    std::optional<Package> current_package;

public:
    Worker(ElementID id, TimeOffset pd, std::unique_ptr<IPackageQueue> q);

    Worker &operator=(Worker &&other);
    Worker(Worker &&) = default;
    void receive_package(Package &&p) override;
    ElementID get_id() const override { return id_; }

    void do_work(Time t);
    TimeOffset get_processing_duration() const { return offset; };
    Time get_package_processing_start_time() const { return start_time; };

    virtual IPackageStockpile::const_iterator cbegin() const override { return queue->cbegin(); }
    virtual IPackageStockpile::const_iterator cend() const override { return queue->cend(); }
    virtual IPackageStockpile::const_iterator begin() const override { return queue->begin(); }
    virtual IPackageStockpile::const_iterator end() const override { return queue->end(); }
};

#endif
