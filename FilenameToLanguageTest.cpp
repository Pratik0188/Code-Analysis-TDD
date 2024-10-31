/*
  @file FilenameToLanguageTest.cpp

  Test program for filenameToLanguage()
*/

#include "FilenameToLanguage.hpp"
#include <cassert>

int main() {

    // known proper values
    assert(filenameToLanguage("file.c")    == "C");
    assert(filenameToLanguage("file.h")    == "C");
    assert(filenameToLanguage("file.i")    == "C");
    assert(filenameToLanguage("file.cpp")  == "C++");
    assert(filenameToLanguage("file.CPP")  == "C++");
    assert(filenameToLanguage("file.cp")   == "C++");
    assert(filenameToLanguage("file.hpp")  == "C++");
    assert(filenameToLanguage("file.cxx")  == "C++");
    assert(filenameToLanguage("file.hxx")  == "C++");
    assert(filenameToLanguage("file.cc")   == "C++");
    assert(filenameToLanguage("file.hh")   == "C++");
    assert(filenameToLanguage("file.c++")  == "C++");
    assert(filenameToLanguage("file.h++")  == "C++");
    assert(filenameToLanguage("file.C")    == "C++");
    assert(filenameToLanguage("file.H")    == "C++");
    assert(filenameToLanguage("file.tcc")  == "C++");
    assert(filenameToLanguage("file.ii")   == "C++");
    assert(filenameToLanguage("file.java") == "Java");
    assert(filenameToLanguage("file.aj")   == "AspectJ");
    assert(filenameToLanguage("file.cs")   == "C#");

    // known non-language extensinos
    assert(filenameToLanguage("file.cs480") == "");
    assert(filenameToLanguage("file.txt")   == "");
    assert(filenameToLanguage("file.doc")   == "");
    assert(filenameToLanguage("file.docx")  == "");

    // just the extension
    assert(filenameToLanguage(".c")    == "C");
    assert(filenameToLanguage(".h")    == "C");
    assert(filenameToLanguage(".i")    == "C");
    assert(filenameToLanguage(".cpp")  == "C++");
    assert(filenameToLanguage(".CPP")  == "C++");
    assert(filenameToLanguage(".cp")   == "C++");
    assert(filenameToLanguage(".hpp")  == "C++");
    assert(filenameToLanguage(".cxx")  == "C++");
    assert(filenameToLanguage(".hxx")  == "C++");
    assert(filenameToLanguage(".cc")   == "C++");
    assert(filenameToLanguage(".hh")   == "C++");
    assert(filenameToLanguage(".c++")  == "C++");
    assert(filenameToLanguage(".h++")  == "C++");
    assert(filenameToLanguage(".C")    == "C++");
    assert(filenameToLanguage(".H")    == "C++");
    assert(filenameToLanguage(".tcc")  == "C++");
    assert(filenameToLanguage(".ii")   == "C++");
    assert(filenameToLanguage(".java") == "Java");
    assert(filenameToLanguage(".aj")   == "AspectJ");
    assert(filenameToLanguage(".cs")   == "C#");

    return 0;
}
