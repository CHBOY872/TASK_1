#include "StringList.h"
#include <stdlib.h>
#include <string.h>

static int start_size = 32;                     /* start len of arr */
static int current_pos = 0;                     /* current position in array */

void StringListInit(char ***list)
{
    *list = malloc(sizeof(char *) * start_size);
    int i;
    for (i = 0; i < start_size; i++)
        (*list)[i] = NULL;
}

void StringListDestroy(char ***list)
{
    int i;
    for (i = 0; i < current_pos; i++)
        free((*list)[i]);
    free(*list);
}

void StringListAdd(char **list, String str)
{
    char ***temp = malloc(sizeof(char **));
    *temp = list;
    char *str_tmp = malloc(strlen(str) + 1);
    if (current_pos >= start_size)
    {
        int new_size = start_size * 2;
        char **tmp = malloc(sizeof(char *) * new_size);
        int i;
        for (i = 0; i < new_size; i++)
            tmp[i] = i < start_size ? list[i] : NULL;
        free(*temp);
        start_size = new_size;
        *temp = tmp;
    }

    strcpy(str_tmp, str);
    (*temp)[current_pos] = str_tmp;
    current_pos++;
    free(temp);
}

void StringListRemove(char **list, String str)
{
    char ***temp = malloc(sizeof(char **));
    *temp = list;
    int i = 0;
    while (i < current_pos)
    {
        if (!strcmp((*temp)[i], str))
        {
            free((*temp)[i]);
            (*temp)[i] = NULL;
            int temp_current_pos = current_pos;
            int j;
            for (j = i; j < temp_current_pos - 1; j++)
            {
                (*temp)[j] = (*temp)[j + 1];
                (*temp)[j + 1] = NULL;
            }
            current_pos--;
            continue;
        }
        i++;
    }
    free(temp);
}

int StringListSize(char **list)
{
    return current_pos;
}

int StringListIndexOf(char **list, char *str)
{
    int i;
    for (i = 0; i < current_pos; i++)
    {
        if (!strcmp(list[i], str))
            return i;
    }

    return -1;
}

int is_at_arr(const char *str, int len, char **arr) /* check if the string */
{                                                   /* is in array */
    int i;
    for (i = 0; i < len; i++)
    {
        if (!arr[i])                                /* if the el is NULL */
            return 0;                               /* return because next */
                                                    /* elements will */
                                                    /* be NULL too */
        if (!strcmp(str, arr[i]))
            return 1;
    }
    return 0;
}

void StringListRemoveDuplicates(char **list)
{
    char **temp = NULL;
    char ***new_list = malloc(sizeof(char **));
    *new_list = list;
    StringListInit(&temp);
    int i, k = 0;
    for (i = 0; i < current_pos; i++)
    {
        if (!is_at_arr(list[i], current_pos, temp))
        {
            temp[k] = malloc(strlen(list[i]) + 1);
            strcpy(temp[k], list[i]);
            k++;
        }
        free(list[i]);
    }
    for (i = 0; i < current_pos; i++)
        (*new_list)[i] = i < k ? temp[i] : 0;

    current_pos = k;
    free(temp);
    free(new_list);
}

void StringListReplaceInStrings(char **list, char *before, char *after)
{
    int new_str_len = strlen(after) + 1;
    int i;
    for (i = 0; i < current_pos; i++)
    {
        if (!strcmp(before, list[i]))
        {
            free(list[i]);
            list[i] = malloc(new_str_len);
            strcpy(list[i], after);
        }
    }
}

void StringListSort(char **list)
{
    char *tmp;
    int quit = 0;
    while (!quit)
    {
        quit = 1;
        int i;
        for (i = current_pos - 1; i >= 1; i--)
        {
            if (strcmp(list[i], list[i - 1]) > 0)
            {
                tmp = list[i];
                list[i] = list[i - 1];
                list[i - 1] = tmp;
                quit = 0;
            }
        }
    }
}
