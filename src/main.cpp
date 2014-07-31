#include <iostream>
#include <string>
#include <functional>
#include <map>

#include "marlight.h"

using namespace std;

static const string   default_host = "localhost";
static const uint16_t default_port = 50000;

inline
void checkArgs(int argc, int cmdIdx, int expectCount)
{
    if (argc - (cmdIdx + 1) != expectCount)
    {
        cerr << "Command expect " << expectCount << " arguments, but " << (argc - (cmdIdx + 1)) << " given" << endl;
        exit(1);
    }
}

struct Command
{
    int                               argsCount;
    string                            argsHelp;
    string                            argsDescription;
    function<void(int, char **, int, MarlightCtx*)> callback;
};


map<string, Command> commands{
    {"channel_on", {
            1,
            "<channel_number>",
            "lamp channel number 1..4",
            [](int argc, char **argv, int cmdIdx, MarlightCtx* ctx){
                string arg(argv[cmdIdx+1]);
                int lamp = stoi(arg);
                if (lamp < 1 || lamp > 4)
                {
                    cerr << "Lamp number must be between 1 and 4" << endl;
                    exit(1);
                }

                marlight_channel_on(ctx, static_cast<MarlightChannel>(lamp));
            }
        }},
    {"channel_off", {
            1,
            "<channel_number>",
            "lamp channel number 1..4",
            [](int argc, char **argv, int cmdIdx, MarlightCtx* ctx){
                string arg(argv[cmdIdx+1]);
                int lamp = stoi(arg);
                if (lamp < 1 || lamp > 4)
                {
                    cerr << "Lamp number must be between 1 and 4" << endl;
                    exit(1);
                }

                marlight_channel_off(ctx, static_cast<MarlightChannel>(lamp));
            }
        }},
    {"rgb_set_color", {
            3,
            "<r> <g> <b>",
            "RGB components",
            [](int argc, char **argv, int cmdIdx, MarlightCtx* ctx){
                uint8_t r = stoi(argv[cmdIdx+1]);
                uint8_t g = stoi(argv[cmdIdx+2]);
                uint8_t b = stoi(argv[cmdIdx+3]);

                marlight_rgb_set_color(ctx, r, g, b);
            }
        }},
    {"preset_timer", {
            4,
            "<on_hour> <on_min> <off_hour> <off_min>",
            "",
            [](int argc, char **argv, int cmdIdx, MarlightCtx* ctx){
                uint8_t c1 = stoi(argv[cmdIdx+1]);
                uint8_t c2 = stoi(argv[cmdIdx+2]);
                uint8_t c3 = stoi(argv[cmdIdx+3]);
                uint8_t c4 = stoi(argv[cmdIdx+4]);

                marlight_preset_timer(ctx, c1, c2, c3, c4);
            }
        }},
    {"preset_alarm", {
            2,
            "<hour> <min>",
            "",
            [](int argc, char **argv, int cmdIdx, MarlightCtx* ctx){
                uint8_t c1 = stoi(argv[cmdIdx+1]);
                uint8_t c2 = stoi(argv[cmdIdx+2]);

                marlight_preset_alarm(ctx, c1, c2);
            }
        }},
    {"preset_recreation", {
            3,
            "<r> <g> <b>",
            "RGB components",
            [](int argc, char **argv, int cmdIdx, MarlightCtx* ctx){
                uint8_t r = stoi(argv[cmdIdx+1]);
                uint8_t g = stoi(argv[cmdIdx+2]);
                uint8_t b = stoi(argv[cmdIdx+3]);

                marlight_preset_recreation(ctx, r, g, b);
            }
        }},

    ////////////////////////////////////////////////////////////////////////////////////////////////

    {"all_on", {
            0,
            "",
            "",
            [](int, char **, int, MarlightCtx* ctx){
                marlight_all_on(ctx);
            }
        }},
    {"all_off", {
            0,
            "",
            "",
            [](int, char **, int, MarlightCtx* ctx){
                marlight_all_off(ctx);
            }
        }},
    {"bright_up", {
            0,
            "",
            "",
            [](int, char **, int, MarlightCtx* ctx){
                marlight_bright_up(ctx);
            }
        }},
    {"bright_down", {
            0,
            "",
            "",
            [](int, char **, int, MarlightCtx* ctx){
                marlight_bright_down(ctx);
            }
        }},
    {"temp_colder", {
            0,
            "",
            "",
            [](int, char **, int, MarlightCtx* ctx){
                marlight_temperature_colder(ctx);
            }
        }},
    {"temp_warmer", {
            0,
            "",
            "",
            [](int, char **, int, MarlightCtx* ctx){
                marlight_temperature_warmer(ctx);
            }
        }},
    {"default_temp_bright", {
            0,
            "",
            "",
            [](int, char **, int, MarlightCtx* ctx){
                marlight_default_temperature_bright(ctx);
            }
        }},
    {"rgb_bright_up", {
            0,
            "",
            "",
            [](int, char **, int, MarlightCtx* ctx){
                marlight_rgb_bright_up(ctx);
            }
        }},
    {"rgb_bright_down", {
            0,
            "",
            "",
            [](int, char **, int, MarlightCtx* ctx){
                marlight_rgb_bright_down(ctx);
            }
        }},
    {"rgb_mode_on", {
            0,
            "",
            "",
            [](int, char **, int, MarlightCtx* ctx){
                marlight_rgb_mode_on(ctx);
            }
        }},
    {"preset_night", {
            0,
            "",
            "",
            [](int, char **, int, MarlightCtx* ctx){
                marlight_preset_night(ctx);
            }
        }},
    {"preset_meeting", {
            0,
            "",
            "",
            [](int, char **, int, MarlightCtx* ctx){
                marlight_preset_meeting(ctx);
            }
        }},
    {"preset_reading", {
            0,
            "",
            "",
            [](int, char **, int, MarlightCtx* ctx){
                marlight_preset_reading(ctx);
            }
        }},
    {"preset_mode", {
            0,
            "",
            "",
            [](int, char **, int, MarlightCtx* ctx){
                marlight_preset_mode(ctx);
            }
        }},
    {"preset_timer_default", {
            0,
            "",
            "",
            [](int, char **, int, MarlightCtx* ctx){
                marlight_preset_timer_default(ctx);
            }
        }},
    {"preset_sleep", {
            0,
            "",
            "",
            [](int, char **, int, MarlightCtx* ctx){
                marlight_preset_sleep(ctx);
            }
        }},
};


void usage(char *prog)
{
    cout << "Use: " << prog << " [--host host] [--port port] command\n";
    cout << "  Commands:\n";

    for (auto &item : commands)
    {
        const string &name    = get<0>(item);
        const Command &detail = get<1>(item);

        cout << "    " << name << " " << detail.argsHelp << '\n';
        if (detail.argsCount > 0 && not detail.argsDescription.empty())
        {
            cout << "      " << detail.argsDescription << '\n';
        }
    }
}

int main(int argc, char **argv)
{
    MarlightCtx *ctx = NULL;
    string   host = default_host;
    uint16_t port = default_port;
    string   cmd;
    int      cmdIdx = -1;

    ctx = marlight_alloc_context();
    if (not ctx)
    {
        cerr << "Can't alloc marlight context" << endl;
        return 1;
    }

    // Add compat alias to lamp_on/off
    commands["lamp_on"]  = commands["channel_on"];
    commands["lamp_off"] = commands["channel_off"];

    for (int i = 1; i < argc; ++i)
    {
        string param(argv[i]);
        if (param == "--host")
        {
            host = argv[++i];
        }
        else if (param == "--port")
        {
            string arg(argv[++i]);
            port = stoi(arg);
        }
        else if (param == "--help")
        {
            usage(argv[0]);
            exit(0);
        }
        else
        {
            cmd    = argv[i];
            cmdIdx = i;
            break;
        }
    }

    if (cmd.empty())
    {
        clog << "Empty command" << endl;
        usage(argv[0]);
        exit(1);
    }

    clog << "Marlight host: " << host << ", port: " << port << ", command: " << cmd << endl;

    marlight_init_context(ctx, host.c_str(), port);

    auto it = commands.find(cmd);
    if (it == commands.end())
    {
        cerr << "Command not found" << endl;
        exit(1);
    }

    Command &detail = get<1>(*it);
    checkArgs(argc, cmdIdx, detail.argsCount);

    detail.callback(argc, argv, cmdIdx, ctx);

    marlight_free_context(&ctx);
    return 0;
}

