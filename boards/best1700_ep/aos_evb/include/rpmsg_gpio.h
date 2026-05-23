#ifndef __RPMSG_GPIO_H__
#define __RPMSG_GPIO_H__

#include <arch/board/board.h>
#include <openamp/rpmsg.h>

#define CONFIG_RPMSG_SERVER_NAME "ap"
#define CONFIG_RPMSG_GPIO_EPT_NAME "rpmsg-gpio"
#define CONFIG_RPMSG_GPIO_EPT_NAME_BTH "rpmsg-gpio-bth"
#if defined(CONFIG_BES1700_BTH)
#define CONFIG_RPMSG_GPIO_EPT_NAME CONFIG_RPMSG_GPIO_EPT_NAME_BTH
#endif

enum
{
  RPMSG_GPIO_CMD_DIRECTION,
  RPMSG_GPIO_CMD_OPTION,
  RPMSG_GPIO_CMD_WRITEPIN,
  RPMSG_GPIO_CMD_READPIN,
  RPMSG_GPIO_CMD_ATTACH,
  RPMSG_GPIO_CMD_DETACH,
  RPMSG_GPIO_CMD_IRQ,
  RPMSG_GPIO_CMD_NUM,
};

struct rpmsg_gpio_msg
{
  uint8_t command;
  uint16_t len;
  bool wait;
  int result;
  void *sem;
  void *reserve;

  uint8_t pin;
  int opt;
  void *value;
};

#endif
