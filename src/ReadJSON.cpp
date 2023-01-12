#include <ascend/Create.h>
#include <ascend/ReadJSON.h>
#include <QJsonArray>
#include <QMetaObject>
#include <QMetaProperty>

auto ascend::ReadJSON(const QJsonObject& x) -> std::unique_ptr<QObject>
{
	const auto type = x.value("type").toString();
	const auto key = type.toStdString();
	auto object = ascend::Create(key);

	if(object == nullptr)
	{
		return nullptr;
	}

	const auto children = x.value("children").toArray();

	for(auto&& value : children)
	{
		ReadJSON(value.toObject(), *object);
	}

	return object;
}

auto ascend::ReadJSON(const QJsonObject& x, QObject& parent) -> QObject*
{
	const auto type = x.value("type");
	const auto key = type.toString().toStdString();
	auto object = ascend::Create(key, parent);

	if(object == nullptr)
	{
		return nullptr;
	}

	auto metaObject = object->metaObject();

	for(auto i = 0; i < metaObject->propertyCount(); i++)
	{
		auto property = metaObject->property(i);
		auto json = x.value(property.name());
		property.write(object, json);
	}

	const auto children = x.value("children").toArray();

	for(auto&& value : children)
	{
		ReadJSON(value.toObject(), *object);
	}

	return object;
}
