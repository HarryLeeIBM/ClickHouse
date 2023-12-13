#include <string>
#include <vector>

#include <Interpreters/FTSTokenExtractor.h>
#include <gtest/gtest.h>

using namespace DB;

TEST(FTSTokenExtractor, SimpleTest)
{
    String test_string = "ABC TEST XYZ";
    FTSTokenExtractor token_extractor;

    token_extractor.openText(test_string.c_str(), test_string.length());
    const char *token_start = nullptr;
    size_t token_length = 0;
    while(token_extractor.nextToken(token_start, token_length))
    {
        String str(token_start, token_length);
        std::cout << str << std::endl;
    }
    token_extractor.closeText();
}
