#include "py3dcnx.h"
#include "hidapi/hidapi.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>

static uint8_t py3dcnx_device_open(py3dcnx_device* dev) {
  dev->dev = hid_open_path(dev->path);
  if(!dev->dev) {
    printf("py3dcnx error while opening device!\n");
    return -1;
  }
  return 0;
}

py3dcnx_context* py3dcnx_init_hidapi(void)
{
  py3dcnx_context* ctx = (py3dcnx_context*)malloc(sizeof(py3dcnx_context));
  if(!ctx)
    return NULL;

  hid_init();

  struct hid_device_info *cur, *devs = hid_enumerate(USB_VID, USB_PID);
  int ret = 0;
  cur = devs;
  ctx->head = NULL;
  py3dcnx_device *tail = NULL;
  while(cur) {
    py3dcnx_device* dev = (py3dcnx_device*)malloc(sizeof(py3dcnx_device));
    if(!dev) {

      ret = -1;
      break;
    }

    strncpy(dev->path, cur->path, MAX_PATH_LEN);
    dev->next = NULL;
    dev->dev = NULL;

    if(ctx->head == NULL)
      ctx->head = tail = dev;
    else {
      tail->next = dev;
      tail = dev;
    }
    cur = cur->next;
  }
  hid_free_enumeration(devs);

  if(ret) {
    py3dcnx_device *tmp;
    while(ctx->head) {
      tmp = ctx->head;
      ctx->head = tmp->next;
      free(tmp);
    }
    free(ctx);
    return NULL;
  }
  return ctx;
}

void py3dcnx_deinit_hidapi(py3dcnx_context* ctx)
{
  if(!ctx) {
    hid_exit();
  } else{
    while(ctx->head){
      py3dcnx_device *tmp = ctx->head;
      ctx->head = tmp->next;
      if(tmp->dev)
        hid_close(tmp->dev);
      free(tmp);
    }
    hid_exit();
    free(ctx);
  }
}

void py3dcnx_get_event(py3dcnx_context* ctx, py3dcnx_event* event, uint8_t devnum)
{
  uint8_t buf[8];
  py3dcnx_device *cur = ctx->head;
  while(devnum && cur) {
    cur = cur->next;
    devnum--;
  }

  if(devnum || cur==NULL) {
    printf("py3dcnx error device number out of range or no device connected\n");
    return;
  }

  if(!cur->dev)
    py3dcnx_device_open(cur);

  hid_read(cur->dev, buf,8);

  event->type = buf[0];
  for(int i=1;i<7;i++)
    event->values[i-1] = buf[i];
}
