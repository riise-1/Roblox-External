#include "game.h"

// Namespace roblox
namespace roblox
{

	// Datamodel
	instance_t game_t::datamodel()
	{
		std::uint64_t fake_datamodel = memory->read<std::uint64_t>(memory->get_module_address() + offsets::FakeDataModel::Pointer);
		if (!fake_datamodel)
		{
			return {};
		}

		return memory->read<std::uint64_t>(fake_datamodel + offsets::FakeDataModel::RealDataModel);
	}

	// Visual engine 
	instance_t game_t::visual_engine()
	{
		return memory->read<std::uint64_t>(memory->get_module_address() + offsets::VisualEngine::Pointer);
	}

}