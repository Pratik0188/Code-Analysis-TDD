/*
  @file CodeAnalysisTest.cpp

  Test program for analysis requests
*/

#include "CodeAnalysis.hpp"

#include <string>
#include <cassert>
#include <iostream>

int main() {

    // option language
    {
        AnalysisRequest request;
        request.sourceCode = R"(
if (a < b) a = b;
)";
        request.diskFilename    = "";
        request.entryFilename   = "";
        request.optionFilename  = "";
        request.sourceURL       = "";
        request.optionURL       = "";
        request.optionLanguage  = "C++";
        request.defaultLanguage = "";
        request.optionHash      = "";
        request.optionLOC       = -1;
        request.timestamp       = "";

        assert(formatAnalysisXML(request) ==
            R"(<?xml version="1.0" encoding="UTF-8" standalone="yes"?>
<code:unit xmlns:code="http://mlcollard.net/code" language="C++">
if (a &lt; b) a = b;
</code:unit>
)");
    }

    return 0;
}
