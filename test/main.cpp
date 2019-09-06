//
// Created by Aleksandr Eismont on 05.09.19.
//

#define CATCH_CONFIG_RUNNER
#include <catch.hpp>

#include <GUIModule/mainwindow.cpp>

int main( int argc, char* argv[] )
{
    QApplication a(argc, argv);
    setlocale(LC_NUMERIC,"C");

    const int result = Catch::Session().run( argc, argv );

    return ( result < 0xff ? result : 0xff );
}