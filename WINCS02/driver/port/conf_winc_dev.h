/*
 * WINCS02 nc_driver — Standalone Configuration
 *
 * Copy this file to your project include path as conf_winc_dev.h.
 * Adjust the values below for your platform.
 */

#ifndef CONF_WINC_DEV_H
#define CONF_WINC_DEV_H

/*---------------------------------------------------------------------------
 * WINC_DEV_CACHE_LINE_SIZE
 *
 * Defines the MCU cache line size in bytes. Used to align DMA buffers to
 * cache line boundaries, avoiding corruption from cache maintenance ops.
 *
 * Set to your MCU's cache line size, or 1 if your MCU has no data cache
 * (e.g. Cortex-M0/M4/M33 without cache).
 *--------------------------------------------------------------------------*/
#define WINC_DEV_CACHE_LINE_SIZE            16

/*---------------------------------------------------------------------------
 * WINC_DEBUG_LEVEL
 *
 * Controls driver debug output verbosity. Requires calling
 * WINC_DevSetDebugPrintf() with your printf-like function at startup.
 *
 * Options:
 *   WINC_DEBUG_TYPE_NONE     - No debug output
 *   WINC_DEBUG_TYPE_ERROR    - Errors only
 *   WINC_DEBUG_TYPE_INFORM   - Errors + informational messages (recommended)
 *   WINC_DEBUG_TYPE_TRACE    - Errors + info + API call tracing
 *   WINC_DEBUG_TYPE_VERBOSE  - Everything (very noisy, useful for SPI debug)
 *--------------------------------------------------------------------------*/
#define WINC_DEBUG_LEVEL                    WINC_DEBUG_TYPE_INFORM

/*---------------------------------------------------------------------------
 * WINC_CONF_SPI_MOSI_IDLE_LEVEL
 *
 * Defines what the SPI MOSI line sends when idle / when pTransmitData is
 * NULL. The WINCS02 interprets 0x00 on MOSI as valid data.
 *
 *   1 = MOSI idles HIGH (0xFF sent as dummy byte) — REQUIRED for WINCS02
 *   0 = MOSI idles LOW  (driver pre-fills a TX buffer with 0xFF internally,
 *       uses more RAM)
 *
 * Set to 1 and ensure your SPI send/receive function sends 0xFF when
 * pTransmitData is NULL.
 *--------------------------------------------------------------------------*/
#define WINC_CONF_SPI_MOSI_IDLE_LEVEL       1

/*---------------------------------------------------------------------------
 * Socket Configuration
 *--------------------------------------------------------------------------*/

/* Number of sockets the driver tracks. */
#define WINC_SOCK_NUM_SOCKETS               10U

/* Socket receive buffer size in bytes. */
#define WINC_SOCK_BUF_RX_SZ                (1500U * 5U)

/* Socket transmit buffer size in bytes. */
#define WINC_SOCK_BUF_TX_SZ                (1500U * 5U)

/* Optional (defaults shown, defined in winc_socket.c):
 *   WINC_SOCK_BUF_RX_PKT_BUF_NUM    5   UDP receive packet buffers per socket
 *   WINC_SOCK_BUF_TX_PKT_BUF_NUM    5   UDP transmit packet buffers per socket
 *   WINC_SOCK_SLAB_ALLOC_MODE       1   1 = all sockets share one slab pool,
 *                                       2 = slabs reserved per socket
 *   WINC_SOCK_SLAB_MEM_ALIGNMENT    4   Byte alignment for socket buffer memory
 *   WINC_SOCK_SLAB_STATS_ENABLE         Define to record slab usage statistics
 *                                       (WINC_SockSlabStatsGet)
 *   WINC_SOCK_NS(FUNC)              FUNC  Rename the Berkeley socket functions
 *                                       e.g. wincs02_socket_##FUNC
 *   WINC_CONF_USE_EXT_SOCK_HDRS         Define to use the platform's socket
 *                                       headers instead of the driver's own
 */

/*---------------------------------------------------------------------------
 * Device Options (optional, defaults shown, defined in winc_dev.c)
 *
 *   WINC_DEV_EXTENDED_ERROR_INFO        Define to record the SPI status and
 *                                       source file/line of the last error
 *                                       (WINC_DevGetLastErrorEx)
 *   WINC_DEV_NUM_AEC_CB_ENTRIES     5   Maximum AEC callbacks which can be
 *                                       registered
 *   WINC_DEV_INT_RELEASE_RETRY_CNT  1000000  Interrupt release checks before
 *                                       the device is treated as failed
 *--------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------
 * Multi-threading / RTOS Lock Support (optional)
 *
 * If your application is single-threaded or bare-metal, leave these
 * commented out — the driver defaults to no-op lock macros via #ifndef
 * guards in winc_dev.h.
 *
 * For RTOS usage, define these to use your OS mutex primitives. Each macro
 * takes the name of the lock storage: WINC_CONF_LOCK_STORAGE(NAME) declares
 * it, and the other macros are passed a pointer to it (&NAME). The driver
 * uses one lock for the device context and one per socket.
 *
 * Example for FreeRTOS:
 *
 *   #include "FreeRTOS.h"
 *   #include "semphr.h"
 *
 *   #define WINC_CONF_LOCK_STORAGE(NAME)    SemaphoreHandle_t NAME
 *   #define WINC_CONF_LOCK_CREATE(NAME)     (*(NAME) = xSemaphoreCreateMutex())
 *   #define WINC_CONF_LOCK_DESTROY(NAME)    vSemaphoreDelete(*(NAME))
 *   #define WINC_CONF_LOCK_ENTER(NAME)      (pdTRUE == xSemaphoreTake(*(NAME), portMAX_DELAY))
 *   #define WINC_CONF_LOCK_LEAVE(NAME)      xSemaphoreGive(*(NAME))
 *--------------------------------------------------------------------------*/

/* #define WINC_CONF_LOCK_STORAGE(NAME)  */
/* #define WINC_CONF_LOCK_CREATE(NAME)   */
/* #define WINC_CONF_LOCK_DESTROY(NAME)  */
/* #define WINC_CONF_LOCK_ENTER(NAME)    */
/* #define WINC_CONF_LOCK_LEAVE(NAME)    */

#endif /* CONF_WINC_DEV_H */
