#ifndef KBIN
#define KBIN

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE    1
#define FALSE   0

// uint8_t, uint16_t, uint32_t and uint64_t.
// unsigned char, unsigned short, unsigned int and unsigned long long.

enum DaysEnum
{
    MONDAY      = 0, 
    TUESDAY     = 1, 
    WEDNESDAY   = 2, 
    THURSDAY    = 3, 
    FRIDAY      = 4, 
    SATURDAY    = 5, 
    SUNDAY      = 6
};

enum PlaneType
{
    UNKNOWN     = 0,
    PASSANGER   = 1,
    CARGO       = 2,
    MILITARY    = 3
};

struct flight_dir
{
    __uint8_t       flight_days[7]; // <- flight days per week (0 represent that this plane wont fly at that day, vice versa for 1)
    __uint64_t      flight_id;
};

struct plane
{
    enum PlaneType  plane_type;
    __uint32_t      capacity;
    float           ticket_cost;
};

// flight data consists of plane structure and flight direction
// flight direction consists of uint array[7] which represents a week staring from MONDAY and of ulong - flight id
struct flight_data
{
    struct plane       plane;
    struct flight_dir  dir;
};

struct flight_data* gen_data    (unsigned int i);
// write data with writebuffer to filename with a pointer at first element of array data, which size is len
void write_data                 (FILE* writebuffer, const char* filename,   struct flight_data* data, size_t len);
// write data with writebuffer to filename with a pointer at the element you want to see at index i in binary file
void replace_data               (FILE* writebuffer, const char* filename,   struct flight_data* data, unsigned int i);
void remove_data                (FILE* readbuffer,  const char* filename,   unsigned int i);                                //__attribute_malloc__
// get data with readbuffer from filename at index i to _dest
// index go from 0 to N (zero-based)
// RETURNS 0 if no data was found, 1 if data was successfully read
__uint32_t read_data            (FILE* readbuffer,  const char* filename,   unsigned int i, struct flight_data* _dest)      __attribute_warn_unused_result__;
// print flight data with readbuffer at filename
void print_flight_data          (FILE* readbuffer,  const char* filename);

#endif // KBIN