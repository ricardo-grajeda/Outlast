#include "local_player.h"


local_player::local_player()
{
	local_player_address = 0;
	origin = nullptr;
	cam_battery = nullptr;
	run_speed = nullptr;
	max_health_capacity = nullptr;
	health = nullptr;
	yaw = nullptr;
}

local_player local_player::local_player_init(uintptr_t game_base)
{
	local_player local = local_player();
	local.get_local_player_address(game_base);
	local.get_cam_battery();
	local.get_origin();
	local.get_run_speed();
	local.get_max_health_capacity();
	local.get_health();
	local.get_fov();
	local.get_yaw();



	return local;
}

//getters

void local_player::get_local_player_address(uintptr_t game_base)
{
	local_player_address = math::resolve_address(offsets::local_entity, game_base);
}

void local_player::get_origin()
{
	origin = (math::vec3*)((uintptr_t*)(local_player_address + offsets::origin));
}

void local_player::get_cam_battery()
{
	cam_battery = (float*)((uintptr_t*)(local_player_address + offsets::camera_battery));
}

void local_player::get_run_speed()
{
	run_speed = (float*)((uintptr_t*)(local_player_address + offsets::run_speed));
}

void local_player::get_max_health_capacity()
{
	max_health_capacity = (int*)((uintptr_t*)(local_player_address + offsets::max_health_capacity));
}

void local_player::get_health()
{
	health = (float*)((uintptr_t*)(local_player_address + offsets::health));
}

void local_player::get_fov()
{

	fov = (math::vec3*)((uintptr_t*)(local_player_address + offsets::fov));
	
}

void local_player::get_yaw()
{
	yaw = (int*)((uintptr_t*)(local_player_address + offsets::yaw));
}



//setters

void local_player::set_fov(math::vec3 new_fov)
{
	math::vec3 old_fov = { fov->x, fov->y, fov->z };
	if (fov)
	{

		fov->z = old_fov.x + new_fov.z;
	}
	else
	{
		std::cerr << "FOV pointer is null!" << std::endl;
	}
}