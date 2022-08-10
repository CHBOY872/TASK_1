#ifndef STRINGLIST_H_SENTRY
#define STRINGLIST_H_SENTRY

#define String const char *

void StringListInit(char ***list);
void StringListDestroy(char ***list);
void StringListAdd(char **list, String str);
void StringListRemove(char **list, String str);
int StringListSize(char **list);
int StringListIndexOf(char **list, char *str);
void StringListRemoveDuplicates(char **list);
void StringListReplaceInStrings(char **list, char *before, char *after);
void StringListSort(char **list);

#endif