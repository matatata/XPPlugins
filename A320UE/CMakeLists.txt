set(PLUGIN_NAME "A320UE")

add_library(${PLUGIN_NAME} SHARED
levers.c
ff.c
plugin.c
plugin.h
v1.c
)

if(WIN32 OR APPLE)
    find_library(FMOD_LIB fmod)
    target_link_libraries(${PLUGIN_NAME} ${FMOD_LIB})
endif()

if (APPLE)
    target_link_libraries(${PLUGIN_NAME} "-framework ApplicationServices")
endif()

link_plugin(${PLUGIN_NAME})