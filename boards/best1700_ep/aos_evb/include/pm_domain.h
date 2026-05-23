/****************************************************************************
 * vendor/bes/boards/best1700_ep/include/pm_domain.h
 *
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.  The
 * ASF licenses this file to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance with the
 * License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
 * License for the specific language governing permissions and limitations
 * under the License.
 *
 ****************************************************************************/

#ifndef __BOARDS_BEST1700_EP_INCLUDE_PM_DOMAIN_H
#define __BOARDS_BEST1700_EP_INCLUDE_PM_DOMAIN_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

#ifdef CONFIG_PM

/****************************************************************************
 * Public Types
 ****************************************************************************/

/* Peripheral IC driver domain definition
 */

enum pm_domain_e
{
  PM_DOMAIN_CPU     = 0, /* CPU */

  PM_DOMAIN_OLED_TP = 1, /* OLED TP */

  PM_DOMAIN_FACTEST = 2, /* factory test */

  PM_DOMAIN_MAX,
};

#endif /* CONFIG_PM */
#endif /* __BOARDS_BEST1700_EP_INCLUDE_PM_DOMAIN_H */
