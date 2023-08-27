set(PLUGIN_NAME "BetterMouseYoke")

add_library(${PLUGIN_NAME} SHARED
plugin.c
plugin.h
)

if (APPLE)
    target_link_libraries(${PLUGIN_NAME} "-framework ApplicationServices")
endif()

link_plugin(${PLUGIN_NAME})