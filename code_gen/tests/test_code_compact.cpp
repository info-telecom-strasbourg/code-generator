#include <iostream>
#include "codeCompact.hpp"

int main(void)
{
    codeCompact::compact("files/files_compact/origin_file.txt", "files/files_compact/compacted_file.txt");
    return 0;
}