#pragma once
#include <nlohmann\json.hpp>

namespace null::json {
	template<typename converting_t, typename = void>
	struct converter_t {
		template<typename basic_json_t, typename value_t = converting_t>
		static void from_json(basic_json_t&& json, value_t& value) { nlohmann::from_json(std::forward<basic_json_t>(json), value); }

		template<typename basic_json_t, typename value_t = converting_t>
		static auto from_json(basic_json_t&& json) -> decltype(nlohmann::from_json(std::forward<basic_json_t>(json), nlohmann::detail::identity_tag<value_t> { })) {
			return nlohmann::from_json(std::forward<basic_json_t>(json), nlohmann::detail::identity_tag<value_t> { });
		}

		template<typename basic_json_t, typename value_t = converting_t>
		static void to_json(basic_json_t& json, value_t&& value) { nlohmann::to_json(json, std::forward<value_t>(value)); }
	};

	using json_t = nlohmann::basic_json<nlohmann::ordered_map, std::vector, std::string, bool, std::int64_t, std::uint64_t, double, std::allocator, converter_t>;
}