#include "str.h"
#include "LZW.h"
#include <stdlib.h>

int compress_file(FILE *in, FILE *out);
int decompress_file(FILE *in, FILE *out);