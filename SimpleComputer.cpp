#include "SimpleComputer.h"

int sc_memoryInit()
{
    for (int i = 0; i < MEMORY_SIZE; i++)
    {
        memory[i] = 0;
    }
    return 0;
}

int sc_memorySet(int address, int value)
{
    try
    {
        if (address < 0 || address >= MEMORY_SIZE)
        {
            throw std::overflow_error("ERROR\tout of memory !");
        }
        memory[address] = value;
        return 0;
    }
    catch (std::overflow_error err)
    {
        sc_regSet(OUT_OF_MEMORY, 1);
        std::cout << err.what() << std::endl;
        return 1;
    }
}

int sc_memoryGet(int address, int* value)
{
    try
    {
        if (address < 0 || address >= MEMORY_SIZE)
        {
            throw std::overflow_error("ERROR\tout of memory !");
        }
        *value = memory[address];
        return 0;
    }
    catch (std::overflow_error err)
    {
        sc_regSet(OUT_OF_MEMORY, 1);
        std::cout << err.what() << std::endl;
        return 1;
    }
}

int sc_memorySave(const std::string& filename)
{
    std::ofstream out(filename, std::ios::binary | std::ios::out);
    try
    {
        if (!out.is_open())
        {
            throw std::runtime_error("ERROR\tНе удалось открыть файл \'" + filename + "\'");
        }
        out.write((char*)&(memory), sizeof(memory));
        out.close();
        return 0;
    }
    catch (std::runtime_error err)
    {
        std::cout << err.what() << std::endl;
        return 1;
    }
}

int sc_memoryLoad(const std::string& filename)
{
    std::ifstream in(filename, std::ios::binary | std::ios::in);
    try
    {
        if (!in.is_open())
        {
            throw std::runtime_error("ERROR\tНе удалось открыть файл \'" + filename + "\'");
        }
        in.read((char*)&(memory), sizeof(memory));
        in.close();
        return 0;
    }
    catch (std::runtime_error err) {
        std::cout << err.what() << std::endl;
        return 1;
    }
}

int sc_regInit()
{
    regFLAGS = 0;
    return 0;
}

int sc_regSet(int reg, int value)
{
    if(reg > 0)
    try
    {
        if (reg < 0 || reg >= REGISTER_SIZE)
            throw std::overflow_error("ERROR\tInvalid Register");
        if (value != 0 && value != 1)
            throw std::invalid_argument("ERROR\tIncorrect value, Correct: 0, 1 ");
        value == 1 ? (regFLAGS |= (1 << reg)) : (regFLAGS &= ~(1 << reg));
        return 0;
    }
    catch (std::exception err)
    {
        std::cout << err.what() << std::endl;
        return 1;
    }
}

int sc_regGet(int reg, int* value)
{
    try
    {
        if (reg < 0 || reg >= REGISTER_SIZE)
            throw std::overflow_error("ERROR\tInvalid Register");
        (REGISTER_SIZE & (1 << reg)) ? *value = 1 : *value = 0;
        return 0;
    }
    catch (std::overflow_error err)
    {
        std::cout << err.what() << std::endl;
        return 1;
    }
}

int sc_commandEncode(int command, int operand, int* value)
{
    try
    {
        if (command  < 0  || command >= 128)
            throw std::invalid_argument("ERROR\tinvalid Argument");
        if ((operand < 0) || (operand >= 128))
            throw std::invalid_argument("ERROR\tinvalid Argument");
        *value = 0;
        /* Операнд */
        for (int i = 0; i < 7; i++)
        {
            int bit = (operand >> i) & 1;
            *value |= (bit << i);
        }
        /* Команда */
        for (int i = 0; i < 7; i++)
        {
            int8_t bit = (command >> i) & 1;
            *value |= (bit << (i + 7));
        }
        return 0;
    }
    catch (std::invalid_argument err)
    {
        sc_regSet(INCORRECT_COMMAND, 1);
        std::cout << err.what() << std::endl;
        return 1;
    }
}

int sc_commandDecode(int value, int* command, int* operand)
{
    try
    {
        int tmpCom = 0, tmpOp = 0;
        if ((value >> 14) & 1)
            throw std::invalid_argument("ERROR\tInvalid Command");

        for (int i = 0; i < 7; i++) 
        {
            int bit = (value >> i) & 1;
            tmpOp |= (bit << i);
        }

        for (int i = 0; i < 7; i++)
        {
            int bit = (value >> (i + 7)) & 1;
            tmpCom |= (bit << i);
        }

        if (!(tmpCom > 0x9 && tmpCom < 0x12) && !(tmpCom > 0x19 && tmpCom < 0x22) && !(tmpCom > 0x29 && tmpCom < 0x34) && !(tmpCom > 0x39 && tmpCom < 0x77))
            throw std::invalid_argument("ERROR\tFailed to decode Command");
        if ((tmpOp < 0) || (tmpOp >= 128))
            throw std::invalid_argument("ERROR\tFailed to decode Operand ");

        *command = tmpCom;
        *operand = tmpOp;
        return 0;
    }
    catch (std::invalid_argument err) {
        sc_regSet(INCORRECT_COMMAND, 1);
        std::cout << err.what() << std::endl;
        return 1;
    }
}
