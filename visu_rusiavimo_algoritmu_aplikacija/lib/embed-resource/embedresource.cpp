#include <iostream>
#include <fstream>
#include <cstdlib>
#include <algorithm>
#include <string>
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;
using namespace std;

int main(int argc, char** argv)
{
    if (argc < 3) {
        fprintf(stderr, "USAGE: %s {sym} {rsrc}\n\n"
                        "  Creates {sym}.c from the contents of {rsrc}\n",
                argv[0]);
        return EXIT_FAILURE;
    }

    fs::path dst{argv[1]};
    fs::path src{argv[2]};

    string sym = src.filename().string();
    std::replace(sym.begin(), sym.end(), '.', '_');
    std::replace(sym.begin(), sym.end(), '-', '_');

    create_directories(dst.parent_path());

    std::ofstream ofs{dst};

    std::ifstream ifs{src};

    ofs << "#include <stdlib.h>" << endl;
    ofs << "const char _resource_" << sym << "[] = {" << endl;

    size_t lineCount = 0;
    while (!ifs.eof())
    {
        char c;
        ifs.get(c);
        ofs << "0x" << hex << (c&0xff) << ", ";
        if (++lineCount == 10) {
            ofs << endl;
            lineCount = 0;
        }
    }


    ofs << "};" << endl;
    ofs << "const size_t _resource_" << sym << "_len = sizeof(_resource_" << sym << ");";

    return EXIT_SUCCESS;
}
