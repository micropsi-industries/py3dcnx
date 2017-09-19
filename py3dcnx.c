#include <Python.h>
#include "py3dcnx.h"
#include <stdlib.h>
#include <stdint.h>

static py3dcnx_context* ctx = NULL;

static PyObject* get_event(PyObject* self, PyObject* args)
{
  PyObject* ret;
  int device_num = 0;

  if(!PyArg_ParseTuple(args, "|i", &device_num))
    return NULL;
    
  if(!ctx){
    Py_RETURN_NONE;
  }

  py3dcnx_event* event = (py3dcnx_event*)malloc(sizeof(py3dcnx_event));
  if(!event)
    Py_RETURN_NONE;

  py3dcnx_get_event(ctx, event, device_num);

  int16_t params[3];
  for(int i=0;i<3;i++)
    params[i] = event->values[2*i] | event->values[2*i+1]<<8;

  switch(event->type) {
    case TRANSLATION:
      ret = Py_BuildValue("{s:s,s:i,s:i,s:i}","type","translate",
            "x", params[0], "y", params[1], "z", params[2]);
      break;
    case ROTATION:
      ret = Py_BuildValue("{s:s,s:i,s:i,s:i}","type","rotate",
            "roll", params[0], "pitch", params[1], "yaw", params[2]);
      break;
    case BUTTON:
      ret = Py_BuildValue("{s:s,s:i}","type","button","val",params[0]);
      break;
    default:
      free(event);
      Py_RETURN_NONE;
  }

  free(event);
  return ret;
}

static PyMethodDef py3dcnx_methods[] = {
  {"get_event", (PyCFunction)get_event, METH_VARARGS, NULL},
  {NULL, NULL, 0, NULL}
};

static void py3dcnx_deinit(void)
{
  py3dcnx_deinit_hidapi(ctx);
}

static void py3dcnx_init(void)
{
  ctx = py3dcnx_init_hidapi();
  Py_AtExit(py3dcnx_deinit);
}

#if PY_MAJOR_VERSION == 3
static struct PyModuleDef py3dcnx =
{
  PyModuleDef_HEAD_INIT,
  "py3dcnx",
  "",
  -1,
  py3dcnx_methods
};

PyMODINIT_FUNC PyInit_py3dcnx(void)
{
  py3dcnx_init();
  return PyModule_Create(&py3dcnx);
}
#else
PyMODINIT_FUNC
initpy3dcnx(void)
{
  py3dcnx_init();
  Py_InitModule("py3dcnx", py3dcnx_methods);
}
#endif
