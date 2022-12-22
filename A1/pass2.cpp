#include <bits/stdc++.h>
using namespace std;

string getAddr(ifstream &fin, string n)
{
    string no, name, addr;
    while (!fin.eof())
    {
        fin >> no >> name >> addr;
        if (no == n)
        {
            fin.seekg(0, ios::beg);
            return addr;
        }
    }
    fin.seekg(0, ios::beg);
    return "NAN";
}

int main()
{
    ifstream ic, st, lt;
    ic.open("ic.txt");
    st.open("symtab.txt");
    lt.open("littab.txt");

    ofstream mct;
    mct.open("machine.txt");

    string lc, opcode, op1, op2, mc = "";

    cout << "\nLC\tOPCODE\tOP1\t\tOP2\t\tMC\n\n";

    while (!ic.eof())
    {
        ic >> lc >> opcode >> op1 >> op2;

        if (opcode.substr(1, 2) == "AD" || (opcode.substr(1, 2) == "DL" && opcode.substr(4, 2) == "02"))
        {
            mc = "-----No machine code-----";
        }
        else if (opcode.substr(1, 2) == "DL")
        {
            mc = "00\t0\t00" + op1.substr(3, 1);
        }
        else
        {
            if (op2 == "NAN")
            {
                if (op1 == "NAN")
                {
                    mc = opcode.substr(4, 2) + "\t0\t000";
                }
                else
                {
                    mc = opcode.substr(4, 2) + "\t" + getAddr(st, op1.substr(3, 1)) + "\t000";
                }
            }
            else
            {
                if (op2.substr(1, 1) == "L")
                {
                    mc = opcode.substr(4, 2) + "\t" + op1.substr(1, 1) + "\t" + getAddr(lt, op2.substr(4, 1));
                }
                else
                {
                    mc = opcode.substr(4, 2) + "\t" + op1.substr(1, 1) + "\t" + getAddr(st, op2.substr(4, 1));
                }
            }
        }
        cout << lc << "\t" << opcode << "\t" << op1 << "\t\t" << op2 << "\t" << mc << "\n";
        mct << lc << "\t" << mc << "\n";
    }
}