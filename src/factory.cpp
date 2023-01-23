#include "factory.hpp"

enum class SenderStatus
{
    NotVisited,
    Visited,
    Verified   //będzie potrzebne do metody is_consistent()
};

// FACTORY

bool Factory::is_consistent() {return false;} //na wiki ZPO jest algorytm jak oni to chca

void Factory::do_deliveries(Time t) {}

void Factory:: do_package_passing() {}

void Factory::do_work(Time t) {}




