#include <stdio.h>
#include <string.h>
#include <malloc.h>

#define FALSE (unsigned int) 0
#define TRUE (unsigned int) 1

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

// deletes words with <= 2 letters
char* _delete_odd(const char* buffer, char delim)
{
    size_t _act_buffer_len = strlen(buffer);
    char* _newbuff = malloc(_act_buffer_len + 1); // <- new buffer without words with less than 2 unique words
    
    /*
    input:
    18
    hi world huh ahahah

    runtime:
    index < beg_point < curr_wlen
    0 < 0 < 1 h
    1 < 0 < 2 i
    2 < 3 < 0 -> delim == ' ' at 2 -> hi

    3 < 3 < 1 w
    4 < 3 < 2 o
    5 < 3 < 3 r
    6 < 3 < 4 l
    7 < 3 < 5 d
    8 < 9 < 0 -> delim == ' ' at 8 -> world

    9 < 9 < 1 h
    10 < 9 < 2 u
    11 < 9 < 3 h
    12 < 13 < 0 -> delim == ' ' at 12 -> huh

    13 < 13 < 1 a
    14 < 13 < 2 h
    15 < 13 < 3 a
    16 < 13 < 4 h
    17 < 13 < 5 a
    18 < 13 < 6 h
    EOF
    */

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
            curr_wlen = 0; // <- if the next symbol after space is another space, than word length should be 0

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

    printf("Final result:\n");
    puts(_delete_odd(buffer, ' '));
}
