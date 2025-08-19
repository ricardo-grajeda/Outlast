#include <iostream>
#include <Windows.h>
#include "offsets.h"
#include "math.h"
#include "local_player.h"
#include "intro.h"
using namespace std;


bool max_battery = false;
bool run_speed = false;
bool b_no_clip = false;
bool max_health_cap = false;
bool b_fov = false; //head postition literally
float run_speed_value = 1500;
math::vec3 original_origins{ 0.0f, 0.0f, 0.0f }; //var used for no clip
math::vec3 clips{ 0.0f, 0.0f, 0.0f }; //var used for no clip

math::vec3 original_fov{ 0.0f, 0.0f, 90.0f };
math::vec3 fovs{ 0.0f, 0.0f, 0.0f };

void noclip(math::vec3& p, int yaw_raw);
void toggled_bools(local_player local);
void if_key_pressed(local_player local);

DWORD WINAPI MainThread(HMODULE hModule)
{
    //allocate console
    AllocConsole();
    FILE* f;
    freopen_s(&f, "CONOUT$", "w", stdout);
    
    uintptr_t game_base = (uintptr_t)(GetModuleHandle("OLGame.exe"));

    local_player local = {};
	local = local.local_player_init(game_base);

    


    intro(max_battery, run_speed, b_no_clip, max_health_cap, b_fov);

    while (true)
    {
        toggled_bools(local);
        
        if_key_pressed(local);

        
        

        if (GetAsyncKeyState(VK_END))
        {
            cout << "exiting..." << endl;
            Sleep(1000);
            break;
        }

        
    }

    fclose(f);
    FreeConsole();
    FreeLibraryAndExitThread(hModule, 0);
}

void toggled_bools(local_player local)
{
    if (max_health_cap)
    {
        *local.max_health_capacity = 9999;
        *local.health = *local.max_health_capacity;
    }

    if (b_fov)
    {
        *local.fov = fovs;
        *local.origin = clips;
        noclip(fovs, *local.yaw);
    }


    if (b_no_clip)
    {
        *local.origin = clips;
        noclip(clips, *local.yaw);
    }

    if (run_speed)
    {
        *local.run_speed = run_speed_value;
    }

    if (max_battery)
    {
        *local.cam_battery = 1.0f;

    }
}

void if_key_pressed(local_player local)
{
    if (GetAsyncKeyState(toggle_battery) & 1)
    {
        max_battery = !max_battery;
        if (max_battery)
        {
            intro(max_battery, run_speed, b_no_clip, max_health_cap, b_fov);
        }
        else if (max_battery == false)
        {
            intro(max_battery, run_speed, b_no_clip, max_health_cap, b_fov);
        }
    }

    if (GetAsyncKeyState(toggle_run_speed) & 1)
    {
        run_speed = !run_speed;
        if (run_speed)
        {
            intro(max_battery, run_speed, b_no_clip, max_health_cap, b_fov);
        }
        else if (run_speed == false)
        {
            intro(max_battery, run_speed, b_no_clip, max_health_cap, b_fov);
        }
    }

    if (GetAsyncKeyState(toggle_noclip) & 1)
    {
        b_no_clip = !b_no_clip; //w,s forward and backwards (use mouse to change direction) q and e to accend and decend
        if (b_no_clip)
        {


            original_origins = *local.origin;
            clips = original_origins;
            b_fov = false;
            intro(max_battery, run_speed, b_no_clip, max_health_cap, b_fov);
        }
        else if (b_no_clip == false)
        {
            intro(max_battery, run_speed, b_no_clip, max_health_cap, b_fov);

        }
    }

    if (GetAsyncKeyState(toggle_fov_fly) & 1)
    {
        b_fov = !b_fov;
        if (b_fov)
        {

            original_fov = *local.fov;
            fovs = original_fov;

            //prevents local player from moving while using keys "w,s"
            original_origins = *local.origin;
            clips = original_origins;
            b_no_clip = false;
            intro(max_battery, run_speed, b_no_clip, max_health_cap, b_fov);
        }
        else if (b_fov == false)
        {
            intro(max_battery, run_speed, b_no_clip, max_health_cap, b_fov);

        }
    }

    if (GetAsyncKeyState(toggle_health) & 1)
    {
        max_health_cap = !max_health_cap;
        if (max_health_cap)
        {
            intro(max_battery, run_speed, b_no_clip, max_health_cap, b_fov);

        }
        else if (max_health_cap == false)
        {
            intro(max_battery, run_speed, b_no_clip, max_health_cap, b_fov);

            *local.max_health_capacity = 100;
        }
    }



    if ((GetAsyncKeyState(toggle_teleport_to_fov) & 1))
    {
        *local.origin = *local.fov; //teleport to fov
        clips = *local.origin; //set noclip to fov
    }


}

void noclip(math::vec3& p, int yaw_raw) //This math credit goes to chatgpt
{   
    static ULONGLONG t0 = GetTickCount64();
    ULONGLONG t1 = GetTickCount64();
    float dt = float(t1 - t0) * 0.001f; t0 = t1;
    if (dt > 0.05f) dt = 0.05f;

    // map raw yaw (±32767) -> radians (−π..+π)
    float r = float(yaw_raw) * (3.14159265358979f / 32768.0f);

    // UE-like axes: X forward, Y right
    float fx = std::cosf(r);
    float fy = std::sinf(r);

    float step = 900.0f * dt; // tune speed

    if (GetAsyncKeyState('W') & 0x8000) { p.x += fx * step; p.y += fy * step; }
    if (GetAsyncKeyState('S') & 0x8000) { p.x -= fx * step; p.y -= fy * step; }
        if (GetAsyncKeyState(0x51) & 1) // q to accend
        {
            p.z += 30.0f;
        }

        if (GetAsyncKeyState(0x45) & 1) // e to decend
        {
            p.z -= 30.0f;
        }
}


BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
		CloseHandle(CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)MainThread, hModule, 0, NULL));
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

