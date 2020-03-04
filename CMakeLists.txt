cmake_minimum_required(VERSION 3.10)
project(Shell)

set(CMAKE_CXX_STANDARD 14)

add_executable(Isc-Shell
        Shell.cpp
        PreserveCommand.cpp PreserveCommand.h
        Log.cpp Log.h
        ProcessRunner.cpp ProcessRunner.h
        Reader.cpp Reader.h
        Exception/IndexOutOfBoundException.h
        Exception/InputOutOfLimitException.h
        Exception/ForkException.h
        Exception/BoundaryException.h
        Exception/InpurFormatException.h
        Exception/PipeException.h
        Exception/FileNotFoundException.h
        SpecialInput/SpecialInput.h SpecialInput/Up.cpp
        SpecialInput/Up.h SpecialInput/Down.cpp
        SpecialInput/Down.h SpecialInput/Left.cpp
        SpecialInput/Left.h SpecialInput/Right.cpp
        SpecialInput/Right.h SpecialInput/BackSpace.cpp
        SpecialInput/BackSpace.h SpecialInput/KeyboardOperation.h)
add_executable(testCode test.cpp)
