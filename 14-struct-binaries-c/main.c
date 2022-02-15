#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <kbin.h>

FILE* restrict _writebuffer;
FILE* restrict _readbuffer;

char _path[32] = "../data/14/";
char _filename[16] = "flight_data.bin";

// returns 1 if flight_dirs are equal, otherwise 0
int fdircmp(struct flight_dir dir1, struct flight_dir dir2)
{
    for (int i = 0; i < 7; i++)
    {
        if (dir1.flight_days[i] != dir2.flight_days[i])
            return 0;
    }
    // return dir1.flight_id == dir2.flight_id;
    return 1; // <- we should ignore flight_id according to task
}

// "constructor" for flight direction (more convenient way)
struct flight_dir get_flight_dir(enum DaysEnum days[], size_t arr_len, unsigned long flight_id)
{
    struct flight_dir output = { // <- initialize empty-value struct
        {0, 0, 0, 0, 0, 0, 0}, 0
    };
    for (int i = 0; i < arr_len; i++) // <- change desired days to 1
    {
        output.flight_days[days[i]] = 1;
    }
    output.flight_id = flight_id;
    return output;
}

// returns the flight_id of a plane with minimal ticket cost at desired flight direction
// returns NULL if no appropriate flight_id was find
unsigned long get_min_ticket_price(struct flight_dir direction, const char* filename)
{
    struct flight_data* output = malloc(sizeof(struct flight_data));
    read_data(_readbuffer, filename, 0, output); // <- needed in order to assign the first ticket cost, so there are no UB (ignore unused_result)
    float min_cost = output->plane.ticket_cost;
    unsigned long _flight_id = output->dir.flight_id;

    // read_data will return 0 when there is no more data left in binary file
    for (int i = 1; read_data(_readbuffer, filename, i, output); i++) // start from 1, as 0 is already in min_cost
    {
        if (!fdircmp(direction, output->dir)) // returns 0 if dir1 and dir2 aren't equal
            continue;

        if (min_cost > output->plane.ticket_cost)
        {
            min_cost = output->plane.ticket_cost;
            _flight_id = output->dir.flight_id;
        }
        printf("[[LOG]] iteration :%d; min_cost: %f; flight_id: %lu\n", i, min_cost, _flight_id);
    }

    free(output);

    return _flight_id;
}

int main(void)
{
    char* filepath = strcat(_path, _filename);
    struct flight_data data[3] = {
        {
            {PASSANGER, 32, 6.99},
            get_flight_dir((enum DaysEnum[]){MONDAY, TUESDAY}, 2, 3974596)
        },
        {
            {CARGO, 220, 39.99},
            {{0, 1, 0, 0, 1, 1, 1}, 143985748}
        },
        {
            {MILITARY, 160, 590.99},
            get_flight_dir((enum DaysEnum[]){MONDAY, TUESDAY}, 2, 78433)
        }
    };
    write_data(_writebuffer, filepath, &data[0], 3);
    print_flight_data(_readbuffer, filepath);
    struct flight_data _data = {
        {UNKNOWN, 233, 433.99},
        get_flight_dir((enum DaysEnum[]){TUESDAY, MONDAY}, 2, 92376434)
    };

    replace_data(_writebuffer, filepath, &_data, 2);
    printf("====\n");
    print_flight_data(_readbuffer, filepath);

    printf("====\n");
    remove_data(_readbuffer, filepath, 1);
    print_flight_data(_readbuffer, filepath);

    printf("flight_id: %lu\n", get_min_ticket_price(get_flight_dir((enum DaysEnum[]){MONDAY, TUESDAY}, 2, 1), filepath));

    return 0;
}

