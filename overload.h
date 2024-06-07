#pragma once
namespace Yc
{
	namespace detail
	{
		template<class T>
		struct overload_helper;
		template<class R, class...Args>
		struct overload_helper<R(Args...)>
		{
			R(*ptr)(Args...);
			R operator()(std::conditional_t<std::is_lvalue_reference_v<Args>, Args&, std::conditional_t<std::is_rvalue_reference_v<Args>, Args&&, const Args&>>... args)
			{
				return ptr(std::forward<std::conditional_t<std::is_lvalue_reference_v<Args>, Args&, std::conditional_t<std::is_rvalue_reference_v<Args>, Args&&, const Args&>>>(args)...);
			}
		};
		template<class R, class...Args>
		struct overload_helper<R(Args......)>
		{
			R(*ptr)(Args......);
			template<class...Ex>
			R operator()(std::conditional_t<std::is_lvalue_reference_v<Args>, Args&, std::conditional_t<std::is_rvalue_reference_v<Args>, Args&&, const Args&>>... args, Ex&&... ex)
			{
				return ptr(std::forward<std::conditional_t<std::is_lvalue_reference_v<Args>, Args&, std::conditional_t<std::is_rvalue_reference_v<Args>, Args&&, const Args&>>>(args)..., std::forward<Ex>(ex)...);
			}
		};
		template<class T>
		struct overload_chooser
		{
			using type = T;
		};
		template<class R, class...Args>
		struct overload_chooser<R(Args...)>
		{
			using type = overload_helper<R(Args...)>;
		};
		template<class R, class...Args>
		struct overload_chooser<R(Args......)>
		{
			using type = overload_helper<R(Args......)>;
		};
		template<class R, class...Args>
		struct overload_chooser<R(*)(Args...)>
		{
			using type = overload_helper<R(Args...)>;
		};
		template<class R, class...Args>
		struct overload_chooser<R(*)(Args......)>
		{
			using type = overload_helper<R(Args......)>;
		};
		template<class T>
		using overload_chooser_t = overload_chooser<T>::type;

	}
 
template<class...Args>
struct overload :detail::overload_chooser_t<Args>...
{
	using detail::overload_chooser_t<Args>:: operator() ...;
	overload(const Args&...args) :detail::overload_chooser_t<Args>{ args }...
	{
	}
};
template<class...Args>
overload(Args...) -> overload<Args...>;
}
