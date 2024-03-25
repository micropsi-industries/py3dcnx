#ifndef _PY3DCNX_H_
#define _PY3DCNX_H_

#include "hidapi/hidapi.h"
#include <Python.h>
#include <stdint.h>

typedef enum {TRANSLATION=1, ROTATION, BUTTON} py3dcnx_event_type;

#define MAX_PATH_LEN  255
#define USB_VID   0x46d
#define USB_PID   0xc635

typedef struct Py3Dcnx_dev{
  hid_device *dev;
  char path[MAX_PATH_LEN];
  PyObject* handlers[2];
  struct Py3Dcnx_dev *next;
} py3dcnx_device;

typedef struct {
  py3dcnx_device *head;
} py3dcnx_context;

typedef struct {
  py3dcnx_event_type type;
  unsigned char values[6];
} py3dcnx_event;

py3dcnx_context* py3dcnx_init_hidapi(void);
void py3dcnx_deinit_hidapi(py3dcnx_context* ctx);

void py3dcnx_get_event(py3dcnx_context* ctx, py3dcnx_event* event, uint8_t devnum, int timeout);

#endif
