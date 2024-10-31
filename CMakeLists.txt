# @file CMakeLists.txt
# 
# CMake files for CodeAnalysis program

cmake_minimum_required(VERSION 3.27)

project(CodeAnalysis)

# Test CodeAnalysis
add_executable(CodeAnalysisTest CodeAnalysisTest.cpp CodeAnalysis.cpp XMLWrapper.cpp FilenameToLanguage.cpp)
target_compile_features(CodeAnalysisTest PRIVATE cxx_std_17)
target_compile_options(CodeAnalysisTest PRIVATE
    $<$<CXX_COMPILER_ID:MSVC>:/W4;/WX>
    $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall;-Wextra;-pedantic;-Werror>
)

# Test FilenameToLanguage
add_executable(FilenameToLanguageTest FilenameToLanguageTest.cpp FilenameToLanguage.cpp)
target_compile_features(FilenameToLanguageTest PRIVATE cxx_std_17)
target_compile_options(FilenameToLanguageTest PRIVATE
    $<$<CXX_COMPILER_ID:MSVC>:/W4;/WX>
    $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall;-Wextra;-pedantic;-Werror>
)

# Run tests
add_custom_target(test COMMENT "Test code analysis functions"
                       COMMAND $<TARGET_FILE:FilenameToLanguageTest>
                       COMMAND $<TARGET_FILE:CodeAnalysisTest>
                       DEPENDS CodeAnalysisTest FilenameToLanguageTest)
