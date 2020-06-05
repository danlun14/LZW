#include "LZW.h"
#include "str.h"
#include <stdlib.h>
#include "command.h"

void usage()
{
    printf("Usage:\n");
    printf("compress:   lzw -d -o text file.lzw\n");
    printf("decompress: lzw -d -o file.lzw text\n");
}

/*void add_print(char *str)
{
    int len = slen(str);
    printf("added - \"");
    for (int i = 0; i < len; i++)
    {
        printf("%c", str[i]);
    }
    printf("\"\n");
}
*/
int main(int argc, char *argv[])
{

    if (argv[1] == NULL || argv[2] == NULL || argv[3] == NULL || argv[4] == NULL)
    {
        usage();
        return 1;
    }
    if (!scmp(argv[1], "-c") && !scmp(argv[2], "-o"))
    {
        FILE *in, *out;
        in = fopen(argv[3], "r");
        out = fopen(argv[4], "wb");
        compress_file(in, out);
        fclose(in);
        fclose(out);

        return 0;
    }

    if (!scmp(argv[1], "-d") && !scmp(argv[2], "-o"))
    {
        FILE *in, *out;
        out = fopen(argv[3], "rb");
        in = fopen(argv[4], "w");
        decompress_file(in, out);
        fclose(in);
        fclose(out);

        return 0;
    }

    return 0;
}
