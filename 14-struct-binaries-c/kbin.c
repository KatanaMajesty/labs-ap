#include <stdio.h>
#include <kbin.h>

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

void replace_data(FILE* restrict writebuffer, const char* filename, struct flight_data* data, unsigned int i)
{
    writebuffer = fopen(filename, "rb+");
    fseek(writebuffer, sizeof(struct flight_data) * i, SEEK_SET);
    fwrite(data, sizeof(struct flight_data), 1, writebuffer);
    fclose(writebuffer);
}

unsigned int read_data(FILE* restrict readbuffer, const char* filename, unsigned int i, struct flight_data* _dest)
{
    readbuffer = fopen(filename, "rb");
    fseek(readbuffer, sizeof(struct flight_data) * i, SEEK_SET);
    unsigned int result = fread(_dest, sizeof(struct flight_data), 1, readbuffer);
    fclose(readbuffer);
    return result;
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
        printf("[LOG] Plane Type: %d; Capacity: %d; Cost: %f; Flight ID: %lu\n", 
                output.plane.plane_type, 
                output.plane.capacity, 
                output.plane.ticket_cost,
                output.dir.flight_id
        );
    }
    fclose(readbuffer);
}