#include <ascend/Factory.h>
#include <gtest/gtest.h>

namespace
{
	class MyClass : public QObject
	{
		Q_OBJECT

	public:
		using QObject::QObject;
	};
}

TEST(Factory, register)
{
	ascend::Factory factory;

	factory.registerType<MyClass>();
	factory.deregisterType<MyClass>();
}

TEST(Factory, create)
{
	ascend::Factory factory;

	factory.registerType<MyClass>();

	auto object = factory.create("MyClass");
	EXPECT_NE(object, nullptr);

	factory.deregisterType<MyClass>();
	object = factory.create("MyClass");
	EXPECT_EQ(object, nullptr);
}

#include <Factory.test.moc>
