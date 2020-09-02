#include <iostream>
#include "unit_test.hpp"
#include "codeCompact.hpp"


/**
 * Test the generation of comments
 */
void test_compact(void)
{
    codeCompact::compact("files/files_compact/originFile.txt", "files/files_compact/testFile.txt");
    assert_file("files/files_compact/testFile.txt", "files/files_compact/compactedFile.txt");
    remove("files/files_compact/testFile.txt");
}

int main(void)
{
    std::cout << "----- Launch tests for the library codeCompact -----" << std::endl << std::endl;
    TEST(test_compact);

    return 0;
}
