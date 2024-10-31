/*
  @file FilenameToLanguage.cpp

  Implementation of filenameToLanguage()
*/

#include "FilenameToLanguage.hpp"
#include <unordered_map>
#include <string>
#include <string_view>

namespace {

    // mapping from file extension to programming language
    const std::unordered_map<std::string_view, std::string_view> extensionToLanguage {

        { ".c", "C" },
        { ".h", "C" },
        { ".i", "C" },
        { ".cpp", "C++" },
        { ".CPP", "C++" },
        { ".cp", "C++" },
        { ".hpp", "C++" },
        { ".cxx", "C++" },
        { ".hxx", "C++" },
        { ".cc", "C++" },
        { ".hh", "C++" },
        { ".c++", "C++" },
        { ".h++", "C++" },
        { ".C", "C++" },
        { ".H", "C++" },
        { ".tcc", "C++" },
        { ".ii", "C++" },
        { ".java", "Java" },
        { ".aj", "AspectJ" },
        { ".cs", "C#" },
    };
}

/**
 * Language based on the filename
 *
 * @param  filename Name of a source-code file
 * @retval language Programming language, empty string if no associated language
 */
std::string_view filenameToLanguage(std::string_view filename) {

    // extract the last extension from the filename, including the '.'
    const auto extensionPosition = filename.rfind('.');
    if (extensionPosition == std::string::npos)
        return "";
    std::string_view extension(filename.substr(extensionPosition));

    // find the extension in the map
    const auto extensionEntry = extensionToLanguage.find(extension);
    if (extensionEntry == extensionToLanguage.end())
        return "";

    // language for this extension from the map
    return extensionEntry->second;
}
