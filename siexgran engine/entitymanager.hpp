#include"componentstorage.hpp"
#include<cassert>


/// ENTITYMANAGER 
/// @tparam CMPLIST = TypeList<CMP0, CMP1, ...>
/// @tparam TAGLIST  = TypeList<TAG0, TAG1, ...>
/// @tparam Capacity = size_t value
template<typename CMPLIST,typename TAGLIST, std::size_t Capacity = 16>
struct EntityManager {
	//Forward declaration
	struct Entity;

template<typename CMP>
	//Types and aliases
	using to_keytype = typename Slotmap<CMP,Capacity>::key_type;
	using cmp_storage_type = ComponentStorage<CMPLIST,TAGLIST>;
	/// ENTITY	
	struct Entity {
		using keytype_list = LOGIC::for_all_insert_template_t<to_keytype,CMPLIST>;
		using key_storage_type = LOGIC::replace_t<std::tuple,keytype_list>;
		
		/// ADDCOMPONENT FUNCTION
		/// @tparam CMP = Component Type 
		/// @param key = key object from slotmap
		template<typename CMP>
		void addComponent(to_keytype key) {
			cmp_mask  |= cmp_storage_type::cmpinfo::template getMask<CMP>();
			std::get<typename to_keytype<CMP>>(cmp_keys) = key;
		}

		/// @brief 
		/// @tparam CMP 
		/// @return 
		template<typename CMP>
		bool hasComponent() const noexcept {
			auto mask = cmp_storage_type::cmpinfo::template getMask<CMP>;
			return cmp_mask & mask;
		}

		template<typename TAG>
		bool hasTag() const noexcept {
			auto mask = cmp_storage_type::taginfo::template getMask<TAG>;
			return tag_mask & mask;
		}

		template<typename CMP>
		to_keytype<CMP> getComponentKey() const {
			assert(hasComponent<CMP>() && "Error: Component not found in entity");
			std::get< to_keytype<CMP> >(cmp_keys);
		}
		
	private:
		inline static std::size_t nextId{0};
		std::size_t id{nextId++};
		key_storage_type cmp_keys{};
		typename cmp_storage_type::cmpinfo::mask_type cmp_mask;
		typename cmp_storage_type::taginfo::mask_type tag_mask;
	};
	
	EntityManager(std::size_t defaultsize=100)
	{
		entities_.reserve(defaultsize);	
	}

	template<typename CMP, typename... InitTypes>
	CMP& addComponent(Entity& entity, InitTypes&&... initVals) {
		assert(!entity.template hasComponent<CMP>() && "Error: Component already exists in entity");
		auto& storage = components_.template getStorage<CMP>();
		to_keytype key = storage.push_back(CMP{std::forward<InitTypes>(initVals)...});
		entity.template addComponent<CMP>(key);
		
		
		return storage[key];
	}
	
	
	auto& createEntity() {return entities_.emplace_back();}
	
	
	

	template<typename CMP>
	CMP& getComponent(Entity& entity) {
	auto& key = entity.template getComponentKey<CMP>();
	auto& storage = components_.template getStorage<CMP>;
	return storage[];

	}

	void forall(auto&& process)
	{
		for(auto& e: entities_)
		{
			process(e);
		}
	}


	template<typename CMPS, typename TAGS>
	void foreach(auto&& process)
	{
		foreach_impl(process, CMPS{}, TAGS{});
	}

	
private:
	std::vector<Entity> entities_{};
	cmp_storage_type components_{};

	template<typename... CMPS, typename... TAGS>
	void foreach_impl(auto&& process, LOGIC::TypeList<CMPS...>,LOGIC::TypeList<TAGS...>)
	{
		for(auto& e: entities_)
		{
			auto hasCMP = (true && ... && e.template hasComponent<CMPS>);
			auto hasTAG = (true && ... && e.template hasTag<TAGS>);
			if(hasCMP && hasTAG)
			{
				process(e, getComponent<CMP>(e)...);
			}
		}
	}
};