#ifndef NETLIST_H_
#define NETLIST_H_

#include "Net.h"
#include "Gate.h"
#include "ConjunctiveNormalForm.h"

#include <string>
#include <vector>
#include <memory>

class Netlist
{
    public:
        Netlist();
        explicit Netlist(std::string file);
        ~Netlist();

        void readFromFile(std::string file);
        ConjunctiveNormalForm cnf();

    private:
        void readIOFromStream(std::ifstream &fs, std::vector<std::string> *out);
        void readNetsFromStream(std::ifstream &fs);
        void readGatesFromStream(std::ifstream &fs);
        unsigned int m_numberOfNets;
        std::vector<std::string> m_inputNames;
        std::vector<std::string> m_outputNames;
        std::vector<std::shared_ptr<Net>> m_nets;
        std::vector<Gate> m_gates;
};

#endif /* NETLIST_H_ */
