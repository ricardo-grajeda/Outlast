#pragma once
#include <iostream>
#include <vector>

namespace offsets
{
	static std:: vector<uintptr_t> local_entity = { 0x02020F38, 0x248};
	static constexpr uintptr_t camera_battery = 0x31A8;
	static constexpr uintptr_t origin = 0x80;
	static constexpr uintptr_t run_speed = 0x3218;
	static constexpr uintptr_t max_health_capacity = 0x380; //default 100
	static constexpr uintptr_t health = 0x3168;
	static constexpr uintptr_t fov = 0x30e4;
	static constexpr uintptr_t yaw = 0x90; //32767 to =-32767 not in degrees

	//cam_stuff
	static constexpr uintptr_t cam_stuff = 0x2bbc;
	static constexpr uintptr_t battery = 0xaa0; // //USAGE: local_entity -> cam_stuff -> battery(0xaa0) (int)
}