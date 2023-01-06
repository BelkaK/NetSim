#ifndef STORAGE_TYPES
#define STORAGE_TYPES

#include <list>

enum class PackageQueueType
{
    FIFO,
    LIFO
};

class PackageQueue : private IPackageStockPile
{
public:
    PackageQueue(PackageQueueType);

    Package pop() override;
    void push() override;
    unsigned int size() const override;
    bool empty() const override;

    PackageQueueType get_queue_type() const override;

    std::list<int>::const_iterator cbegin() const override;
    std::list<int>::const_iterator cend() const override;
    std::list<int>::const_iterator begin() const override;
    std::list<int>::const_iterator end() const override;

private:
    std::list<int> queue;
};

class IPackageStockPile : private IPackageQueue
{
public:
    using const_iterator = std::list<Package>::const_iterator;
    virtual void push() = 0;
    virtual unsigned int size() const = 0;
    virtual bool empty() const = 0;
    virtual ~IPackageStockPile() = default;
    virtual std::list<int>::const_iterator cbegin() const = 0;
    virtual std::list<int>::const_iterator cend() const = 0;
    virtual std::list<int>::const_iterator begin() const = 0;
    virtual std::list<int>::const_iterator end() const = 0;
};
class IPackageQueue
{
public:
    virtual Package pop() = 0;
    virtual PackageQueueType get_queue_type() const = 0;
};

#endif