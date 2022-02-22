cmake_minimum_required(VERSION 3.15)

set(CMAKE_CXX_STANDARD 17)
project("Alarm Timer" LANGUAGES CXX)

find_package(Threads REQUIRED)

set(BINARY_NAME alarm_timer)
add_executable(${BINARY_NAME}
  "src/main.cc"
  "src/simple_timer.cc"
)

target_include_directories(${BINARY_NAME} PRIVATE "src")
target_link_libraries(${BINARY_NAME}
  PRIVATE
    Threads::Threads
)
