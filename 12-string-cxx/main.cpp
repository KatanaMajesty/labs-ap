#include <iostream>
#include <vector>

// will split a string by delimeter into a vector
std::vector<std::string> split_delim(const char* str, size_t len, char delim)
{
    std::vector<std::string> m_words;
    
    int begpoint = 0;
    int wlen;
    for (int i = 0; i < len + 1; i++) // <- 1 more iteration to append last word, which is not followed by space but by '\0'
    {
        if (str[i] == delim || str[i] == '\0')
        {
            wlen = i - begpoint; // word length
            char* m_tempbuff = new char[wlen + 1];
            m_tempbuff[wlen] = '\0';
            for (int j = 0; j < wlen; j++) // <- will copy currently found word to m_tempbuff
            {
                m_tempbuff[j] = str[begpoint + j]; 
            }
            begpoint = i + 1; // <- will be on the beginning of the next word
            // std::cout << "\n[LOG] split_delim (found word): " << m_tempbuff;
            m_words.push_back(m_tempbuff);
            delete[] m_tempbuff; // <- free allocated memory
        }
    }
    return m_words;
}

char* encode(const char* base, size_t base_size, const char* input, size_t input_size, char delim)
{
    std::vector<std::string> base_words = split_delim(base, base_size, delim);
    std::vector<std::string> input_words = split_delim(input, input_size, delim);

    // Base: HELLO_WORLD_GOODBYE_NIGHT
    // Input: HI_GUYS
    // BASE_BASE_INPUT_BASE_BASE_INPUT
    // Output: HELLO_WORLD_HI_GOODBYE_NIGHT_GUYS

    const int word_count = base_words.size() + input_words.size(); 
    int act_size = input_size + base_size + 1; // 1 stands for extra delimeter after concatenating both strings
    char* newbuff = new char[act_size + 1];
    int cursor = 0;
    int input_cursor = 0;
    int base_cursor = 0;
    for (int i = 0; i < word_count; i++)
    {
        std::string target = i % 3 == 2 ? 
                input_words.at(input_cursor++) : 
                base_words.at(base_cursor++);
    
        size_t wlen = target.size();;
        for (int j = 0; j < wlen; j++)
        {
            newbuff[cursor + j] = target[j];
        }
        if (i != word_count - 1)
            newbuff[cursor + wlen] = delim;
        cursor += wlen + 1;
    }
    newbuff[act_size] = '\0'; 
    return newbuff;
}

char* decode(const char* buffer, size_t buff_size, char delim)
{
    std::vector<std::string> buffvec = split_delim(buffer, buff_size, delim);

    char* newbuff = new char[buff_size + 1];
    const int word_count = buffvec.size();
    int cursor = 0;
    for (int i = 0; i < word_count; i++)
    {
        if (i % 3 == 2)
        {
            std::string curr_word = buffvec.at(i);
            size_t wlen = curr_word.size();
            for (int j = 0; j < wlen; j++)
            {
                newbuff[cursor + j] = curr_word[j];
            }
            if (i != word_count - 1)
                newbuff[cursor + wlen] = delim;
            cursor += wlen + 1;
        }
    }
    newbuff[buff_size] = '\0';
    return newbuff;
}

int main(void)
{
    std::string input;
    std::string base;
    
    std::cout << "Enter base\n";
    std::cin >> base;

    std::cout << "Enter input\n";
    std::cin >> input;

    std::cout << "[LOG] Base: " << base << std::endl;
    std::cout << "[LOG] Input: " << input << std::endl;

    int act_size = input.size() + base.size() + 1; // <- needed to decode a string
    char* encoded = encode(base.c_str(), base.size(), input.c_str(), input.size(), '_');
    std::cout << "[LOG] Encoded result: " << encoded << std::endl;
    std::cout << "[LOG] Decoded result: " << decode(encoded, act_size, '_') << std::endl;
}