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
    unit.addContent(request.sourceCode);
    unit.endElement();

    return unit.xml();
}
