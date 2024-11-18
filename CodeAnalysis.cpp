/*
@file CodeAnalysis.cpp
Implementation of analysis requests
*/

#include "CodeAnalysis.hpp"
#include "FilenameToLanguage.hpp"
#include "XMLWrapper.hpp"
#include <iostream>

/**
 * Generate source analysis XML based on the request
 * Content is wrapped with an XML element that includes the metadata
 *
 * @param request Data that forms the request
 * @retval Source analysis request in XML format
 * @retval Empty string if invalid
 */
std::string formatAnalysisXML(const AnalysisRequest& request) {

    // Check for missing language or unsupported extension
    if (request.optionLanguage.empty() && request.diskFilename != "-") {
        std::cerr << "Extension not supported" << std::endl;
        return "";
    }
    if (request.diskFilename == "-" && request.optionLanguage.empty()) {
        std::cerr << "Using stdin requires a declared language" << std::endl;
        return "";
    }

    // Initialize language and determine its value with if-then logic
    std::string_view language;
    if (!request.optionLanguage.empty()) {
        language = request.optionLanguage;
    }
    if (language.empty()) {
        language = filenameToLanguage(request.diskFilename);
    }
    if (language.empty()) {
        if (request.diskFilename.empty()) {
            std::cerr << "Using stdin requires a declared language" << std::endl;
            return "";
        }
        std::cerr << "Extension not supported" << std::endl;
        return "";
    }

    // Initialize filename and determine its value with if-then logic
    std::string_view filename = request.diskFilename;
    if (!request.optionFilename.empty()) {
        filename = request.optionFilename;
    }
    // Special case for stdin input with diskFilename as "-" and entryFilename as "data"
    if (request.diskFilename == "-" && request.entryFilename == "data" && !request.optionFilename.empty()) {
        filename = request.optionFilename; // Use optionFilename in this case
    }
    if (filename == "-" && !request.entryFilename.empty()) {
        filename = request.entryFilename;
    }
    if (!request.entryFilename.empty() && filename == request.diskFilename) {
        filename = request.entryFilename;
    }

    // Create XML wrapper and add the starting element
    XMLWrapper unit("code", "http://mlcollard.net/code");
    unit.startElement("unit");

    // Output attributes
    unit.addAttribute("language", language);
    if (!filename.empty()) {
        unit.addAttribute("filename", filename);
    }
    if (!request.timestamp.empty()) {
        unit.addAttribute("timestamp", request.timestamp);
    }
    if (request.optionLOC >= 0) {
        unit.addAttribute("loc", std::to_string(request.optionLOC));
    }
    if (!request.optionURL.empty()) {
        unit.addAttribute("url", request.optionURL);
    }
    if (!request.sourceURL.empty() && request.optionURL.empty()) {
        unit.addAttribute("url", request.sourceURL);
    }
    if (!request.optionHash.empty()) {
        unit.addAttribute("hash", request.optionHash);
    }

    // Add the source code content and end the element
    unit.addContent(request.sourceCode);
    unit.endElement();

    return unit.xml();
}