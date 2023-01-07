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

	EXPECT_TRUE(factory.registerType<MyClass>());
	EXPECT_TRUE(factory.deregisterType<MyClass>());
}

TEST(Factory, create)
{
	ascend::Factory factory;

	EXPECT_TRUE(factory.registerType<MyClass>());

	auto object = factory.create("MyClass");
	EXPECT_NE(object, nullptr);
}

#include <Factory.test.moc>
