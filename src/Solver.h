#ifndef SOLVER_H_
#define SOLVER_H_

#include "Netlist.h"
#include <vector>

class Solver
{
public:
    Solver(std::vector<Netlist> netlists);
    ~Solver();
private:
    Netlist merge(std::vector<Netlist> netlists);
};

#endif /* SOLVER_H_ */

