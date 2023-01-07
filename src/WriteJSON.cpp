#include <ascend/WriteJSON.h>
#include <QJsonArray>
#include <QMetaProperty>

auto ascend::WriteJSON(const QObject& x) -> QJsonObject
{
	QJsonObject object;

	auto metaObject = x.metaObject();

	for(auto i = 0; i < metaObject->propertyCount(); i++)
	{
		const auto p = metaObject->property(i);
		object.insert(p.name(), QJsonValue::fromVariant(p.read(&x)));
	}

	QJsonArray children;

	for(auto&& child : x.children())
	{
		auto object = ascend::WriteJSON(*child);
		children.push_back(object);
	}

	object.insert("type", metaObject->className());
	object.insert("children", children);

	return object;
}
