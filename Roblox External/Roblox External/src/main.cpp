#include <iostream>
#include <thread>
#include <chrono>

#include <sdk/sdk.h>
#include <sdk/game.h>

// Main function
int main()
{
	// Process name
	const std::string BINARY_NAME = "RobloxPlayerBeta.exe";

	// Attach to roblox
	memory->find_process_id(BINARY_NAME);
	memory->attach_to_process(BINARY_NAME);

	// Find module address
	memory->find_module_address(BINARY_NAME);
	printf("Module address -> 0x%llx\n", memory->get_module_address());

	// Getting datamodel
	printf("Datamodel address -> 0x%llx\n", game->datamodel().address);

	// Getting visual engine
	printf("Visual engine address -> 0x%llx\n", game->visual_engine().address);

	// End screen
	std::cout << "Bye!" << std::endl;
	std::cin.get();
}