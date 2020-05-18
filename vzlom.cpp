#include <stdio.h>

int main()
{
    FILE* fp = fopen("S:/Doc/vzlomm.com", "rb+");
    if (fp == NULL)
        return -1;

    char c = 0x74;
    fseek(fp, 0x01C, 0);
    fwrite(&c, 1, 1, fp);

    fclose(fp);
    return 0;
}
