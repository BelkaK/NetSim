#include "nodes.hpp"

//STOREHOUSE

Storehouse::Storehouse(ElementID id, std::unique_ptr<IPackageQueue> d = nullptr){
    if(d == nullptr)
    {
        this->id_ = id;
        d = std::make_unique<PackageQueue>(PackageQueueType::FIFO);
    }
}

void Storehouse::receive_package(Package&& p) {
    d_->push(std::move(p));
}



//ReceiverPreferences

void ReceiverPreferences::add_receiver(IPackageReceiver* r) {
    preferences_.insert(std::pair<IPackageReceiver*,double>(r, 1.0/double(preferences_.size())));
    for(auto i = preferences_.begin(); i != preferences_.end(); i++)
    {
        i->second = 1.0/double(preferences_.size());
    }
}

void ReceiverPreferences::remove_receiver(IPackageReceiver* r) {
    preferences_.erase(r);
    for(auto i = preferences_.begin(); i != preferences_.end(); i++)
    {
        i->second = 1.0/double(preferences_.size());
    }
}

IPackageReceiver* ReceiverPreferences::choose_receiver() {
    double lottery = gen();
    for(auto i = preferences_.begin(); i!=preferences_.end(); i++){
        if (lottery < i->second)
        {
            return i->first;
        }
        else
        {
            lottery -= i->second;
        }
    }
    throw std::invalid_argument("reached end of function choose_receiver: probably empty list");
}



//PACKAGE SENDER

void PackageSender::send_package() {
    if (buffer_) {
        IPackageReceiver* chosen_receiver = receiver_preferences_.choose_receiver();
        chosen_receiver->receive_package(std::move(*buffer_));
        buffer_ = std::nullopt;
    }
}


void PackageSender::push_package(Package&& p) {
    buffer_.emplace(std::move(p));
}

//RAMP

void Ramp::deliver_goods(Time t) {
    push_package(Package());
    if(delivery_time_ + offset_ <= t)
    {
        send_package();
        delivery_time_ = t;
    }
}



//WORKER

Worker::Worker(ElementID id, TimeOffset pd, std::unique_ptr<IPackageQueue> q) {
    PackageSender();
    this->id_ = id;
    this->offset = pd;
    this->queue = std::move(q);
    this->start_time = 0;
}

void Worker::receive_package(Package&& p) {
    if(!get_sending_buffer())
    {
        queue->push(std::move(p));
    }
    else
    {
        queue->push(std::move(p));
        push_package(queue->pop());
    }
}

void Worker::do_work(Time t) {
    if(!current_package && queue)
    {
        current_package.emplace(queue->pop());
        start_time = t;
    }
    if(current_package && t + 1 - start_time >= offset)
    {
        push_package(std::move(current_package.value()));
        current_package.reset();
        start_time = 0;
    }
}

