cmake_minimum_required (VERSION 2.8)
project(csapp)

include_directories(${CMAKE_CURRENT_LIST_DIR}/csapp_common/include)

file(GLOB SAMPLE_CPP_FILES ${CMAKE_CURRENT_LIST_DIR}/src/*.c)
foreach(SAMPLE_SOURCE ${SAMPLE_CPP_FILES})
  string(REGEX REPLACE ".+/(.+)\\..*" "\\1" SAMPLE_NAME ${SAMPLE_SOURCE})
  add_executable(${SAMPLE_NAME} ${SAMPLE_SOURCE} ${CMAKE_CURRENT_LIST_DIR}/csapp_common/src/csapp.c)
  target_link_libraries(${SAMPLE_NAME}  pthread )
endforeach(SAMPLE_SOURCE ${SAMPLE_CPP_FILES})