#include "Clause.h"
#include "Netlist.h"

#include <iostream>

int main(int argc, char **argv)
{
    if (argc == 0)
        return -1;


    std::vector<Netlist> netlists = {Netlist(argv[1])};

    //netlists.push_back(Netlist("/home/tobias/edat/netlists/sample_1.net"));

    for (Netlist netlist : netlists)
    {
        std::cout << netlist.cnf().string() << std::endl;
    }
}
