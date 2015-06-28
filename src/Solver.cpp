#include "Solver.h"

#include <iostream>
#include <algorithm>
#include <thread>
#include <future>

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
    if (dp(cnf))
        std::cout << "UNEQUAL" << std::endl;
    else
        std::cout << "EQUAL" << std::endl;

    //std::shared_ptr<ConjunctiveNormalForm> cnf1 = std::make_shared<ConjunctiveNormalForm>(*cnf);
    //cnf1->setVariable(11, 0);
    ////for (int i = 1; i <= 12; i++)
    ////    cnf1->removeLiteralsByNumber(i);
    //for (auto clause : cnf1->clauses())
    //{
    //    for (auto literal : clause->literals())
    //    {
    //        std::cout << literal->netNumber() << std::endl;
    //    }
    //}
    //std::cout << cnf->string() << std::endl;
    //std::cout << cnf1->string() << std::endl;
    //std::cout << cnf1->empty() << std::endl;
    //std::cout << cnf1->emptyClause() << std::endl;
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
    numberOffset = 0;
    for (auto netlist : netlists)
    {
        for (auto net : netlist.internalNets())
        {
            std::shared_ptr<Net> modifiedNet = std::make_shared<Net>(*net);
            modifiedNet->setNumber(modifiedNet->number() + numberOffset);
            combinedInternals.push_back(modifiedNet);
        }
        numberOffset += netlist.numberOfNets();
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

bool Solver::dp(std::shared_ptr<ConjunctiveNormalForm> cnf)
{
    bool propagate = true;
    while (propagate)
    {
        propagate = pureLiteral(cnf) || unitClause(cnf);
    }

    if (cnf->empty())
    {
        return true;
    }
    else if (cnf->emptyClause())
    {
        return false;
    }
    else
    {
        // backtracking
        std::shared_ptr<ConjunctiveNormalForm> cnf0 = std::make_shared<ConjunctiveNormalForm>(*cnf);
        int rightMost = cnf0->getRightMost();
        cnf0->setVariable(rightMost, 0);

        std::shared_ptr<ConjunctiveNormalForm> cnf1 = std::make_shared<ConjunctiveNormalForm>(*cnf);
        rightMost = cnf1->getRightMost();
        cnf1->setVariable(rightMost, 1);

        auto handle1 = std::async(std::launch::async, &Solver::dp, this, cnf1);

        bool out = dp(cnf0);
        return out || handle1.get();
    }
}

bool Solver::pureLiteral(std::shared_ptr<ConjunctiveNormalForm> cnf)
{
    std::vector<std::shared_ptr<Literal>> pureLiterals;

    int applied = 0;
    for (auto clause : cnf->clauses())
    {
        auto literals = clause->literals();
        pureLiterals.insert(pureLiterals.end(), literals.begin(), literals.end());
    }

    std::for_each (pureLiterals.begin(), pureLiterals.end(), [pureLiterals, cnf](std::shared_ptr<Literal> p) {
            if (p->inverted())
            {
                auto it = std::find_if(pureLiterals.begin(), pureLiterals.end(), [](std::shared_ptr<Literal> pl) {
                        return !pl->inverted();
                });
                if (it == pureLiterals.end())
                    cnf->setVariable(p->netNumber(), 0);
            }
            else
            {
                auto it = std::find_if(pureLiterals.begin(), pureLiterals.end(), [](std::shared_ptr<Literal> pl) {
                        return pl->inverted();
                });
                if (it == pureLiterals.end())
                    cnf->setVariable(p->netNumber(), 1);
            }
    });

    return applied;
}

bool Solver::unitClause(std::shared_ptr<ConjunctiveNormalForm> cnf)
{
    bool applied = false;
    for (unsigned int i = 0; i < cnf->clauses().size(); ++i)
    {
        auto clause = cnf->clauses().at(i);
        if (clause->literals().size() == 1)
        {
            auto literal = clause->literals().at(0);
            cnf->setVariable(literal->netNumber(), literal->inverted() ? 0 : 1);
            applied = true;
        }
    }

    return applied;
}
