#ifndef KBIN
#define KBIN

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct flight_data* gen_data    (unsigned int i);
// write data with writebuffer to filename with a pointer at first element of array data, which size is len
void write_data                 (FILE* writebuffer, const char* filename,   struct flight_data* data, size_t len);
// write data with writebuffer to filename with a pointer at the element you want to see at index i in binary file
void insert_data                (FILE* writebuffer, const char* filename,   struct flight_data* data, unsigned int i);
void remove_data                (FILE* readbuffer,  const char* filename,   unsigned int i);                                __attribute_malloc__
// get data with readbuffer from filename at index i to _dest
// index go from 0 to N (zero-based)
struct flight_data* read_data   (FILE* readbuffer,  const char* filename,   unsigned int i, struct flight_data* _dest)      __attribute_warn_unused_result__;
// print flight data with readbuffer at filename
void print_flight_data          (FILE* readbuffer,  const char* filename);

#endif // KBIN