#include <ascend/Create.h>

auto ascend::Create(std::string_view x) -> std::unique_ptr<QObject>
{
	const auto type = QMetaType::fromName(x.data());
	const auto pointer = type.create();
	const auto object = static_cast<QObject*>(pointer);

	return std::unique_ptr<QObject>(object);
}

auto ascend::Create(std::string_view x, QObject& parent) -> QObject*
{
	const auto type = QMetaType::fromName(x.data());
	const auto pointer = type.create();
	const auto object = static_cast<QObject*>(pointer);
	object->setParent(&parent);
	return object;
}
