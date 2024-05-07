#pragma once
#include"typetraits.hpp"

template<typename List> //TYPELIST<...>
struct common_tag_cmp_traits{
	//TYPE HELPERS
	
    //MASK_TYPE
    using mask_type = select_min_mask_type<List>;
	
    //ID_TYPE
    using id_type = std::uint8_t;
    
    //	SIZE FUNCTION
    static consteval std::uint8_t size() noexcept {return List::size();}
    
    //	GETID FUNCTION
    //--------------------------------------------
    template<typename Type>
    static consteval id_type getId() noexcept {return List::pos<id_type,Type>;}
    //-----------------------------------------------------------
    //	GETMASK FUNCTION
    //-----------------------------------------------------------
    //	>>NAME:		getMask()
    //	>>INPUT:		void
    //	>>OUTPUT:		mask_type
    //-----------------------------------------------------------
    template<typename Type>
    static consteval mask_type getMask() noexcept {return 1 << getId<Type>();}
};

template<typename List>
using select_min_mask_type = 
    LOGIC::IFTYPE_t<(List::size()<=8),
    std::uint8_t, //8 types
    LOGIC::IFTYPE_t<(List::size()<=16),
    std::uint16_t, //16 types
    LOGIC::IFTYPE_t<(List::size()<=32),
    std::uint32_t, //32 types
    LOGIC::IFTYPE_t<(List::size()<=64),
    std::size_t, //64 types
    void>>>>;

template<typename TAGLIST>
struct tag_traits : common_tag_cmp_traits {};

template<typename CMPLIST>
struct cmp_traits : common_tag_cmp_traits {};