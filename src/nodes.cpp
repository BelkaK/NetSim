#include "nodes.hpp"

#include <utility>

//STOREHOUSE

Storehouse::Storehouse(ElementID id, std::unique_ptr<IPackageStockPile> d) {
    id_ = id;
    d_ = std::move(d);
}

void Storehouse::receive_package(Package&& p) {

}

ElementID Storehouse::get_id() const {
    return id_;
}

std::list<Package>::const_iterator Storehouse::begin() const {

}

std::list<Package>::const_iterator Storehouse::cbegin() const {

}

std::list<Package>::const_iterator Storehouse::end() const {

}

std::list<Package>::const_iterator Storehouse::cend() const {

}


//ReceiverPreferences

void ReceiverPreferences::add_receiver(IPackageReceiver* r) {

}

void ReceiverPreferences::remove_receiver(IPackageReceiver* r) {

}

IPackageReceiver* ReceiverPreferences::choose_receiver() {

}

ReceiverPreferences::preferences_t ReceiverPreferences::get_preferences() const {

}

ReceiverPreferences::ReceiverPreferences(ProbabilityGenerator pg) {
    pg_ = std::move(pg);
}

std::list<Package>::const_iterator ReceiverPreferences::begin() const {

}
std::list<Package>::const_iterator ReceiverPreferences::cend() const{

}
std::list<Package>::const_iterator ReceiverPreferences::cbegin() const{

}
std::list<Package>::const_iterator ReceiverPreferences::end() const{

}


//PACKAGE SENDER

void PackageSender::send_package() {

}

std::optional<Package>& PackageSender::get_sending_buffer() const {

}

void PackageSender::push_package(Package&&) {

}

//RAMP
Ramp::Ramp(ElementID id, TimeOffset di) {

}

void Ramp::deliver_goods(Time t) {

}

TimeOffset Ramp::get_delivery_interval() const {

}

ElementID Ramp::get_id() const {

}

//WORKER

Worker::Worker(ElementID id, TimeOffset pd, std::unique_ptr<IPackageQueue>) {

}

void Worker::receive_package(Package&& p) {

}

ElementID Worker::get_id() const {

}

void Worker::do_work(Time t) {

}

TimeOffset Worker::get_processing_duration() const{

}

Time Worker::get_package_processing_start_time() const{

}