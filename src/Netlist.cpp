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

    //// debug output
    //std::cout << this->m_numberOfNets << std::endl;
    //for (std::string input : m_inputNames)
    //{
    //    std::cout << "input: " << input << std::endl;
    //}
    //for (std::string output : m_outputNames)
    //{
    //    std::cout << "output: " << output << std::endl;
    //}
    //for (std::shared_ptr<Net> net : m_nets)
    //{
    //    std::cout << "name: " << net->name() << " number: " << net->number() << std::endl;
    //}
    //for (Gate gate : m_gates)
    //{
    //    std::cout << "type: " << gate.typeAsString() << std::endl;
    //}
}

void Netlist::readIOFromStream(std::ifstream &fs, std::vector<std::string> *out)
{
    std::string line;
    std::string name;
    std::stringstream lineStream;
    std::getline(fs, line);

    lineStream << line;
    while (lineStream >> name)
        out->push_back(name);
}

void Netlist::readNetsFromStream(std::ifstream &fs)
{
    std::string line;
    std::stringstream ls;
    std::string name;
    unsigned int number;
    bool read = true;
    
    for (unsigned int i = 1; i <= m_numberOfNets; ++i)
    {
        if (read)
        {
            std::getline(fs, line);
            ls << line;
            ls >> number;
            ls >> name;
            read = false;
        }
        if (!read && number == i)
        {
            m_nets.push_back(std::make_shared<Net>(number, name));
            ls.clear();
            name.clear();
            number = 0;
            if (line.length() == 0)
                read = false; 
            else
                read = true;
            continue;
        }
        m_nets.push_back(std::make_shared<Net>(i));
    }
}

void Netlist::readGatesFromStream(std::ifstream &fs)
{
    // read gates
    Gate gate;
    std::vector<std::shared_ptr<Net>> ioNets;
    std::stringstream ls;
    std::string name;
    std::string line;
    int number;
    while (std::getline(fs, line))
    {
        ls.clear();
        ls << line;
        ls >> name;

        if (name == "and")
            gate.setType(Gate::Type::AND);
        else if (name == "or")
            gate.setType(Gate::Type::OR);
        else if (name == "inv")
            gate.setType(Gate::Type::INV);
        else if (name == "xor")
            gate.setType(Gate::Type::XOR);
        else if (name == "zero")
            gate.setType(Gate::Type::ZERO);
        else if (name == "one")
            gate.setType(Gate::Type::ONE);
        else
            gate.setType(Gate::Type::UNKNOWN);

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

        gate.setNets(ioNets);
        ioNets.clear();

        this->m_gates.push_back(gate);
    }
}

ConjunctiveNormalForm Netlist::cnf()
{
    ConjunctiveNormalForm cnf;
    for (Gate gate : m_gates)
    {
        cnf.addClausesFromCNF(gate.characteristicFunction());
    }
    return cnf;
}
