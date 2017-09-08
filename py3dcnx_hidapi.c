#include "py3dcnx.h"
#include "hidapi.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

py3dcnx_context* py3dcnx_init_hidapi(void)
{
  py3dcnx_context* ctx = (py3dcnx_context*)malloc(sizeof(py3dcnx_context));
  hid_init();
  ctx->dev = hid_open(0x46d, 0xc626, NULL);
  if(!ctx->dev) {
      printf("py3dcnx error: no device found\n");
      return NULL;
  }
  return ctx;
}

void py3dcnx_deinit_hidapi(py3dcnx_context* ctx)
{
  if(!ctx) {
    hid_exit();
  } else{
    hid_close(ctx->dev);
    hid_exit();
    free(ctx);
  }
}

void py3dcnx_get_event(py3dcnx_context* ctx, py3dcnx_event* event)
{
  uint8_t buf[8];
  hid_read(ctx->dev, buf,8);

  event->type = buf[0];
  for(int i=1;i<7;i++)
    event->values[i-1] = buf[i];
}
