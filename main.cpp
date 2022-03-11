#include <iostream> 
#include "SimpleComputer.h"

int main()
{
    int value;
    sc_memoryInit();
    sc_memorySet(1, 5);
    sc_memorySet(2, 4);
    sc_memorySet(3, 3);
    sc_memorySet(4, 2);
    sc_memorySet(5, 1);
    for (int i = 0; i < 5; i++)
    {
        sc_memoryGet(i + 1, &value);
        std::cout << "RAM[" << i + 1 << "] = " << value << "\n";
    }
    sc_memorySave("test.bin");
    std::cout << "Save file" << "\n";
    sc_memorySet(1, 15);
    sc_memoryGet(1, &value);
    std::cout << "RAM[" << 1 << "] = " << value << "\n";
    sc_memoryLoad("test.bin");
    std::cout << "Load file" << "\n";
    for (int i = 0; i < 5; i++)
    {
        sc_memoryGet(i + 1, &value);
        std::cout << "RAM[" << i + 1 << "] = " << value << "\n";
    }

    std::cout << "\n\n";
    sc_regInit();
    sc_regSet(IGNORING_TACT_PULSE, 1);

    sc_regGet(OVERFLOW, &value);
    std::cout << "FLAG \"OVERFLOW\": " << value << "\n";
    sc_regGet(DIVISION_BY_ZERO, &value);
    std::cout << "FLAG \"DIVISION BY ZERO \": " << value << "\n";
    sc_regGet(OUT_OF_MEMORY, &value);
    std::cout << "FLAG \"OUT OF MEMORY\": " << value << "\n";
    sc_regGet(IGNORING_TACT_PULSE, &value);
    std::cout << "FLAG \"IGNORING TACT PULSE\": " << value << "\n";
    sc_regGet(INCORRECT_COMMAND, &value);
    std::cout << "FLAG \"INCORRECT COMMAND\": " << value << "\n";

    std::cout << "\n\n";
    int f = 0, f_c = 0, f_o = 0;
    sc_commandEncode(0x33, 0x59, &f);
    std::cout << "Encoded command: " << f << "\n";
    sc_commandDecode(f, &f_c, &f_o);
    std::cout << "Command: " << std::hex << f_c << "   Operand: " << std::hex << f_o << "\n";
    return 0;
}
