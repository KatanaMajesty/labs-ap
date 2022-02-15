#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <kbin.h>

FILE* restrict _writebuffer;
FILE* restrict _readbuffer;

char _path[32] = "../data/14/";
char _filename[16] = "flight_data.bin";

// FIXME: struct constructor wont work correctly
// "constructor" for flight direction (more convenient way)
struct flight_dir get_flight_dir(enum DaysEnum days[], size_t arr_len, unsigned long flight_id)
{
    unsigned char _days[7];
    for (int i = 0; i < arr_len; i++)
    {
        _days[days[i]] = 1;
    }

    struct flight_dir output = {
        .flight_days = _days, 
        .flight_id = flight_id
    };
    return output;
}

// FIXME: currently UB
unsigned long get_min_ticket_price(struct flight_dir direction, const char* filename)
{
    struct flight_data* output = malloc(sizeof(struct flight_data));
    
    for (int i = 0; read_data(_readbuffer, filename, i, output); i++)
    {
        printf("[[LOG]]: Flight days: ");
        for (int j = 0; j < 7; j++)
        {
            printf("%u ", output->dir.flight_days[j]);
        }
        printf("\n");
        printf("[[LOG]]: Flight id: %lu\n", output->dir.flight_id);
    }
}

int main(void)
{
    char* filepath = strcat(_path, _filename);
    struct flight_data data[3] = {
        {
            {PASSANGER, 32, 6.99},
            get_flight_dir((enum DaysEnum[]){MONDAY, TUESDAY}, 2, 00000000)
        },
        {
            {CARGO, 220, 39.99},
            {{0, 1, 0, 0, 1, 1, 1}, 143985748}
        },
        {
            {MILITARY, 160, 590.99},
            get_flight_dir((enum DaysEnum[]){WEDNESDAY, TUESDAY}, 2, 12323235453)
        }
    };
    write_data(_writebuffer, filepath, &data[0], 3);
    print_flight_data(_readbuffer, filepath);
    struct flight_data _data = {
        {UNKNOWN, 233, 433.99},
        get_flight_dir((enum DaysEnum[]){TUESDAY, FRIDAY}, 2, 00000000)
        // {{1, 1, 1, 1, 1, 0, 0}, 1111111111}
    };

    replace_data(_writebuffer, filepath, &_data, 2);
    printf("====\n");
    print_flight_data(_readbuffer, filepath);

    printf("====\n");
    remove_data(_readbuffer, filepath, 1);
    print_flight_data(_readbuffer, filepath);

    get_min_ticket_price(get_flight_dir((enum DaysEnum[]){MONDAY, TUESDAY}, 2, 0000000), filepath);

    return 0;
}

