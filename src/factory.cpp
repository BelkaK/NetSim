#include "factory.hpp"

enum class SenderStatus
{
    NotVisited,
    Visited,
    Verified // będzie potrzebne do metody is_consistent()
};

// FACTORY

bool has_reachable_storehouse(PackageSender *sender, std::map<PackageSender *, SenderStatus> &statuses)
{
    if (statuses[sender] == SenderStatus::Verified)
        return true;

    statuses[sender] = SenderStatus::Verified;

    if (sender->receiver_preferences_.begin() == sender->receiver_preferences_.end())
        throw std::logic_error("Graph is diconnected");

    bool alo = false;
    auto prefs = sender->receiver_preferences_;

    for (auto r : prefs.get_preferences())
    {
        auto type = r.first->get_receiver_type();
        if (type == ReceiverType::WORKER)
        {
            IPackageReceiver *r_ptr = r.first;
            auto w_ptr = dynamic_cast<Worker *>(r_ptr);
            auto s_ptr = dynamic_cast<PackageSender *>(w_ptr);
            if (s_ptr == sender || s_ptr == nullptr)
                continue;

            alo = true;
            if (statuses[s_ptr] == SenderStatus::NotVisited)
                has_reachable_storehouse(s_ptr, statuses);
        }
    }

    statuses[sender] = SenderStatus::Verified;
    if (alo)
        return true;
    else
        throw std::logic_error("Graph is diconnected");
}

bool Factory::is_consistent()
{
    std::map<PackageSender *, SenderStatus> statuses;

    for (auto it = &(*worker_collection.begin()), end = &(*worker_collection.end()); it < end; it++)
        statuses.insert({it, SenderStatus::NotVisited});

    for (auto it = &(*ramp_collection.begin()), end = &(*ramp_collection.end()); it < end; it++)
        statuses.insert({it, SenderStatus::NotVisited});

    try
    {
        for (auto it = &(*ramp_collection.begin()), end = &(*ramp_collection.end()); it < end; it++)
            if (!has_reachable_storehouse(dynamic_cast<PackageSender *>(it), statuses))
                return false;
    }
    catch (const std::logic_error &)
    {
        return false;
    }

    return true;
}

void Factory::do_deliveries(Time t)
{
    for (auto ramp = ramp_collection.begin(); ramp < ramp_collection.end(); ramp++)
        ramp->deliver_goods(t);
}

void Factory::do_package_passing()
{

    for (auto i = ramp_collection.begin(); i < ramp_collection.end(); i++)
        i->send_package();

    for (auto i = worker_collection.begin(); i < worker_collection.end(); i++)
        i->send_package();
}

void Factory::do_work(Time t)
{
    for (auto worker = worker_collection.begin(); worker < worker_collection.end(); worker++)
        worker->do_work(t);
}
