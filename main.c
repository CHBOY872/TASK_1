#include "StringList.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char **list;

int main(int argc, const char **argv)
{
    FILE *f = fopen("main.txt", "r");
    if (!f)
    {
        perror("file");
        return 1;
    }
    char buf[256];
    memset(buf, 0, 256);
    StringListInit(&list);
    while (fscanf(f, "%s", buf) != EOF)
    {
        StringListAdd(list, buf);
        memset(buf, 0, 256);
    }
    printf("Size: %d\n", StringListSize(list));
    int a = StringListIndexOf(list, "Hello");
    printf("String Index: %d\n", a);
    fclose(f);
    int i;
    for (i = 0; i < StringListSize(list); i++)
        printf("%s\n", list[i]);
    printf("\n\n\n");
    StringListSort(list);
    StringListReplaceInStrings(list, "Hello", "Bye");
    for (i = 0; i < StringListSize(list); i++)
        printf("%s\n", list[i]);
    StringListRemove(list, "Wee");
    StringListRemoveDuplicates(list);
    printf("\n\n\n\n");
    for (i = 0; i < StringListSize(list); i++)
        printf("%s\n", list[i]);
    StringListDestroy(&list);
    return 0;
}
