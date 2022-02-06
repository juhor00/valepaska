#include "eventhandler.h"
#include "tester.h"
#include <string>
#include <iostream>


using namespace std;

int main(int argc, char *argv[])
{
    if(argc == 2 && (string) argv[1] == "test"){
        cout << "Starting tester" << endl;
        Tester t;
    } else {
        EventHandler e;
    }

    return EXIT_SUCCESS;
}
