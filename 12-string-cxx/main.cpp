#include <iostream>
#include <vector>
#include <string.h>

// will split a string by delimeter and create a vector
std::vector<std::string> split_delim(std::string str, char delim)
{
    std::vector<std::string> m_words;
    const char* cstr = str.c_str();
    
    char* word = strtok((char*) cstr, &delim); // <- (char*) cast is very unlikely as it may be UB, but not for strtok (no modification of string)
    while (word != NULL)
    {
        m_words.push_back(word);
        word = strtok(NULL, &delim); 
    }
    
    return m_words;
}

std::string encode(const char* base, size_t base_size, const char* input, size_t input_size, char delim)
{
    std::vector<std::string> base_words = split_delim(base, delim);
    std::vector<std::string> input_words = split_delim(input, delim);

    // Base: HELLO_WORLD_GOODBYE_NIGHT
    // Input: HI_GUYS
    // BASE_BASE_INPUT_BASE_BASE_INPUT
    // Output: HELLO_WORLD_HI_GOODBYE_NIGHT_GUYS

    size_t word_count = base_words.size() + input_words.size(); 
    // int act_size = input_size + base_size + 1; // 1 stands for extra delimeter after concatenating both strings
    std::string result_string;
    
    int input_cursor = 0;
    int base_cursor = 0;
    
    if (base_words.size() / 2 != input_words.size()) // check if there are enough words in BASE, so there are no std::out_of_range error
    {
        std::cout << "Not enough words in base!" << std::endl;
        return "undefined"; // <- std::string(nullptr) will lead to UB
    }

    for (size_t i = 0; i < word_count; i++)
    {
        std::string target = i % 3 == 2 ? // hardcode pog
                input_words.at(input_cursor++) : 
                base_words.at(base_cursor++);
    
        result_string.append(target);
        if (i != word_count - 1)
            result_string.append(&delim);
    }
    // result_string[act_size] = '\0'; // <- null-term char automatically appended by std::string
    return result_string;
}

std::string decode(std::string buffer, char delim)
{
    std::vector<std::string> buffvec = split_delim(buffer.c_str(), delim);

    std::string decoded;
    size_t word_count = buffvec.size();
    for (int i = 0; i < word_count; i++)
    {
        if (i % 3 == 2)
        {
            std::string curr_word = buffvec.at(i);

            decoded.append(curr_word);
            if (i != word_count - 1)
                decoded.append(&delim); 
        }
    }
    // newbuff[buff_size] = '\0'; // <- null-term char automatically appended by std::string
    return decoded;
}

int main(void)
{
    char delim = '_';
    std::string input;
    std::string base;
    
    std::cout << "Enter base\n";
    std::cin >> base;

    std::cout << "Enter input\n";
    std::cin >> input;

    std::cout << "[LOG] Base: " << base << std::endl;
    std::cout << "[LOG] Input: " << input << std::endl;

    int act_size = input.size() + base.size() + 1; // <- needed to decode a string
    std::string encoded = encode(base.c_str(), base.size(), input.c_str(), input.size(), delim);
    std::cout << "[LOG] Encoded result: " << encoded << std::endl;
    std::cout << "[LOG] Decoded result: " << decode(encoded, delim) << std::endl;
}