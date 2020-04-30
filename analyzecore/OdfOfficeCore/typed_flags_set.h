#pragma once
#include "types.h"
#include <type_traits>

namespace o3tl {

	namespace detail {

		template<typename T> inline SAL_CONSTEXPR
			typename std::enable_if<std::is_signed<T>::value, bool>::type isNonNegative(
			T value)
		{
			return value >= 0;
		}

		template<typename T> inline SAL_CONSTEXPR
			typename std::enable_if<std::is_unsigned<T>::value, bool>::type isNonNegative(T)
		{
			return true;
		}

	}

	template<typename T> struct typed_flags {};

	/// Mark a (scoped) enumeration as a set of bit flags, with accompanying
	/// operations.
	///
	///   template<>
	///   struct o3tl::typed_flags<TheE>: o3tl::is_typed_flags<TheE, TheM> {};
	///
	/// All relevant values must be non-negative.  (Typically, the enumeration's
	/// underlying type will either be fixed and unsigned, or it will be unfixed---
	/// and can thus default to a signed type---and all enumerators will have non-
	/// negative values.)
	///
	/// \param E the enumeration type.
	/// \param M the all-bits-set value for the bit flags.
	template<typename E, typename std::underlying_type<E>::type M>
	struct is_typed_flags {
		static_assert(
			M >= 0, "is_typed_flags expects only non-negative bit values");

		typedef E Self;

		class Wrap {
		public:
			typedef is_typed_flags Unwrapped;

			explicit SAL_CONSTEXPR Wrap(
				typename std::underlying_type<E>::type value) :
				value_(value)
			{
#if !HAVE_CXX11_CONSTEXPR || HAVE_CXX14_CONSTEXPR
				assert(detail::isNonNegative(value));
				assert((value & ~M) == 0);
#endif
			}

			SAL_CONSTEXPR operator E() const { return static_cast<E>(value_); }

			explicit SAL_CONSTEXPR operator typename std::underlying_type<E>::type()
				const
			{
				return value_;
			}

			explicit SAL_CONSTEXPR operator bool() const { return value_ != 0; }

		private:
			typename std::underlying_type<E>::type value_;
		};

		static typename std::underlying_type<E>::type const mask = M;
	};

}

template<typename E>
inline SAL_CONSTEXPR typename o3tl::typed_flags<E>::Wrap operator ~(E rhs) {
#if !HAVE_CXX11_CONSTEXPR || HAVE_CXX14_CONSTEXPR
	assert(
		o3tl::detail::isNonNegative(
		static_cast<typename std::underlying_type<E>::type>(rhs)));
#endif
	return static_cast<typename o3tl::typed_flags<E>::Wrap>(
		o3tl::typed_flags<E>::mask
		& ~static_cast<typename std::underlying_type<E>::type>(rhs));
}

template<typename E>
inline SAL_CONSTEXPR typename o3tl::typed_flags<E>::Wrap operator ~(
	typename o3tl::typed_flags<E>::Wrap rhs)
{
	return static_cast<typename o3tl::typed_flags<E>::Wrap>(
		o3tl::typed_flags<E>::mask
		& ~static_cast<typename std::underlying_type<E>::type>(rhs));
}

template<typename E>
inline SAL_CONSTEXPR typename o3tl::typed_flags<E>::Wrap operator ^(
	E lhs, E rhs)
{
#if !HAVE_CXX11_CONSTEXPR || HAVE_CXX14_CONSTEXPR
	assert(
		o3tl::detail::isNonNegative(
		static_cast<typename std::underlying_type<E>::type>(lhs)));
	assert(
		o3tl::detail::isNonNegative(
		static_cast<typename std::underlying_type<E>::type>(rhs)));
#endif
	return static_cast<typename o3tl::typed_flags<E>::Wrap>(
		static_cast<typename std::underlying_type<E>::type>(lhs)
		^ static_cast<typename std::underlying_type<E>::type>(rhs));
}

template<typename E>
inline SAL_CONSTEXPR typename o3tl::typed_flags<E>::Wrap operator ^(
	E lhs, typename o3tl::typed_flags<E>::Wrap rhs)
{
#if !HAVE_CXX11_CONSTEXPR || HAVE_CXX14_CONSTEXPR
	assert(
		o3tl::detail::isNonNegative(
		static_cast<typename std::underlying_type<E>::type>(lhs)));
#endif
	return static_cast<typename o3tl::typed_flags<E>::Wrap>(
		static_cast<typename std::underlying_type<E>::type>(lhs)
		^ static_cast<typename std::underlying_type<E>::type>(rhs));
}

template<typename E>
inline SAL_CONSTEXPR typename o3tl::typed_flags<E>::Wrap operator ^(
	typename o3tl::typed_flags<E>::Wrap lhs, E rhs)
{
#if !HAVE_CXX11_CONSTEXPR || HAVE_CXX14_CONSTEXPR
	assert(
		o3tl::detail::isNonNegative(
		static_cast<typename std::underlying_type<E>::type>(rhs)));
#endif
	return static_cast<typename o3tl::typed_flags<E>::Wrap>(
		static_cast<typename std::underlying_type<E>::type>(lhs)
		^ static_cast<typename std::underlying_type<E>::type>(rhs));
}

template<typename W>
inline SAL_CONSTEXPR
typename o3tl::typed_flags<typename W::Unwrapped::Self>::Wrap operator ^(
W lhs, W rhs)
{
	return static_cast<W>(
		static_cast<
		typename std::underlying_type<typename W::Unwrapped::Self>::type>(
		lhs)
		^ static_cast<
		typename std::underlying_type<typename W::Unwrapped::Self>::type>(
		rhs));
}

template<typename E>
inline SAL_CONSTEXPR typename o3tl::typed_flags<E>::Wrap operator &(
	E lhs, E rhs)
{
#if !HAVE_CXX11_CONSTEXPR || HAVE_CXX14_CONSTEXPR
	assert(
		o3tl::detail::isNonNegative(
		static_cast<typename std::underlying_type<E>::type>(lhs)));
	assert(
		o3tl::detail::isNonNegative(
		static_cast<typename std::underlying_type<E>::type>(rhs)));
#endif
	return static_cast<typename o3tl::typed_flags<E>::Wrap>(
		static_cast<typename std::underlying_type<E>::type>(lhs)
		& static_cast<typename std::underlying_type<E>::type>(rhs));
}

template<typename E>
inline SAL_CONSTEXPR typename o3tl::typed_flags<E>::Wrap operator &(
	E lhs, typename o3tl::typed_flags<E>::Wrap rhs)
{
#if !HAVE_CXX11_CONSTEXPR || HAVE_CXX14_CONSTEXPR
	assert(
		o3tl::detail::isNonNegative(
		static_cast<typename std::underlying_type<E>::type>(lhs)));
#endif
	return static_cast<typename o3tl::typed_flags<E>::Wrap>(
		static_cast<typename std::underlying_type<E>::type>(lhs)
		& static_cast<typename std::underlying_type<E>::type>(rhs));
}

template<typename E>
inline SAL_CONSTEXPR typename o3tl::typed_flags<E>::Wrap operator &(
	typename o3tl::typed_flags<E>::Wrap lhs, E rhs)
{
#if !HAVE_CXX11_CONSTEXPR || HAVE_CXX14_CONSTEXPR
	assert(
		o3tl::detail::isNonNegative(
		static_cast<typename std::underlying_type<E>::type>(rhs)));
#endif
	return static_cast<typename o3tl::typed_flags<E>::Wrap>(
		static_cast<typename std::underlying_type<E>::type>(lhs)
		& static_cast<typename std::underlying_type<E>::type>(rhs));
}

template<typename W>
inline SAL_CONSTEXPR
typename o3tl::typed_flags<typename W::Unwrapped::Self>::Wrap operator &(
W lhs, W rhs)
{
	return static_cast<W>(
		static_cast<
		typename std::underlying_type<typename W::Unwrapped::Self>::type>(
		lhs)
		& static_cast<
		typename std::underlying_type<typename W::Unwrapped::Self>::type>(
		rhs));
}

template<typename E>
inline SAL_CONSTEXPR typename o3tl::typed_flags<E>::Wrap operator |(E lhs, E rhs) {
#if !HAVE_CXX11_CONSTEXPR || HAVE_CXX14_CONSTEXPR
	assert(
		o3tl::detail::isNonNegative(
		static_cast<typename std::underlying_type<E>::type>(lhs)));
	assert(
		o3tl::detail::isNonNegative(
		static_cast<typename std::underlying_type<E>::type>(rhs)));
#endif
	return static_cast<typename o3tl::typed_flags<E>::Wrap>(
		static_cast<typename std::underlying_type<E>::type>(lhs)
		| static_cast<typename std::underlying_type<E>::type>(rhs));
}

template<typename E>
inline SAL_CONSTEXPR typename o3tl::typed_flags<E>::Wrap operator |(
	E lhs, typename o3tl::typed_flags<E>::Wrap rhs)
{
#if !HAVE_CXX11_CONSTEXPR || HAVE_CXX14_CONSTEXPR
	assert(
		o3tl::detail::isNonNegative(
		static_cast<typename std::underlying_type<E>::type>(lhs)));
#endif
	return static_cast<typename o3tl::typed_flags<E>::Wrap>(
		static_cast<typename std::underlying_type<E>::type>(lhs)
		| static_cast<typename std::underlying_type<E>::type>(rhs));
}

template<typename E>
inline SAL_CONSTEXPR typename o3tl::typed_flags<E>::Wrap operator |(
	typename o3tl::typed_flags<E>::Wrap lhs, E rhs)
{
#if !HAVE_CXX11_CONSTEXPR || HAVE_CXX14_CONSTEXPR
	assert(
		o3tl::detail::isNonNegative(
		static_cast<typename std::underlying_type<E>::type>(rhs)));
#endif
	return static_cast<typename o3tl::typed_flags<E>::Wrap>(
		static_cast<typename std::underlying_type<E>::type>(lhs)
		| static_cast<typename std::underlying_type<E>::type>(rhs));
}

template<typename W>
inline SAL_CONSTEXPR typename o3tl::typed_flags<typename W::Unwrapped::Self>::Wrap operator |(
	W lhs, W rhs)
{
	return static_cast<W>(
		static_cast<
		typename std::underlying_type<typename W::Unwrapped::Self>::type>(
		lhs)
		| static_cast<
		typename std::underlying_type<typename W::Unwrapped::Self>::type>(
		rhs));
}

template<typename E>
inline typename o3tl::typed_flags<E>::Self operator &=(E & lhs, E rhs) {
	assert(
		o3tl::detail::isNonNegative(
		static_cast<typename std::underlying_type<E>::type>(lhs)));
	assert(
		o3tl::detail::isNonNegative(
		static_cast<typename std::underlying_type<E>::type>(rhs)));
	lhs = lhs & rhs;
	return lhs;
}

template<typename E>
inline typename o3tl::typed_flags<E>::Self operator &=(
	E & lhs, typename o3tl::typed_flags<E>::Wrap rhs)
{
	assert(
		o3tl::detail::isNonNegative(
		static_cast<typename std::underlying_type<E>::type>(lhs)));
	lhs = lhs & rhs;
	return lhs;
}

template<typename E>
inline typename o3tl::typed_flags<E>::Self operator |=(E & lhs, E rhs) {
	assert(
		o3tl::detail::isNonNegative(
		static_cast<typename std::underlying_type<E>::type>(lhs)));
	assert(
		o3tl::detail::isNonNegative(
		static_cast<typename std::underlying_type<E>::type>(rhs)));
	lhs = lhs | rhs;
	return lhs;
}

template<typename E>
inline typename o3tl::typed_flags<E>::Self operator |=(
	E & lhs, typename o3tl::typed_flags<E>::Wrap rhs)
{
	assert(
		o3tl::detail::isNonNegative(
		static_cast<typename std::underlying_type<E>::type>(lhs)));
	lhs = lhs | rhs;
	return lhs;
}

template<typename E>
inline typename o3tl::typed_flags<E>::Self operator ^=(E & lhs, E rhs) {
	assert(
		o3tl::detail::isNonNegative(
		static_cast<typename std::underlying_type<E>::type>(lhs)));
	assert(
		o3tl::detail::isNonNegative(
		static_cast<typename std::underlying_type<E>::type>(rhs)));
	lhs = lhs ^ rhs;
	return lhs;
}

template<typename E>
inline typename o3tl::typed_flags<E>::Self operator ^=(
	E & lhs, typename o3tl::typed_flags<E>::Wrap rhs)
{
	assert(
		o3tl::detail::isNonNegative(
		static_cast<typename std::underlying_type<E>::type>(lhs)));
	lhs = lhs ^ rhs;
	return lhs;
}