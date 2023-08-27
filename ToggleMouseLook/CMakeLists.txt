set(PLUGIN_NAME "ToggleMouseLook")

add_library(${PLUGIN_NAME} SHARED
plugin.c
plugin.c
)

if (APPLE)
    target_link_libraries(${PLUGIN_NAME} "-framework ApplicationServices")
endif()

link_plugin(${PLUGIN_NAME})