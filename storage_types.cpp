#include "storage_types.hpp"

class PackageQueue : public IPackageQueue
{
public:
    PackageQueue(PackageQueueType queue_t)
    {
        // konstruktor, ustawia queue_type na argument
        queue_type = queue_t;
    }

    Package pop() override
    {
        // w zależności od rodzaju kolejki wyciąga
        // pierwszy lub ostatni element
        Package result;
        switch (queue_type)
        {
        case PackageQueueType::LIFO:
            result = queue.back();
            queue.pop_back();
            break;
        case PackageQueueType::FIFO:
            result = queue.front();
            queue.pop_front();
            break;

        default:
            break;
        }
        return result;
    }
    void push(Package &&package) override
    {
        // wkłada element na koniec kolejki
        queue.push_back(package);
    }
    unsigned int size() const override
    {
        // oddaje ilość elementów w kolejce
        return queue.size();
    }
    bool empty() const override
    {
        // zwraca true jeżeli kolejka jest pusta
        // false w każdym innym przypadku
        return queue.empty();
    }

    PackageQueueType get_queue_type() const override
    {
        // oddaje rodzaj kolejki
        return queue_type;
    }

    // iteratory : )
    std::list<Package>::const_iterator cbegin() const override
    {
        return queue.cbegin();
    }
    std::list<Package>::const_iterator cend() const override
    {
        return queue.cend();
    }
    std::list<Package>::const_iterator begin() const override
    {
        return queue.begin();
    }
    std::list<Package>::const_iterator end() const override
    {
        return queue.end();
    }

private:
    std::list<Package> queue;
    PackageQueueType queue_type;
};