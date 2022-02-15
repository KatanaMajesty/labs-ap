#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

enum PlaneType
{
    UNKNOWN = 0,
    PASSANGER = 1,
    CARGO = 2,
    MILITARY = 3
};

struct _flight_dir
{
    unsigned int flight_days;
    unsigned long flight_id;
};

struct _plane
{
    enum PlaneType plane_type;
    unsigned int capacity;
    float ticket_cost;
};

struct flight_data
{
    struct _plane plane;
    struct _flight_dir dir;
};

FILE* restrict writebuffer;
FILE* restrict readbuffer;
char _path[32] = "../data/14/";
char _filename[16] = "flight_data.bin";

struct flight_data* gen_data(unsigned int i);
// write data with writebuffer to filename with a pointer at first element of array data, which size is len
void write_data(FILE* restrict writebuffer, const char* filename, struct flight_data* data, size_t len);
// write data with writebuffer to filename with a pointer at the element you want to see at index i in binary file
void insert_data(FILE* restrict writebuffer, const char* filename, struct flight_data* data, unsigned int i);
void get_data(FILE* restrict readbuffer, struct flight_data* _dest) __attribute_deprecated_msg__("use read_data instead");
// get data with readbuffer from filename at index i to _dest
// index go from 0 to N (zero-based)
struct flight_data* read_data(FILE* restrict readbuffer, const char* filename, unsigned int i, struct flight_data* _dest) __attribute_warn_unused_result__;
// print flight data with readbuffer at filename
void print_flight_data(FILE* restrict readbuffer, const char* filename);

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

    write_data(writebuffer, filepath, &data[0], 3);
    print_flight_data(readbuffer, filepath);
    // write_data()
    struct flight_data _data = {
        {UNKNOWN, 233, 433.99},
        {7, 43554345}
    };
    insert_data(writebuffer, filepath, &_data, 1);
    printf("====\n");
    print_flight_data(readbuffer, filepath);
    return 0;
}

void write_data(FILE* writebuffer, const char* filename, struct flight_data* data, size_t len)
{
    writebuffer = fopen(filename, "ab");
    for (size_t i = 0; i < len; i++)
    {
        fwrite(&data[i], sizeof(struct flight_data), 1, writebuffer);
    }
    fclose(writebuffer);
}

void insert_data(FILE* restrict writebuffer, const char* filename, struct flight_data* data, unsigned int i)
{
    writebuffer = fopen(filename, "rb+");
    fseek(writebuffer, sizeof(struct flight_data) * i, SEEK_SET);
    fwrite(data, sizeof(struct flight_data), 1, writebuffer);
    fclose(writebuffer);
}

struct flight_data* read_data(FILE* restrict readbuffer, const char* filename, unsigned int i, struct flight_data* _dest)
{
    readbuffer = fopen(filename, "rb");
    fseek(readbuffer, sizeof(struct flight_data) * i, SEEK_SET);
    fread(_dest, sizeof(struct flight_data), 1, readbuffer);
    fclose(readbuffer);
    return _dest;
}

void print_flight_data(FILE* restrict readbuffer, const char* filename)
{
    readbuffer = fopen(filename, "rb");
    while (TRUE)
    {
        struct flight_data output;
        if (fread(&output, sizeof(struct flight_data), 1, readbuffer) != 1)
        {
            if (feof(readbuffer))
                printf("[LOG] EOF\n");
            else printf("[LOG] Error while reading binary\n");
            break;
        }
        printf("[LOG] Plane Type: %d; Capacity: %d; Cost: %f\n", 
                output.plane.plane_type, 
                output.plane.capacity, 
                output.plane.ticket_cost
        );
    }
    fclose(readbuffer);
}