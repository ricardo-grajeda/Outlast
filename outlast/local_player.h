#pragma once
#include <iostream>
#include "offsets.h"
#include "math.h"

#define toggle_run_speed VK_F6
#define toggle_health VK_F5
#define toggle_battery VK_F4
#define toggle_noclip VK_F1
#define toggle_fov_fly VK_F2
#define toggle_teleport_to_fov VK_F3

class local_player
{
public:
	//variables
	uintptr_t local_player_address;
	math::vec3* origin;
	float* cam_battery;
	float* run_speed;
	int* max_health_capacity;
	float* health;
	math::vec3 *fov;
	float* test;
	int* yaw;

	//constuctors
	local_player();
	

	//function getters
	local_player local_player_init(uintptr_t game_base);
	void get_local_player_address(uintptr_t game_base);
	void get_origin();
	void get_cam_battery();
	void get_run_speed();	
	void get_max_health_capacity();
	void get_health();
	void get_fov();
	void get_yaw();

	//function setters
	void set_fov(math::vec3 new_fov);
};

