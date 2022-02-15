#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <kbin.h>

#define TRUE    1
#define FALSE   0

enum PlaneType
{
    UNKNOWN     = 0,
    PASSANGER   = 1,
    CARGO       = 2,
    MILITARY    = 3
};

struct _flight_dir
{
    unsigned int    flight_days;
    unsigned long   flight_id;
};

struct _plane
{
    enum PlaneType  plane_type;
    unsigned int    capacity;
    float           ticket_cost;
};

struct flight_data
{
    struct _plane       plane;
    struct _flight_dir  dir;
};

FILE* restrict _writebuffer;
FILE* restrict _readbuffer;
char _path[32] = "../data/14/";
char _filename[16] = "flight_data.bin";



int main(void)
{
    char* filepath = strcat(_path, _filename);
    struct flight_data data[3] = {
        {
            {PASSANGER, 32, 6.99},
            {4, 143378320}
        },
        {
            {CARGO, 220, 39.99},
            {1, 143985748}
        },
        {
            {MILITARY, 160, 590.99},
            {0, 793857444}
        }
    };
    write_data(_writebuffer, filepath, &data[0], 3);
    print_flight_data(_readbuffer, filepath);
    struct flight_data _data = {
        {UNKNOWN, 233, 433.99},
        {7, 43554345}
    };

    insert_data(_writebuffer, filepath, &_data, 1);
    printf("====\n");
    print_flight_data(_readbuffer, filepath);

    printf("====\n");
    remove_data(_readbuffer, filepath, 1);
    print_flight_data(_readbuffer, filepath);

    return 0;
}

