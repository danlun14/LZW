#ifndef STR_H
#define STR_H

int slen(char *str);

int sspn(char *str, const char *substr);

int scmp(char *mstr, const char *cpstr);

char *scat(char *des, char *src);

char *scpy(char *des, const char *src);

#endif