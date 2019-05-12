/**
 * MouseButtons - X-Plane 11 Plugin
 *
 * Enables the use of extra mouse buttons and allows the right mouse button
 * and mouse wheel to be re-assigned to arbitrary commands.
 *
 * Copyright 2019 Torben K�nke.
 */
#ifndef _PLUGIN_H_
#define _PLUGIN_H_

#include "../Util/util.h"

typedef enum {
    M_NONE,
    M_RIGHT,
    M_MIDDLE,
    M_FORWARD,
    M_BACKWARD,
    M_W_FORWARD,
    M_W_BACKWARD,
    M_W_LEFT,
    M_W_RIGHT
} mbutton_t;

#define M_MOD_CTRL    (1 << 0)
#define M_MOD_SHIFT   (1 << 1)
#define M_MOD_ALT     (1 << 2)

#define M_STATE_DOWN  (1 << 0)
#define M_STATE_UP    (1 << 1)

/* bindings */
int bindings_init();
XPLMCommandRef bindings_get(mbutton_t mbutton, int mod);

#ifdef IBM
int hook_wnd_proc();
int unhook_wnd_proc();
#endif

#endif /* _PLUGIN_H_ */
