#ifndef MYBIGCHARS_HPP
#define MYBIGCHARS_HPP

#include <unistd.h>

#include "MyTerm.h"

/* ������������� */
#define ACS_CKBOARD  'a' // ���������
#define ACS_ULCORNER 'l' // ����� ������� ����
#define ACS_URCORNER 'k' // ������ ������� ����
#define ACS_LRCORNER 'j' // ������ ������ ����
#define ACS_LLCORNER 'm' // ����� ������ ����
#define ACS_HLINE    'q' // �������������� �����
#define ACS_VLINE    'x' // ������������ �����

extern unsigned int bc[][2];

int bc_printA(char ch);

int bc_box(int x, int y, int width, int height);

int bc_printBigChar(unsigned int* big, int x, int y, enum colors colorFG = DEFAULT, enum colors colorBG = DEFAULT);

int bc_setBigCharPos(unsigned int* big, int x, int y, bool value);
int bc_getbigCharPos(unsigned int* big, int x, int y, bool* value);


int bc_bigCharWrite(int fd, unsigned int* big, int count);
int bc_bigCharRead(int fd, unsigned int* big, int need_count, int* count);

#endif //MYBIGCHARS_HPP