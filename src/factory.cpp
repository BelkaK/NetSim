#include "factory.hpp"

enum class SenderStatus
{
    NotVisited,
    Visited,
    Verified // będzie potrzebne do metody is_consistent()
};

// FACTORY

bool Factory::is_consistent() { return false; } // na wiki ZPO jest algorytm jak oni to chca

void Factory::do_deliveries(Time t)
{
    for (auto ramp = ramp_collection.begin(); ramp < ramp_collection.end(); ramp++)
        ramp->deliver_goods(t)
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
