#include <ascend/WriteJSON.h>
#include <gtest/gtest.h>
#include <QJsonDocument>

namespace
{
	class MyClass : public QObject
	{
		Q_OBJECT
		Q_PROPERTY(int intMember MEMBER intMember)

	public:
		using QObject::QObject;

		int intMember{};
	};
}

TEST(WriteJSON, write)
{
	QObject parent;
	new QObject(&parent);
	new MyClass(&parent);
	new QObject(&parent);
	QJsonDocument doc;
	auto json = ascend::WriteJSON(parent);
	doc.setObject(json);
	const auto jsonString = doc.toJson().toStdString();
	EXPECT_FALSE(jsonString.empty());
}

#include <WriteJSON.test.moc>
