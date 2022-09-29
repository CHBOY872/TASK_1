#include <gtest/gtest.h>
extern "C" {
#include "StringList.h"
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

TEST(MainTest, CorrectCountOfWordsTest)
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

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
