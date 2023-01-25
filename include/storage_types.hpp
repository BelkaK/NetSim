#ifndef STORAGE_TYPES
#define STORAGE_TYPES
#include <list>
#include "package.hpp"

enum class PackageQueueType
{
    FIFO,
    LIFO
};

class IPackageStockpile
{
public:
    using const_iterator = std::list<Package>::const_iterator;
    virtual void push(Package &&t) = 0;
    virtual std::size_t size() const = 0;
    virtual bool empty() const = 0;
    virtual ~IPackageStockpile() = default;
    virtual std::list<Package>::const_iterator cbegin() const = 0;
    virtual std::list<Package>::const_iterator cend() const = 0;
    virtual std::list<Package>::const_iterator begin() const = 0;
    virtual std::list<Package>::const_iterator end() const = 0;
};

class IPackageQueue : public IPackageStockpile
{
public:
    virtual Package pop() = 0;
    virtual PackageQueueType get_queue_type() const = 0;

protected:
    PackageQueueType queue_type;
};

class PackageQueue : public IPackageQueue
{
public:
    PackageQueue(PackageQueueType queue_type) : queue_type(queue_type){};

    Package pop() override;
    void push(Package &&t) override { queue.push_back(std::move(t)); };
    std::size_t size() const override { return queue.size(); };
    bool empty() const override;

    PackageQueueType get_queue_type() const override { return queue_type; };

    std::list<Package>::const_iterator cbegin() const override { return queue.cbegin(); };
    std::list<Package>::const_iterator cend() const override { return queue.cend(); };
    std::list<Package>::const_iterator begin() const override { return queue.begin(); };
    std::list<Package>::const_iterator end() const override { return queue.end(); };

private:
    std::list<Package> queue;
    PackageQueueType queue_type;
};

#endif