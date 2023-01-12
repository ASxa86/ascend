#include <ascend/Create.h>
#include <gtest/gtest.h>

namespace
{
	class MyClass : public QObject
	{
		Q_OBJECT

	public:
		using QObject::QObject;

		int test{5};
	};
}

TEST(Create, register)
{
	const auto type = qRegisterMetaType<MyClass>("MyClass");
	EXPECT_NE(type, 0);
	EXPECT_EQ(type, QMetaType::type("MyClass"));
	EXPECT_EQ(type, QMetaType::fromType<MyClass>().id());
	EXPECT_EQ(type, QMetaType::fromName("MyClass").id());
	QMetaType::unregisterMetaType(QMetaType::fromName("MyClass"));
}

TEST(Create, create)
{
	const auto type = qRegisterMetaType<MyClass>("MyClass");
	auto object = ascend::Create("MyClass");
	EXPECT_NE(object, nullptr);

	auto myClass = qobject_cast<MyClass*>(object.get());
	EXPECT_NE(myClass, nullptr);
	QMetaType::unregisterMetaType(QMetaType::fromType<MyClass>());
}

TEST(Create, createWithParent)
{
	const auto type = qRegisterMetaType<MyClass>("MyClass");
	QObject parent;
	auto object = ascend::Create("MyClass", parent);
	ASSERT_NE(object, nullptr);
	EXPECT_EQ(object->parent(), &parent);
	QMetaType::unregisterMetaType(QMetaType::fromType<MyClass>());
}

TEST(Create, createTemplate)
{
	const auto type = qRegisterMetaType<MyClass>("MyClass");
	auto object = ascend::Create<MyClass>("MyClass");
	EXPECT_NE(object, nullptr);
	QMetaType::unregisterMetaType(QMetaType::fromType<MyClass>());
}

TEST(Create, createTemplateWithParent)
{
	const auto type = qRegisterMetaType<MyClass>("MyClass");
	QObject parent;
	auto object = ascend::Create<MyClass>("MyClass", parent);
	ASSERT_NE(object, nullptr);
	EXPECT_EQ(object->parent(), &parent);
	QMetaType::unregisterMetaType(QMetaType::fromType<MyClass>());
}

#include <Create.test.moc>
