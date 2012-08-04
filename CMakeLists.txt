cmake_minimum_required(VERSION 2.6)
project(NEW_NOISE)

# INCLUDE MY CUSTOM HELPER STUFF
INCLUDE(Custom_CMake_Utils.cmake)

##IF(WIN32)
##	SET(CMAKE_CXX_FLAGS "-g std=c++0x")
##ENDIF(WIN32)


# Set location to output binaries
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${NEW_NOISE_SOURCE_DIR}/bin)
set(CMAKE_INCLUDE_PATH "${NEW_NOISE_SOURCE_DIR}/include")

include_directories("${NEW_NOISE_SOURCE_DIR}/include")

# These next two are pretty much the same
#set(CMAKE_CXX_FLAGS "-g -std=c++0x")
add_definitions("-g -std=c++0x")
##add_definitions("-g -std=c++0x -DGLEW_STATIC -static")
#add_subdirectory(src)

		
## ADD AN EXECUTABLE TO BUILD
## FORMAT :
##   SET(PROGRAM_NAMES <executable_name>)
##   INSERT_INTO_MAP(<executable_name> <source_file_1> <source_file_2> ... )
set(PROGRAM_NAMES "test1")
##set(final "src/final.cpp" "src/model/model.cpp" "src/emitter/emitter.cpp")
set(test1 "tests/test1.cpp" 
          "src/map_grid.cpp"
    )
INSERT_INTO_MAP("test1" "${test1}")

#SET(_VERBOSE TRUE)

foreach(CURRENT_PROGRAM ${PROGRAM_NAMES})
    GET_FROM_MAP("${CURRENT_PROGRAM}" CURRENT_SOURCES)
    message(${CURRENT_SOURCES})
    IF(DEFINED _VERBOSE AND _VERBOSE)
        message("\nBUILDING ${CURRENT_PROGRAM} FROM SOURCES :")
        foreach(SOURCE_FILENAME ${CURRENT_SOURCES})
            message("\t${SOURCE_FILENAME}")
        endforeach(SOURCE_FILENAME)
        message(" ")
    ENDIF(DEFINED _VERBOSE AND _VERBOSE)
    
    add_executable(${CURRENT_PROGRAM} WIN32 MACOSX_BUNDLE ${CURRENT_SOURCES})
endforeach(CURRENT_PROGRAM)

