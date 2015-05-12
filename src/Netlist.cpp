#include "Netlist.h"

#include <fstream>
#include <iostream>
#include <sstream>

Netlist::Netlist()
{
}

Netlist::~Netlist()
{
}

void Netlist::readFromFile(std::string fileName)
{
    std::ifstream fileStream(fileName);
    if (! fileStream.is_open())
        return;

    std::string tmp;

    std::getline(fileStream, tmp);

    // read number of nets and create Net array
    this->m_numberOfNets = std::stoi(tmp);

    // read inputs
    std::getline(fileStream, tmp);
    this->m_inputNames = this->readIOFromLine(tmp);
   
    // read outputs
    std::getline(fileStream, tmp);
    this->m_outputNames = this->readIOFromLine(tmp);

    // read mappings
    std::stringstream tmpStream;
    int tmpNumber;
    std::string tmpName;
    for (unsigned int i = 0; i < (m_inputNames.size() + m_outputNames.size()); ++i)
    {
        std::getline(fileStream, tmp);
        tmpStream.str(tmp);
        tmpStream.clear();
        tmpStream >> tmpNumber;
        tmpStream >> tmpName;

        m_nets[tmpNumber] = Net(tmpNumber, tmpName);

    }
    
    // read empty line
    std::getline(fileStream, tmp);
    if (tmp.length() > 1)
        return;

    // read gates
    Gate tmpGate;
    std::vector<Net> ioNets;
    while (std::getline(fileStream, tmp))
    {
        tmpStream.str(tmp);
        tmpStream.clear();
        tmpStream >> tmpName;

        std::cout << tmpName << std::endl;

        if (tmpName == "and")
            tmpGate.setType(Gate::Type::AND);

        while (tmpStream >> tmpNumber)
        {
            ioNets.push_back(m_nets[tmpNumber]); 
        }

        tmpGate.setIONets(ioNets);

        this->m_gates.push_back(tmpGate);
    }

    fileStream.close();

    // debug output
    std::cout << this->m_numberOfNets << std::endl;
    for (std::string input : m_inputNames)
    {
        std::cout << input << std::endl;
    }
    for (std::string output : m_outputNames)
    {
        std::cout << output << std::endl;
    }
    for (unsigned int i = 0; i < (m_inputNames.size() + m_outputNames.size()); ++i)
    {
        std::cout << m_nets[i].name();
    }
}

std::vector<std::string> Netlist::readIOFromLine(std::string line)
{
    std::stringstream lineStream(line);
    std::string tmp;
    std::vector<std::string> io;

    while (lineStream >> tmp)
    {
        io.push_back(tmp);
    }

    return io;
}
