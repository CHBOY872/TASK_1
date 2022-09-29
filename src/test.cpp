#include <gtest/gtest.h>
extern "C" {
#include "StringList.h"
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

TEST(MainTest, CorrectCountOfWordsTest1)
{
    char **list;
    FILE *f = fopen("main.txt", "r");
    if (!f)
    {
        perror("file");
        return;
    }
    char buf[256];
    memset(buf, 0, 256);
    StringListInit(&list);
    while (fscanf(f, "%s", buf) != EOF)
    {
        StringListAdd(list, buf);
        memset(buf, 0, 256);
    }
    ASSERT_EQ(25, StringListSize(list));
}

TEST(MainTest, CorrectCountOfWordsTest2)
{
    char **list;
    StringListInit(&list);
    StringListAdd(list, "Hello");
    StringListAdd(list, "World");
    StringListAdd(list, "How");
    ASSERT_EQ(3, StringListSize(list));
}

TEST(MainTest, CorrectCountOfWordsTest3)
{
    char **list;
    StringListInit(&list);
    StringListAdd(list, "Hello");
    StringListAdd(list, "World");
    StringListAdd(list, "How");
    StringListRemove(list, "How");
    ASSERT_EQ(2, StringListSize(list));
}

TEST(MainTest, CorrectCountOfWordsTest4)
{
    char **list;
    StringListInit(&list);
    StringListAdd(list, "Hello");
    StringListAdd(list, "World");
    StringListAdd(list, "How");
    StringListAdd(list, "How");
    StringListAdd(list, "World");
    StringListRemoveDuplicates(list);
    ASSERT_EQ(3, StringListSize(list));
}

TEST(MainTest, CorrectIndex1)
{
    char **list;
    StringListInit(&list);
    StringListAdd(list, "Hello");
    StringListAdd(list, "World");
    StringListAdd(list, "How");
    StringListAdd(list, "How");
    StringListAdd(list, "World");
    StringListRemoveDuplicates(list);
    ASSERT_EQ(0, StringListIndexOf(list, "Hello"));
}
 
int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
