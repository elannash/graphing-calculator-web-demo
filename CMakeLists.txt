project(nash_s21 CXX)

# CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

# ------------------------------------
# place binaries and libraries according to GNU standards
include(GNUInstallDirs)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR})
if(CMAKE_CXX_COMPILER_ID MATCHES GNU)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
endif()
#. . . . . . . . . . . . . . . . . . . .
include(cmake/googletest.cmake)
fetch_googletest(
    ${PROJECT_SOURCE_DIR}/cmake
    ${PROJECT_BINARY_DIR}/googletest
    )



# ------------------------------------------------------------------------------------------
#                                    DO NOT EDIT 
#                               ANYTHING ABOVE THIS LINE
# ------------------------------------------------------------------------------------------


# ADD_SUBDIRECTORY(googletest)

ADD_EXECUTABLE(main
    main.cpp
    includes/linked_list_functions/linked_list_functions.cpp 
    includes/node/node.cpp 
    includes/queue/MyQueue.cpp 
    includes/stack/MyStack.cpp 
    includes/rpn/rpn.cpp 
    includes/shunting_yard/shunting_yard.cpp 
    includes/token/token.cpp 
    includes/token/function.cpp 
    includes/token/special_function.cpp 
    includes/token/number.cpp 
    includes/token/leftparen.cpp 
    includes/token/rightparen.cpp 
    includes/token/operator.cpp
    includes/token/variable.cpp
)

ADD_EXECUTABLE(basic_test
    _tests/_test_files/basic_test.cpp
    includes/linked_list_functions/linked_list_functions.cpp 
    includes/node/node.cpp 
    includes/queue/MyQueue.cpp 
    includes/stack/MyStack.cpp 
    includes/rpn/rpn.cpp 
    includes/shunting_yard/shunting_yard.cpp 
    includes/token/token.cpp 
    includes/token/function.cpp 
    includes/token/special_function.cpp 
    includes/token/number.cpp 
    includes/token/leftparen.cpp 
    includes/token/rightparen.cpp 
    includes/token/operator.cpp
    includes/token/variable.cpp
)

ADD_EXECUTABLE(testB
    _tests/_test_files/testB.cpp
    includes/linked_list_functions/linked_list_functions.cpp 
    includes/node/node.cpp 
    includes/queue/MyQueue.cpp 
    includes/stack/MyStack.cpp 
    includes/rpn/rpn.cpp 
    includes/shunting_yard/shunting_yard.cpp 
    includes/token/token.cpp 
    includes/token/function.cpp 
    includes/token/special_function.cpp 
    includes/token/number.cpp 
    includes/token/leftparen.cpp 
    includes/token/rightparen.cpp 
    includes/token/operator.cpp
    includes/token/variable.cpp
)

TARGET_LINK_LIBRARIES(basic_test gtest)
TARGET_LINK_LIBRARIES(testB gtest)
