#include <ascend/Factory.h>
#include <ranges>

using ascend::Factory;

auto Factory::create(std::string_view x, QObject& parent) -> QObject*
{
	auto creator = this->findCreator(x);

	if(creator != nullptr)
	{
		return creator->create(parent);
	}

	return nullptr;
}

auto Factory::create(std::string_view x) -> std::unique_ptr<QObject>
{
	auto creator = this->findCreator(x);

	if(creator != nullptr)
	{
		return creator->create();
	}

	return nullptr;
}

auto Factory::findCreator(std::string_view x) const -> CreatorBase*
{
	const auto foundIt = this->map.find(x);

	if(foundIt != std::end(this->map))
	{
		return foundIt->second.get();
	}

	return nullptr;
}
