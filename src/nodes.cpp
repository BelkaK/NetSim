#include "nodes.hpp"

//STOREHOUSE

Storehouse::Storehouse(ElementID id, std::unique_ptr<IPackageStockPile> d) {

}

void Storehouse::receive_package(Package&& p) {

}

ElementID Storehouse::get_id() const {

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