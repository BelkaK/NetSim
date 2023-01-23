#ifndef SIECI_FACTORY_HPP
#define SIECI_FACTORY_HPP
#include "nodes.hpp"
#include <iostream>
#include <iterator>

template<class T>
class NodeCollection
{
public:
    using container_t = typename std::vector<T>;
    using iterator = typename container_t::iterator;
    using const_iterator = typename container_t::const_iterator;


    NodeCollection<T>::iterator begin() {return collection.begin();}
    NodeCollection<T>::iterator end() {return collection.end();}
    NodeCollection<T>::const_iterator cbegin() const {return collection.cbegin();}
    NodeCollection<T>::const_iterator cend() const {return collection.cend();}

    void add(T&& node) {collection.push_back(std::move(node));}
    void remove_by_id(ElementID id)
    {
        auto it = find_by_id(id);
        if(it != end())
            collection.erase(it);
    }
    NodeCollection<T>::iterator find_by_id(ElementID id)
    {
        for (auto it = begin(); it < end(); it++)
        {
            if(it->get_id() == id)
                return it;
        }
        std::cout << "element not found" << std::endl;
        return end();
    }
    NodeCollection<T>::const_iterator find_by_id(ElementID id) const
    {
        for(auto it = cbegin(); it < cend(); it++)
        {
            if(it->get_id() == id)
                return it;
        }
        std::cout << "element not found" << std::endl;
        return cend();
    }

private:
    container_t collection;
};

class Factory
{
private:
    template<class T>
    void remove_receiver(NodeCollection<T> collection,ElementID id);

    NodeCollection<Ramp> ramp_collection;
    NodeCollection<Worker> worker_collection;
    NodeCollection<Storehouse> storehouse_collection;
public:
    // dla węzłów typu Ramp
    void add_ramp(Ramp&& ramp) {ramp_collection.add(std::move(ramp));}
    void remove_ramp(ElementID id) {ramp_collection.remove_by_id(id);}
    NodeCollection<Ramp>::iterator find_ramp_by_id(ElementID id) {return ramp_collection.find_by_id(id);}
    NodeCollection<Ramp>::const_iterator find_ramp_by_id(ElementID id) const {return ramp_collection.find_by_id(id);}
    NodeCollection<Ramp>::const_iterator ramp_cbegin() const {return ramp_collection.cbegin();}
    NodeCollection<Ramp>::const_iterator ramp_cend() const {return ramp_collection.cend();}

    // dla węzłów typu Worker
    void add_worker(Worker&& worker) {worker_collection.add(std::move(worker));}
    void remove_worker(ElementID id) {worker_collection.remove_by_id(id);}
    NodeCollection<Worker>::iterator find_worker_by_id(ElementID id) {return worker_collection.find_by_id(id);}
    NodeCollection<Worker>::const_iterator find_worker_by_id(ElementID id) const {return worker_collection.find_by_id(id);}
    NodeCollection<Worker>::const_iterator worker_cbegin() const {return worker_collection.cbegin();}
    NodeCollection<Worker>::const_iterator worker_cend() const {return worker_collection.cend();}

    // dla węzłów typu Storehouse
    void add_storehouse(Storehouse&& storehouse) {storehouse_collection.add(std::move(storehouse));}
    void remove_storehouse(ElementID id) {storehouse_collection.remove_by_id(id);}
    NodeCollection<Storehouse>::iterator find_storehouse_by_id(ElementID id) { return storehouse_collection.find_by_id(id);}
    NodeCollection<Storehouse>::const_iterator find_storehouse_by_id(ElementID id) const {return storehouse_collection.find_by_id(id);}
    NodeCollection<Storehouse>::const_iterator storehouse_cbegin() const {return storehouse_collection.cbegin();}
    NodeCollection<Storehouse>::const_iterator storehouse_cend() const {return storehouse_collection.cend();}

    bool is_consistent();
    void do_deliveries(Time t);
    void do_package_passing();
    void do_work(Time t);
};

#endif
