#include "nodes.hpp"

//STOREHOUSE

Storehouse::Storehouse(ElementID id, std::unique_ptr<PackageQueue> d){
    this->id_ = id;
    d_ = std::move(d);

}

void Storehouse::receive_package(Package&& p) {
    d_->push(std::move(p));
}


//ReceiverPreferences

void ReceiverPreferences::add_receiver(IPackageReceiver* r) {
    preferences_.insert(std::pair<IPackageReceiver*,double>(r, 1/double(preferences_.size())));
    for(auto i = preferences_.begin(); i != preferences_.end(); i++)
    {
        i->second = 1/double(preferences_.size());
    }
}

void ReceiverPreferences::remove_receiver(IPackageReceiver* r) {
    preferences_.erase(r);
    if(preferences_.size() != 0)
    {
        for(auto i = preferences_.begin(); i != preferences_.end(); i++)
        {
            i->second = 1/double(preferences_.size());
        }
    }

}

IPackageReceiver* ReceiverPreferences::choose_receiver() {
    double lottery = gen();
    double suma = 0.0;
    for(auto i = preferences_.begin(); i!=preferences_.end(); i++){
        suma += i->second;
        if(suma > lottery)
            return i->first;
    }
    return nullptr; //jak coś poszło nie tak
}



//PACKAGE SENDER

void PackageSender::send_package() {
    if(buffer_)
    {
        IPackageReceiver* package_receiver = receiver_preferences_.choose_receiver();
        package_receiver->receive_package(std::move(buffer_.value()));
        buffer_.reset();
    }
}


void PackageSender::push_package(Package&& p) {
    buffer_.emplace(std::move(p));
}

//RAMP

void Ramp::deliver_goods(Time t){
    if(start_time_ == UINTMAX_MAX) start_time_ = t;
    if((t-start_time_)%offset_ == 0){
        if(!buffer_){
            Package pac = Package();
            push_package(std::move(pac));
        }
    }
}

//WORKER

Worker::Worker(ElementID id, TimeOffset pd, std::unique_ptr<IPackageQueue> q) {
    PackageSender();
    this->id_ = id;
    this->offset = pd;
    this->queue = std::move(q);
}

void Worker::receive_package(Package&& p) {
    if(!get_sending_buffer())
    {
        queue->push(std::move(p));
        push_package(queue->pop());
    }
    else {
        queue->push(std::move(p));
    }
}

void Worker::do_work(Time t) {
    if(current_package and !queue->empty())
    {
        current_package = queue->pop();
        start_time = t;
    }
    if(bool(current_package) and t + 1 - start_time >= offset)
    {
        push_package(std::move(current_package.value()));
        current_package.reset();
        start_time = 0;
    }
}



