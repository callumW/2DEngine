/** @file file_utils.h
 *  @brief File Utility Functions
 */
#ifndef EX_NIHILO_FILE_UTILITIES_H
#define EX_NIHILO_FILE_UTILITIES_H

#include <memory>
#include <string>
#include <utility>

/**
 * @brief Load contents of file into a std::vector of chars
 * @param filename filepath of file to load
 * @return std::pair of std::unique_ptr & size_t. On succes, the unique_ptr will point to an array
 * of chars loaded from the file and the size_t member will be the number of chars read. On failure
 * the unique_ptr will be nullptr and the size_t will be 0.
 */
std::pair<std::unique_ptr<char[]>, size_t> read_file(std::string const& filename);
#endif
