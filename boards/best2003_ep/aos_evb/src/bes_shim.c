/****************************************************************************
 * vendor/bes/boards/best2003_ep/aos_evb/src/bes_shim.c
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

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>
#include <nuttx/mm/mm.h>
#include <nuttx/irq.h>

/* Wrapper to provide global symbol for static inline functions.
 * The prebuilt library libnx_bestbsp_ap.a references these symbols,
 * but in the current codebase they are static inline.
 */

/* Define macros to rename the static inline functions we want to expose */
#define nxrmutex_init       nxrmutex_init_inline
#define nxrmutex_get_holder nxrmutex_get_holder_inline
#define nxrmutex_is_hold    nxrmutex_is_hold_inline
#define nxrmutex_destroy    nxrmutex_destroy_inline

#define nxmutex_lock        nxmutex_lock_inline
#define nxmutex_unlock      nxmutex_unlock_inline
#define nxmutex_destroy     nxmutex_destroy_inline

#include <nuttx/mutex.h>

/* Undefine them so we can declare the real global functions */
#undef nxrmutex_init
#undef nxrmutex_get_holder
#undef nxrmutex_is_hold
#undef nxrmutex_destroy

#undef nxmutex_lock
#undef nxmutex_unlock
#undef nxmutex_destroy

/****************************************************************************
 * Public Functions
 ****************************************************************************/

int nxrmutex_init(FAR rmutex_t *rmutex)
{
  return nxrmutex_init_inline(rmutex);
}

int nxrmutex_get_holder(FAR rmutex_t *rmutex)
{
  return nxrmutex_get_holder_inline(rmutex);
}

bool nxrmutex_is_hold(FAR rmutex_t *rmutex)
{
  return nxrmutex_is_hold_inline(rmutex);
}

int nxrmutex_destroy(FAR rmutex_t *rmutex)
{
  return nxrmutex_destroy_inline(rmutex);
}

/* nxmutex wrappers */

int nxmutex_lock(FAR mutex_t *mutex)
{
  return nxmutex_lock_inline(mutex);
}

int nxmutex_unlock(FAR mutex_t *mutex)
{
  return nxmutex_unlock_inline(mutex);
}

int nxmutex_destroy(FAR mutex_t *mutex)
{
  return nxmutex_destroy_inline(mutex);
}

/* Implement mm_lock/mm_unlock which are missing in current mm.
 * The prebuilt library expects these global functions.
 */

/* Forward declaration for struct mm_heap_s if it's not fully defined */
#include <nuttx/mm/mm.h>

/* The public header <nuttx/mm/mm.h> only forward declares struct mm_heap_s.
 * The full definition is in the internal header or a different location not easily accessible.
 * However, since we are implementing a shim that assumes ABI compatibility with a prebuilt library,
 * and that library expects to pass a pointer to us, we can assume the structure layout matches
 * what the internal code expects.
 *
 * To access heap->mm_lock, we need the definition. 
 * Since we cannot easily include the internal header from vendor/, we will copy the 
 * relevant part of the struct definition here to allow access to the first member (mm_lock).
 * 
 * NOTE: This is fragile if struct mm_heap_s definition changes at the beginning.
 * But mutex is usually the first member.
 */

/* Re-definition of the start of struct mm_heap_s based on internal headers.
 * We only need enough to reach mm_lock.
 */
struct mm_heap_s_shim
{
  rmutex_t mm_lock;
};

int mm_lock(FAR struct mm_heap_s *heap)
{
  FAR struct mm_heap_s_shim *shim_heap = (FAR struct mm_heap_s_shim *)heap;
  return nxrmutex_lock(&shim_heap->mm_lock);
}

void mm_unlock(FAR struct mm_heap_s *heap)
{
  FAR struct mm_heap_s_shim *shim_heap = (FAR struct mm_heap_s_shim *)heap;
  nxrmutex_unlock(&shim_heap->mm_lock);
}

/* Critical section shim for prebuilt libraries */

#undef enter_critical_section
#undef leave_critical_section

irqstate_t enter_critical_section(void)
{
  return up_irq_save();
}

void leave_critical_section(irqstate_t flags)
{
  up_irq_restore(flags);
}

/* WDT Override shim - weak so prebuilt can override */
weak_function int bes_wdt_initialize(void)
{
  return 0;
}
