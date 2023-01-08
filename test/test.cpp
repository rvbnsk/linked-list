#include <catch2/catch_test_macros.hpp>
#include <node.hpp>

constexpr std::size_t size_0 = 0;
constexpr std::size_t size_1 = 1;

TEST_CASE("Creating object and size asserting")
{
    constexpr int elem = 1;

    lst::List<int> list;
    CHECK(list.size() == size_0);
    list.push_back(elem);
    CHECK(list.size() == size_1);
}

TEST_CASE("Creating object by initializer list and push_back comparison")
{
    using List = lst::List<int>;
    const List list{0, 1, 2};
    List list2;
    list2.push_back(0);
    list2.push_back(1);
    list2.push_back(2);

    REQUIRE(list == list2);
}

TEST_CASE("Copying object and comparison operator")
{
    constexpr std::string_view elem = "test";
    lst::List<std::string_view> list;
    list.push_back(elem);

    const auto copied = list;

    REQUIRE(copied == list);
    CHECK(copied.size() == size_1);
}

TEST_CASE("Moving object")
{
    constexpr auto elem = 5.0;
    lst::List<double> list;
    list.push_back(elem);

    const auto moved = std::move(list);
    REQUIRE(moved.size() == size_1);
    REQUIRE(list.size() == size_0);
}
