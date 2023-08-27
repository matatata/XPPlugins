set(PLUGIN_NAME "CycleQuickLooks")

add_library(${PLUGIN_NAME} SHARED
plugin.c
)

link_plugin(${PLUGIN_NAME})