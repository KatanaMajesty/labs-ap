#include <string>
#include <string.h>
#include <iostream>
#include <vector>
#include <fstream>

/*
Панасенко Александр Андреевич +380-99-256-46-41
Терентьев Михаил Павлович 22-505
Сергеев Сергей Сергеевич +380-99-999-49-99
*/

const char* filename = "../data/15/data";

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

        // fout.write(buffer.c_str(), 128);
        fout << buffer << std::endl;
    }
    fout.close();
}

std::string find_number(const char* filename, const std::string& request)
{
    std::ifstream fin(filename, std::ios_base::in);
    if (!fin.is_open())
        throw std::runtime_error("couldn't read a file");

    std::string word;
    std::string initials;
    for (int i = 0; true; i++)
    {
        fin >> word;
        if (fin.peek() == EOF)
            break;

        if (i % 4 == 3) // number
        {
            if (request == initials)
                return word;
            else initials = "";
        }
        // initials
        else initials.append(word + " "); 
        if (fin.peek() == '\n')
            initials = "";
    }
    return "unknown";
}

int main(void)
{
    std::cout << "Keep entering file info or leave a blank line to stop entering and continue." << std::endl;
    write_file(filename);
    
    std::cout << "Enter the name of person:" << std::endl;
    std::string request;
    std::getline(std::cin, request);
    request.append(" "); // <- to avoid bugs

    std::string result = find_number(filename, request);
    if (result == "unknown")
        std::cout << "Failed to find a number of requested student" << std::endl;
    else std::cout << "Number of student " << request << ": " << result << std::endl;
}