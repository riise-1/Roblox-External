#include "sdk.h"

// Namespace roblox
namespace roblox
{

	// Name
	std::string nameable_t::get_name()
	{
		std::uint64_t name_container = memory->read<std::uint64_t>(this->address + offsets::Instance::NameContainer);
		if (!name_container)
		{
			return "Unknown";
		}

		return memory->read_string(name_container + offsets::Instance::Name);
	}

	// Classname
	std::string nameable_t::get_class_name()
	{
		std::uint64_t class_descriptor = memory->read<std::uint64_t>(this->address + offsets::Instance::ClassDescriptor);
		if (!class_descriptor)
		{
			return "Unknown";
		}

		std::uint64_t class_pointer = memory->read<std::uint64_t>(class_descriptor + offsets::Instance::ClassName);
		if (!class_pointer)
		{
			return "Unknown";
		}

		return memory->read_string(class_pointer);
	}

	// Find first child
	instance_t instance_t::find_first_child(std::string_view name)
	{
		std::uint64_t start = memory->read<std::uint64_t>(this->address + offsets::Instance::ChildrenStart);
		if (!start)
		{
			return {};
		}

		std::uint64_t end = memory->read<std::uint64_t>(start + offsets::Instance::ChildrenEnd);
		if (!end || end < start)
		{
			return {};
		}

		const auto count = (end - start) / sizeof(std::uint64_t);
		if (count > 10000)
		{
			return {};
		}

		for (auto current = start; current < end; current += sizeof(std::uint64_t))
		{
			instance_t instance = memory->read<std::uint64_t>(current);

			if (!instance.address)
			{
				continue;
			}

			if (instance.get_name() == name)
			{
				return instance;
			}
		}

		return {};
	}

	// Find first child of class
	instance_t instance_t::find_first_child_of_class(std::string_view classname)
	{
		std::uint64_t start = memory->read<std::uint64_t>(this->address + offsets::Instance::ChildrenStart);
		if (!start)
		{
			return {};
		}

		std::uint64_t end = memory->read<std::uint64_t>(start + offsets::Instance::ChildrenEnd);
		if (!end || end < start)
		{
			return {};
		}

		const auto count = (end - start) / sizeof(std::uint64_t);
		if (count > 10000)
		{
			return {};
		}

		for (auto current = start; current < end; current += sizeof(std::uint64_t))
		{
			instance_t instance = memory->read<std::uint64_t>(current);

			if (!instance.address)
			{
				continue;
			}

			if (instance.get_class_name() == classname)
			{
				return instance;
			}
		}

		return {};
	}

}