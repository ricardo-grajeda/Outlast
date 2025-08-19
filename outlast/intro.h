#include <iostream>
#include <string>

void intro(bool battery, bool run_speed, bool noclip, bool health, bool fov)
{


	system("cls");
	std::cout << "		:::OUTLAST SHIT MENU:::\n" <<
		"----------------------------------------------------------" <<
		"\nNo Clip: " << (noclip ? "ON" : "OFF") <<
		"\nFov fly: " << (fov ? "ON" : "OFF") <<
		"\nTeleport to FOV: " << "DEFAULT IS \"F3\" KEY" <<
		"\nMax_battery: " << (battery ? "True" : "False") <<
		"\nMax_health: " << (health ? "True" : "False") <<
		"\nRun_speed enhanced: " << (run_speed ? "True" : "False");
		
	std::cout << "\n\n[NO CLIP & FOV FLY info] --- [W]FORWARD, [S] BACKWARDS , [Q]ACCEND, [E] DECEND";




	std::cout << "\n\n\n***HINT: [+]set toggle buttons in local_player.h[+]" << std::endl;
		
}

