#include "MyUI.h"

int instructionCounter;


/// ��������� "������"
/// \return 0 - � ������ ��������� ����������, -1 - � ������ ������
int drawingBoxes() {
    if (bc_box(1, 1, 61, 12)) // ���� Memory
        return -1;
    if (bc_box(62, 1, 22, 3)) // ���� accumulator
        return -1;
    if (bc_box(62, 4, 22, 3)) // ���� instructionCounter
        return -1;
    if (bc_box(62, 7, 22, 3)) // ���� Operation
        return -1;
    if (bc_box(62, 10, 22, 3)) // ���� Flags
        return -1;
    if (bc_box(1, 13, 52, 10)) // ���� BigChars
        return -1;
    if (bc_box(53, 13, 31, 10)) // ���� Keys
        return -1;

    return 0;
}

/// ��������� ���������� � ������
/// \return 0 - � ������ ��������� ����������, -1 - � ������ ������
int drawingTexts() {
    /* ��������� */
    mt_gotoXY(30, 1);
    printf(" Memory ");
    mt_gotoXY(66, 1);
    printf(" accumulator ");
    mt_gotoXY(63, 4);
    printf(" instructionCounter ");
    mt_gotoXY(68, 7);
    printf(" Operation ");
    mt_gotoXY(68, 10);
    printf(" Flags ");
    mt_gotoXY(54, 13);
    printf(" Keys: ");

    /* HotKeys */
    char* hotK[] = { (char*)"l  - load",
                    (char*)"s  - save",
                    (char*)"r  - run",
                    (char*)"t  - step",
                    (char*)"i  - reset",
                    (char*)"F5 - accumulator",
                    (char*)"F6 - instructionCounter" };

    for (int i = 0; i < sizeof(hotK) / sizeof(*hotK); ++i) {
        mt_gotoXY(54, i + 14);
        printf("%s", hotK[i]);
    }
    mt_gotoXY(1, 23);
    printf("%s", "Input/Output:");
    return 0;
}

/// ��������� ������
/// \return 0 - � ������ ��������� ����������, -1 - � ������ ������
int drawingMemory() {
    for (int i = 0; i < 10; ++i)
        for (int j = 0; j < 10; ++j) {
            mt_gotoXY(2 + (5 * j + j), 2 + i);
            int tmp = memory[i * 10 + j];
            if ((i * 10 + j) == instructionCounter)
                mt_setBGcolor(GREEN);
            if ((tmp >> 14) & 1)
                printf(" %04X", tmp & (~(1 << 14)));
            else
                printf("+%04X", tmp);
            mt_setDefaultColorSettings();
        }



    return 0;
}

/// ��������� ������
/// \return 0 - � ������ ��������� ����������, -1 - � ������ ������
int drawingFlags() {
    char tmp[] = { 'O', 'Z', 'M', 'P', 'C' };
    for (int i = 0; i < REGISTER_SIZE; ++i) {
        int value;
        if (sc_regGet(i, &value))
            return -1;
        if (value) {
            mt_gotoXY(69 + (i * 2), 11);
            printf("%c", tmp[i]);
        }
    }

    return 0;
}

/// ��������� "BigChar'��"
/// \return 0 - � ������ ��������� ����������, -1 - � ������ ������
int drawingBigChars() {
    int tmp = memory[instructionCounter];
    if (!((tmp >> 14) & 1))
        bc_printBigChar(bc[16], 2, 14, GREEN);


    for (int i = 0; i < 4; ++i) {
        int ch = (tmp & (0b1111 << (4 * (3 - i)))) >> (4 * (3 - i));

        bc_printBigChar(bc[ch], 2 + 8 * (i + 1) + 2 * (i + 1), 14, GREEN);
    }

    return 0;
}


/// ��������� ���������  ���������� ������������
/// \return 0 - � ������ ��������� ����������, -1 - � ������ ������
int ui_initial() {
    mt_clrScreen();
    instructionCounter = 0;
    if (drawingBoxes())
        return -1;
    if (drawingTexts())
        return -1;
    mt_gotoXY(1, 24);

    return 0;
}

/// ���������� ���������� ������������
/// \return 0 - � ������ ��������� ����������, -1 - � ������ ������
int ui_update() {
    if (drawingMemory())
        return -1;
    if (drawingFlags())
        return -1;
    if (drawingBigChars())
        return -1;
    mt_gotoXY(1, 24);
    return 0;
}