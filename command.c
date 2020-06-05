#include "LZW.h"
#include "str.h"
#include <stdlib.h>
#include "command.h"

int compress_file(FILE *in, FILE *out)
{
    Dictionary *dic = calloc(1, sizeof(Dictionary));

    dic_init(dic, 65655);

    fill_and_compress(dic, in, out);
    return 0;
    //write_bits(out, code, code_id);
}
int decompress_file(FILE *in, FILE *out)
{
    Dictionary *dic = calloc(1, sizeof(Dictionary));
    dic_init(dic, 65655);
    fill_and_decompress(dic, in, out);
    return 0;
}