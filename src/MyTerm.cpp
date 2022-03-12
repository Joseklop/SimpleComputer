#include "MyTerm.h"

/// ���������� ������� � ����������� ������� � ����� ������� ���� ������
/// \return 0 - � ������ ��������� ����������, -1 - � ������ ������
int mt_clrScreen() {
    printf("\033[H\033[2J");
    return 0;
}

/// ���������� ������ � ��������� �������
/// \param col - �������
/// \param row - ������
/// \return 0 - � ������ ��������� ����������, -1 - � ������ ������
int mt_gotoXY(int col, int row)
{
    int rows, cols;
    if (mt_getScreenSize(&rows, &cols) == -1)
        return -1;
    if ((row > rows) || (row <= 0) || (col > cols) || (col <= 0))
        return -1;

    printf("\033[%d;%dH", row, col);
    return 0;
}

/// ���������� ������ ������ ���������
/// \param rows - ���-�� �����
/// \param cols - ���-�� ��������
/// \return 0 - � ������ ��������� ����������, -1 - � ������ ������
int mt_getScreenSize(int* rows, int* cols) {
    struct winsize ws;
    if (ioctl(1, TIOCGWINSZ, &ws))
        return -1;
    *rows = ws.ws_row;
    *cols = ws.ws_col;
    return 0;

}

/// ������������� ���� ����������� ��������� ��������
/// \param color - ���� �� ������������ colors
/// \return 0 - � ������ ��������� ����������, -1 - � ������ ������
int mt_setFGcolor(enum colors color) {
    printf("\033[38;5;%dm", color);
    return 0;
}

/// ������������� ���� ���� ����������� ��������� ��������
/// \param color - ���� �� ������������ colors
/// \return 0 - � ������ ��������� ����������, -1 - � ������ ������
int mt_setBGcolor(enum colors color) {
    printf("\033[48;5;%dm", color);
    return 0;
}

/// ���������� ����� � ����������� ���������
/// \return 0 - � ������ ��������� ����������, -1 - � ������ ������
int mt_setDefaultColorSettings() {
    printf("\033[0m");
    return 0;
}