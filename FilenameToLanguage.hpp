/*
  @file FilenameToLanguage.hpp

  Declaration of filenameToLanguage()
*/

#ifndef INCLUDED_FILENAMETOLANGUAGE_HPP
#define INCLUDED_FILENAMETOLANGUAGE_HPP

#include <string_view>

/**
 * Language based on the filename
 *
 * @param  filename Name of a source-code file
 * @retval language Programming language, empty string if no associated language
 */
std::string_view filenameToLanguage(std::string_view filename);

#endif
