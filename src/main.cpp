#include "Clause.h"
#include "Netlist.h"
#include "Solver.h"

#include <iostream>

int main(int argc, char **argv)
{
    if (argc == 0)
        return -1;


    std::vector<Netlist> netlists;

    //// equal
    //netlists.push_back(Netlist("/home/tobias/edat/netlists/sample_1.net"));
    //netlists.push_back(Netlist("/home/tobias/edat/netlists/sample_1.net"));

    //// unequal
    //netlists.push_back(Netlist("/home/tobias/edat/netlists/sample_1.net"));
    //netlists.push_back(Netlist("/home/tobias/edat/netlists/sample_2.net"));

    // equal
    netlists.push_back(Netlist("/home/tobias/edat/netlists/xor2.net"));
    netlists.push_back(Netlist("/home/tobias/edat/netlists/xor2_nand.net"));

    // unequal
    //netlists.push_back(Netlist("/home/tobias/edat/netlists/adder4_rc.net"));
    //netlists.push_back(Netlist("/home/tobias/edat/netlists/adder4_rc_wrong.net"));

    std::shared_ptr<Solver> solver = std::make_shared<Solver>(netlists);

    solver->solve();
}
