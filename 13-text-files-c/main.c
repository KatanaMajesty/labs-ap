#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define TRUE 1
#define FALSE 0

/*
    10 - linefeed - used to switch to a new line
    13 - carriage return - used to reset a device's position to the beginning of a line of text
    26 - substitute - EOF
*/

void pflush(const char *str)
{
    puts(str);
    fflush(stdin);
}

// flush after scanf
void _flush_scanf()
{
    int f = 0;
    while ((f = getchar()) != '\n' && f != EOF);
}

FILE* restrict readbuffer;
FILE* restrict writebuffer;

char filename[16];
char words_filename[16];

void write_file(FILE* restrict writebuffer, const char* filename);
void read_file(FILE* restrict readbuffer, const char* filename);
void write_max_word_file(FILE* restrict writebuffer, FILE* restrict readbuffer, const char* _newfilename, const char* filename);\
// writebuffer should be closed or segfault will be throwed
// will open writebuffer again with mode "a" and close at the end of function
void write_line(FILE* restrict writebuffer, const char* filename, const char* line);
// converts string to lowercase not depending on '\0'
// returns a pointer to the same part of memory
char* strlower(char* str, size_t len);

int main(void)
{
    pflush("Enter the name of the file:");
    char _filepath[32] = "../data";
    scanf("%s", &filename);
    _flush_scanf();

    strcat(_filepath, filename);
    pflush("Creating blank file... Listening for input:");
    write_file(writebuffer, _filepath);

    pflush("Reading a file... Result:");
    read_file(readbuffer, _filepath);

    pflush("Enter the name of the second file:");
    char _wfilepath[32] = "../data";
    scanf("%s", &words_filename);
    _flush_scanf();

    strcat(_wfilepath, words_filename);
    write_max_word_file(writebuffer, readbuffer, _wfilepath, _filepath);
}

void write_max_word_file(FILE* restrict writebuffer, FILE* restrict readbuffer, const char* _newfilename, const char* filename)
{
    // should check if the name is correct
    readbuffer = fopen(filename, "r");
    
    char _rline[128];
    char delim[] = " ,.;!?";

    char* restrict _wpointer;
    char target_word[128];
    size_t wlen;
    while(TRUE)
    {
        fgets(_rline, sizeof(_rline), readbuffer);
        if (feof(readbuffer))
            break;
        // split word
        _wpointer = strtok(_rline, delim); // get first word
        wlen = strlen(_wpointer);
        strcpy(target_word, _wpointer);

        // get all words and check them
        while (_wpointer != NULL)
        {
            size_t curr_wlen = strlen(_wpointer);
            if (_wpointer[curr_wlen - 1] == '\n') // <- \n will be recorded by fgets, so we are forced to check it
                curr_wlen -= 1;

            if (wlen <= curr_wlen)
            {
                wlen = curr_wlen;
                strcpy(target_word, _wpointer);
                if (target_word[wlen - 1] == '\n') // <- lets remove odd \n and replace it by null-termination so that we could easily concat out strings
                    target_word[wlen - 1] = '\0';
            }
            _wpointer = strtok(NULL, delim);
        }
        char len[4]; // will convert wlen to char* with sprintf
        sprintf(len, " %d\n", wlen);
        strcat(target_word, len);
        write_line(writebuffer, _newfilename, target_word);
    }

    fclose(readbuffer);
}

void write_file(FILE* restrict writebuffer, const char* filename)
{
    if (strcmp(filename, "") == TRUE)
    {
        pflush("not a valid filename. Returning");
        return;
    }
    writebuffer = fopen(filename, "w"); // create new file for write and read
    char answ;
    char line[128];

    pflush("Keep entering strings (type EXIT to stop entering):");
    while (TRUE) {
        /*
        Note: The gets() function can also be to take input from the user. However, it is removed from the C/CXX standard.
        It's because gets() allows you to input any length of characters. Hence, there might be a buffer overflow.
        */
        fgets(line, sizeof(line), stdin); // <- \n will be recorded by fgets, so we are forced to check for exit\n underneath
        // line[sizeof(line) - 1] = '\0'; // < for strlower() to work correctly
        if (strcmp(strlower(line, sizeof(line)), "exit\n") == 0) // 0 if equal
            break;
        fputs(line, writebuffer);
    } 
    fputs("\0", writebuffer);
    fclose(writebuffer);
}

void read_file(FILE* restrict readbuffer, const char* filename)
{
    readbuffer = fopen(filename, "r");
    if (readbuffer == NULL)
        return;

    char ch;
    char line[128];
    while (TRUE)
    {
        fgets(line, sizeof(line), readbuffer);
        if (feof(readbuffer)) // we should check EOF here as the line is updated so that it will try to print EOF
            break;
        printf("%s", line);
    }
    fclose(readbuffer);
}

void write_line(FILE* restrict writebuffer, const char* filename, const char* line)
{
    writebuffer = fopen(filename, "a");
    if (writebuffer == NULL)
    {
        pflush("no writebuffer found. Returning");
        return;
    }
    fputs(line, writebuffer);
    fclose(writebuffer);
}

char* strlower(char* str, size_t len)
{
    for (int i = 0; i < len; i++)
        str[i] = tolower(str[i]);
    return str;
}