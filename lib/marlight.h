#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    LAMP_1,
    LAMP_2,
    LAMP_3,
    LAMP_4
} MarlightLamp;

typedef struct MarlightCtx MarlightCtx;

MarlightCtx *marlight_alloc_context();
void         marlight_free_context(MarlightCtx **ctx);
void         marlight_init_context(MarlightCtx *ctx, const char *host, uint16_t port);


int          marlight_send_custom_message(MarlightCtx *ctx, const char *message, size_t size);

int          marlight_lamp_on(MarlightCtx *ctx, MarlightLamp lamp);
int          marlight_lamp_off(MarlightCtx *ctx, MarlightLamp lamp);

int          marlight_all_on(MarlightCtx *ctx);
int          marlight_all_off(MarlightCtx *ctx);

int          marlight_bright_up(MarlightCtx *ctx);
int          marlight_bright_down(MarlightCtx *ctx);

int          marlight_temperature_colder(MarlightCtx *ctx);
int          marlight_temperature_warmer(MarlightCtx *ctx);

int          marlight_default_temperature_bright(MarlightCtx *ctx);

int          marlight_rgb_bright_up(MarlightCtx *ctx);
int          marlight_rgb_bright_down(MarlightCtx *ctx);

int          marlight_rgb_mode_on(MarlightCtx *ctx);
int          marlight_rgb_set_color(MarlightCtx *ctx, uint8_t r, uint8_t g, uint8_t b);

int          marlight_preset_night(MarlightCtx *ctx);
int          marlight_preset_meeting(MarlightCtx *ctx);
int          marlight_preset_reading(MarlightCtx *ctx);
int          marlight_preset_mode(MarlightCtx *ctx);

int          marlight_preset_timer(MarlightCtx *ctx, uint8_t on_hour, uint8_t on_minutes, uint8_t off_hour, uint8_t off_minutes);
int          marlight_preset_timer_default(MarlightCtx *ctx);

int          marlight_preset_alarm(MarlightCtx *ctx, uint8_t hour, uint8_t min);

int          marlight_preset_sleep(MarlightCtx *ctx);

int          marlight_preset_recreation(MarlightCtx *ctx, uint8_t r, uint8_t g, uint8_t b);


#ifdef __cplusplus
}
#endif
