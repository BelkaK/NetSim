#ifndef STORAGE_TYPES
#define STORAGE_TYPES

#include <list>
#include "package.hpp"

enum class PackageQueueType
{
    FIFO,
    LIFO
};

class PackageQueue : public IPackageQueue
{
public:
    PackageQueue(PackageQueueType);

    Package pop() override;
    void push(Package &&) override;
    unsigned int size() const override;
    bool empty() const override;

    PackageQueueType get_queue_type() const override;

    std::list<Package>::const_iterator cbegin() const override;
    std::list<Package>::const_iterator cend() const override;
    std::list<Package>::const_iterator begin() const override;
    std::list<Package>::const_iterator end() const override;

private:
    std::list<Package> queue;
    PackageQueueType queue_type;
};

class IPackageQueue : public IPackageStockPile
{
public:
    virtual Package pop() = 0;
    virtual PackageQueueType get_queue_type() const = 0;
};

class IPackageStockPile
{
public:
    using const_iterator = std::list<Package>::const_iterator;
    virtual void push(Package &&) = 0;
    virtual unsigned int size() const = 0;
    virtual bool empty() const = 0;
    virtual ~IPackageStockPile() = default;
    virtual std::list<Package>::const_iterator cbegin() const = 0;
    virtual std::list<Package>::const_iterator cend() const = 0;
    virtual std::list<Package>::const_iterator begin() const = 0;
    virtual std::list<Package>::const_iterator end() const = 0;
};

#endif