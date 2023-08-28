set(PLUGIN_NAME "BetterMouseYoke")

add_library(${PLUGIN_NAME} SHARED
plugin.c
plugin.h
detours.h
)

if(WIN32)
    target_link_libraries(${PLUGIN_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/detours.lib)
endif()

if (APPLE)
    target_link_libraries(${PLUGIN_NAME} "-framework ApplicationServices")
endif()


link_plugin(${PLUGIN_NAME})