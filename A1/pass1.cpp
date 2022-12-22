#include <bits/stdc++.h>
using namespace std;

struct OPTAB
{
    string opcode, mclass, mnemonic;
};

OPTAB OP[18]{
    {"STOP", "IS", "00"},
    {"ADD", "IS", "01"},
    {"SUB", "IS", "02"},
    {"MULT", "IS", "03"},
    {"MOVER", "IS", "04"},
    {"MOVEM", "IS", "05"},
    {"COMP", "IS", "06"},
    {"BC", "IS", "07"},
    {"DIV", "IS", "08"},
    {"READ", "IS", "09"},
    {"PRINT", "IS", "10"},
    {"START", "AD", "01"},
    {"END", "AD", "02"},
    {"ORIGIN", "AD", "03"},
    {"EQU", "AD", "04"},
    {"LTORG", "AD", "05"},
    {"DC", "DL", "01"},
    {"DS", "DL", "02"},
};

struct SYMTAB
{
    int no;
    string sname, addr;
};

SYMTAB ST[10];

struct LITTAB
{
    int no;
    string lname, addr;
};

LITTAB LT[10];

struct POOLTAB
{
    int no;
    string lno;
};

POOLTAB PT[10];

bool presentST(string name)
{
    for (int i = 0; i < 10; i++)
    {
        if (ST[i].sname == name)
        {
            return true;
        }
    }
    return false;
}

int getSTId(string name)
{
    for (int i = 0; i < 10; i++)
    {
        if (ST[i].sname == name)
        {
            return i; // i or no
        }
    }
    return -1;
}

bool presentLT(string name)
{
    for (int i = 0; i < 10; i++)
    {
        if (LT[i].lname == name)
        {
            return true;
        }
    }
    return false;
}

int getLTId(string name)
{
    for (int i = 0; i < 10; i++)
    {
        if (LT[i].lname == name)
        {
            return i; // i or no
        }
    }
    return -1;
}

string getOPClass(string op)
{
    for (int i = 0; i < 18; i++)
    {
        if (OP[i].opcode == op)
        {
            return OP[i].mclass;
        }
    }
    return "-1";
}

string getOPCode(string op)
{
    for (int i = 0; i < 18; i++)
    {
        if (OP[i].opcode == op)
        {
            return OP[i].mnemonic;
        }
    }
    return "-1";
}

int getRegId(string name)
{
    if (name == "AREG")
        return 1;
    if (name == "BREG")
        return 2;
    if (name == "CREG")
        return 3;
    if (name == "DREG")
        return 4;
    return -1;
}

int getCondCode(string name)
{
    if (name == "LT")
        return 1;
    if (name == "LE")
        return 2;
    if (name == "EQ")
        return 3;
    if (name == "GT")
        return 4;
    if (name == "GE")
        return 5;
    if (name == "ANY")
        return 6;
    return -1;
}

int main()
{
    ifstream fin;
    fin.open("input.txt");

    ofstream ic, lt, st, pt;
    ic.open("ic.txt");
    lt.open("littab.txt");
    st.open("symtab.txt");
    pt.open("pooltab.txt");

    string label, opcode, op1, op2, lc, IC = "";
    int LC = 0, scnt = 0, lcnt = 0, pcnt = 0, nlcnt = 0;

    while (!fin.eof())
    {
        fin >> label >> opcode >> op1 >> op2;
        IC = "(" + getOPClass(opcode) + "," + getOPCode(opcode) + ")    ";

        if (opcode == "START")
        {
            lc = "---";

            if (op1 != "NAN")
            {
                LC = stoi(op1);
                IC += "(C," + op1 + ")  NAN";
            }
            else
            {
                IC += "NAN  NAN";
            }
        }

        if (opcode == "EQU" && label != "NAN")
        {
            lc = "---";
            IC += "  NAN    NAN";

            if (presentST(label))
            {
                ST[getSTId(label)].addr = ST[getSTId(op1)].addr;
            }
            else
            {
                ST[scnt].no = scnt + 1;
                ST[scnt].sname = label;
                ST[scnt].addr = ST[getSTId(op1)].addr;
                scnt++;
            }
        }
        else if (label != "NAN")
        {
            if (presentST(label))
            {
                ST[getSTId(label)].addr = to_string(LC);
            }
            else
            {
                ST[scnt].no = scnt + 1;
                ST[scnt].sname = label;
                ST[scnt].addr = to_string(LC);
                scnt++;
            }
        }

        if (opcode == "ORIGIN")
        {
            lc = "---";
            // IC += " NAN  NAN";

            char op;
            if (op1.find('+') != string::npos)
            {
                op = '+';
            }
            else
            {
                op = '-';
            }

            int i = 0;
            string token1 = "", token2 = "";
            for (i = 0; i < op1.length(); i++)
            {
                if (op1[i] == op)
                    break;
                token1 += op1[i];
            }
            for (i = i + 1; i < op1.length(); i++)
            {
                token2 += op1[i];
            }

            if (op == '+')
            {
                LC = stoi(ST[getSTId(token1)].addr) + stoi(token2);
            }
            else
            {
                LC = stoi(ST[getSTId(token1)].addr) - stoi(token2);
            }
            IC += "(S,0" + to_string(getSTId(token1)) + ")" + op + token2;
        }

        if (opcode == "LTORG")
        {
            lc = "---";
            cout << label << "\t" << opcode << "\t" << op1 << "\t" << op2 << "\t";

            for (int i = lcnt - nlcnt; i < lcnt; i++)
            {
                lc = to_string(LC);
                LC++;
                string c(1, LT[i].lname[2]);
                IC = "(DL,01)   (C," + c + ")   NAN";
                LT[i].addr = lc;

                if (i != lcnt - 1)
                {
                    cout << lc << "\t" << IC << "\n\t\t\t\t";
                }
                else
                {
                    cout << lc << "\t" << IC << "\n";
                }

                ic << lc << "\t" << IC << "\n";
            }

            PT[pcnt].no = pcnt + 1;
            PT[pcnt].lno = "#" + to_string(LT[lcnt - nlcnt].no);
            pcnt++;
            nlcnt = 0;
            continue;
        }

        if (opcode == "END")
        {
            lc = "---";
            IC += "  NAN    NAN";

            cout << label << "\t" << opcode << "\t" << op1 << "\t" << op2 << "\t" << lc << "\t" << IC << "\n\t\t\t\t";
            ic << lc << "\t" << IC << "\n";

            if (nlcnt)
            {
                for (int i = lcnt - nlcnt; i < lcnt; i++)
                {
                    lc = to_string(LC);
                    LC++;

                    string c(1, LT[i].lname[2]);
                    IC = "(DL,01)    (C," + c + ")  NAN";

                    LT[i].addr = lc;

                    if (i != lcnt - 1)
                    {
                        cout << lc << "\t" << IC << "\n\t\t\t\t";
                    }
                    else
                    {
                        cout << lc << "\t" << IC << "\n";
                    }
                    ic << lc << "\t" << IC << "\n";
                }

                PT[pcnt].no = pcnt + 1;
                PT[pcnt].lno = "#" + to_string(LT[lcnt - nlcnt].no);
                pcnt++;
                nlcnt = 0;
            }
            break;
        }

        if (opcode == "DC" || opcode == "DS")
        {
            lc = to_string(LC);

            if (opcode == "DC")
            {
                IC += "(C," + to_string(op1[1]) + ")  NAN";
                LC++;
            }
            else
            {
                IC += "(C," + op1 + ")  NAN";
                LC += stoi(op1);
            }
        }

        if (opcode != "START" && opcode != "EQU" && opcode != "END" && opcode != "ORIGIN" && opcode != "LTORG" && opcode != "DS" && opcode != "DC")
        {
            lc = to_string(LC);
            LC++;

            if (op2 == "NAN")
            {
                if (op1 == "NAN")
                {
                    IC += "   NAN     NAN";
                }
                else
                {
                    if (presentST(op1))
                    {
                        IC += "(S,0" + to_string(ST[getSTId(op1)].no) + ")  NAN";
                    }
                    else
                    {
                        ST[scnt].no = scnt + 1;
                        ST[scnt].sname = op1;
                        ST[scnt].addr = lc;
                        scnt++;
                        IC += "(S,0" + to_string(ST[getSTId(op1)].no) + ")  NAN";
                    }
                }
            }
            else
            {
                if (opcode == "BC")
                {
                    IC += " (" + to_string(getCondCode(op1)) + ")    ";
                }
                else
                {
                    IC += " (" + to_string(getRegId(op1)) + ")   ";
                }

                if (op2[0] == '=')
                {
                    LT[lcnt].no = lcnt + 1;
                    LT[lcnt].lname = op2;
                    lcnt++;
                    nlcnt++;
                    IC += "(L,0" + to_string(LT[getLTId(op2)].no) + ")  ";
                }
                else
                {
                    if (presentST(op2))
                    {
                        // if present only process ic hence done after if else
                    }
                    else
                    {
                        ST[scnt].no = scnt + 1;
                        ST[scnt].sname = op2;
                        // ST[scnt].addr = to_string(LC);
                        scnt++;
                    }
                    // cout << label << " " << to_string(LC) << "\n";

                    IC += "(S,0" + to_string(ST[getSTId(op2)].no) + ")  ";
                }
            }
        }

        cout << label << "\t" << opcode << "\t" << op1 << "\t" << op2 << "\t" << lc << "\t" << IC << "\n";
        ic << lc << "\t" << IC << "\n";
    }

    cout << "\n---------------------------------------------------------------------\n";
    cout << "------------SYMBOL TABLE---------------\n";
    cout << "\nNO\tSYMBOL\tADDRESS\n";
    for (int i = 0; i < scnt; i++)
    {
        cout << "  " << ST[i].no << "\t" << ST[i].sname << "\t" << ST[i].addr << "\n";
        st << ST[i].no << "\t" << ST[i].sname << "\t" << ST[i].addr << "\n";
    }
    cout << "\n---------------------------------------------------------------------\n";
    cout << "------------LITERAL TABLE---------------\n";
    cout << "\nNO\tSYMBOL\tADDRESS\n";
    for (int i = 0; i < lcnt; i++)
    {
        cout << "  " << LT[i].no << "\t" << LT[i].lname << "\t" << LT[i].addr << "\n";
        lt << LT[i].no << "\t" << LT[i].lname << "\t" << LT[i].addr << "\n";
    }
    cout << "\n---------------------------------------------------------------------\n";
    cout << "------------POOL TABLE---------------\n";
    cout << "\nNO\tLITERAL NO\n";
    for (int i = 0; i < pcnt; i++)
    {
        cout << "  " << PT[i].no << "\t" << PT[i].lno << "\n";
        pt << PT[i].no << "\t" << PT[i].lno << "\n";
    }
    return 0;
}