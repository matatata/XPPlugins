set(PLUGIN_NAME "A320UE")

add_library(${PLUGIN_NAME} SHARED
levers.c
ff.c
plugin.c
plugin.h
v1.c
)




link_plugin(${PLUGIN_NAME})

if(WIN32)
    target_link_libraries(${PLUGIN_NAME} ${CMAKE_SOURCE_DIR}/FMOD/Libs/fmod_vc.lib)
else()
    target_link_libraries(${PLUGIN_NAME} ${FMOD_LIB})
endif()

if (APPLE)
    target_link_libraries(${PLUGIN_NAME} "-framework ApplicationServices")
endif()