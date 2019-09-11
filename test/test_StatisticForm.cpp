#include "catch.hpp"
#include <iostream>
#include <GUIModule/statisticform.cpp>

using namespace std;

TEST_CASE("StatisticForm: Convert double to string is correctly", "[app]") {

    StatisticForm* s = new StatisticForm();
    double n_1 = 15.11111;
    string a1 = "15.11";
    REQUIRE(a1 == s->convertDoubleToStr(n_1));
    double n_2 = 1.699;
    string a2 = "1.70";
    REQUIRE(a2 == s->convertDoubleToStr(n_2));
    double n_3 = 1;
    string a3 = "1.00";
    REQUIRE(a3 == s->convertDoubleToStr(n_3));
}

TEST_CASE("StatisticForm: Print Platform Types is correctly", "[app]") {

    StatisticForm* s = new StatisticForm();
    REQUIRE("CPU" == s->toString(PlatformType::CPU));
    REQUIRE("GPU" == s->toString(PlatformType::GPU));
    REQUIRE("CPU_TORCH" == s->toString(PlatformType::CPU_TORCH));
    REQUIRE("ASIC" == s->toString(PlatformType::ASIC));
}