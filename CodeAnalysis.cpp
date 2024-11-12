/*
@file CodeAnalysis.cpp
Implementation of analysis requests
*/

#include "CodeAnalysis.hpp"
#include "FilenameToLanguage.hpp"
#include "XMLWrapper.hpp"

/**
 * Generate source analysis XML based on the request
 * Content is wrapped with an XML element that includes the metadata
 *
 * @param request Data that forms the request
 * @retval Source analysis request in XML format
 * @retval Empty string if invalid
 */
std::string formatAnalysisXML(const AnalysisRequest& request) {

    // wrap the content with a unit element
    XMLWrapper unit("code", "http://mlcollard.net/code");
    unit.startElement("unit");
    unit.addAttribute("language", request.optionLanguage);

    // Determine the filename based on whether the request is an archive or not
    std::string_view filename;
    if (!request.entryFilename.empty()) {
        filename = request.entryFilename;
    } else {
        filename = request.diskFilename;
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
    // Add url attribute if sourceURL is non-empty
    if (!request.sourceURL.empty()) {
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