#include <iostream>
#include <vector>
#include <map>
#include <set>

using namespace std;

class CPU {
    // Registers
    vector<int> d_registers;

  public:
    CPU()
    : d_registers(4, 0)
    {
    }
    
    CPU(const vector<int>& registers)
    : d_registers(registers)
    {
    }

    void setRegisters(const vector<int>& registers)
    {
        d_registers = registers;
    }
    
    int getRegister(int i)
    {
        return d_registers[i];
    }

    bool checkRegisters(const vector<int>& registers) const
    {
        for (int i = 0; i < registers.size(); i++)
        {
            if (d_registers[i] != registers[i])
            {
                return false;
            }
        }
        return true;
    }

    // Addition
    // addr (add register) stores into register C the result of adding register
    // A and register B.
    void addr(int A, int B, int C)
    {
        d_registers[C] = d_registers[A] + d_registers[B];
    }

    // addi (add immediate) stores into register C the result of adding
    // register A and value B.
    void addi(int A, int B, int C)
    {
        d_registers[C] = d_registers[A] + B;
    }

    // Multiplication
    // mulr (multiply register) stores into register C the result of
    // multiplying register A and register B.
    void mulr(int A, int B, int C)
    {
        d_registers[C] = d_registers[A] * d_registers[B];
    }

    // muli (multiply immediate) stores into register C the result of
    // multiplying register A and value B.
    void muli(int A, int B, int C)
    {
        d_registers[C] = d_registers[A] * B;
    }

    // Bitwise AND:
    // banr (bitwise AND register) stores into register C the result of the
    // bitwise AND of register A and register B.
    void banr(int A, int B, int C)
    {
        d_registers[C] = d_registers[A] & d_registers[B];
    }

    // bani (bitwise AND immediate) stores into register C the result of the
    // bitwise AND of register A and value B.
    void bani(int A, int B, int C)
    {
        d_registers[C] = d_registers[A] & B;
    }

    // Bitwise OR
    // borr (bitwise OR register) stores into register C the result of the bitwise OR of register A and register B.
    void borr(int A, int B, int C)
    {
        d_registers[C] = d_registers[A] | d_registers[B]; 
    }

    // bori (bitwise OR immediate) stores into register C the result of the bitwise OR of register A and value B.
    void bori(int A, int B, int C)
    {
        d_registers[C] = d_registers[A] | B; 
    }

    // Assignment
    // setr (set register) copies the contents of register A into register C.
    // (Input B is ignored.)
    void setr(int A, int B, int C)
    {
        d_registers[C] = d_registers[A];
    }

    // seti (set immediate) stores value A into register C. (Input B is
    // ignored.)
    void seti(int A, int B, int C)
    {
        d_registers[C] = A;
    }

    // Greater-than testing
    // gtir (greater-than immediate/register) sets register C to 1 if value A
    // is greater than register B. Otherwise, register C is set to 0.
    void gtir(int A, int B, int C)
    {
        d_registers[C] = A > d_registers[B] ? 1 : 0; 
    }

    // gtri (greater-than register/immediate) sets register C to 1 if register
    // A is greater than value B. Otherwise, register C is set to 0.
    void gtri(int A, int B, int C)
    {
        d_registers[C] = d_registers[A] > B ? 1 : 0;
    }

    // gtrr (greater-than register/register) sets register C to 1 if register A
    // is greater than register B. Otherwise, register C is set to 0.
    void gtrr(int A, int B, int C)
    {
        d_registers[C] = d_registers[A] > d_registers[B] ? 1 : 0; 
    }

    // Equality testing
    //eqir (equal immediate/register) sets register C to 1 if value A is equal
    //to register B. Otherwise, register C is set to 0.
    void eqir(int A, int B, int C)
    {
        d_registers[C] = A == d_registers[B] ? 1 : 0; 
    }

    //eqri (equal register/immediate) sets register C to 1 if register A is
    //equal to value B. Otherwise, register C is set to 0.
    void eqri(int A, int B, int C)
    {
        d_registers[C] = d_registers[A] == B ? 1 : 0;
    }

    //eqrr (equal register/register) sets register C to 1 if register A is
    //equal to register B. Otherwise, register C is set to 0.
    void eqrr(int A, int B, int C)
    {
        d_registers[C] = d_registers[A] == d_registers[B] ? 1 : 0; 
    }

    void executeCommand(const string& op, int A, int B, int C)
    {
        if (op == "addr") {
            addr(A, B, C);
        }
        else if (op == "addi") {
            addi(A, B, C);
        }
        else if (op == "mulr") {
            mulr(A, B, C);
        }
        else if (op == "muli") {
            muli(A, B, C);
        }
        else if (op == "banr") {
            banr(A, B, C);
        }
        else if (op == "bani") {
            bani(A, B, C);
        }
        else if (op == "borr") {
            borr(A, B, C);
        }
        else if (op == "bori") {
            bori(A, B, C);
        }
        else if (op == "setr") {
            setr(A, B, C);
        }
        else if (op == "seti") {
            seti(A, B, C);
        }
        else if (op == "gtir") {
            gtir(A, B, C);
        }
        else if (op == "gtri") {
            gtri(A, B, C);
        }
        else if (op == "gtrr") {
            gtrr(A, B, C);
        }
        else if (op == "eqir") {
            eqir(A, B, C);
        }
        else if (op == "eqri") {
            eqri(A, B, C);
        }
        else if (op == "eqrr") {
            eqrr(A, B, C);
        }
    }
};


int main(int argc, char* argv[])
{
    const bool VERBOSE = false;
    int total = 0; 
    int count = 0;

    const vector<string> opCodes({
        "addr", "addi", "mulr", "muli", "banr", "bani", "borr", "bori", 
        "setr", "seti", "gtir", "gtri", "gtrr", "eqir", "eqri", "eqrr",
    });

    map<int, set<string>> possibleOpcodes;
    for (int i = 0; i < opCodes.size(); i++)
    {
        for (const string& opCode : opCodes)
        {
            possibleOpcodes[i].insert(opCode);
        }
    }

    string line;
    while (true)
    {
        char s[200];
        int a, b, c, d;
        scanf("%s [%d, %d, %d, %d]", s, &a, &b, &c, &d);
        if (VERBOSE)
        {
            cout << s << a << b << c << d << "\n";
        }

        // Note: I decided to modify my input to make the parsing a tiny bit simpler
        if (string(s) == "STOP")
        {
            break; 
        }

        int op, x, y, z;
        scanf("%d %d %d %d", &op, &x, &y, &z);
        if (VERBOSE)
        {
            cout << op << x << y << z << "\n";
        }
    
        int e, f, g, h;
        scanf("%s [%d, %d, %d, %d]", s, &e, &f, &g, &h);
        if (VERBOSE)
        {
            cout << s << e << f << g << h << "\n";
        }
    
        int sum = 0;

        CPU cpu;

        for (const string& opCode : opCodes) { 
            cpu.setRegisters({a, b, c, d});
            cpu.executeCommand(opCode, x, y, z);
            if (!cpu.checkRegisters({e, f, g, h}))
            {
                possibleOpcodes[op].erase(opCode);
            }
        }

        if (sum >= 3)
        {
            count++;
        }
        total++;
    }

    map<int, string> actualOpCodes;

    while (true)
    {
        for (int i = 0; i < opCodes.size(); i++)
        {
            if (possibleOpcodes[i].size() == 1)
            {
                const string erasing  =  *possibleOpcodes[i].begin();
                actualOpCodes[i] = erasing;
                for (int j = 0; j < opCodes.size(); j++)
                {
                    possibleOpcodes[j].erase(erasing);
                }
                break;
            }
        }
        bool allEmpty = true;
        for (int i = 0; i < opCodes.size(); i++)
        {
            if (!possibleOpcodes[i].empty())
            {
                allEmpty = false;
            }
        }
        if (allEmpty)
        {
            break;
        }
    }

    CPU cpu;
    while (true)
    {
        int op, a, b, c;
        if (!(cin >> op >> a >> b >> c))
        {
            break;
        }
        cpu.executeCommand(actualOpCodes[op], a, b ,c);
    }

    cout << "Answer: " << cpu.getRegister(0) << "\n";
    return 0;
}
