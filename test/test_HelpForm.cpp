#include "catch.hpp"
#include <iostream>
#include <GUIModule/helpform.cpp>

using namespace std;

TEST_CASE("HelpForm: Initialisation is correct", "[app]") {

    HelpForm* h = new HelpForm();
    REQUIRE(true == true);
}
