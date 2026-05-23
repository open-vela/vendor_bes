#ifndef __NET_MUTEX_H__
#define __NET_MUTEX_H__

#include "net_defs.h"
#include "cmsis_os.h"
#include "net_debug.h"

struct net_mutex {
    osMutexId mutex_id;
#if (osCMSIS >= 0x20000U)
    osMutexAttr_t mutex_attr;
#else
#ifdef CMSIS_OS_NUTTX
    osMutexDef_t mutex;
#else
    uint32_t  os_mutex_cb[3];
#endif
#endif
};

extern void local_bh_enable(void);
extern void local_bh_disable(void);
extern void net_mutex_init_def(struct net_mutex *mutex);

static inline void net_mutex_init(struct net_mutex *mutex)
{
    osThreadId tid = osThreadGetId();
    const char *name = tid ? osThreadGetName(tid) : NULL;

    if (name && strcmp(name, "device_wifi_rx_thread") == 0) {
        printk(KERN_WARN,
               "WFSTEP mutex init enter mutex=%p old_id=%p\n",
               mutex, mutex ? mutex->mutex_id : NULL);
    }

    net_mutex_init_def((mutex));

    if (name && strcmp(name, "device_wifi_rx_thread") == 0) {
        printk(KERN_WARN,
               "WFSTEP mutex init done mutex=%p new_id=%p\n",
               mutex, mutex ? mutex->mutex_id : NULL);
    }

    NET_ASSERT((mutex)->mutex_id);
}

static inline int net_mutex_lock(struct net_mutex *lock)
{
    osStatus _ret;
    NET_ASSERT((lock)->mutex_id);
    _ret = osMutexWait((lock)->mutex_id, osWaitForever);
    if (_ret) {
        printk(KERN_ERR, "%s %d, mutex lock failed(%d)\n", __func__, __LINE__, (int)_ret);
    }
    return _ret;
}

static inline int net_mutex_trylock(struct net_mutex *lock)
{
    int ret;
    NET_ASSERT(lock->mutex_id);
#ifdef CMSIS_OS_NUTTX
    ret = osMutexWait(lock->mutex_id, 1);
#else
    ret = osMutexWait(lock->mutex_id, 0);
#endif
    return ret ? 0 : 1;
}

static inline int net_mutex_unlock(struct net_mutex *lock)
{
    osStatus _ret;
    NET_ASSERT((lock)->mutex_id);
    _ret = osMutexRelease((lock)->mutex_id);
    if (_ret) {
        printk(KERN_ERR, "%s %d, mutex unlock failed(%d)\n", __func__, __LINE__, (int)_ret);
    }
    return _ret;
}

static inline void net_mutex_destroy(struct net_mutex *lock)
{
    NET_ASSERT(lock->mutex_id);
    osMutexDelete(lock->mutex_id);
    lock->mutex_id = NULL;
}

#ifdef __NuttX__
typedef struct net_mutex net_spinlock_t;
#define spinlock_t net_spinlock_t
#else
typedef struct net_mutex spinlock_t;
#endif

static inline unsigned int spin_lock_irqsave(spinlock_t *lock, unsigned long *cpu_sr)
{
    cpu_sr = cpu_sr;
    lock = lock;
    NET_ASSERT(lock->mutex_id);
    osMutexWait(lock->mutex_id, osWaitForever);
    return 0;
}

static inline void spin_unlock_irqrestore(spinlock_t *lock, unsigned long cpu_sr)
{
    cpu_sr = cpu_sr;
    osMutexRelease(lock->mutex_id);
}

static inline void spin_lock_init(spinlock_t *lock)
{
    if (lock->mutex_id != NULL)
        osMutexDelete(lock->mutex_id);

#if (osCMSIS >= 0x20000U)
    memset(&lock->mutex_attr, 0, sizeof(osMutexAttr_t));
#ifdef KERNEL_FREERTOS
    lock->mutex_attr.attr_bits = osMutexRecursive | osMutexPrioInherit;
#else /* KERNEL_FREERTOS */
    lock->mutex_attr.attr_bits = osMutexRecursive | osMutexPrioInherit | osMutexRobust;
#endif /* KERNEL_FREERTOS */

    lock->mutex_id = osMutexNew(&lock->mutex_attr);
#else
#ifdef CMSIS_OS_NUTTX
    memset(&lock->mutex, 0, sizeof(osMutexDef_t));
    lock->mutex_id = osMutexCreate(&lock->mutex);
#else
    osMutexDef_t osmutexdef;
    memset(&osmutexdef, 0, sizeof(osmutexdef));
#ifdef osCMSIS_RTX
    osmutexdef.mutex = lock->os_mutex_cb;
    memset(lock->os_mutex_cb, 0, sizeof(lock->os_mutex_cb));
#endif
    lock->mutex_id = osMutexCreate(&osmutexdef);
#endif
#endif

    NET_ASSERT(lock->mutex_id);
}

static inline void spin_lock_destroy(spinlock_t *lock)
{
    NET_ASSERT(lock->mutex_id);
    osMutexDelete(lock->mutex_id);
    lock->mutex_id = NULL;
}

static inline int spin_lock(spinlock_t *lock)
{
    osStatus _ret;
    NET_ASSERT((lock)->mutex_id);
    _ret = osMutexWait((lock)->mutex_id, osWaitForever);
    if (_ret) {
        printk(KERN_ERR, "%s %d, mutex lock failed(%d)\n", __func__, __LINE__, (int)_ret);
    }
    return _ret;
}

static inline int spin_unlock(spinlock_t *lock)
{
    osStatus _ret;
    NET_ASSERT((lock)->mutex_id);
    _ret = osMutexRelease((lock)->mutex_id);
    if (_ret) {
        printk(KERN_ERR, "%s %d, mutex unlock failed(%d)\n", __func__, __LINE__, (int)_ret);
    }
    return _ret;
}

#define spin_lock_bh(lock) spin_lock(lock)
#define spin_unlock_bh(lock) spin_unlock(lock)

#endif
