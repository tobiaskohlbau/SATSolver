#ifndef SOLVER_H_
#define SOLVER_H_

#include "Netlist.h"
#include <vector>

class Solver
{
public:
    Solver(std::vector<Netlist> netlists);
    ~Solver();
    void solve();
private:
    Netlist m_netlist;
    Netlist miter(std::vector<Netlist> netlists);
    void dp(std::shared_ptr<ConjunctiveNormalForm> cnf);
    void unitClause(std::shared_ptr<ConjunctiveNormalForm> cnf);
};

#endif /* SOLVER_H_ */

