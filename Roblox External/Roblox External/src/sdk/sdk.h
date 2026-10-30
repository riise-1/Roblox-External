#pragma once

#include <vector>

#include <sdk/offsets/offsets.h>
#include <memory/memory.h>

namespace roblox
{

	// Addressable class
	struct addressable_t
	{
		std::uint64_t address;

		addressable_t() : address(0) {}
		addressable_t(std::uint64_t address) : address(address) {}
	};

	// Nameable class
	struct nameable_t : public addressable_t
	{
		using addressable_t::addressable_t;

		std::string get_name();
		std::string get_class_name();
	};

	// Instance class
	struct instance_t : public nameable_t
	{
		using nameable_t::nameable_t;

		template <typename T = instance_t>
		std::vector<T> get_children();

		instance_t find_first_child(std::string_view name);
		instance_t find_first_child_of_class(std::string_view classname);
	};

}

// Template for get_children
template <typename T>
std::vector<T> roblox::instance_t::get_children()
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

	std::vector<T> children;
	children.reserve(count);

	for (auto current = start; current < end; current += sizeof(std::uint64_t))
	{
		const auto address = memory->read<std::uint64_t>(current);
		if (!address)
		{
			continue;
		}

		children.emplace_back(address);
	}

	return children;
}