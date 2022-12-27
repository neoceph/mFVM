set(SubProject ${CMAKE_PROJECT_NAME}_lib) # setting the library name

# specifying the project name
project(${SubProject})

# # selecting all the files with .cpp extension and assigning them to a variable 'SOURCES'
file(GLOB SOURCES "sources/*.*")
file(GLOB HEADERS "headers/*.*")

# # adding to the library all the files that are selected and assigned to the variable name 'SOURCES'
add_library(
    ${SubProject} STATIC # Name of the project that is extracted from the root directory CMakeLists.txt
    ${SOURCES} # 
    ${HEADERS}
    )

target_link_libraries(${SubProject} PUBLIC ${VTK_LIBRARIES})

install(TARGETS ${SubProject} DESTINATION lib)