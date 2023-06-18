cmake_minimum_required(VERSION 3.22)
project(Phonebook C)

set(CMAKE_C_STANDARD 99)

add_library(core STATIC src/screen.c src/contact.c)

target_include_directories(core
        PUBLIC include/screen
        PUBLIC include/contact
        PRIVATE lib)

target_link_libraries(core jansson_d)

target_link_directories(core PUBLIC lib)

if (CMAKE_BUILD_TYPE MATCHES "Test")
    add_executable(test test/contact_test.c)

    target_include_directories(test PRIVATE include)

    target_link_libraries(test core)
else ()
    #The executable
    add_executable(phonebook src/main.c)

    #target_include_directories(phonebook PRIVATE include)
    target_link_libraries(phonebook core)

    target_include_directories(phonebook
            PRIVATE include)
endif ()