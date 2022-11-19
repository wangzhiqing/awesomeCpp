cmake_minimum_required (VERSION 2.8)

file(GLOB SAMPLE_CPP_FILES ${CMAKE_CURRENT_LIST_DIR}/src/*.cpp)
foreach(SAMPLE_SOURCE ${SAMPLE_CPP_FILES})
  string(REGEX REPLACE ".+/(.+)\\..*" "\\1" SAMPLE_NAME ${SAMPLE_SOURCE})
  add_executable(${SAMPLE_NAME} ${SAMPLE_SOURCE})
  target_include_directories(${SAMPLE_NAME} PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include)
endforeach(SAMPLE_SOURCE ${SAMPLE_CPP_FILES})