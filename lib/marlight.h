#pragma once

#include <stdint.h>

/* Support for GCC, Mingw and MSVC */
#if __GNUC__ >= 4
#  if (defined(_WIN32) || defined(__WIN32__) || defined(WIN32)) && !defined(__CYGWIN__)
#    define HAS_DECLSPEC
#    define SYMBOL_EXPORT __attribute__((dllexport))
#    define SYMBOL_IMPORT __attribute__((dllimport))
#  endif // defined(_WIN32)
#elif !defined(__GNUC__)
#  define HAS_DECLSPEC
#  define SYMBOL_EXPORT __declspec(dllexport)
#  define SYMBOL_IMPORT __declspec(dllimport)
#endif // __GNUC__

#ifdef HAS_DECLSPEC
#  ifdef MARLIGHT_SOURCE
#    define MARLIGHT_API SYMBOL_EXPORT
#  else
#    define MARLIGHT_API SYMBOL_IMPORT
#  endif
#endif

#ifndef MARLIGHT_API
#define MARLIGHT_API
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    CHANNEL_1 = 1,
    CHANNEL_2,
    CHANNEL_3,
    CHANNEL_4,
    // Compat
    LAMP_1 = CHANNEL_1,
    LAMP_2 = CHANNEL_2,
    LAMP_3 = CHANNEL_3,
    LAMP_4 = CHANNEL_4
} MarlightChannel;

typedef MarlightChannel MarlightLamp;

typedef struct MarlightCtx MarlightCtx;

MARLIGHT_API MarlightCtx *marlight_alloc_context();
MARLIGHT_API void         marlight_free_context(MarlightCtx **ctx);
MARLIGHT_API void         marlight_init_context(MarlightCtx *ctx, const char *host, uint16_t port);

MARLIGHT_API int          marlight_send_custom_message(MarlightCtx *ctx, const char *message, size_t size);

MARLIGHT_API int          marlight_lamp_on(MarlightCtx *ctx, MarlightLamp lamp) __attribute__((deprecated("Use marlight_channel_on() insted")));
MARLIGHT_API int          marlight_lamp_off(MarlightCtx *ctx, MarlightLamp lamp) __attribute__((deprecated("Use marlight_channel_off() insted")));

MARLIGHT_API int          marlight_channel_on(MarlightCtx *ctx, MarlightChannel channel);
MARLIGHT_API int          marlight_channel_off(MarlightCtx *ctx, MarlightChannel channel);

MARLIGHT_API int          marlight_all_on(MarlightCtx *ctx);
MARLIGHT_API int          marlight_all_off(MarlightCtx *ctx);

MARLIGHT_API int          marlight_bright_up(MarlightCtx *ctx);
MARLIGHT_API int          marlight_bright_down(MarlightCtx *ctx);

MARLIGHT_API int          marlight_temperature_colder(MarlightCtx *ctx);
MARLIGHT_API int          marlight_temperature_warmer(MarlightCtx *ctx);

MARLIGHT_API int          marlight_default_temperature_bright(MarlightCtx *ctx);

MARLIGHT_API int          marlight_rgb_bright_up(MarlightCtx *ctx);
MARLIGHT_API int          marlight_rgb_bright_down(MarlightCtx *ctx);

MARLIGHT_API int          marlight_rgb_mode_on(MarlightCtx *ctx);
MARLIGHT_API int          marlight_rgb_set_color(MarlightCtx *ctx, uint8_t r, uint8_t g, uint8_t b);

MARLIGHT_API int          marlight_preset_night(MarlightCtx *ctx);
MARLIGHT_API int          marlight_preset_meeting(MarlightCtx *ctx);
MARLIGHT_API int          marlight_preset_reading(MarlightCtx *ctx);
MARLIGHT_API int          marlight_preset_mode(MarlightCtx *ctx);

MARLIGHT_API int          marlight_preset_timer(MarlightCtx *ctx, uint8_t on_hour, uint8_t on_minutes, uint8_t off_hour, uint8_t off_minutes);
MARLIGHT_API int          marlight_preset_timer_default(MarlightCtx *ctx);

MARLIGHT_API int          marlight_preset_alarm(MarlightCtx *ctx, uint8_t hour, uint8_t min);

MARLIGHT_API int          marlight_preset_sleep(MarlightCtx *ctx);

MARLIGHT_API int          marlight_preset_recreation(MarlightCtx *ctx, uint8_t r, uint8_t g, uint8_t b);

#ifdef __cplusplus
}
#endif
