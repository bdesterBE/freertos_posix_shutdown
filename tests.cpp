#include <catch2/catch_all.hpp>


TEST_CASE("Example") {
    REQUIRE(1);
}

int main(int argc, char* argv[]) {
    return Catch::Session().run(argc, argv);
}