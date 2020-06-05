#ifndef LZW_H
#define LZW_H
#include <stdio.h>

typedef struct
{
    char *str;
} Dictionary_item;

typedef struct
{
    Dictionary_item *dic_i;
    int size;
    int capacity;
} Dictionary;

void dic_init(Dictionary *dic, int capacity);

void fill_and_decompress(Dictionary *dic, FILE *in, FILE *out);

void fill_and_compress(Dictionary *dic, FILE *in, FILE *out);

int find_i(Dictionary dic, char *tmp);

void clear_dic(Dictionary *dic);

void free_dic(Dictionary *dic);

#endif