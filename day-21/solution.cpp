#include <iostream>
#include <iomanip>
#include <vector>
#include <unordered_set>

using namespace std;

class CPU {
    vector<int> d_registers;

  public:
    CPU()
    : d_registers(6, 0)
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
   
    void setRegister(int r, int val)
    {
        d_registers[r] = val;
    }

    int getRegister(int i)
    {
        return d_registers[i];
    }

    const vector<int>& getRegisters() const
    {
        return d_registers;
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

    void executeCommand(int op, int A, int B, int C)
    {
        switch (op)
        {
            case 0:
                addr(A, B, C);
                break; 
            case 1:
                addi(A, B, C);
                break; 
            case 2:
                mulr(A, B, C);
                break; 
            case 3:
                muli(A, B, C);
                break; 
            case 4:
                banr(A, B, C);
                break; 
            case 5:
                bani(A, B, C);
                break; 
            case 6:
                borr(A, B, C);
                break; 
            case 7:
                bori(A, B, C);
                break; 
            case 8:
                setr(A, B, C);
                break; 
            case 9:
                seti(A, B, C);
                break; 
            case 10:
                gtir(A, B, C);
                break; 
            case 11:
                gtri(A, B, C);
                break; 
            case 12:
                gtrr(A, B, C);
                break; 
            case 13:
                eqir(A, B, C);
                break; 
            case 14:
                eqri(A, B, C);
                break; 
            case 15:
                eqrr(A, B, C);
                break; 
        }
    }

    void printCommand(const string& op, int A, int B, int C)
    {
        if (op == "addr") {
            cout << "[" << C<< "] = [" << A << "] + [" << B << "]";
        }
        else if (op == "addi") {
            cout << "[" << C<< "] = [" << A << "] + " << B << "";
        }
        else if (op == "mulr") {
            cout << "[" << C<< "] = [" << A << "] x [" << B << "]";
        }
        else if (op == "muli") {
            cout << "[" << C<< "] = [" << A << "] x " << B << "";
        }
        else if (op == "banr") {
            cout << "[" << C<< "] = [" << A << "] & [" << B << "]";
        }
        else if (op == "bani") {
            cout << "[" << C<< "] = [" << A << "] & " << B << "";
        }
        else if (op == "borr") {
            cout << "[" << C<< "] = [" << A << "] | [" << B << "]";
        }
        else if (op == "bori") {
            cout << "[" << C<< "] = [" << A << "] | " << B << "";
        }
        else if (op == "setr") {
            cout << "[" << C<< "] = [" << A << "]";
        }
        else if (op == "seti") {
            cout << "[" << C<< "] = " << A << "";
        }
        else if (op == "gtir") {
            cout << "[" << C<< "] = " << A << " > [" << B << "]";
        }
        else if (op == "gtri") {
            cout << "[" << C<< "] = [" << A << "] > " << B << "";
        }
        else if (op == "gtrr") {
            cout << "[" << C<< "] = [" << A << "] > [" << B << "]";
        }
        else if (op == "eqir") {
            cout << "[" << C<< "] = " << A << " == [" << B << "]";
        }
        else if (op == "eqri") {
            cout << "[" << C<< "] = [" << A << "] == " << B << "";
        }
        else if (op == "eqrr") {
            cout << "[" << C<< "] = [" << A << "] == [" << B << "]";
        }
    }
};

int optStrToInt(const string& op)
{
    if (op == "addr") {
        return 0; 
    }
    else if (op == "addi") {
        return 1;
    }
    else if (op == "mulr") {
        return 2;
    }
    else if (op == "muli") {
        return 3;
    }
    else if (op == "banr") {
        return 4;
    }
    else if (op == "bani") {
        return 5;
    }
    else if (op == "borr") {
        return 6;
    }
    else if (op == "bori") {
        return 7;
    }
    else if (op == "setr") {
        return 8;
    }
    else if (op == "seti") {
        return 9;
    }
    else if (op == "gtir") {
        return 10;
    }
    else if (op == "gtri") {
        return 11;
    }
    else if (op == "gtrr") {
        return 12;
    }
    else if (op == "eqir") {
        return 13;
    }
    else if (op == "eqri") {
        return 14;
    }
    else if (op == "eqrr") {
        return 15;
    }
    return -1; 
}

void printRegisters(const vector<int>& registers)
{
    for (int i : registers)
    {
        cout << i << " ";
    }
    cout << "\n";
}

struct Instruction {
    Instruction(int instruction, int a, int b, int c)
    : d_instruction(instruction), d_a(a), d_b(b), d_c(c)
    {
    }

    int d_instruction; 
    int d_a;
    int d_b; 
    int d_c;
};

int main(int argc, char* argv[])
{
    const bool VERBOSE = false;

    string firstWord;
    cin >> firstWord;

    int pc_reg = 0; 
    cin >> pc_reg;
    cout << "Setting program counter register to: " << pc_reg << "\n";

    vector<Instruction> instructions;
    string instruction;
    int a, b, c;
    while (cin >> instruction >> a >> b >> c)
    {
        instructions.emplace_back(optStrToInt(instruction), a, b, c);
    }

    unordered_set<int> seen;

    CPU cpu;
    cpu.setRegister(0, 0);
    int pc = 0;
    int previous = -1;

    while (true)
    {
        cpu.setRegister(pc_reg, pc);
        const auto& instr = instructions[pc];
        cpu.executeCommand(instr.d_instruction, instr.d_a, instr.d_b, instr.d_c);
        pc = cpu.getRegister(pc_reg) + 1;

        if (pc == 28)
        {
            const int y = cpu.getRegister(5);
            if (seen.empty())
            {
                cout << "Part I: " << y << "\n";
            }
            if (seen.find(y) != seen.end())
            {
                cout << "Part II: " << previous << "\n";
                return 0 ; 
            }
            else
            {
                seen.insert(y);
                previous = y;
            }
        }
    }

    return 0; 
}
