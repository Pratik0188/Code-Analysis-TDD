/*
    XMLWrapper.hpp

    Creates XML of a single element around content:
    * Single-include file
    * Processes in UTF-8, and only in UTF-8
    * Requires namespace prefix and uri (non-blank)
*/

#include <string>
#include <string_view>

class XMLWrapper {
public:

    /*
        constructor

        @param prefix Non-empty namespace prefix
        @param uri Non-empty namespace URI
    */
    XMLWrapper(std::string_view prefix, std::string_view uri);

    /*
        Start the element

        @param name Element name
        @pre Can only be called once
        @pre Must not be preceded by a call to attribute, addContent(), or endElement()
    */
    void startElement(std::string_view name);

    /*
        Add attribute of the form name="value"

        May be called multiple times.

        @param name Element name
        @pre Must not be preceded by a call to addContent() or endElement()
    */
    void addAttribute(std::string_view name, std::string_view value);

    /*
        End the element

        @pre Must be preceded by call to startElement()
        @pre Only allowed to be called once
        @pre No calls to startElement(), addAttribute(), or addContent() after
    */
    void endElement();

    /*
        Add content. May be called multiple times.

        @param content Non-element content inside the tags
        @pre Must be preceded by call to startElement()
        @pre Cannot be called after endElement()
    */
    void addContent(std::string_view content);

    /*
        Accessor for XML

        May be called at any point, even before completion.
    */
    std::string xml() const;

private:
    std::string localName;
    std::string nsPrefix;
    std::string nsUri;
    std::string text;
    enum { ROOT, STARTTAG, CONTENT, COMPLETED } state = ROOT;
};
