
#include <iostream>
#include <sstream>
#include <cstdlib>

const char default_glyphs[2] = { ' ', '*' };

std::string pyramid(unsigned int height, const char* glyphs = default_glyphs ) {
    const unsigned int width = 2u*height-1u;

    std::stringstream ss;
    for(unsigned int i=1; i<=height; i++) {
        ss << '|';
        for(unsigned int j=1; j<=width; j++) {
            ss << glyphs[(j<height+i) && (j>height-i)];
        }
        ss << '|' << std::endl;
    }
    return ss.str();
}

int main(int argc, const char *argv[]) {
    std::cout << pyramid(10) << std::endl; 
    return EXIT_SUCCESS;
}
