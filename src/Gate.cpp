#include "Gate.h"
#include "Literal.h"
#include "ConjunctiveNormalForm.h"

#include <iostream>

Gate::Gate()
{
}

Gate::Gate(Type type, std::vector<std::shared_ptr<Net>> nets) :
    m_type(type),
    m_nets(nets)
{
}

Gate::~Gate()
{
}

Gate::Type Gate::type() const
{
    return this->m_type;
}

std::string Gate::typeAsString()
{
    switch (this->m_type)
    {
    case Type::AND:
        return "AND";
    case Type::OR:
        return "OR";
    case Type::INV:
        return "INV";
    case Type::XOR:
        return "XOR";
    case Type::ZERO:
        return "ZERO";
    case Type::ONE:
        return "ONE";
    case Type::EQUAL:
        return "EQUAL";
    default:
        return "UNKNOWN";
    }
}

void Gate::setType(Type type)
{
    this->m_type = type; 
}

std::vector<std::shared_ptr<Net>> Gate::nets() const
{
    return this->m_nets;
}

void Gate::setNets(std::vector<std::shared_ptr<Net>> nets)
{
    this->m_nets = nets; 
}

ConjunctiveNormalForm Gate::characteristicFunction()
{
    ConjunctiveNormalForm cnf;
    std::vector<Literal> literals;
    switch (this->m_type)
    {
    case Type::AND:
        literals.push_back({m_nets.at(0), true, 0});
        literals.push_back({m_nets.at(1), true, 0}); 
        literals.push_back({m_nets.at(2), false, 0});

        cnf.addClausesFromLiterals(literals);
        literals.clear();
         
        literals.push_back({m_nets.at(0), false, 0}); 
        literals.push_back({m_nets.at(2), true, 0});
        
        cnf.addClausesFromLiterals(literals);
        literals.clear();

        literals.push_back({m_nets.at(1), false, 0}); 
        literals.push_back({m_nets.at(2), true, 0});
        
        cnf.addClausesFromLiterals(literals);
        literals.clear();
        return cnf;
    case Type::OR:
        literals.push_back({m_nets.at(0), false, 0}); 
        literals.push_back({m_nets.at(1), false, 0}); 
        literals.push_back({m_nets.at(2), true, 0});

        cnf.addClausesFromLiterals(literals);
        literals.clear();
         
        literals.push_back({m_nets.at(0), true, 0}); 
        literals.push_back({m_nets.at(2), false, 0});
        
        cnf.addClausesFromLiterals(literals);
        literals.clear();

        literals.push_back({m_nets.at(1), true, 0}); 
        literals.push_back({m_nets.at(2), false, 0});
        
        cnf.addClausesFromLiterals(literals);
        literals.clear();
        return cnf;
    case Type::INV:
        literals.push_back({m_nets.at(0), false, 0}); 
        literals.push_back({m_nets.at(1), false, 0});
        
        cnf.addClausesFromLiterals(literals);
        literals.clear();

        literals.push_back({m_nets.at(0), true, 0}); 
        literals.push_back({m_nets.at(1), true, 0});
        
        cnf.addClausesFromLiterals(literals);
        literals.clear();
        return cnf;
    case Type::XOR:
        literals.push_back({m_nets.at(0), false, 0}); 
        literals.push_back({m_nets.at(1), false, 0}); 
        literals.push_back({m_nets.at(2), true, 0});

        cnf.addClausesFromLiterals(literals);
        literals.clear();
        
        literals.push_back({m_nets.at(0), true, 0}); 
        literals.push_back({m_nets.at(1), true, 0}); 
        literals.push_back({m_nets.at(2), true, 0});

        cnf.addClausesFromLiterals(literals);
        literals.clear();

        literals.push_back({m_nets.at(0), true, 0}); 
        literals.push_back({m_nets.at(1), false, 0}); 
        literals.push_back({m_nets.at(2), false, 0});

        cnf.addClausesFromLiterals(literals);
        literals.clear();

        literals.push_back({m_nets.at(0), false, 0}); 
        literals.push_back({m_nets.at(1), true, 0}); 
        literals.push_back({m_nets.at(2), false, 0});

        cnf.addClausesFromLiterals(literals);
        literals.clear();
        return cnf;
    case Type::ZERO:
        literals.push_back({m_nets.at(0), true, 0});
        cnf.addClausesFromLiterals(literals);
        literals.clear();
        return cnf;
    case Type::ONE:
        literals.push_back({m_nets.at(0), false, 0});
        cnf.addClausesFromLiterals(literals);
        literals.clear();
        return cnf;
    case Type::EQUAL:
        literals.push_back({m_nets.at(0), true, 0}); 
        literals.push_back({m_nets.at(1), false, 0});
        
        cnf.addClausesFromLiterals(literals);
        literals.clear();

        literals.push_back({m_nets.at(0), false, 0}); 
        literals.push_back({m_nets.at(1), true, 0});
        
        cnf.addClausesFromLiterals(literals);
        literals.clear();
        return cnf;
    default:
       return ConjunctiveNormalForm();
    }
}
