#pragma once
namespace MI {

/*A type that can be used to replace if/else logic with the procedure of using
* a custom parametric equation to map from parameter values to the appropriate function.
* 
* Example. (consider MethodN functions to be defined with signature "void MethodN (char)") you could do:
* 	LookupTable<4, void (*) char> lookup(Method1, Method2, Method3, Method4);
*	char c = 'a'
*	lookup[c/32](c);
* Which would call Method4, passing it the character c. (This is because lowercase
*	 letters fall in the range where c/32 is exactly 3, the index of the 4th element)
*/
template <int TOTAL, typename ElmT>
struct LookupTable {
	ElmT arr[TOTAL];
	
	//Construct an array from the given CSVs
	template< typename ... ElmTs >
	constexpr LookupTable(ElmTs ... items);
	
	constexpr void Set(int index, ElmT item);
	
	//Get the function from a transform on the argument.
	ElmT operator[](int);
private:
	template<int index, typename ...Args>
	constexpr void Initialize(ElmT e1, Args... rest);
	
	/*template<int index, typename ...Args>
	constexpr void InitializeExpand(ElmT f, Args... fs);*/
};


template <int TOTAL, typename FuncT>
template<int index, typename ...Args>
constexpr void LookupTable<TOTAL, FuncT>::Initialize(FuncT func, Args... funcs ) {
	Set(index, func);
	if constexpr (index != TOTAL - 1) {
		Initialize<index + 1>(funcs...);
	}
}

template <int TOTAL, typename FuncT>
constexpr void LookupTable<TOTAL, FuncT>::Set(int index, FuncT func) {
	arr[index] = func;
}

template <int TOTAL, typename FuncT>
template<typename ...Funcs>
constexpr LookupTable<TOTAL, FuncT>::LookupTable(Funcs... funcs) {
	if constexpr (sizeof...(funcs) != 0) {
		LookupTable<TOTAL, FuncT>::Initialize<0>(funcs...);
	}
}

template <int TOTAL, typename FuncT>
FuncT LookupTable<TOTAL, FuncT>::operator[](int arg) {
	return arr[arg];
}



}
