#include <stdio.h>
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

void remove_data(FILE* restrict readbuffer, const char* filename, unsigned int i)
{
    char* tmp_filename = malloc(strlen(filename) + 4);
    strcpy(tmp_filename, filename);
    strcat(tmp_filename, ".tmp");

    int j = 0;
    int found = FALSE;

    readbuffer = fopen(filename, "rb");
    if (!readbuffer)
    {
        printf("Unable to open file %s\n", filename);
        return;
    }
    FILE* tmpbuffer = fopen(tmp_filename, "wb");
    if (!tmpbuffer)
    {
        printf("Unable to open file temp file.\n");
        return;
    }
    struct flight_data output;
    
    for (int j = 0; fread(&output, sizeof(struct flight_data), 1, readbuffer) == 1; j++)
    {
        if (i == j)
        {
            printf("Successfully deleted record at index %d\n", i);
            found = TRUE;
        }
        else fwrite(&output, sizeof(struct flight_data), 1, tmpbuffer);
    }
    if (!found)
        printf("Couldn't find a record at index %d\n", i);

    fclose(readbuffer);
    fclose(tmpbuffer);

    remove(filename);
    rename(tmp_filename, filename);
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