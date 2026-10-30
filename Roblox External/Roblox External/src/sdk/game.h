#pragma once

#include <memory>

#include <sdk/sdk.h>

// Namespace roblox
namespace roblox
{
	
	// Game class
	class game_t
	{
	public:
		instance_t datamodel();
		instance_t visual_engine();
	};

}

// Unique pointer to game
inline std::unique_ptr<roblox::game_t> game = std::make_unique<roblox::game_t>();