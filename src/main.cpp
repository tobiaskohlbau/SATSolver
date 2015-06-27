#include "Clause.h"
#include "Netlist.h"
#include "Solver.h"

#include <iostream>

int main(int argc, char **argv)
{
    if (argc == 0)
        return -1;


    std::vector<Netlist> netlists;

    netlists.push_back(Netlist("/home/tobias/edat/netlists/sample_1.net"));
    netlists.push_back(Netlist("/home/tobias/edat/netlists/sample_2.net"));
    //netlists.push_back(Netlist("/home/tobias/edat/netlists/sample_2.net"));

    std::shared_ptr<Solver> solver = std::make_shared<Solver>(netlists);

    solver->solve();
}
