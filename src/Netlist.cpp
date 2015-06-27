#include "Netlist.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>

Netlist::Netlist()
{
}

Netlist::Netlist(std::string file)
{
    this->readFromFile(file);
}

Netlist::Netlist(unsigned int numberOfNets, std::set<std::string> inputNames, std::set<std::string> outputNames,
    std::vector<std::shared_ptr<Net>> nets, std::vector<std::shared_ptr<Gate>> gates) :
    m_numberOfNets(numberOfNets),
    m_inputNames(inputNames),
    m_outputNames(outputNames),
    m_nets(nets),
    m_gates(gates)
{
}

Netlist::~Netlist()
{
}

void Netlist::readFromFile(std::string fileName)
{
    std::ifstream fileStream(fileName);
    if (!fileStream.is_open())
        return;

    std::string tmp;

    std::getline(fileStream, tmp);

    // read number of nets and create Net array
    this->m_numberOfNets = std::stoi(tmp);

    // read inputs
    this->readIOFromStream(fileStream, &m_inputNames);
   
    // read outputs
    this->readIOFromStream(fileStream, &m_outputNames);

    // read nets
    this->readNetsFromStream(fileStream);

    // read gates
    this->readGatesFromStream(fileStream);

    fileStream.close();

    // debug output
    std::cout << this->m_numberOfNets << std::endl;
    for (std::string input : m_inputNames)
    {
        std::cout << "input: " << input << std::endl;
    }
    for (std::string output : m_outputNames)
    {
        std::cout << "output: " << output << std::endl;
    }
    for (std::shared_ptr<Net> net : m_nets)
    {
        std::cout << "name: " << net->name() << " number: " << net->number() << std::endl;
    }
    for (auto gate : m_gates)
    {
        std::cout << "type: " << gate->typeAsString() << std::endl;
    }
}

void Netlist::readIOFromStream(std::ifstream &fs, std::set<std::string> *out)
{
    std::string line;
    std::string name;
    std::stringstream lineStream;
    std::getline(fs, line);

    lineStream << line;
    while (lineStream >> name)
        out->insert(name);
}

void Netlist::readNetsFromStream(std::ifstream &fs)
{
    std::string line;
    std::stringstream ls;
    std::string name;
    unsigned int number;
    
    m_nets.reserve(m_numberOfNets);
    for (unsigned int i = 1; i <= m_numberOfNets; ++i)
    {
        m_nets.push_back(std::make_shared<Net>(i));
    }
    
    while(std::getline(fs, line))
    {
        if (line.length() <= 1)
            break;
        ls << line;
        ls >> number;
        ls >> name;
        m_nets.at(number - 1)->setName(name);
        ls.clear();
    }
}

void Netlist::readGatesFromStream(std::ifstream &fs)
{
    // read gates
    std::shared_ptr<Gate> gate;
    std::vector<std::shared_ptr<Net>> ioNets;
    std::stringstream ls;
    std::string name;
    std::string line;
    int number;
    while (std::getline(fs, line))
    {
        gate = std::make_shared<Gate>();
        ls.clear();
        ls << line;
        ls >> name;

        if (name == "and")
            gate->setType(Gate::Type::AND);
        else if (name == "or")
            gate->setType(Gate::Type::OR);
        else if (name == "inv")
            gate->setType(Gate::Type::INV);
        else if (name == "xor")
            gate->setType(Gate::Type::XOR);
        else if (name == "zero")
            gate->setType(Gate::Type::ZERO);
        else if (name == "one")
            gate->setType(Gate::Type::ONE);
        else
            gate->setType(Gate::Type::UNKNOWN);


        while (ls >> number)
        {
            auto iter = std::find_if(m_nets.begin(), m_nets.end(),
                    [number](const std::shared_ptr<Net> &net) {
                        return net->number() == number ? true : false; 
                    });
            if (iter != std::end(m_nets))
            {
                ioNets.push_back(*iter);
            }
        }

        gate->setNets(ioNets);
        ioNets.clear();

        this->m_gates.push_back(gate);
    }
}

std::shared_ptr<ConjunctiveNormalForm> Netlist::cnf()
{
    std::shared_ptr<ConjunctiveNormalForm> cnf = std::make_shared<ConjunctiveNormalForm>();
    for (auto gate : m_gates)
    {
        cnf->addClausesFromCNF(gate->characteristicFunction());
    }
    return cnf;
}

unsigned int Netlist::numberOfNets()
{
    return m_numberOfNets;
}

std::set<std::string> Netlist::names()
{
    std::set<std::string> names;
    std::set_union(m_inputNames.begin(), m_inputNames.end(),
            m_outputNames.begin(), m_outputNames.end(),
            std::inserter(names, names.end()));
    return names;
}

std::set<std::string> Netlist::inputNames()
{
    return m_inputNames;
}

std::set<std::string> Netlist::outputNames()
{
    return m_outputNames;
}

std::vector<std::shared_ptr<Net>> Netlist::nets()
{
    return m_nets;
}

std::vector<std::shared_ptr<Net>> Netlist::inputNets()
{
    std::vector<std::shared_ptr<Net>> inputs;

    for (auto net : m_nets)
    {
        if (m_inputNames.find(net->name()) != m_inputNames.end())
            inputs.push_back(net);
    }
    return inputs;
}

std::vector<std::shared_ptr<Net>> Netlist::outputNets()
{
    std::vector<std::shared_ptr<Net>> outputs;

    for (auto net : m_nets)
    {
        if (m_outputNames.find(net->name()) != m_outputNames.end())
            outputs.push_back(net);
    }
    return outputs;
}

std::vector<std::shared_ptr<Net>> Netlist::internalNets()
{
    std::vector<std::shared_ptr<Net>> internals;

    for (auto net : m_nets)
    {
        if (net->name() == "undefined")
            internals.push_back(net);
    }
    return internals;
}

std::vector<std::shared_ptr<Gate>> Netlist::gates()
{
    return m_gates;
}
