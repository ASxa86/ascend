#pragma once

#include <ascend/StringHash.h>
#include <QObject>
#include <ascend/export.hxx>
#include <memory>
#include <unordered_map>

namespace ascend
{
	class ASCEND_EXPORT Factory
	{
	public:
		Factory() = default;
		~Factory() = default;
		Factory(const Factory&) = delete;
		Factory(Factory&&) noexcept = default;

		auto operator=(const Factory&) -> Factory& = delete;
		auto operator=(Factory&&) noexcept -> Factory& = default;

		template <typename T>
		auto registerType(std::string_view x = {}) -> bool
		{
			if(x.empty() == true)
			{
				x = T::staticMetaObject.className();
			}

			this->map[std::string{x}] = std::make_unique<Creator<T>>();
			return true;
		}

		template <typename T>
		auto deregisterType(std::string_view x = {}) -> bool
		{
			if(x.empty() == true)
			{
				x = T::staticMetaObject.className();
			}

			const auto foundIt = this->map.find(x);
			this->map.erase(foundIt);

			return true;
		}

		auto create(std::string_view x, QObject& parent) -> QObject*;
		auto create(std::string_view x) -> std::unique_ptr<QObject>;

	private:
		struct CreatorBase
		{
			virtual ~CreatorBase() = default;

			virtual auto create(QObject& parent) -> QObject* = 0;
			virtual auto create() -> std::unique_ptr<QObject> = 0;
		};

		template <typename T>
		struct Creator final : CreatorBase
		{
			auto create(QObject& parent) -> QObject* override
			{
				return new T{&parent};
			}

			auto create() -> std::unique_ptr<QObject> override
			{
				return std::make_unique<T>();
			}
		};

		auto findCreator(std::string_view x) const -> CreatorBase*;
		std::unordered_map<std::string, std::unique_ptr<CreatorBase>, ascend::StringHash, std::equal_to<>> map;
	};
}
