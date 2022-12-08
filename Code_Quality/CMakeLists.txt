cmake_minimum_required (VERSION 2.8)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

include_directories(${CMAKE_CURRENT_LIST_DIR}/include/)
link_directories(${CMAKE_CURRENT_LIST_DIR}/lib/)

file(GLOB SAMPLE_CPP_FILES ${CMAKE_CURRENT_LIST_DIR}/src/*.cpp)
foreach(SAMPLE_SOURCE ${SAMPLE_CPP_FILES})
  string(REGEX REPLACE ".+/(.+)\\..*" "\\1" SAMPLE_NAME ${SAMPLE_SOURCE})
  add_executable(${SAMPLE_NAME} ${SAMPLE_SOURCE})
  target_include_directories(${SAMPLE_NAME} PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include)
  target_link_libraries(${SAMPLE_NAME} 
    Threads::Threads 
    gtest 
    gtest_main
  )
endforeach(SAMPLE_SOURCE ${SAMPLE_CPP_FILES})