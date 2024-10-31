/*
  @file AnalysisRequest.hpp

  Header for analysis requests
*/

#ifndef INCLUDED_ANALYSISREQUEST_HPP
#define INCLUDED_ANALYSISREQUEST_HPP

#include <string>

struct AnalysisRequest {
    std::string sourceCode;
    std::string diskFilename;
    std::string entryFilename;
    std::string optionFilename;
    std::string sourceURL;
    std::string optionURL;
    std::string optionLanguage;
    std::string defaultLanguage;
    std::string optionHash;
    int optionLOC = 0;
    std::string timestamp;
};

#endif
