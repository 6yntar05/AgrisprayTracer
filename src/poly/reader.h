#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

namespace agris {

    std::string readfile(const std::string& path) {
        // DANGEROUS! Hard-coded XML tags! -> TODO: Get rid
        std::string code;
        std::ifstream file;
        file.exceptions(std::ifstream::badbit);
        try {
            file.open(path);
            std::stringstream stream;
            stream << file.rdbuf();
            file.close();
            code = stream.str();
        } catch (std::ifstream::failure const& e) {
            std::cerr << "Failed to read file!" << std::endl;
        }

        size_t start = code.find("<Placemark");
        size_t stop = code.find("</Placemark>");
        size_t stopTagLen = 12;

        code = "<kml>\n" + code.substr(start, stop - start + stopTagLen) + "\n</kml>";

        return code;
    }
    
}