#include "Clause.h"
#include "Netlist.h"

int main(int argc, char **arv)
{
    Literal *tmpLiteral = new Literal(1, true, -1);

    Netlist *netlist = new Netlist();

    netlist->readFromFile("/home/tobias/edat/netlists/adder4.net");
}
