cmake_minimum_required(VERSION 3.8)

include_directories(../deps/cpp-httplib ../deps/nlohmann)

project(server2)

file (GLOB APP_FILES
  main.cpp
)
add_executable(server2 ${APP_FILES})

