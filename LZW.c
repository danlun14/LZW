#include "str.h"
#include "LZW.h"
#include <stdlib.h>

void fill_and_compress(Dictionary *dic, FILE *in, FILE *out)
{
    int *code = calloc(65655, sizeof(short));
    int i = 0, sub_id = 0;
    char *substr = calloc(2, sizeof(char));
    int cur_sym = 0;
    int code_id = 0;
    int len;
    i = fread(substr, sizeof(char), 1, in);
    char *tmp = calloc(1, 1);
    while (1)
    {
        if (dic->size == dic->capacity)
        {
            clear_dic(dic);
        }
        cur_sym = find_i(*dic, substr);
        if (0 <= cur_sym)

        {

            sub_id++;
            substr = realloc(substr, (sub_id + 1) * sizeof(char));
            i = fread(tmp, sizeof(char), 1, in);
            if (i == 0)
            {
                code[code_id] = cur_sym;

                code_id++;
                len = slen(substr);
                dic->dic_i[dic->size].str = calloc(len, sizeof(char));
                scpy(dic->dic_i[dic->size].str, substr);
                dic->size++;
                break;
            }
            substr[sub_id] = *tmp;
            code[code_id] = cur_sym;
        }
        else
        {
            code_id++;

            len = slen(substr);
            dic->dic_i[dic->size].str = calloc(len, sizeof(char));
            scpy(dic->dic_i[dic->size].str, substr);
            dic->size++;
            substr = calloc(1, sizeof(char));
            substr[0] = *tmp;
            sub_id = 0;
            cur_sym = find_i(*dic, substr);
        }
    }
    for (int i = 0; i < code_id; i++)
    {
        fwrite(code + i, sizeof(char), 2, out);
    }
    free(dic);
    free(tmp);
    free(code);
    free(substr);
}

void fill_and_decompress(Dictionary *dic, FILE *in, FILE *out)
{
    short cur_code, next_code;
    fread(&cur_code, sizeof(short), 1, out);
    fprintf(in, "%s", dic->dic_i[cur_code].str);
    while (fread(&next_code, sizeof(short), 1, out))
    {

        if (dic->size == dic->capacity)
        {
            clear_dic(dic);
        }
        if (next_code < dic->size)
        {
            dic->dic_i[dic->size].str = calloc(slen(dic->dic_i[cur_code].str) + 1, sizeof(char));
            scpy(dic->dic_i[dic->size].str, dic->dic_i[cur_code].str);
            dic->dic_i[dic->size].str[slen(dic->dic_i[cur_code].str)] = dic->dic_i[next_code].str[0];
            dic->size++;
        }
        else
        {
            dic->dic_i[dic->size].str = calloc(slen(dic->dic_i[cur_code].str) + 1, sizeof(char));
            scpy(dic->dic_i[dic->size].str, dic->dic_i[cur_code].str);
            dic->dic_i[dic->size].str[slen(dic->dic_i[cur_code].str)] = dic->dic_i[cur_code].str[0];
            dic->size++;
            //add_print();
        }

        cur_code = next_code;
        fprintf(in, "%s", dic->dic_i[cur_code].str);
    }
    free(dic);
}
void dic_init(Dictionary *dic, int capacity)
{
    dic->capacity = capacity;
    dic->size = 256;
    dic->dic_i = calloc(dic->capacity, sizeof(Dictionary_item));
    for (int i = 0; i < 256; i++)
    {
        dic->dic_i[i].str = calloc(2, sizeof(char));
        *(dic->dic_i[i].str) = i;
    }
}

int find_i(Dictionary dic, char *tmp)
{
    if (!scmp("\n", tmp))
    {
        return 0;
    }
    for (int i = 0; i < dic.size; i++)
    {
        int len = sspn(dic.dic_i[i].str, tmp);
        if (len == slen(tmp))
        {
            return i;
        }
    }
    return -1;
}

void clear_dic(Dictionary *dic)
{
    for (int i = 1; i < dic->capacity; i++)
    {
        free(dic->dic_i[i].str);
        dic->dic_i[i].str = NULL;
    }
    dic->size = 1;
}
void free_dic(Dictionary *dic)
{
    for (int i = 0; i < dic->capacity; i++)
    {
        free(dic->dic_i[i].str);
    }
    free(dic);
}