#include <stdio.h>
#include <iostream>
#include <windows.h>

using namespace std;

void DrawLbl();
void CrHSymb(unsigned char trmask, HANDLE hStdOut);
void CrASymb(unsigned char trmask, HANDLE hStdOut);
void CrCSymb(unsigned char trmask, HANDLE hStdOut);
void CrKSymb(unsigned char trmask, HANDLE hStdOut);
void CrESymb(unsigned char trmask, HANDLE hStdOut);
void CrDSymb(unsigned char trmask, HANDLE hStdOut);
void hackedPrint(HANDLE hStdOut);

unsigned char hpaint[9][14] = {0};
unsigned char apaint[9][16] = {0};
unsigned char cpaint[9][14] = {0};
unsigned char kpaint[9][12] = {0};
unsigned char epaint[9][12] = {0};
unsigned char dpaint[9][14] = {0};
unsigned char spac[9][2] = {0};

int main()
{
    FILE* fp = fopen("S:/Doc/vzlomm.com", "rb+");
    if (fp == NULL)
        return -1;

    char c = 0x74;
    char wassymb[2] = {0};
    fseek(fp, 0x01C, 0);
    fread(&wassymb, 1, 2, fp);

    if ((wassymb[0] == 0x74) && (wassymb[1] == 0x3))
    {
        printf("It isn't file we need or this file already hacked.\n");
        return 1;
    }
    if ((wassymb[0] != 0x75) || (wassymb[1] != 0x3))
    {
        printf("It isn't file we need!\n");
        return 2;
    }

    fseek(fp, 0x01C, 0);
    fwrite(&c, 1, 1, fp);

    fclose(fp);

    DrawLbl();

    return 0;
}

void DrawLbl()
{
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    cout << '\n';

    CrHSymb(0b10110000, hStdOut);
    CrASymb(0b10100000, hStdOut);
    CrCSymb(0b10010000, hStdOut);
    CrKSymb(0b11010000, hStdOut);
    CrESymb(0b11000000, hStdOut);
    CrDSymb(0b11100000, hStdOut);

    hackedPrint(hStdOut);

    return;
}

void CrHSymb(unsigned char trmask, HANDLE hStdOut)
{
    for (int i = 0; i < 9; ++i)
        for (int j = 0; j < 2; ++ j)
        {
            hpaint[i][j] = trmask;
            hpaint[i][13 - j] = trmask;
        }

    for (int i = 2; i < 12; ++i)
        hpaint[4][i] = trmask;

    return;
}

void CrASymb(unsigned char trmask, HANDLE hStdOut)
{
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 2; ++j)
            for (int k = 0; k < 2; ++k)
            {
            apaint[i * 2 + k][7 - i * 2 - j] = trmask;
            apaint[i * 2 + k][8 + i * 2 + j] = trmask;
            }

    for (int i = 0; i < 2; ++i)
        for (int j = 0; j < 2; ++j)
        {
            apaint[8 - i][j] = trmask;
            apaint[8 - i][15 - j] = trmask;
        }

    for (int i = 2; i < 14; ++i)
        apaint[6][i] = trmask;

    return;
}

void CrCSymb(unsigned char trmask, HANDLE hStdOut)
{
    for (int i = 4; i < 12; ++i)
    {
        cpaint[0][i] = trmask;
        cpaint[8][i] = trmask;
    }

    for (int i = 2; i < 5; ++i)
    {
        cpaint[1][i] = trmask;
        cpaint[7][i] = trmask;
    }

    for (int i = 11; i < 14; ++i)
    {
        cpaint[1][i] = trmask;
        cpaint[7][i] = trmask;
    }

    cpaint[2][2] = trmask;
    cpaint[6][2] = trmask;

    for (int i = 2; i < 7; ++i)
    {
        cpaint[i][0] = trmask;
        cpaint[i][1] = trmask;
    }

    return;
}

void CrKSymb(unsigned char trmask, HANDLE hStdOut)
{
    for (int i = 0; i < 9; ++i)
    {
        kpaint[i][0] = trmask;
        kpaint[i][1] = trmask;
    }

    for (int i = 1; i < 6; ++i)
        for (int j = 0; j < 2; ++j)
        {
            kpaint[5 - i][i * 2 + j] = trmask;
            kpaint[3 + i][i * 2 + j] = trmask;
        }

    return;
}

void CrESymb(unsigned char trmask, HANDLE hStdOut)
{
    for (int i = 0; i < 9; ++i)
    {
        epaint[i][0] = trmask;
        epaint[i][1] = trmask;
    }

    for (int j = 0; j < 9; j += 4)
    {
        for (int i = 2; i < 12; ++i)
            epaint[j][i] = trmask;
    }

    return;
}

void CrDSymb(unsigned char trmask, HANDLE hStdOut)
{
    for (int i = 0; i < 9; ++i)
    {
        dpaint[i][0] = trmask;
        dpaint[i][1] = trmask;
    }

    for (int i = 2; i < 10; ++i)
    {
        dpaint[0][i] = trmask;
        dpaint[8][i] = trmask;
    }

    for (int i = 10; i < 12; ++i)
    {
        dpaint[1][i] = trmask;
        dpaint[7][i] = trmask;
    }

    for (int i = 2; i < 7; ++i)
    {
        dpaint[i][12] = trmask;
        dpaint[i][13] = trmask;
    }

    return;
}

void hackedPrint(HANDLE hStdOut)
{
    for (int j = 0; j < 9; ++j)
    {
        for (int i = 0; i < 14; ++i)
        {
            SetConsoleTextAttribute(hStdOut, hpaint[j][i]);
            cout << ' ';
        }

        for (int i = 0; i < 2; ++i)
        {
            SetConsoleTextAttribute(hStdOut, spac[j][i]);
            cout << ' ';
        }

        for (int i = 0; i < 16; ++i)
        {
            SetConsoleTextAttribute(hStdOut, apaint[j][i]);
            cout << ' ';
        }

        for (int i = 0; i < 2; ++i)
        {
            SetConsoleTextAttribute(hStdOut, spac[j][i]);
            cout << ' ';
        }

        for (int i = 0; i < 14; ++i)
        {
            SetConsoleTextAttribute(hStdOut, cpaint[j][i]);
            cout << ' ';
        }

        for (int i = 0; i < 2; ++i)
        {
            SetConsoleTextAttribute(hStdOut, spac[j][i]);
            cout << ' ';
        }

        for (int i = 0; i < 12; ++i)
        {
            SetConsoleTextAttribute(hStdOut, kpaint[j][i]);
            cout << ' ';
        }

        for (int i = 0; i < 2; ++i)
        {
            SetConsoleTextAttribute(hStdOut, spac[j][i]);
            cout << ' ';
        }

        for (int i = 0; i < 12; ++i)
        {
            SetConsoleTextAttribute(hStdOut, epaint[j][i]);
            cout << ' ';
        }

        for (int i = 0; i < 2; ++i)
        {
            SetConsoleTextAttribute(hStdOut, spac[j][i]);
            cout << ' ';
        }

        for (int i = 0; i < 14; ++i)
        {
            SetConsoleTextAttribute(hStdOut, dpaint[j][i]);
            cout << ' ';
        }

        SetConsoleTextAttribute(hStdOut, 7);
        cout << '\n';
    }
    return;
}
