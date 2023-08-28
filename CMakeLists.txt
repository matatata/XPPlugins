cmake_minimum_required(VERSION 3.9)

project("XPPlugins")


# X-Plane supports OS X 10.10+, so this should ensure the plugin can run on
# all supported versions.
set(CMAKE_OSX_DEPLOYMENT_TARGET "10.10")
set(CMAKE_OSX_ARCHITECTURES "x86_64;arm64") 


# By default, use optimized release configuration.
if (NOT CMAKE_BUILD_TYPE OR CMAKE_BUILD_TYPE STREQUAL "")
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "" FORCE)
endif ()

set(CMAKE_CXX_STANDARD 14)

include_directories("${CMAKE_SOURCE_DIR}/SDK/CHeaders/Widgets")
include_directories("${CMAKE_SOURCE_DIR}/SDK/CHeaders/Wrappers")
include_directories("${CMAKE_SOURCE_DIR}/SDK/CHeaders/XPLM")
include_directories("${CMAKE_SOURCE_DIR}/FMOD")

# Specify library search locations.
if (WIN32)
    list(APPEND CMAKE_LIBRARY_PATH "${CMAKE_SOURCE_DIR}/SDK/Libraries/Win")
elseif (APPLE)
    list(APPEND CMAKE_FRAMEWORK_PATH "${CMAKE_SOURCE_DIR}/SDK/Libraries/Mac")
elseif (UNIX)
endif ()
list(APPEND CMAKE_LIBRARY_PATH "${CMAKE_SOURCE_DIR}/FMOD/Libs")

if (WIN32 OR APPLE)
    find_library(XPLM_LIBRARY NAMES XPLM XPLM_64.lib)
    find_library(XPWIDGETS_LIBRARY NAMES XPWidgets XPWidgets_64.lib)
endif()
if (APPLE)
    find_library(CORE_FOUNDATION_LIBRARY CoreFoundation)
    find_library(IOKIT_LIBRARY IOKit)
endif ()

# Link Fmod related libraries.
# Windows will not find the dll so we have to do this dance
if (APPLE OR UNIX)
    if (APPLE)
       find_library(FMOD_LIB NAMES libfmod.dylib)
    elseif (UNIX)
       find_library(FMOD_LIB NAMES libfmod.so.13.10)
    elseif(WIN32)
    endif ()
endif () 


# Enable all X-Plane SDK APIs up to the newest version.
add_definitions(-DXPLM200=1 -DXPLM210=1 -DXPLM300=1 -DXPLM301=1 -DXPLM303=1 -DXPLM400=1)
# Define platform macros.
add_definitions(-DAPL=$<BOOL:${APPLE}> -DIBM=$<BOOL:${WIN32}> -DLIN=$<AND:$<BOOL:${UNIX}>,$<NOT:$<BOOL:${APPLE}>>>)




function(link_plugin PLUGIN_NAME)
    target_link_libraries(${PLUGIN_NAME} Util)

    if (WIN32 OR APPLE)
        target_link_libraries(${PLUGIN_NAME} ${XPLM_LIBRARY} ${XPWIDGETS_LIBRARY})
    endif ()
    # Link library for dynamic loading of shared objects on UNIX systems.
    if (UNIX)
        find_library(DL_LIBRARY dl)
        target_link_libraries(${PLUGIN_NAME} ${DL_LIBRARY})
    endif ()

    if (WIN32)
        # Unlike OS X and Linux we build standard libraries statically since X-Plane does not provide them.
        target_link_libraries(${PLUGIN_NAME} -static-libgcc -static-libstdc++)
        # MSYS2 for some reason always links against winpthread, so we have to work around it by statically linking the
        # entire plugin. This allows building the plugin nativaly on Windows.
        target_link_libraries(${PLUGIN_NAME} -static)
    elseif (APPLE)
        # Restrict set of symbols exported from the plugin. This reduces changes of
        # conflict with other plugins, in particular ones with Lua interpreter
        # embedded.
        target_link_libraries(${PLUGIN_NAME} "-exported_symbols_list ${CMAKE_SOURCE_DIR}/symbols.sym_mac")
        target_link_libraries(${PLUGIN_NAME} ${IOKIT_LIBRARY} ${CORE_FOUNDATION_LIBRARY})
    elseif (UNIX)
        # Specify additional runtime search laths for dynamically-linked libraries.
        target_link_libraries(${PLUGIN_NAME} -Wl,-rpath=./Resources/plugins/${PLUGIN_NAME}/64)
        # Restrict set of symbols exported from the plugin. This reduces chances of
        # conflict with other plugins, in particular ones with Lua interpreter
        # embedded.
        target_link_libraries(${PLUGIN_NAME} -Wl,--version-script -Wl,${CMAKE_SOURCE_DIR}/symbols.sym)
    endif ()

    set_target_properties(${PLUGIN_NAME} PROPERTIES PREFIX "")
    if (WIN32)
        set_target_properties(${PLUGIN_NAME} PROPERTIES OUTPUT_NAME "win")
    elseif (APPLE)
        set_target_properties(${PLUGIN_NAME} PROPERTIES OUTPUT_NAME "mac")
    elseif (UNIX)
        set_target_properties(${PLUGIN_NAME} PROPERTIES OUTPUT_NAME "lin")
    endif ()
    set_target_properties(${PLUGIN_NAME} PROPERTIES SUFFIX ".xpl")


    set_target_properties(${PLUGIN_NAME} PROPERTIES  LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/install/${PLUGIN_NAME}/64/)


 endfunction(link_plugin)


 add_subdirectory(Util)

 foreach(plug BetterMouseYoke CycleQuickLooks MouseButtons ToggleMouseLook A320UE) 
    add_subdirectory(${plug})
 endforeach()


