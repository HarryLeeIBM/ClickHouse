#pragma once

#include <base/types.h>
#include <cassert>
#include <unicode/utext.h>
#include <unicode/ubrk.h>
#include <unicode/ustring.h>

namespace DB
{
class FTSTokenExtractor
{
public:
    FTSTokenExtractor();
    ~FTSTokenExtractor()
    {
        if(token_iter != nullptr)
        {
            ubrk_close(token_iter);
        }
    }

    void openText(const char * data_, size_t length)
    {
        UErrorCode status = U_ZERO_ERROR;
        text = utext_openUTF8(nullptr, data_, length, &status);
        if (U_FAILURE(status)) {
            //std::cout << "Error: Failed to set text to be iterated over." << std::endl;
            return;
        }
        ubrk_setUText(token_iter, text, &status);

        data = data_;
        current_pos = 0;
        prev_pos = -1;
    }

    bool nextToken(const char * & token_start, size_t & token_length);

    void closeText()
    {
        assert(text != nullptr);
        utext_close(text);
        text = nullptr;
    }
private:
    UBreakIterator* token_iter = nullptr;
    UText *text = nullptr;
    Int32 prev_pos = 0;
    Int32 current_pos = 0;
    const char *data = nullptr;
};

}
