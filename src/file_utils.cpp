#include "file_utils.h"

#include <fstream>
#include <iostream>

std::pair<std::unique_ptr<char[]>, size_t> read_file(std::string const& filename)
{
    /* open file at end so we can quickly get file size */
    std::ifstream file(filename, std::ios::ate | std::ios::binary);

    if (file.is_open()) {
        size_t file_size = static_cast<size_t>(file.tellg());
        file.seekg(0);

        std::unique_ptr<char[]> file_data = std::unique_ptr<char[]>(new char[file_size]);

        file.read(file_data.get(), file_size);

        if (file.gcount() != file_size) {
            std::cout << "Failed to read all characters from file: " << filename << " only read "
                      << file.gcount() << " out of " << file_size << " characters" << std::endl;
            file_data = nullptr;
            file_size = 0;
        }

        return std::pair<std::unique_ptr<char[]>, size_t>(std::move(file_data), file_size);
    }
    else {
        std::cout << "failed to open file: " << filename << std::endl;
    }

    return std::make_pair<std::unique_ptr<char[]>, size_t>(std::unique_ptr<char[]>(nullptr), 0);
}
