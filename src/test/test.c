


#include "../UL.h"
#include <string.h>
void test_read_file()
{
        char * res;
        i64_t length;
        res = read_sfile("testfile.txt", &length);
        printf("TESTING read_file:\nbytes: %li, strlen: %li\nread:\n%s",
        length, strlen(res), res);
        free(res);
}

void test_write_file()
{
        char * res, *wr;
        i64_t length;
        res = read_sfile("testfile.txt", &length);

        printf("TESTING write_file:");
        write_file("write.txt", res);

        wr = read_sfile("write.txt", NULL);

        if(!strcmp(res, wr))
                printf(" succeded\n");
        else
                printf(" failed\n");
        free(res);
}

void test_append_file()
{
        char * res, *wr, *res2;
        i64_t length;
        res = read_sfile("testfile.txt", &length);

        printf("TESTING append_file:");
        remove_file("write.txt");
        append_file("write.txt", res);
        append_file("write.txt", res);

        wr = read_sfile("write.txt", NULL);
        res2 = malloc((2* length + 2)*sizeof(char));
        strcat(res2, res);
        strcat(res2, res);

        if(!strcmp(res2, wr))
                printf(" succeded\n");
        else
                printf(" failed\n");
        free(res);
        free(res2);
}
