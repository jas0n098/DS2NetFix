#include <windows.h>
#include <stdbool.h>

char *Scan(char *pattern, char *mask, char *begin, size_t size)
{
    size_t patternLen = strlen(mask);

    for (int i = 0; i < size - patternLen; i++)
    {
        bool found = true;
        for (int j = 0; j < patternLen; j++)
        {
            if (mask[j] != '?' && pattern[j] != *(char*)((size_t)begin + i + j))
            {
                found = false;
                break;
            }
        }
        if (found)
        {
            return (begin + i);
        }
    }

    return 0;
}
