//there is some "metaprogramming" methods that can be useful
#pragma once
#include<cstdint>
#include<cstddef>
void seeType(auto) {std::cout << __PRETTY_FUNCTION__ << std::endl;}
namespace LOGIC{
    //type helper
    template<typename T>
    struct _type_helper {};
       
       
	//meta-constants for any type
    template<typename T, T VAL>
    struct constant
    {
        static constexpr T value() {return VAL;};
    };
	//meta-true constant
    struct true_t : constant<bool, true> {};
    //meta-false constant
    struct false_t : constant<bool, false> {};
	
	//comparative meta-method
	template<typename T, typename U>
	struct is_same : false_t {};
	//is_same<T,U> specialition 
	template<typename T>
	struct is_same<T, T> : true_t {};
	//expression friendly
    template<typename T, typename U>
    constexpr bool is_same_v = is_same<T, U>::value;
    //meta-id give us a form to use and know the type of some typename parameter
    template<typename T>
    struct type_id {using type = T;};
        
       //If type or meta-if method and its variations
    template<bool COND,typename TRUE,typename FALSE>
    struct IFTYPE : type_id<FALSE> {};
    template<typename TRUE,typename FALSE>
    struct IFTYPE<true, TRUE, FALSE> : type_id<TRUE> {};
    template<bool COND,typename TRUE,typename FALSE>
    using IFTYPE_t = typename IFTYPE<COND,TRUE,FALSE>::type;

	//PRINT_TYPE FUNCTION
	//
	template<typename Type>
	struct print_type {static_assert(is_same_v<Type,void>);};
}


    
