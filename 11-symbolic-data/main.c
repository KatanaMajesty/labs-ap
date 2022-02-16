#include <stdio.h>
#include <string.h>
#include <malloc.h>

#define FALSE 0
#define TRUE 1

void _flushout(void)
{
    int f = 0;
    while ((f = getchar()) != '\n' && f != EOF);
}

// checks if a buffer contains a letter
unsigned int _buffcontains(char* buffer, size_t len, char c)
{
    for (int i = 0; i < len; i++)
    {
        if (buffer[i] == c)
            return TRUE;
    }
    return FALSE;
}

// returns number of unique letters in sentence/word
unsigned int _get_letters(char* buffer, size_t len)
{
    unsigned int c = 0;
    char* _uniquebuff = malloc(len);
    for (int i = 0; i < len; i++)
    {
        if (!_buffcontains(_uniquebuff, len, buffer[i]))
        {
            _uniquebuff[c] = buffer[i];
            c++;
        }
    }
    free(_uniquebuff);
    return c;
}

/*
input:
19
hi world huh ahahah
*/

// deletes words with <= 2 letters
__attribute_malloc__ char* _delete_odd(const char* buffer, char delim) 
{
    size_t _act_buffer_len = strlen(buffer);
    char* _newbuff = calloc(_act_buffer_len + 1, sizeof(char)); // <- new buffer without words with less than 2 unique letters
    
    int beg_point = 0;
    int curr_wlen = 0;
    for (size_t i = 0; i < _act_buffer_len; i++)
    {
        // debugging purposes
        // printf("char %c with id %d\n", buffer[i], buffer[i]);
        if (buffer[i] == delim || buffer[i] == '\n') // <- check if buffer eq to delim or linefeed, which is a result of user input
        {
            char* _cpy = malloc(curr_wlen + 1);
            memcpy(_cpy, &buffer[beg_point], curr_wlen); // <- will copy a string starting from the beginning of the word til its end
            _cpy[curr_wlen] = '\0';

            // this may be commented for testing purposes
            unsigned int _letters = _get_letters(_cpy, curr_wlen); // <- will return number of unique letters in word
            if (_letters > 2) // <- will remove all the words with less than 2 unique letters
            {
                strcat(_newbuff, _cpy);
                strcat(_newbuff, " ");
            }

            beg_point = i + 1; // <- will point on the first letter of the word
            curr_wlen = 0;

            free(_cpy);
        } 
        else curr_wlen++;
    }
    return _newbuff;
}

int main(void)
{
    size_t size;
    printf("Enter the size of array:\n");
    scanf("%d", &size);
    _flushout();

    char buffer[size + 1]; // <- extra symbol for \0 that is not added automatically
    printf("Enter words:\n");
    fgets(buffer, sizeof(buffer), stdin);
    buffer[size] = '\0';
    strcat(buffer, " ");

    char* result = _delete_odd(buffer, ' ');
    printf("Final result:\n");
    puts(result);
    fflush(stdin);
    free(result);
}
