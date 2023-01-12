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

    const List list3;
    CHECK(list != list3);
    CHECK(list2 != list3);
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

    SECTION("moved")
    {
        REQUIRE(moved.size() == size_1);
        REQUIRE(not moved.empty());
    }

    SECTION("base")
    {
        REQUIRE(list.size() == size_0);
        REQUIRE(list.empty());
    }
}

TEST_CASE("at")
{
    constexpr auto value = 5.0;
    constexpr std::size_t index = 0;
    constexpr std::size_t out_of_bounds_index = 1;
    lst::List<double> list{value};
    const auto list2 = list;

    SECTION("at")
    {
        REQUIRE(list.at(index) == value);
        REQUIRE(list2.at(index) == value);
    }

    SECTION("at excpt")
    {
        REQUIRE_THROWS_AS(
            list.at(out_of_bounds_index),
            lst::exceptions::index_out_of_bounds);

        REQUIRE_THROWS_AS(
            list2.at(out_of_bounds_index),
            lst::exceptions::index_out_of_bounds);
    }
}

TEST_CASE("operator[]")
{
    constexpr auto value = 5.0;
    constexpr std::size_t index = 0;
    constexpr std::size_t out_of_bounds_index = 1;
    lst::List<double> list{value};
    const auto list2 = list;

    SECTION("operator[]")
    {
        REQUIRE(list[index] == value);
        REQUIRE(list2[index] == value);
    }

    SECTION("operator[] excpt")
    {
        REQUIRE_THROWS_AS(
            list[out_of_bounds_index],
            lst::exceptions::index_out_of_bounds);
        REQUIRE_THROWS_AS(
            list2[out_of_bounds_index],
            lst::exceptions::index_out_of_bounds);
    }
}

TEST_CASE("indices")
{
    lst::List<int> list{5, 6, 7};
    const std::vector<std::size_t> indices{0, 1, 2};
    const auto list2 = list;

    REQUIRE(list.indices() == indices);
    REQUIRE(list2.indices() == indices);
}

TEST_CASE("index")
{
    lst::List<int> list{5, 6, 7};
    constexpr auto searched_element = 6;
    constexpr std::size_t target_index = 1;
    const auto list2 = list;
    REQUIRE(list.index(searched_element) == target_index);
    REQUIRE(list2.index(searched_element) == target_index);
}
