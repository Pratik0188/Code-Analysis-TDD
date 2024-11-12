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

   // Test case: non-archive source file uses diskFilename as filename attribute
    {
        AnalysisRequest request;
        request.sourceCode = R"(
if (a < b) a = b;
)";
        request.diskFilename    = "main.cpp";
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
<code:unit xmlns:code="http://mlcollard.net/code" language="C++" filename="main.cpp">
if (a &lt; b) a = b;
</code:unit>
)");
    }

    // Test case: archive file uses entryFilename as filename attribute
    {
        AnalysisRequest request;
        request.sourceCode = R"(
if (a < b) a = b;
)";
        request.diskFilename    = "archive.zip";
        request.entryFilename   = "main.cpp"; // Entry filename within the archive
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
<code:unit xmlns:code="http://mlcollard.net/code" language="C++" filename="main.cpp">
if (a &lt; b) a = b;
</code:unit>
)");
    }

    // Test case: include timestamp if it's non-empty
    {
        AnalysisRequest request;
        request.sourceCode = R"(
if (a < b) a = b;
)";
        request.diskFilename    = "main.cpp";
        request.entryFilename   = "";
        request.optionFilename  = "";
        request.sourceURL       = "";
        request.optionURL       = "";
        request.optionLanguage  = "C++";
        request.defaultLanguage = "";
        request.optionHash      = "";
        request.optionLOC       = -1;
        request.timestamp       = "2024-11-05T12:34:56"; // Non-empty timestamp

        assert(formatAnalysisXML(request) ==
            R"(<?xml version="1.0" encoding="UTF-8" standalone="yes"?>
<code:unit xmlns:code="http://mlcollard.net/code" language="C++" filename="main.cpp" timestamp="2024-11-05T12:34:56">
if (a &lt; b) a = b;
</code:unit>
)");
    }

    // Test case: include loc attribute if optionLOC is non-negative
    {
        AnalysisRequest request;
        request.sourceCode = R"(
if (a < b) a = b;
)";
        request.diskFilename    = "main.cpp";
        request.entryFilename   = "";
        request.optionFilename  = "";
        request.sourceURL       = "";
        request.optionURL       = "";
        request.optionLanguage  = "C++";
        request.defaultLanguage = "";
        request.optionHash      = "";
        request.optionLOC       = 10; // Non-negative LOC
        request.timestamp       = "";

        assert(formatAnalysisXML(request) ==
            R"(<?xml version="1.0" encoding="UTF-8" standalone="yes"?>
<code:unit xmlns:code="http://mlcollard.net/code" language="C++" filename="main.cpp" loc="10">
if (a &lt; b) a = b;
</code:unit>
)");
    }
    // Test case: include url attribute if sourceURL is non-empty
    {
        AnalysisRequest request;
        request.sourceCode = R"(
if (a < b) a = b;
)";
        request.diskFilename    = "main.cpp";
        request.entryFilename   = "";
        request.optionFilename  = "";
        request.sourceURL       = "http://example.com/source"; // Non-empty URL
        request.optionURL       = "";
        request.optionLanguage  = "C++";
        request.defaultLanguage = "";
        request.optionHash      = "";
        request.optionLOC       = -1;
        request.timestamp       = "";
        assert(formatAnalysisXML(request) ==
            R"(<?xml version="1.0" encoding="UTF-8" standalone="yes"?>
<code:unit xmlns:code="http://mlcollard.net/code" language="C++" filename="main.cpp" url="http://example.com/source">
if (a &lt; b) a = b;
</code:unit>
)");
    }

    // Test case: use optionHash for the hash attribute if it's non-empty
    {
        AnalysisRequest request;
        request.sourceCode = R"(
if (a < b) a = b;
)";
        request.diskFilename    = "main.cpp";
        request.entryFilename   = "";
        request.optionFilename  = "";
        request.sourceURL       = "";
        request.optionURL       = "";
        request.optionLanguage  = "C++";
        request.defaultLanguage = "";
        request.optionHash      = "abc123"; // Non-empty hash
        request.optionLOC       = -1;
        request.timestamp       = "";

        assert(formatAnalysisXML(request) ==
            R"(<?xml version="1.0" encoding="UTF-8" standalone="yes"?>
<code:unit xmlns:code="http://mlcollard.net/code" language="C++" filename="main.cpp" hash="abc123">
if (a &lt; b) a = b;
</code:unit>
)");
}

    // Test case: diskFilename is "-" and entryFilename should be used for the filename attribute
    {
        AnalysisRequest request;
        request.sourceCode = R"(
if (a < b) a = b;
)";
        request.diskFilename    = "-";           // Single dash for source code from stdin
        request.entryFilename   = "main.cpp";    // Entry filename within the archive
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
<code:unit xmlns:code="http://mlcollard.net/code" language="C++" filename="main.cpp">
if (a &lt; b) a = b;
</code:unit>
)");
}

    return 0;
}