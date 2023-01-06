#include "storage_types.hpp"

class PackageQueue : public IPackageQueue
{
public:
    PackageQueue(PackageQueueType queue_type)
    {
        // konstruktor, ustawia queue_type na argument
    }

    Package pop() override
    {
        // w zależności od rodzaju kolejki wyciąga
        // pierwszy lub ostatni element
    }
    void push() override
    {
        // wkłada element na koniec kolejki
    }
    unsigned int size() const override
    {
        // oddaje ilość elementów w kolejce
    }
    bool empty() const override
    {
        // zwraca true jeżeli kolejka jest pusta
        // false w każdym innym przypadku
    }

    PackageQueueType get_queue_type() const override
    {
        // oddaje rodzaj kolejki
        return queue_type;
    }

    // iteratory : )
    std::list<int>::const_iterator cbegin() const override
    {
        return queue.cbegin();
    }
    std::list<int>::const_iterator cend() const override
    {
        return queue.cend();
    }
    std::list<int>::const_iterator begin() const override
    {
        return queue.begin();
    }
    std::list<int>::const_iterator end() const override
    {
        return queue.end();
    }

private:
    std::list<int> queue;
    PackageQueueType queue_type;
};