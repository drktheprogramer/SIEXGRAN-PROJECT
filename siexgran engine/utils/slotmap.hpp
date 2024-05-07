#pragma once
#include<array>
#include<cstdint>
#include<stdexcept>
#include<cassert>


template<typename DataType, std::size_t Capacity, typename IndexType = std::uint32_t>
struct Slotmap 
{
	template<typename T>
	using container = 	std::array<T,Capacity>;
	using value_type = 	DataType;
	using index_type = 	IndexType;
	using gen_type = 	index_type;
	using key_type = 	struct {index_type id; gen_type gen;};
	using iterator = 	value_type*;
	using c_iterator = 	value_type const*;
	
	value_type& 		operator[](std::size_t const i) noexcept {
		assert(i<Capacity);
		return data_[i]; //return aux[i];
	}
	value_type const& 	operator[](std::size_t const i) noexcept const {
		assert(i<Capacity);
		return data_[i]; //return aux[i];
	}
    
	constexpr explicit 	Slotmap() {clear();}
	
	[[nodiscard]] constexpr std::size_t 	size() const noexcept {return size_;}
	[[nodiscard]] constexpr std::size_t 	capacity() const noexcept {return Capacity;}
	[[nodiscard]] constexpr key_type 		push_back(value_type&& newVal) noexcept {
		auto reservedid = 	allocate();
		auto& slot = 		index_[reservedid];
		//move data
		data_[slot.id]=		std::move(newVal);
		erase_[slot.id]=	reservedid;
		//user key
		auto key{slot};
		key.id=				reservedid;
		return key;
	}
	[[nodiscard]] constexpr key_type 	push_back(value_type const& newVal) noexcept{return push_back(value_type{newVal});} 
	[[nodiscard]] constexpr bool 		is_valid(key_type key) const noexcept {
		if(		key.id >= Capacity 
			||  index_[key.id].gen != key.gen) 
			return false;
		return true;
	}
	
	constexpr bool erase(key_type key) noexcept
	{
		if(!is_valid(key)) return false;
		free(key);
		
	}
	//Iterators - like stl container's iterators
	[[nodiscard]] constexpr iterator 	begin() 		noexcept {return data_.begin();}
	[[nodiscard]] constexpr iterator 	end() 			noexcept {return data_.begin()+size_;}
	[[nodiscard]] constexpr c_iterator 	cbegin() const 	noexcept {return data_.begin();}
	[[nodiscard]] constexpr c_iterator 	cend() 	const 	noexcept {return data_.begin()+size_;}
	
	constexpr void clear() {freelist_init();}
	
private:
	index_type	 					 size_{};
	index_type					  	 freelist_{};
	gen_type						 gen_{};
	container<value_type> 			 data_{};
	container<index_type>			 erase_{};
	container<key_type> 		   	 index_{};
	
	constexpr void freelist_init(){
		for(index_type i{}; i < index_.size(); ++i)
		{
			index_[i].id=i+1;
		}
		freelist_=0;
	}

	[[nodiscard]] constexpr index_type allocate() noexcept {
		if(size_>= Capacity) throw std::runtime_error("No space left in the Slotmap");
		assert(freelist_<Capacity);
		//reserve
		auto slotid = freelist_;
		freelist_ = index_[slotid].id; // freelist = first freelist
		//init slot
		auto& slot = index_[slotid];
		slot.gen = gen_;
		slot.id=size_;
		//update space and generation
		size_++;
		gen_++;
		
		return slotid;
	}
	
	constexpr void free(key_type key) noexcept {
		assert(is_valid(key));
		
		auto& slot = index_[key.id];
		auto dataid = slot.id; //id of data slot
		//update freelist
		slot.id = freelist_;
		slot.gen = gen_;
		freelist_ = key.id;
		
		if(dataid!=size_-1)
		{
			//data slot is not last, copy data from the last here
			data_[dataid]=data_[size_-1];
			erase_[dataid]=erase_[size_-1];
			index_[erase_[dataid]].id = dataid; 
		}
		//update size;
		--size_;
		++gen_;
		
	}
	
	
	
};



