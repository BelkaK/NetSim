#include "storage_types.hpp"

Package PackageQueue::pop(){
    Package result;
    Package::freed_IDs_.insert(result.get_id());
    Package::assigned_IDs_.erase(result.get_id());
    switch(queue_type){
        case PackageQueueType::LIFO:
            result = std::move(*queue.end());
            queue.pop_back();
            break;
        case PackageQueueType::FIFO:
            result = std::move(*queue.begin());
            queue.pop_front();
            break;
        default:

            break;
    }
    return result;
}

bool PackageQueue::empty() const
{
    // zwraca true jeżeli kolejka jest pusta
    // false w każdym innym przypadku
    return queue.size() == 0;
}