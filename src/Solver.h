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
    std::shared_ptr<ConjunctiveNormalForm> m_satifiable;
    Netlist m_netlist;
    Netlist miter(std::vector<Netlist> netlists);
    bool dp(std::shared_ptr<ConjunctiveNormalForm> cnf);
    bool pureLiteral(std::shared_ptr<ConjunctiveNormalForm> cnf);
    bool unitClause(std::shared_ptr<ConjunctiveNormalForm> cnf);
};

#endif /* SOLVER_H_ */

