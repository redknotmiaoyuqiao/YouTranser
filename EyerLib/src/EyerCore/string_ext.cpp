#include "string_ext.h"

#include <stdio.h>
#include <string.h>

char * strrpl(char * in, char * out, int outlen, const char * src, char * dst)
{
    char *p = in;
    unsigned int  len = outlen - 1;

    // 这几段检查参数合法性
    if((NULL == src) || (NULL == dst) || (NULL == in) || (NULL == out)) {
        return NULL;
    }
    if((strcmp(in, "") == 0) || (strcmp(src, "") == 0)) {
        return NULL;
    }
    if(outlen <= 0) {
        return NULL;
    }

    while((*p != '\0') && (len > 0)) {
        if(strncmp(p, src, strlen(src)) != 0) {
            int n = strlen(out);

            out[n] = *p;
            out[n + 1] = '\0';

            p++;
            len--;
        }
        else {
            strcat(out, dst);
            p += strlen(src);
            len -= strlen(dst);
        }
    }

    return out;
}