#include <string.h>

#include "FTSTokenExtractor.h"

namespace DB
{
    FTSTokenExtractor::FTSTokenExtractor()
    {
        UErrorCode error_code = U_ZERO_ERROR;
        token_iter = ubrk_open(UBRK_WORD, "en_us", nullptr, 0, &error_code);
        if (U_FAILURE(error_code))
        {
            //std::cout << "Error: Failed to create Unicode Break Iterator." << std::endl;

            return;
        }
    }
    
    bool FTSTokenExtractor::isDelimiter(char ch) const
    {
        return memchr(";,'\"!?\r\n\t ()[]{}<>", ch, 18) != nullptr;
    }

    void FTSTokenExtractor::trim()
    {
        while (prev_pos < current_pos && isDelimiter(*(data + prev_pos)))
            prev_pos++;

        while (prev_pos < current_pos && isDelimiter(*(data + current_pos - 1)))
            current_pos--;
    }

    bool FTSTokenExtractor::nextToken(const char * & token_start, size_t & token_length)
    {
        while (true)
        {

            if (prev_pos == -1)
            {
                prev_pos = 0;
                current_pos = ubrk_first(token_iter);
            }
            else
            {
                prev_pos = current_pos;
                current_pos = ubrk_next(token_iter);
            }

            if(current_pos == UBRK_DONE)
                return false;

            trim();
            if (current_pos == prev_pos)
                continue;

            token_start = data + prev_pos;
            token_length = current_pos - prev_pos;

            break;
        }
        return true;
    }
}
