#include"utils/common_tags_cmps_traits.hpp"
#include"utils/slotmap.hpp"
#include<cassert>
#include<iostream>
#include<cstdio>
#include<cstdint>

template<typename CMPLIST, typename TAGLIST, std::size_t Capacity = 16>
struct ComponentStorage {

//ALIASES
	using taginfo = tag_traits<TAGLIST>;
	using cmpinfo = cmp_traits<CMPLIST>;
	template<typename Type>
	using to_slotmap = Slotmap<CMPLIST,Capacity>;
	template<typename List>
	using to_tuple = LOGIC::replace<std::tuple,List>;
	using storage_type = to_tuple<LOGIC::for_all_insert_template_t<to_slotmap,CMPLIST>>;

//SIZE FUNCTION
	constexpr auto size() { return LOGIC::TypeList<CMPLIST...>::size(); }

//STORAGE GETTER
	template<typename CMP>
	[[nodiscard]] constexpr auto& getStorage() const noexcept {
		constexpr auto id {cmpinfo::template getId<CMP>()};
		return std::get<id>(componentTuple_);
	}


private:
//COMPONENT'S TUPLE
	storage_type componentTuple_{};

	
};
