#pragma once

#include <QObject>
#include <ascend/export.hxx>
#include <memory>

namespace ascend
{
	ASCEND_EXPORT auto Create(std::string_view x) -> std::unique_ptr<QObject>;
	ASCEND_EXPORT auto Create(std::string_view x, QObject& parent) -> QObject*;

	template <typename T>
	auto Create(std::string_view x) -> std::unique_ptr<T>
	{
		auto object = Create(x);
		auto t = qobject_cast<T*>(object.get());

		if(t == nullptr)
		{
			return nullptr;
		}

		// Relinquish ownsership to the new unique_ptr<T>.
		object.release();
		return std::unique_ptr<T>{t};
	}

	template <typename T>
	auto Create(std::string_view x, QObject& parent) -> T*
	{
		auto object = Create(x, parent);
		auto t = qobject_cast<T*>(object);
		return t;
	}
}
