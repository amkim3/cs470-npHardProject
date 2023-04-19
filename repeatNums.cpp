#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

int main() {
     std::string input_filename = "ex.dat";
    std::string output_filename = "output.dat";
    std::ifstream input_file(input_filename);
    std::ofstream output_file(output_filename);

    if (!input_file) {
        std::cerr << "Failed to open input file: " << input_filename << std::endl;
        return 1;
    }

    if (!output_file) {
        std::cerr << "Failed to open output file: " << output_filename << std::endl;
        return 1;
    }

    std::string line;
    while (std::getline(input_file, line)) {
        stringstream ss;
        for(int i=0;i<line.length();i++) if(isdigit(line[i])) ss << line[i];
        string newLine = line;
        output_file << ss.str() << " " << ss.str() << '\r';
    }

    input_file.close();
    output_file.close();

    return 0;
}