#include "Solver.h"

#include <iostream>
#include <algorithm>

Solver::Solver(std::vector<Netlist> netlists)
{
    m_netlist = this->miter(netlists);
}

Solver::~Solver()
{
}

void Solver::solve()
{
    std::shared_ptr<ConjunctiveNormalForm> cnf = m_netlist.cnf();
    cnf->setVariable(12, 1);
    std::cout << cnf->string() << std::endl;
}

Netlist Solver::miter(std::vector<Netlist> netlists)
{
    unsigned int numberOffset = 0;
    std::set<std::string> inputNames;
    std::set<std::string> outputNames;
    std::vector<std::shared_ptr<Net>> nets;
    std::vector<std::shared_ptr<Gate>> gates;

    std::vector<std::vector<std::shared_ptr<Net>>> combinedInputs;
    std::vector<std::vector<std::shared_ptr<Net>>> combinedOutputs;
    std::vector<std::shared_ptr<Net>> combinedInternals;

    // process input nets
    for (auto net : netlists.at(0).inputNets())
    {
        inputNames.insert(net->name());
        numberOffset = 0;
        std::vector<std::shared_ptr<Net>> combinedNets;
        combinedNets.push_back(net);
        for (unsigned int i = 1; i < netlists.size(); i++)
        {
            numberOffset += netlists.at(i-1).numberOfNets();
            for (auto n : netlists.at(i).inputNets())
            {
                if (net->name() == n->name())
                {
                    std::shared_ptr<Net> modifiedNet = std::make_shared<Net>(*n);
                    modifiedNet->setNumber(modifiedNet->number() + numberOffset);
                    combinedNets.push_back(modifiedNet);
                }
            }
        }
        combinedInputs.push_back(combinedNets);
    }

    // process output nets
    for (auto net : netlists.at(0).outputNets())
    {
        outputNames.insert(net->name());
        numberOffset = 0;
        std::vector<std::shared_ptr<Net>> combinedNets;
        combinedNets.push_back(net);
        for (unsigned int i = 1; i < netlists.size(); i++)
        {
            numberOffset += netlists.at(i-1).numberOfNets();
            for (auto n : netlists.at(i).outputNets())
            {
                if (net->name() == n->name())
                {
                    std::shared_ptr<Net> modifiedNet = std::make_shared<Net>(*n);
                    modifiedNet->setNumber(modifiedNet->number() + numberOffset);
                    combinedNets.push_back(modifiedNet);
                }
            }
        }
        combinedOutputs.push_back(combinedNets);
    }

    // process internal nets
    for (auto net : netlists.at(0).internalNets())
    {
        combinedInternals.push_back(net);
        numberOffset = 0;
        for (unsigned int i = 1; i < netlists.size(); i++)
        {
            numberOffset += netlists.at(i-1).numberOfNets();
            for (auto n : netlists.at(i).internalNets())
            {
                std::shared_ptr<Net> modifiedNet = std::make_shared<Net>(*n);
                modifiedNet->setNumber(modifiedNet->number() + numberOffset);
                combinedInternals.push_back(modifiedNet);
            }
        }
    }

    for (auto input : combinedInputs)
    {
        for (auto net : input)
        {
            nets.push_back(net);
        }
    }

    for (auto output : combinedOutputs)
    {
        for (auto net : output)
        {
            nets.push_back(net);
        }
    }

    nets.insert(nets.end(), combinedInternals.begin(), combinedInternals.end());

    std::sort(nets.begin(), nets.end(), [](std::shared_ptr<Net> n1, std::shared_ptr<Net> n2) {
                return n1->number() < n2->number();
            });

    // process gates
    std::shared_ptr<Gate> gate;
    std::vector<std::shared_ptr<Net>> tmpNets;
    numberOffset = 0;
    for (auto netlist : netlists)
    {
        for (auto g : netlist.gates())
        {
            gate = std::make_shared<Gate>(*g);
            for (auto net : g->nets())
            {
                tmpNets.push_back(nets.at(net->number() - 1 + numberOffset));
            }
            gate->setNets(tmpNets);
            gates.push_back(gate);
            tmpNets.clear();
        }
        numberOffset += netlist.numberOfNets();
    }

    // connect inputs
    for (auto input : combinedInputs)
    {
        gates.push_back(std::make_shared<Gate>(Gate::Type::EQUAL, input));
    }

    // connect outputs
    int numberOfOutputs = 0;
    numberOffset++;
    std::shared_ptr<Net> newNet;
    for (auto output : combinedOutputs)
    {
        newNet = std::make_shared<Net>(numberOffset++);
        nets.push_back(newNet);
        output.push_back(newNet);
        gates.push_back(std::make_shared<Gate>(Gate::Type::XOR, output));
        ++numberOfOutputs;
    }

    std::vector<std::shared_ptr<Net>> combinedNets;
    for (unsigned int i = numberOfOutputs - 1; i > 0; --i)
    {
        combinedNets.push_back(nets.at(numberOffset - numberOfOutputs - 1));
        combinedNets.push_back(nets.at(numberOffset - numberOfOutputs));
        newNet = std::make_shared<Net>(numberOffset++);
        nets.push_back(newNet);
        combinedNets.push_back(newNet);
        gates.push_back(std::make_shared<Gate>(Gate::Type::OR, combinedNets));
        combinedNets.clear();
    }

    combinedNets.push_back(nets.at(numberOffset - 2));
    gates.push_back(std::make_shared<Gate>(Gate::Type::ONE, combinedNets));

    return Netlist(numberOffset, inputNames, outputNames, nets, gates);
}

void Solver::dp(std::shared_ptr<ConjunctiveNormalForm> cnf)
{
    if (cnf->empty())
    {
        // terminate
    }
    else if (cnf->emptyClause())
    {
        // no possible solution
    }
    else
    {
        // backtracking
        cnf->setVariable(cnf->getRightMost(), 0);
        dp(cnf);

        cnf->setVariable(12, 1);
        dp(cnf);
    }
}

void Solver::unitClause(std::shared_ptr<ConjunctiveNormalForm> cnf)
{
    for (auto clause : cnf->clauses())
    {
        if (clause->literals().size() == 1)
        {
            std::cout << clause->string();
        }
    }
}
