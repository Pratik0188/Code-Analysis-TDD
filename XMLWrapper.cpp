/*
    XMLWrapper.cpp

    Creates XML of a single element around content:
    * Single-include file
    * Processes in UTF-8, and only in UTF-8
    * Requires namespace prefix and uri (non-blank)
*/

#include "XMLWrapper.hpp"
#include <stdexcept>

/*
    constructor

    @param prefix Non-empty namespace prefix
    @param uri Non-empty namespace URI
*/
XMLWrapper::XMLWrapper(std::string_view prefix, std::string_view uri)
    : nsPrefix(prefix), nsUri(uri) {

    if (uri.empty())
        throw std::invalid_argument("Requires URI for namespace");

    if (prefix.empty())
        throw std::invalid_argument("Requires non-default prefix for namespace");

    text = R"^^^(<?xml version="1.0" encoding="UTF-8" standalone="yes"?>)^^^";
    text += '\n';
}

/*
    Start the element

    @param name Element name
    @pre Can only be called once
    @pre Must not be preceded by a call to attribute, addContent(), or endElement()
*/
void XMLWrapper::startElement(std::string_view name) {

    // verify is allowed
    switch (state) {
        case ROOT:
            break;
        case STARTTAG:
        case CONTENT:
        case COMPLETED:
            throw std::out_of_range("startElement() called multiple times");
    }

    // save the element name to write the end element
    localName = name;

    // start of start tag
    text += '<';
    text += nsPrefix;
    text += ':';
    text += localName;

    // namespace
    text += ' ';
    text += "xmlns:";
    text += nsPrefix;
    text += "=\"";
    text += nsUri;
    text += '"';

    state = STARTTAG;
}

/*
    Add attribute of the form name="value"

    May be called multiple times.

    @param name Element name
    @pre Must not be preceded by a call to addContent() or endElement()
*/
void XMLWrapper::addAttribute(std::string_view name, std::string_view value) {

    // verify is allowed
    switch (state) {
        case ROOT:
            throw std::out_of_range("Must call startElement() before addAttribute()");
        case STARTTAG:
            break;
        case CONTENT:
            throw std::out_of_range("addAttribute() called after addContent()");
        case COMPLETED:
            throw std::out_of_range("addAttribute() called after endElement()");
    }

    // attribute of the form name="value"
    text += ' ';
    text += name;
    text += "=\"";
    text += value;
    text += '"';
}

/*
    End the element

    @pre Must be preceded by call to startElement()
    @pre Only allowed to be called once
    @pre No calls to startElement(), addAttribute(), or addContent() after
*/
void XMLWrapper::endElement() {

    // verify is allowed
    switch (state) {
        case ROOT:
            throw std::out_of_range("startElement() must be called before endElement()");
        case STARTTAG:
        case CONTENT:
            break;
        case COMPLETED:
            throw std::out_of_range("endElement() called multiple times");
    }

    // end previous start tag if not closed
    if (state == STARTTAG)
        text += ">";

    // end element tag
    text += "</";
    text += nsPrefix;
    text += ":";
    text += localName;
    text += ">\n";

    state = COMPLETED;
}

/*
    Add content. May be called multiple times.

    @param content Non-element content inside the tags
    @pre Must be preceded by call to startElement()
    @pre Cannot be called after endElement()
*/
void XMLWrapper::addContent(std::string_view content) {

    switch (state) {
        case ROOT:
            throw std::out_of_range("startElement() must be called before addContent()");
        case STARTTAG:
        case CONTENT:
            break;
        case COMPLETED:
            throw std::out_of_range("addContent() called after endElement()");
    }

    // end previous start tag if not closed
    if (state == STARTTAG)
        text += ">";

    // insert content, escaping if needed
    if (content.find("<") == std::string::npos &&
        content.find(">") == std::string::npos) {

        text += content;

    } else {

        // escape text
        for (char c : content) {
            if (c == '<') {
                text += "&lt;";
            } else if (c == '>') {
                text += "&gt;";
            } else if (c == '&') {
                text += "&amp;";
            } else {
                text += c;
            }
        }
    }

    state = CONTENT;
}

/*
    Accessor for XML

    May be called at any point, even before completion.
*/
std::string XMLWrapper::xml() const {

    // xml() is allowed for any state

    return text;
}
