#ifndef NETLIST_H_
#define NETLIST_H_

#include "Net.h"
#include "Gate.h"

#include <string>
#include <vector>
#include <map>

class Netlist
{
    public:
        Netlist();
        ~Netlist();

        void readFromFile(std::string file);
    private:
        std::vector<std::string> readIOFromLine(std::string line);
        int m_numberOfNets;
        std::vector<std::string> m_inputNames;
        std::vector<std::string> m_outputNames;
       
        std::map<int, Net> m_nets;

        std::vector<Gate> m_gates;
};

#endif /* NETLIST_H_ */
