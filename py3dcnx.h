#ifndef _PY3DCNX_H_
#define _PY3DCNX_H_

#include "hidapi/hidapi.h"

typedef enum {TRANSLATION=1, ROTATION, BUTTON} py3dcnx_event_type;

typedef struct {
  hid_device *dev;
} py3dcnx_context;

typedef struct {
  py3dcnx_event_type type;
  char values[6];
} py3dcnx_event;

py3dcnx_context* py3dcnx_init_hidapi(void);
void py3dcnx_deinit_hidapi(py3dcnx_context* ctx);

void py3dcnx_get_event(py3dcnx_context* ctx, py3dcnx_event* event);

#endif
