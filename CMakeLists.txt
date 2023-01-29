cmake_minimum_required(VERSION 3.21)


# setting up the vcpkg toolpath. 
execute_process(COMMAND which vcpkg OUTPUT_VARIABLE VCPKG_COMMAND_PATH)
string(REGEX REPLACE "vcpkg\n" "" VCPKG_PATH "${VCPKG_COMMAND_PATH}")
set(VCPKG_TOOLCHAIN_PATH ${VCPKG_PATH}scripts/buildsystems/vcpkg.cmake)
message("vcpkg path: "${VCPKG_TOOLCHAIN_PATH})
set(CMAKE_TOOLCHAIN_FILE ${VCPKG_TOOLCHAIN_PATH} CACHE STRING "TEST") 
# set(CMAKE_TOOLCHAIN_FILE "/home/nirjhor/Software/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "" FORCE) 

# Read the JSON file. JSON file contains all information regarding project titles and named variables including developers.
file(READ ${CMAKE_CURRENT_SOURCE_DIR}/CMakeSetup.json CMakeSetup_STRING)

# extracting project name and devleoper names from the json file.
string(JSON Project_NAME GET ${CMakeSetup_STRING} 0 ProjectName)
string(JSON Project_DEVELOPER GET ${CMakeSetup_STRING} 0 Developer)
string(JSON Document_Generation GET ${CMakeSetup_STRING} 0 DocumentGeneration)

# setting project and project library variable names.
set(Project ${Project_NAME})
set(ProjectLib ${Project}_lib)

set(version_file "${CMAKE_CURRENT_BINARY_DIR}/version.cpp")
set(source_files "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp")

# settting the project name.
project(${Project} C CXX)



############ Find Package Stuffs########################################################
########################################################################################
# check if openMP compilers are available and link them
find_package(OpenMP 4.0)
if (OPENMP_FOUND)
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()

find_package(VTK)




############ CPack and Git Versioning ##################################################
########################################################################################

# Appends the cmake/modules path to MAKE_MODULE_PATH variable.
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules ${CMAKE_MODULE_PATH})

# setting the directory of the source for doxygen documentation
set(PROJECT_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/src")
set(source_files "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp")


# Make a version file containing the current version from git.
if(EXISTS "${PROJECT_SOURCE_DIR}/versionForSourcePackage.cmake")
  include("${PROJECT_SOURCE_DIR}/versionForSourcePackage.cmake")
else()
  include(GetGitRevisionDescription)
  git_describe(VERSION --tags --dirty=-dirty)
endif()

#parse the version information into pieces.
string(REGEX REPLACE "^v([0-9]+)\\..*" "\\1" VERSION_MAJOR "${VERSION}")
string(REGEX REPLACE "^v[0-9]+\\.([0-9]+).*" "\\1" VERSION_MINOR "${VERSION}")
string(REGEX REPLACE "^v[0-9]+\\.[0-9]+\\.([0-9]+).*" "\\1" VERSION_PATCH "${VERSION}")
string(REGEX REPLACE "^v[0-9]+\\.[0-9]+\\.[0-9]+(.*)" "\\1" VERSION_SHA1 "${VERSION}")
set(VERSION_SHORT "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")

set(CMAKE_INSTALL_PREFIX "/${Project_NAME}_${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")





# specifying the header directory
include_directories(
    ${ProjectLib} "${CMAKE_SOURCE_DIR}/src/headers"
    )



# generating executable program by specifying the location of the file

######### Generating Executables #######################################################
########################################################################################
add_executable(
    ${Project} src/main.cpp  ${version_file}
    )
add_executable(
    vtkExample src/sources/write.cpp
)

add_subdirectory(src)

target_link_directories(vtkExample PUBLIC src/)

target_link_libraries(vtkExample PUBLIC ${VTK_LIBRARIES} ${ProjectLib})
target_link_libraries(${Project} PUBLIC ${VTK_LIBRARIES} ${ProjectLib})

 

vtk_module_autoinit(
  TARGETS vtkExample
  MODULES ${VTK_LIBRARIES}
)


########################################################################################
# intializing and enabling test.

# adding git submodules chekout from the source

# Download all the submodules
find_package(Git REQUIRED)
# if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
message(STATUS "Git and directory Found!")
# update submodules as needed
    option(GIT_SUBMODULE "Check submodules during build" ON)
    if(GIT_SUBMODULE)
        message(STATUS "Recursive submodule updating ...")
        execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                        RESULT_VARIABLE GIT_SUBMOD_RESULT)
        if(NOT GIT_SUBMOD_RESULT EQUAL "0")
            message(FATAL_ERROR "git submodule update --init --recursive failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
        endif()
    endif()
endif()

# check all the submodules
if(
    NOT EXISTS "${PROJECT_SOURCE_DIR}/extLibs/googletest/CMakeLists.txt"
    )
    message(FATAL_ERROR "The googletest submodules was not downloaded! GIT_SUBMODULE is either turned off or failed. Please update submodules")
endif()
########################################################################################

include(CTest)
enable_testing()

add_subdirectory(
    test
    )

# adding the googletest library separately as including the subdirectory with the previous command did not work!
add_subdirectory(
    extLibs/googletest EXCLUDE_FROM_ALL
    )    



########################################################################################
# setting the directory of the source for doxygen documentation
# set(PROJECT_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/src")

if (${Document_Generation})
# setting up sphinx-build with readthedocs theme
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/doc/usermanual)    
configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/CMakeSetup.json ${CMAKE_CURRENT_BINARY_DIR}/CMakeSetup.json
    COPYONLY
    )

message("Copying Sphinx setup files")
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/doc/readthedocs/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/doc/usermanual/)

message("Sphinx Document generation started")
add_custom_command(
    OUTPUT ../html/index.html
    COMMAND make html
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/doc/usermanual
    VERBATIM
    )

message("Sphinx PDF documentation generation started")
add_custom_target(
    HTML_MANUAL ALL
    COMMAND make latexpdf
    DEPENDS ../html/index.html
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/doc/usermanual
    )

# setting up doxygen and code documenation html and pdf
find_package(Doxygen)
if (DOXYGEN_FOUND)
    # creating a /build/doc directory for generating doxyfile outputs in the separate build directory
    file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/doc/api/latex)
    # set input and output files
    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/doc/Doxyfile)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile.out)

    message(${CMAKE_CURRENT_SOURCE_DIR}/doc/Doxyfile.in)
    message(${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT})
    # request to configure the file
    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
    message("Doxygen build started")

    # Note: do not put "ALL" - this builds docs together with application EVERY TIME!
    add_custom_target(
        docs
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM
        )

    message("Doxygen Document generation started")
    add_custom_command(
        OUTPUT refman.tex
        COMMAND make docs
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        VERBATIM
        )

    message("Doxygen PDF generation started")
    add_custom_target(
        API_PDF ALL
        COMMAND make pdf
        DEPENDS refman.tex
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/doc/api/latex
        )

else (DOXYGEN_FOUND)
    message("Doxygen need to be installed to generate the doxygen documentation!")
endif (DOXYGEN_FOUND)
endif(${Document_Generation})
########################################################################################    



########### CPack Commands #############################################################
########################################################################################
set(CPACK_SOURCE_GENERATOR "TGZ")
set(CPACK_PACKAGE_VERSION_MAJOR "${VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${VERSION_PATCH}")

# The following will transfer the version from git to the source package.
set(CPACK_SOURCE_PACKAGE_FILE_NAME "${PROJECT_NAME}-${VERSION_SHORT}-Source")

# Exclude the build and .git directory from the source package.
set(CPACK_SOURCE_IGNORE_FILES "${PROJECT_SOURCE_DIR}/.git/;${PROJECT_BINARY_DIR}/;${CPACK_SOURCE_IGNORE_FILES}")


configure_file(${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules/version.cpp.in
                ${CMAKE_CURRENT_BINARY_DIR}/version.cpp)

configure_file(
   ${PROJECT_SOURCE_DIR}/versionForSourcePackage.cmake.in
   ${PROJECT_BINARY_DIR}/versionForSourcePackage.cmake @ONLY)



########################################################################################
# specifying install rules for dependency libraries
install(DIRECTORY ${PROJECT_SOURCE_DIR}/dependencies/lib DESTINATION .)
set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")



# specifying install rules for documentation 
string(TOLOWER ${Project_NAME} User_Guide)
include(InstallRequiredSystemLibraries)
install(
    TARGETS ${Project} vtkExample RUNTIME_DEPENDENCIES
    )
install(DIRECTORY ${PROJECT_BINARY_DIR}/doc/api/html DESTINATION help/api)
install(DIRECTORY ${PROJECT_BINARY_DIR}/doc/usermanual/documentation/html DESTINATION help/manual)
install(FILES ${PROJECT_BINARY_DIR}/doc/api/latex/refman.pdf DESTINATION help/api RENAME "Api Documentation.pdf")
install(FILES ${PROJECT_BINARY_DIR}/doc/usermanual/documentation/latex/${User_Guide}.pdf DESTINATION help/manual RENAME "User Guide.pdf")

# CPACK ruls
string(TIMESTAMP YEAR_MONTH "%Y_%m")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/License.txt")
# set(CPACK_GENERATOR "RPM;DEB;TGZ;TXZ;TZ;STGZ;NSIS;NSIS64") # NSIS 3.0 and above is not available for Ubuntu 18.04
set(CPACK_GENERATOR "STGZ")
set(CPACK_PACKAGE_NAME ${Project})
set(CPACK_PACKAGE_RELEASE ${YEAR_MONTH})
set(CPACK_PACKAGE_CONTACT ${Project_DEVELOPER})
set(CPACK_PACKAGE_VENDOR "My Company")
set(CPACK_PACKAGING_INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX})
set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${VERSION_SHORT}-${CPACK_PACKAGE_RELEASE}-${CMAKE_SYSTEM_PROCESSOR}")
include(CPack)