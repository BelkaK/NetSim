#include "storage_types.hpp"

Package PackageQueue::pop()
{
    // w zależności od rodzaju kolejki wyciąga
    // pierwszy lub ostatni element
    Package result;
    if (queue_type == PackageQueueType::LIFO)
    {
        result = std::move(queue.back());
        queue.pop_back();
    }
    if (queue_type == PackageQueueType::FIFO)
    {
        result = std::move(queue.front());
        queue.pop_front();
    }
    return result;
}

bool PackageQueue::empty() const
{
    // zwraca true jeżeli kolejka jest pusta
    // false w każdym innym przypadku
    return queue.size() == 0;
}