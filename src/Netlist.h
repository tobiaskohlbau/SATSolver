#ifndef NETLIST_H_
#define NETLIST_H_

#include "Net.h"
#include "Gate.h"
#include "ConjunctiveNormalForm.h"

#include <string>
#include <vector>
#include <set>
#include <memory>

class Netlist
{
    public:
        Netlist();
        Netlist(unsigned int numberOfNets, std::set<std::string> inputNames, std::set<std::string> outputNames,
                std::vector<std::shared_ptr<Net>> nets, std::vector<std::shared_ptr<Gate>> gates);
        explicit Netlist(std::string file);
        ~Netlist();

        void readFromFile(std::string file);
        std::shared_ptr<ConjunctiveNormalForm> cnf();

        unsigned int numberOfNets();

        std::set<std::string> names();
        std::set<std::string> inputNames();
        std::set<std::string> outputNames();
        std::vector<std::shared_ptr<Net>> nets();
        std::vector<std::shared_ptr<Net>> inputNets();
        std::vector<std::shared_ptr<Net>> outputNets();
        std::vector<std::shared_ptr<Net>> internalNets();
        std::vector<std::shared_ptr<Gate>> gates();
    private:
        void readIOFromStream(std::ifstream &fs, std::set<std::string> *out);
        void readNetsFromStream(std::ifstream &fs);
        void readGatesFromStream(std::ifstream &fs);
        unsigned int m_numberOfNets;
        std::set<std::string> m_inputNames;
        std::set<std::string> m_outputNames;
        std::vector<std::shared_ptr<Net>> m_nets;
        std::vector<std::shared_ptr<Gate>> m_gates;
};

#endif /* NETLIST_H_ */
