
#include "package.hpp"
#include "storage_types.hpp"
#include "types.hpp"
#include "gtest/gtest.h"

TEST(class_PackageQueue, LIFO)
{
    Package package1;
    Package package2;

    PackageQueueType type = PackageQueueType::LIFO;
    PackageQueue queue(type);
    queue.push(std::move(package1));
    queue.push(std::move(package2));
    Package result = queue.pop();
    EXPECT_EQ(result.get_id(), package2.get_id());
}


TEST(class_PackageQueue, FIFO)
{
    Package package1;
    Package package2;

    PackageQueueType type = PackageQueueType::FIFO;
    PackageQueue queue(type);
    queue.push(std::move(package1));
    queue.push(std::move(package2));
    Package result = queue.pop();
    EXPECT_EQ(result.get_id(), package1.get_id());
}




TEST(class_Package, diffirent_ID){
    Package package1;
    Package package2;
    ElementID  id_1 = package1.get_id();
    ElementID  id_2 = package2.get_id();
    EXPECT_FALSE(id_1 == id_2);
}