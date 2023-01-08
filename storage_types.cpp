#include "storage_types.hpp"

PackageQueue::PackageQueue(PackageQueueType queue_t)
{
    // konstruktor, ustawia queue_type na argument
    queue_type = queue_t;
}

Package PackageQueue::pop()
{
    // w zależności od rodzaju kolejki wyciąga
    // pierwszy lub ostatni element
    Package result;
    switch (queue_type)
    {
    case PackageQueueType::LIFO:
        result = std::move(queue.back());
        queue.pop_back();
        break;
    case PackageQueueType::FIFO:
        result = std::move(queue.front());
        queue.pop_front();
        break;

    default:
        break;
    }
    return result;
}
void PackageQueue::push(Package &&package)
{
    // wkłada element na koniec kolejki
    queue.push_back(package);
}
unsigned int PackageQueue::size() const
{
    // oddaje ilość elementów w kolejce
    return queue.size();
}
bool PackageQueue::empty() const
{
    // zwraca true jeżeli kolejka jest pusta
    // false w każdym innym przypadku
    return queue.empty();
}

PackageQueueType PackageQueue::get_queue_type() const
{
    // oddaje rodzaj kolejki
    return queue_type;
}

// iteratory : )
std::list<Package>::const_iterator PackageQueue::cbegin() const
{
    return queue.cbegin();
}
std::list<Package>::const_iterator PackageQueue::cend() const
{
    return queue.cend();
}
std::list<Package>::const_iterator PackageQueue::begin() const
{
    return queue.begin();
}
std::list<Package>::const_iterator PackageQueue::end() const
{
    return queue.end();
}