set(ProjectTest ${CMAKE_PROJECT_NAME}_Tests)

set(Sources
    ExampleTests.cpp
)

file(GLOB FVMSources "FVM/*.*")
  
add_executable(${ProjectTest} ${Sources} ${FVMSources})



target_link_libraries(
    ${ProjectTest}
    PUBLIC gtest_main
    PUBLIC ${CMAKE_PROJECT_NAME}_lib
    PUBLIC ${ARMADILLO_LIBRARIES}
    PUBLIC ${VTK_LIBRARIES} 
)

add_test(
    NAME ${ProjectTest}
    COMMAND ${ProjectTest}
)
