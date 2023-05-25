cmake_minimum_required(VERSION 3.15)
project(FinalProjExamples)

# filesystem.h require C++17
set(CMAKE_CXX_STANDARD 17)

file(COPY sample_data/ DESTINATION sample_data/)

# show compiler output and enable warnings
set(CMAKE_VERBOSE_MAKEFILE ON)
add_compile_options(-Wall -Wextra -pedantic)


#add_executable(rapidJSONExample rapidJSONExample.cpp documentParser.cpp documentParser.h porter2_stemmer.cpp porter2_stemmer.h)
add_executable(supersearch main.cpp queryPro.cpp queryPro.h porter2_stemmer.cpp porter2_stemmer.h documentParser.cpp documentParser.h article.h userInterface.cpp userInterface.h IndexHandler.cpp IndexHandler.h relevancyRanking.cpp relevancyRanking.h)

# this makes sure we also link rapidjson
target_include_directories(supersearch PRIVATE rapidjson/)

set(CMAKE_VERBOSE_MAKEFILE OFF)

include(CTest)
add_executable(tests test.cpp test.cpp)
add_test(NAME SimpleTest COMMAND tests)


