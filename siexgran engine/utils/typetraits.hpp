#pragma once
#include "logic4ecs.hpp"

//typelist traits
namespace LOGIC {

	template<typename...Types>
	struct TypeList {
		//-----------------------------------------------------------
		//	SIZE FUNCTION
		//-----------------------------------------------------------
		//	>>NAME:		size()
		//	>>INPUT:		void/null
		//	>>OUTPUT:		size_t
		//-----------------------------------------------------------
	    static consteval std::size_t size() noexcept { return sizeof ... (Types); }
	
	    //MAX SIZE COMPROBATION
	    static_assert(!(size()>64),"Error: TypeList is too big, max size = 64");
	
	
	
		//-----------------------------------------------------------
		//	IS_THERE FUNCTION
		//-----------------------------------------------------------
		//	>>NAME:		is_there()
		//	>>INPUT:		void
		//	>>OUTPUT:		bool
		//-----------------------------------------------------------
	    template<typename First>
	    static consteval bool is_there() noexcept {return(false || ... || LOGIC::is_same_v<First, Types>);}
		//-----------------------------------------------------------
		//	POS FUNCTION
		//-----------------------------------------------------------
		//	>>NAME:		pos()
		//	>>INPUT:		void
		//	>>OUTPUT:		id_type
		//-----------------------------------------------------------
	    template<typename Integer_Type,typename Type>
	    static consteval Integer_Type pos() noexcept {
			static_assert(is_there<Type>(),"Error: Type not found in type list");
			return INDEX::pos_of_v<Integer_Type,Type,Types...>;
		}
	
	

	};


	//FOR_ALL_INSERT_TEMPLATE FUNCTION
	//
	template<template <typename...> class New, typename List>
	struct for_all_insert_template {};

	//PARTIAL SPECIALIZATION
	template<template <typename...> class New, typename...Types>
	struct for_all_insert_template<New,TypeList<Types...>> : LOGIC::type_id<TypeList<New<Types>...>> {};

	//HELPER
	template<template <typename...> class New, typename List>
	using for_all_insert_template_t = for_all_insert_template<New,List>::type;




	//FOR_EACH_TYPE (WIP)
	//template<template <typename...> class T, typename... Args>
	//struct for_each_type : T<Args>... {};



	//REPLACE FUNCTION
	//
	template<template <typename...> class New, typename List>
	struct replace{};

	//PARTIAL SPECIALIZATION
	template<template <typename...> class New, typename ...Types>
	struct replace<New,TypeList<Types...>> : LOGIC::type_id<New<Types...>> {};

	//HELPER
	template<template <typename...> class New, typename List>
	using replace_t = replace<New,List>;


	//FRONT
	//front marker

	template<typename List>
	struct front {};

	//partial specialization
	template<typename FRONT, typename ...REST>
	struct front<TypeList<FRONT,REST...>> : LOGIC::type_id<FRONT> {};

	//friendly sintax
	template<typename List>
	using front_t = typename front<List>::type;
	//BACK
	//back marker

	/* template<typename List>
	struct back{};

	//partial specialization
	template<typename ...REST,typename BACK> 
	struct back<TypeList<REST..., BACK> :
	LOGIC::type_id<BACK> {};

	//friendly sintax
	template<typename List>
	using back_t = typename back<List>::type;
	 *///POP FRONT
	//pop_front method

	template<typename List>
	struct pop_front  {};

	//partial specialitation
	template<typename FRONT, typename ...REST>
	struct pop_front<TypeList<FRONT,REST...>> : LOGIC::type_id<TypeList<REST...>> {};

	//friendly sintax
	template<typename List>
	using pop_front_t = typename pop_front<List>::type;
	//PUSH FRONT
	//push_front method

	template<typename TYPELIST, typename ELEMENT>
	struct push_front {};

	//partial specialitation
	template<typename ...TYPELIST, typename ELEMENT>
	struct push_front<TypeList<TYPELIST...>,ELEMENT> : LOGIC::type_id<TypeList<ELEMENT, TYPELIST...>> {};

	//friendly sintax
	template<typename TYPELIST, typename ELEMENT>
	using push_front_t = typename push_front<TYPELIST,ELEMENT>::type;

	//PUSH BACK
	//push_back method

	template<typename TYPELIST, typename ELEMENT>
	struct push_back {};

	//partial specialitation 
	template<typename ELEMENT,typename ...TYPELIST>
	struct push_back<ELEMENT,TypeList<TYPELIST...>> :
	LOGIC::type_id<TypeList<TYPELIST..., ELEMENT>> {};

	//friendly sintax
	template<typename ELEMENT, typename TYPELIST>
	using push_back_t = typename push_back<ELEMENT,TYPELIST>::type;


	//REVERSE LIST
	//reverse method
	template<typename>
	struct reverse {};

	template<typename First, typename ...Rest>
	struct reverse<TypeList<First,Rest...>> : reverse<TypeList<Rest...>>
	{using type = First;};

	/* //pop_back method

	template<typename List>
	struct pop_back {};

	//partial specialitation
	template<typename ...FIRST, typename LAST>
	struct pop_back<TypeList<FIRST..., LAST>> : LOGIC::type_id<TypeList<FIRST...>> {};

	//friendly
	template<typename List>
	using pop_back_t= typename pop_back<List>::type;
	 */
	


	

	namespace INDEX {
		//INTEGER CONSTANT
		//An integer number which is knew at compilation time
		//PARAMETERS:
		// >> idType  - typename of an integer type, like STL's an other headers
		// >> Num 	- value of integer constant

		template<typename idType,idType Num>
		using int_const_ = LOGIC::constant<idType,Num>;

		//NTH_TYPE

		//INITIAL IMPLEMENTATION
		template<typename INT_CONST, INT_CONST Num,typename... ELEMENTS>
		struct nth_type {};

		//HELPER
		//nth_type_t
		template<typename INT_CONST, INT_CONST Num, typename... ELEMENTS>
		using nth_type_t = typename nth_type<INT_CONST,Num,ELEMENTS...>::type;

		//PARTIAL IMPLEMENTATION
		//caso de fuga
		template<typename INT_CONST,typename ELEMENT, typename... ELEMENTS>
		struct nth_type<INT_CONST,INT_CONST{0},ELEMENT,ELEMENTS...> : LOGIC::type_id<ELEMENT> {};

		//PARTIAL IMPLEMENTATION
		template<typename INT_CONST,INT_CONST Num, typename ELEMENT, typename... ELEMENTS>
		struct nth_type<INT_CONST,Num,ELEMENT,ELEMENTS...> : LOGIC::type_id<typename nth_type_t<INT_CONST,Num-1,ELEMENTS...>> {};



		//POS OF

		//INITIAL IMPLEMENTATION			
		template<typename INT_CONST,typename rELEMENT,typename... ELEMENTS>
		struct pos_of {static_assert(sizeof ...(ELEMENTS) != 0,"Error: type not found in type list");};

		//HELPER
		//pos_of_v
		template<typename INT_CONST, typename rELEMENT, typename... ELEMENTS>
		static constexpr INT_CONST pos_of_v = pos_of<INT_CONST,rELEMENT,ELEMENTS...>::value;

		//PARTIAL IMPLEMENTATION
		//caso de fuga
		template<typename INT_CONST,typename rELEMENT, typename... ELEMENTS>
		struct pos_of<INT_CONST,rELEMENT,rELEMENT,ELEMENTS...> : int_const_<INT_CONST,0> {};

		//PARTIAL IMPLEMENTATION
		template<typename INT_CONST,typename rELEMENT, typename ELEMENT, typename... ELEMENTS>
		struct pos_of<INT_CONST,rELEMENT,ELEMENT,ELEMENTS...> : int_const_<INT_CONST, 1+pos_of_v<INT_CONST,rELEMENT,ELEMENTS...>> {};


		//INDEX OF

		//INITIAL IMPLEMENTATION
		template<typename,typename,typename>
		struct index_of{};

		//HELPER
		//index_of_v
		template<typename IntConst, typename Element, typename Elements>
		static constexpr IntConst index_of_v = index_of<IntConst,Element,Elements>::value;

		//PARTIAL IMPLEMENTATION
		//caso de fuga
		template<typename IntConst, typename Element, typename... Elements>
		struct index_of<IntConst,Element,TypeList<Element, Elements...>> : int_const_<IntConst,0> {};
		//PARTIAL IMPLEMENTATION
		template<typename IntConst, typename Element, typename OElement, typename ...Elements>
		struct index_of<IntConst, Element, TypeList<OElement, Elements...>> : int_const_<intConst,1+index_of<IntConst,Element,TypeList<Elements...>>::value> {};
	} 
}