#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>

#include "marlight.h"

// ----------------------------- FIRST PAGE IPHONE APPLICATION  -----------------------------------
static const char ALL_ON[]      = { 0x01, 0x55 };
static const char ALL_OFF[]     = { 0x02, 0x55 };

static const char BRIGHT_UP[]   = { 0x03, 0x55 };
static const char BRIGHT_DOWN[] = { 0x04, 0x55 };

static const char TEMP_COLDER[] = { 0x05, 0x55 };
static const char TEMP_WARMER[] = { 0x06, 0x55 };

static const char BRIGHT_TEMP_DEFAULT[] = { 0x07, 0x55 };

static const char ON_1[]  = { 0x08, 0x55 };
static const char OFF_1[] = { 0x09, 0x55 };
static const char ON_2[]  = { 0x0A, 0x55 };
static const char OFF_2[] = { 0x0B, 0x55 };
static const char ON_3[]  = { 0x0C, 0x55 };
static const char OFF_3[] = { 0x0D, 0x55 };
static const char ON_4[]  = { 0x0E, 0x55 };
static const char OFF_4[] = { 0x0F, 0x55 };

// ----------------------------- SECOND PAGE IPHONE APPLICATION (RGB) -----------------------------------
static const char RGB_MODE_ON[]          = { 0x12, 0x55 };
static const char RGB_MODE_BRIGHT_DOWN[] = { 0x10, 0x55 };
static const char RGB_MODE_BRIGHT_UP[]   = { 0x11, 0x55 };
static const char RGB_MODE_SET_COLOR[]   = { 0x13, 0x00, 0x00, 0x00, 0x55 };

// ----------------------------- THIRD PAGE IPHONE APPLICATION (PRESETS) -----------------------------------
static const char MODE_NIGHT[]   = { 0x14, 0x55 };
static const char MODE_MEETING[] = { 0x15, 0x55 };
static const char MODE_READING[] = { 0x16, 0x55 };
static const char MODE_MODE[]    = { 0x17, 0x55 };

static const char MODE_TIMER[]      = { 0x18, 0x00, 0x00, 0x00, 0x00, 0x09, 0x14, 0x55 };
static const char MODE_ALARM[]      = { 0x19, 0x00, 0x00, 0x09, 0x14, 0x55 };
static const char MODE_SLEEP[]      = { 0x1A, 0x55 }; // ??????
static const char MODE_RECREATION[] = { 0x1B, 0x00, 0x00, 0x00, 0x55 };

////////////////////////////////////////////////////////////////////////////////////////////////////

struct MarlightCtx {
    char      *host;
    uint16_t   port;
};


MarlightCtx *marlight_alloc_context()
{
    return (MarlightCtx*)calloc(1, sizeof(MarlightCtx));
}

void marlight_free_context(MarlightCtx **ctx)
{
    if (!ctx || !*ctx)
        return;

    if (!(*ctx)->host)
        free((*ctx)->host);

    free(*ctx);
    *ctx = NULL;
}


void marlight_init_context(MarlightCtx *ctx, const char *host, uint16_t port)
{
    assert(ctx);
    assert(host);
    assert(port > 0);

    if (ctx->host)
        free(ctx->host);

    ctx->host = strdup(host);
    ctx->port = port;
}

#define SEND_MESSAGE(ctx, message) send_message(ctx, message, sizeof(message))

static
int send_message(MarlightCtx *ctx, const char* message, size_t size)
{
    int                 s;
    int                 status;
    ssize_t             sended;
    ssize_t             total = 0;
    struct sockaddr_in  addr;
    struct hostent     *host;

    assert(ctx);
    assert(message);
    assert(size > 0);

    bzero(&addr, sizeof(addr));
    addr.sin_family = AF_INET;
    host = gethostbyname(ctx->host);
    bcopy(host->h_addr, &(addr.sin_addr.s_addr), host->h_length);
    addr.sin_port = htons(ctx->port);

    s = socket(PF_INET, SOCK_DGRAM, 0);
    if (s < 0)
        return -1;

    status = connect(s, (struct sockaddr *)&addr, sizeof(addr));
    if (status < 0)
        goto handle_error;


    while (true)
    {
        sended = send(s, message + total, size - total, 0);
        if (sended < 0)
        {
            if (errno == EINTR)
                continue;
            status = -1;
            goto handle_error;
        }

        total += sended;
        if (total == size)
            break;
    }

handle_error:
    close(s);
    return status;
}


int marlight_send_custom_message(MarlightCtx *ctx, const char *message, size_t size)
{
    return send_message(ctx, message, size);
}


int marlight_lamp_on(MarlightCtx *ctx, MarlightLamp lamp)
{
    return marlight_channel_on(ctx, (MarlightChannel)lamp);
}


int marlight_lamp_off(MarlightCtx *ctx, MarlightLamp lamp)
{
    return marlight_channel_off(ctx, (MarlightChannel)lamp);
}

int marlight_all_on(MarlightCtx *ctx)
{
    return send_message(ctx, ALL_ON, sizeof(ALL_ON));
}


int marlight_all_off(MarlightCtx *ctx)
{
    return send_message(ctx, ALL_OFF, sizeof(ALL_OFF));
}

int marlight_bright_up(MarlightCtx *ctx)
{
    return send_message(ctx, BRIGHT_UP, sizeof(BRIGHT_UP));
}


int marlight_bright_down(MarlightCtx *ctx)
{
    return send_message(ctx, BRIGHT_DOWN, sizeof(BRIGHT_DOWN));
}


int marlight_temperature_colder(MarlightCtx *ctx)
{
    return send_message(ctx, TEMP_COLDER, sizeof(TEMP_COLDER));
}

int marlight_temperature_warmer(MarlightCtx *ctx)
{
    return send_message(ctx, TEMP_WARMER, sizeof(TEMP_WARMER));
}


int marlight_default_temperature_bright(MarlightCtx *ctx)
{
    return send_message(ctx, BRIGHT_TEMP_DEFAULT, sizeof(BRIGHT_TEMP_DEFAULT));
}

int marlight_rgb_bright_up(MarlightCtx *ctx)
{
    return send_message(ctx, RGB_MODE_BRIGHT_UP, sizeof(RGB_MODE_BRIGHT_UP));
}

int marlight_rgb_bright_down(MarlightCtx *ctx)
{
    return send_message(ctx, RGB_MODE_BRIGHT_DOWN, sizeof(RGB_MODE_BRIGHT_DOWN));
}


int marlight_rgb_mode_on(MarlightCtx *ctx)
{
    return send_message(ctx, RGB_MODE_ON, sizeof(RGB_MODE_ON));
}


int marlight_rgb_set_color(MarlightCtx *ctx, uint8_t r, uint8_t g, uint8_t b)
{
    char buf[sizeof(RGB_MODE_SET_COLOR)];
    memcpy(buf, RGB_MODE_SET_COLOR, sizeof(RGB_MODE_SET_COLOR));
    buf[1] = r;
    buf[2] = g;
    buf[3] = b;
    return send_message(ctx, buf, sizeof(buf));
}


int marlight_preset_night(MarlightCtx *ctx)
{
    return SEND_MESSAGE(ctx, MODE_NIGHT);
}


int marlight_preset_meeting(MarlightCtx *ctx)
{
    return SEND_MESSAGE(ctx, MODE_MEETING);
}


int marlight_preset_reading(MarlightCtx *ctx)
{
    return SEND_MESSAGE(ctx, MODE_READING);
}


int marlight_preset_mode(MarlightCtx *ctx)
{
    return SEND_MESSAGE(ctx, MODE_MODE);
}


int marlight_preset_timer(MarlightCtx *ctx, uint8_t on_hour, uint8_t on_minutes, uint8_t off_hour, uint8_t off_minutes)
{
    char buf[sizeof(MODE_TIMER)];
    memcpy(buf, MODE_TIMER, sizeof(buf));
    buf[1] = on_hour;
    buf[2] = on_minutes;
    buf[3] = off_hour;
    buf[4] = off_minutes;
    return SEND_MESSAGE(ctx, buf);
}



int marlight_preset_timer_default(MarlightCtx *ctx)
{
    return SEND_MESSAGE(ctx, MODE_TIMER);
}


int marlight_preset_alarm(MarlightCtx *ctx, uint8_t hour, uint8_t min)
{
    char buf[sizeof(MODE_ALARM)];
    memcpy(buf, MODE_ALARM, sizeof(buf));
    buf[1] = hour;
    buf[2] = min;
    return SEND_MESSAGE(ctx, buf);
}


int marlight_preset_sleep(MarlightCtx *ctx)
{
    return SEND_MESSAGE(ctx, MODE_SLEEP);
}


int marlight_preset_recreation(MarlightCtx *ctx, uint8_t r, uint8_t g, uint8_t b)
{
    char buf[sizeof(MODE_RECREATION)];
    memcpy(buf, MODE_RECREATION, sizeof(buf));
    buf[1] = r;
    buf[2] = g;
    buf[3] = b;
    return SEND_MESSAGE(ctx, buf);
}


int marlight_channel_on(MarlightCtx *ctx, MarlightChannel channel)
{
    switch (channel)
    {
        case CHANNEL_1:
            return send_message(ctx, ON_1, sizeof(ON_1));
        case CHANNEL_2:
            return send_message(ctx, ON_2, sizeof(ON_2));
        case CHANNEL_3:
            return send_message(ctx, ON_3, sizeof(ON_3));
        case CHANNEL_4:
            return send_message(ctx, ON_4, sizeof(ON_4));
    }
    return -1;
}


int marlight_channel_off(MarlightCtx *ctx, MarlightChannel channel)
{
    switch (channel)
    {
        case CHANNEL_1:
            return send_message(ctx, OFF_1, sizeof(OFF_1));
        case CHANNEL_2:
            return send_message(ctx, OFF_2, sizeof(OFF_2));
        case CHANNEL_3:
            return send_message(ctx, OFF_3, sizeof(OFF_3));
        case CHANNEL_4:
            return send_message(ctx, OFF_4, sizeof(OFF_4));
    }
    return -1;
}
