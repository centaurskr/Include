/**
 * @file    netlog2.h
 * @brief   Public API for high-performance UNIX domain socket logging.
 *
 * This library provides a lightweight, non-blocking logging interface
 * designed for high-throughput, multi-threaded server applications.
 *
 * Key characteristics:
 *  - Zero mutex (thread-local socket)
 *  - Fire-and-forget logging
 *  - JSON formatted messages
 *  - UNIX domain datagram transport
 *
 * Typical usage:
 * @code
 *   InitNetLogout("order-engine", 3);
 *   NetLogout(LOG_INFO, "engine started");
 * @endcode
 *
 * Logging path:
 *   Application -> netlog -> UNIX DGRAM -> Vector
 *
 * @note
 *  - Logging must never block main execution path.
 *  - When Vector is unavailable, logs are silently dropped.
 *
 * @author
 *   Cento
 *
 * @date
 *   2025. 12. 23. (화) 15:07:13 KST
 */

#ifndef NETLOG_H
#define NETLOG_H

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

/* -------------------------------------------------------------------------- */
/*                              Log levels                                    */
/* -------------------------------------------------------------------------- */

/**
 * @enum LogLevel
 * @brief Supported log severity levels.
 *
 * The numeric order is significant and may be used for filtering
 * or sampling in future extensions.
 */
enum LogLevel {
    /** Debug-level messages (high volume, optional) */
    LOG_DEBUG = 0,

    /** Informational messages (default operational logs) */
    LOG_INFO  = 1,

    /** Error-level messages (failures, alerts) */
    LOG_ERROR = 2
};

/* -------------------------------------------------------------------------- */
/*                          Public API functions                               */
/* -------------------------------------------------------------------------- */

/**
 * @brief Initialize network logging for the current process.
 *
 * This function must be called exactly once during process startup
 * (before any NetLogout() invocation).
 *
 * It sets process-wide metadata that will be included in every log record.
 *
 * @param pname
 *  Logical process name.
 *  Example: "order-engine", "price-feed", "auth-service"
 *
 * @param pindex
 *  Logical process index (instance number).
 *  Used for:
 *   - sharding
 *   - grouping
 *   - retention policies
 *
 * @return
 *  - 0 on success
 *  - -1 on invalid arguments
 *
 * @note
 *  This function does NOT open any socket.
 *  Sockets are created lazily per-thread on first log emission.
 */
extern int InitNetLogout(const char *pname, int pindex);

/**
 * @brief Core logging function (internal use).
 *
 * This function is normally NOT called directly.
 * Use the NetLogout() macro instead.
 *
 * @param level
 *  Log severity level (LOG_DEBUG, LOG_INFO, LOG_ERROR)
 *
 * @param file
 *  Source file name (usually __FILE__)
 *
 * @param func
 *  Function name (usually __FUNCTION__ or __func__)
 *
 * @param line
 *  Source line number (usually __LINE__)
 *
 * @param fmt
 *  printf-style format string
 *
 * @param ...
 *  Format arguments
 *
 * @warning
 *  This function is NOT async-signal-safe.
 *  Do NOT call from signal handlers.
 */
extern void _NetLogout(int level,
                const char *file,
                const char *func,
                int line,
                const char *fmt, ...);

/* -------------------------------------------------------------------------- */
/*                               Public macro                                  */
/* -------------------------------------------------------------------------- */

/**
 * @brief Emit a log message with source context.
 *
 * This macro automatically captures:
 *  - source file
 *  - function name
 *  - line number
 *
 * and forwards them to the internal logger.
 *
 * @param level
 *  Log severity level
 *
 * @param fmt
 *  printf-style format string
 *
 * @param ...
 *  Format arguments
 *
 * Example:
 * @code
 *   NetLogout(LOG_INFO, "connected to %s", host);
 *   NetLogout(LOG_ERROR, "failed rc=%d", rc);
 * @endcode
 */
#define NetLogout(level, fmt, ...) \
    _NetLogout(level, __FILE__, __FUNCTION__, __LINE__, fmt, ##__VA_ARGS__)

/* -------------------------------------------------------------------------- */
/*                          Design and usage notes                              */
/* -------------------------------------------------------------------------- */

/**
 * @section threading Threading model
 *
 * - The library is fully thread-safe.
 * - Each thread owns its own UNIX domain socket (TLS).
 * - No mutex or global lock is used.
 *
 * @section performance Performance characteristics
 *
 * - Main path cost: formatting + single sendto() syscall
 * - Non-blocking I/O
 * - Suitable for hundreds of millions of logs per day
 *
 * @section failure Failure behavior
 *
 * - If Vector is down or socket buffer is full:
 *     logs are silently dropped.
 * - Logging never blocks or slows down application logic.
 *
 * @section limitations Limitations
 *
 * - JSON escaping for message field is minimal.
 * - Not safe for use inside signal handlers.
 * - Log ordering is guaranteed only per-thread.
 */

#ifdef __cplusplus
}
#endif

#endif /* NETLOG_H */

