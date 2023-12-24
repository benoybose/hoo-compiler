# CMakeLists.txt

CMAKE_MINIMUM_REQUIRED(VERSION 3.12)
PROJECT(hoo)

MESSAGE("CMake Version: ${CMAKE_VERSION}")
SET(CMAKE_CXX_STANDARD 14)
LIST(APPEND ANTLR_INCLUDE_DIRS /usr/include/antlr4-runtime/)
SET(GMOCK_INCLUDE_DIRS /usr/src/googletest/googlemock/include/)
LIST(APPEND ANTLR_LIBRARY_DIRS /usr/lib/x86_64-linux-gnu/)
LINK_DIRECTORIES(${ANTLR_LIBRARY_DIRS})
FIND_PACKAGE(LLVM REQUIRED CONFIG)
ADD_DEFINITIONS(${LLVM_DEFINITIONS})
SET(UTF8_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/utf8cpp)

ADD_CUSTOM_COMMAND(
    OUTPUT
        ${CMAKE_BINARY_DIR}/antlr/HooLexer.cpp
        ${CMAKE_BINARY_DIR}/antlr/HooParser.cpp
        ${CMAKE_BINARY_DIR}/antlr/HooBaseVisitor.cpp
        ${CMAKE_BINARY_DIR}/HooVisitor.cpp
    COMMAND
        antlr4
        -Dlanguage=Cpp
        -listener
        -visitor
        -o ${CMAKE_BINARY_DIR}/antlr
        ${CMAKE_CURRENT_SOURCE_DIR}/antlr/Hoo.g4
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/antlr/Hoo.g4
)

INCLUDE_DIRECTORIES(${ANTLR_INCLUDE_DIRS}
    ${GMOCK_INCLUDE_DIRS}
    ${LLVM_INCLUDE_DIRS}
    ${UTF8_INCLUDE_DIR}
    ${CMAKE_BINARY_DIR})

ADD_LIBRARY(hoocompiler STATIC
    ${CMAKE_BINARY_DIR}/antlr/HooLexer.cpp
    ${CMAKE_BINARY_DIR}/antlr/HooParser.cpp
    ${CMAKE_BINARY_DIR}/antlr/HooBaseVisitor.cpp

    src/HooVisitor.h
    src/HooVisitor.cpp

    src/Emitter.h
    src/Emitter.cpp
    src/SymbolTable.h
)

TARGET_LINK_LIBRARIES(hoocompiler ${ANTLR_LIBRARIES})

ADD_EXECUTABLE(hooc
    src/Main.cpp
)

LLVM_MAP_COMPONENTS_TO_LIBNAMES(llvm_libs support core irreader)
TARGET_LINK_LIBRARIES(hooc hoocompiler antlr4-runtime ${llvm_libs})

# # Add source files
# add_executable(LiteralExpressionTest tests/LiteralExpressTest.cpp)

# # Link against GTest and LLVM
# target_link_libraries(LiteralExpressionTest PRIVATE GTest::gtest_main LLVM::LLVMCore)

# # Add include directories
# target_include_directories(LiteralExpressionTest PRIVATE ${LLVM_INCLUDE_DIRS})