#include "StringList.h"
#include <stdlib.h>
#include <string.h>

static int start_size = 32; /* start len of arr */
static int current_pos = 0; /* current position in array */

static char ***list_array = NULL;
static int list_array_count = 0;
static int list_array_max_count = 32;
static int *start_sizes = NULL;
static int *current_poss = NULL;

void StringListInit(char ***list)
{
    if (!list_array)
    {
        list_array = malloc(sizeof(char **) * list_array_max_count);
        start_sizes = malloc(sizeof(int) * list_array_max_count);
        current_poss = malloc(sizeof(int) * list_array_max_count);
        int i;
        for (i = 0; i < list_array_max_count; i++)
        {
            list_array[i] = NULL;
            start_sizes[i] = start_size;
            current_poss[i] = current_pos;
        }
    }
    if (list_array_count == list_array_max_count)
    {
        int new_list_array_max_count = list_array_max_count * 2;
        char ***new_list_array =
            malloc(sizeof(char **) * new_list_array_max_count);
        int *new_start_sizes = malloc(sizeof(int) * new_list_array_max_count);
        int *new_current_poss = malloc(sizeof(int) * new_list_array_max_count);
        int i;
        for (i = 0; i < new_list_array_max_count; i++)
        {
            new_list_array[i] = i < list_array_count ? list_array[i] : NULL;
            new_start_sizes[i] =
                i < list_array_count ? start_sizes[i] : start_size;
            new_current_poss[i] =
                i < list_array_count ? current_poss[i] : current_pos;
        }
        list_array_max_count = new_list_array_max_count;
        free(start_sizes);
        free(list_array);
        free(current_poss);
        start_sizes = new_start_sizes;
        list_array = new_list_array;
        current_poss = new_current_poss;
    }

    list_array[list_array_count] = malloc(sizeof(char *) * start_size);
    start_sizes[list_array_count] = start_size;
    current_poss[list_array_count] = current_pos;

    int i;
    for (i = 0; i < start_sizes[list_array_count]; i++)
        list_array[list_array_count][i] = NULL;

    (*list) = list_array[list_array_count];

    list_array_count++;
}

int find_list_in_array(char **list, char ***lists)
{
    int i;
    for (i = 0; i < list_array_count; i++)
    {
        if (list == lists[i])
            return i;
    }
    return -1;
}

void StringListDestroy(char ***list)
{
    int idx = find_list_in_array(*list, list_array);
    if (-1 == idx)
        return;
    int i;
    for (i = 0; i < current_poss[idx]; i++)
        free((*list)[i]);
    free(*list);
    *list = NULL;
}

void StringListAdd(char **list, String str)
{
    int idx = find_list_in_array(list, list_array);
    if (-1 == idx)
        return;
    char ***temp = malloc(sizeof(char **));
    *temp = list;
    char *str_tmp = malloc(strlen(str) + 1);
    if (current_poss[idx] >= start_sizes[idx])
    {
        int new_size = start_sizes[idx] * 2;
        char **tmp = malloc(sizeof(char *) * new_size);
        int i;
        for (i = 0; i < new_size; i++)
            tmp[i] = i < start_size ? list[i] : NULL;
        free(*temp);
        start_sizes[idx] = new_size;
        *temp = tmp;
    }

    strcpy(str_tmp, str);
    (*temp)[current_poss[idx]] = str_tmp;
    current_poss[idx]++;
    free(temp);
}

void StringListRemove(char **list, String str)
{
    int idx = find_list_in_array(list, list_array);
    if (-1 == idx)
        return;
    char ***temp = malloc(sizeof(char **));
    *temp = list;
    int i = 0;
    while (i < current_poss[idx])
    {
        if (!strcmp((*temp)[i], str))
        {
            free((*temp)[i]);
            (*temp)[i] = NULL;
            int temp_current_pos = current_poss[idx];
            int j;
            for (j = i; j < temp_current_pos - 1; j++)
            {
                (*temp)[j] = (*temp)[j + 1];
                (*temp)[j + 1] = NULL;
            }
            current_poss[idx]--;
            continue;
        }
        i++;
    }
    free(temp);
}

int StringListSize(char **list)
{
    int idx = find_list_in_array(list, list_array);
    if (idx == -1)
        return -1;
    return current_poss[idx];
}

int StringListIndexOf(char **list, char *str)
{
    int idx = find_list_in_array(list, list_array);
    if (idx == -1)
        return -1;
    int i;
    for (i = 0; i < current_poss[idx]; i++)
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
        if (!arr[i])  /* if the el is NULL */
            return 0; /* return because next */
                      /* elements will */
                      /* be NULL too */
        if (!strcmp(str, arr[i]))
            return 1;
    }
    return 0;
}

void StringListRemoveDuplicates(char **list)
{
    int idx = find_list_in_array(list, list_array);
    if (-1 == idx)
        return;

    char **temp = malloc(sizeof(char *) * current_poss[idx]);
    int i;
    for (i = 0; i < current_poss[idx]; i++)
		temp[i] = NULL;	
    char ***new_list = malloc(sizeof(char **));
    *new_list = list;
    int k = 0;
    for (i = 0; i < current_poss[idx]; i++)
    {
        if (!is_at_arr(list[i], current_poss[idx], temp))
        {
            temp[k] = malloc(strlen(list[i]) + 1);
            strcpy(temp[k], list[i]);
            k++;
        }
        free(list[i]);
    }
    for (i = 0; i < current_poss[idx]; i++)
        (*new_list)[i] = i < k ? temp[i] : 0;

    current_poss[idx] = k;
    free(temp);
    free(new_list);
}

void StringListReplaceInStrings(char **list, char *before, char *after)
{
    int idx = find_list_in_array(list, list_array);
    if (-1 == idx)
        return;
    int new_str_len = strlen(after) + 1;
    int i;
    for (i = 0; i < current_poss[idx]; i++)
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
    int idx = find_list_in_array(list, list_array);
    if (-1 == idx)
        return;

    char *tmp;
    int quit = 0;
    while (!quit)
    {
        quit = 1;
        int i;
        for (i = current_poss[idx] - 1; i >= 1; i--)
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
