/*
@file CodeAnalysis.cpp

Implementation of analysis requests
*/

#include "CodeAnalysis.hpp"
#include "FilenameToLanguage.hpp"
#include "XMLWrapper.hpp"
#include <string_view>

/**
 * Generate source analysis XML based on the request
 * Content is wrapped with an XML element that includes the metadata
 *
 * @param request Data that forms the request
 * @retval Source analysis request in XML format
 * @retval Empty string if invalid
 */
std::string formatAnalysisXML(const AnalysisRequest& request) {
    XMLWrapper unit("code", "http://mlcollard.net/code");
    unit.startElement("unit");

    unit.addAttribute("language", request.optionLanguage);

    // Determine the filename based on whether the request is an archive or not
    std::string_view filename = !request.entryFilename.empty() ? request.entryFilename : request.diskFilename;
    // Add filename attribute if it's not empty
    if (!filename.empty()) {
        unit.addAttribute("filename", filename);
    }

    unit.addContent(request.sourceCode);
    unit.endElement();

    return unit.xml();
}
