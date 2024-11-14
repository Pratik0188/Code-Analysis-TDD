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

    // Handle case where language cannot be determined (extension not supported)
    if (request.optionLanguage.empty() && request.diskFilename != "-") {
        std::cerr << "Extension not supported" << std::endl;
        return "";
    }

    // Handle case where stdin is used but no declared language
    if (request.diskFilename == "-" && request.optionLanguage.empty()) {
        std::cerr << "Using stdin requires a declared language" << std::endl;
        return "";
    }

    // Wrap the content with a unit element
    XMLWrapper unit("code", "http://mlcollard.net/code");
    unit.startElement("unit");

    // Initialize language, choosing from optionLanguage or filename
    std::string language;
    if (!request.optionLanguage.empty()) {
        language = request.optionLanguage;
    } 
    if (language.empty()) {
        language = filenameToLanguage(request.diskFilename);
    }

    // Error handling
    if (language.empty()) {
        if (request.diskFilename.empty()) {  // Standard input case
            std::cerr << "Using stdin requires a declared language" << std::endl;
        } else {  // Extension-based language determination
            std::cerr << "Extension not supported" << std::endl;
        }
        return "";  
    }

    unit.addAttribute("language", request.optionLanguage);

    // Initialize filename with the disk filename by default
    std::string_view filename = request.diskFilename;

    // Determine the filename based on the optionFilename priority
    if (!request.optionFilename.empty()) {
    filename = request.optionFilename;
    }

    if (filename == "-" && !request.entryFilename.empty()) {
        // If diskFilename is "-" (stdin), use entryFilename as filename attribute
        filename = request.entryFilename;
    }
    if (!request.entryFilename.empty() && filename == request.diskFilename) {
        // Use entryFilename if it's not empty and diskFilename isn't "-"
        filename = request.entryFilename;
    }

    // Add filename attribute if it's not empty
    if (!filename.empty()) {
        unit.addAttribute("filename", filename);
    }

    // Use timestamp as an attribute if it's not empty
    if (!request.timestamp.empty()) {
        unit.addAttribute("timestamp", request.timestamp);
    }

    // Add loc attribute if optionLOC is non-negative
    if (request.optionLOC >= 0) {
        unit.addAttribute("loc", std::to_string(request.optionLOC));
    }

    // Add url attribute, prioritizing optionURL over sourceURL
    if (!request.optionURL.empty()) {
    unit.addAttribute("url", request.optionURL);
    }
    if (request.optionURL.empty() && !request.sourceURL.empty()) {
        unit.addAttribute("url", request.sourceURL);
    }


    // Add hash attribute if optionHash is non-empty
    if (!request.optionHash.empty()) {
        unit.addAttribute("hash", request.optionHash);
    }

    unit.addContent(request.sourceCode);
    unit.endElement();

    return unit.xml();
}