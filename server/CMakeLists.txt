cmake_minimum_required(VERSION 2.8.4)

include_directories(../deps/cpp-httplib ../deps/nlohmann)

project(server)

file (GLOB APP_FILES
  main.cpp
)
add_executable(server ${APP_FILES})

