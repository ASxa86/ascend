#pragma once

#include <cstddef>
#include <functional>
#include <string>

namespace ascend
{
	/// @brief This class defines a string hash definition for heterogeneous lookup within unordered containers.
	///	https://www.cppstories.com/2021/heterogeneous-access-cpp20/
	class StringHash
	{
	public:
		using is_transparent = void;

		[[nodiscard]] auto operator()(const char* x) const -> std::size_t
		{
			return std::hash<std::string_view>{}(x);
		}

		[[nodiscard]] auto operator()(std::string_view x) const -> std::size_t
		{
			return std::hash<std::string_view>{}(x);
		}

		[[nodiscard]] auto operator()(const std::string& x) const -> std::size_t
		{
			return std::hash<std::string>{}(x);
		}
	};
}
