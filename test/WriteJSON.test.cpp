#include <ascend/ReadJSON.h>
#include <ascend/WriteJSON.h>
#include <gtest/gtest.h>
#include <QJsonArray>
#include <QJsonDocument>

namespace
{
	class MyClass : public QObject
	{
		Q_OBJECT
		Q_PROPERTY(int intMember MEMBER intMember)
		Q_PROPERTY(std::vector<int> intVector MEMBER intVector)

	public:
		using QObject::QObject;

		std::vector<int> intVector{5, 6, 7};
		int intMember{};
	};
}

TEST(WriteJSON, write)
{
	qRegisterMetaType<QObject>("QObject");
	qRegisterMetaType<MyClass>("MyClass");

	// auto myClass = static_cast<MyClass*>(QMetaType::fromName("MyClass").create());
	// ASSERT_NE(myClass, nullptr);

	QMetaType::registerConverter<std::vector<int>, QJsonValue>(
		[](const std::vector<int>& x)
		{
			QJsonArray array;
			for(auto&& v : x)
			{
				array.push_back(v);
			}

			return array;
		});

	QMetaType::registerConverter<QJsonValue, std::vector<int>>(
		[](const QJsonValue& x)
		{
			std::vector<int> v;

			if(x.isArray() == true)
			{
				auto array = x.toArray();

				for(auto&& i : array)
				{
					v.push_back(i.toInt());
				}
			}

			return v;
		});

	QObject parent;
	new QObject(&parent);
	new MyClass(&parent);
	new QObject(&parent);
	const auto json = ascend::WriteJSON(parent);
	const auto doc = QJsonDocument{json};
	const auto jsonString = doc.toJson().toStdString();
	EXPECT_FALSE(jsonString.empty());

	const auto obj = ascend::ReadJSON(json);
	ASSERT_NE(obj, nullptr);
	EXPECT_EQ(obj->children().size(), 3);

	auto myClass = obj->findChild<MyClass*>();
	ASSERT_NE(myClass, nullptr);

	auto v = myClass->intVector;
	EXPECT_FALSE(v.empty());

	QMetaType::unregisterMetaType(QMetaType::fromType<MyClass>());
}

#include <WriteJSON.test.moc>
