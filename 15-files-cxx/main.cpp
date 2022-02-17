#include <string>
#include <string.h>
#include <iostream>
#include <vector>
#include <fstream>

struct Record
{
    // SURNAME NAME MIDNAME NUMBER
    std::string _arr[4];

    Record() = default;
    Record(char* line)
    {
        const char* delim = " ,.:;?!";
        char* word;
        for (int i = 0; i < 4; i++)
        {
            word = strtok(i == 0 ? line : NULL, delim);

            if (word == NULL)
                throw std::runtime_error("unexcepted format");

            _arr[i] = word;
        }
    }

    std::string get_initials()
    {
        return _arr[0] + " " + _arr[1] + " " + _arr[2];
    }

    std::string get_number()
    {
        return _arr[3];
    }
};

const char* filename = "../data/15/data.txt";

void write_file(const char* filename)
{
    std::ofstream fout(filename, std::ios_base::out);
    if (!fout.is_open())
        throw std::runtime_error("couldn't open/create a file");

    std::string buffer;
    while (true)
    {
        std::getline(std::cin, buffer);
        if (buffer == "")
            break;

        fout << buffer << std::endl;
    }
    fout.close();
}

std::vector<Record> read_file(const char* filename)
{
    std::vector<Record> records{};
    std::ifstream fin(filename, std::ios_base::in);

    if (!fin.is_open())
        throw std::runtime_error("couldn't read a file");

    size_t pos = 0;
    while (fin.peek() != EOF)
    {
        char line[128];
        fin.getline(line, 128);
        records.push_back(Record(line)); // rvalue ref
    }
    fin.close();
    return records;
}

int main(void)
{
    std::cout << "Keep entering file info or leave a blank line to stop entering and continue." << std::endl;
    write_file(filename);
    std::vector<Record> vec = read_file(filename);
    
    std::cout << "Enter the name of person:" << std::endl;
    std::string request;
    std::getline(std::cin, request);

    for (int i = 0; i < vec.size(); i++)
    {
        if (vec[i].get_initials() == request)
            std::cout << "Number of " << request << ": " << vec[i].get_number() << std::endl;
    }
}