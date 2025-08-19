#pragma once

namespace math
{
	struct vec3
	{
		float x, y, z;
	};

	struct vec2
	{
		float x, y;
	};

	inline uintptr_t resolve_address(std::vector<uintptr_t> offsets, uintptr_t base_address)
	{
		uintptr_t address = base_address;
		for (int i = 0; i < offsets.size(); i++)
		{
			address = *(uintptr_t*)(address + offsets[i]);
		}
		return address;
	}

	
}

