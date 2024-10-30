// Georgy Treshchev 2024.

#pragma once

#include <string>
#include "Misc/CString.h"
#include "Misc/EngineVersionComparison.h" // SPLICED_DIVERGENCE - Aaron.Ruiz - 2024/10/29 Handle deprecation of TIsSame since Unreal 5.2

// SPLICED_DIVERGENCE - Aaron.Ruiz - 2024/10/29 Handle deprecation of TIsSame since Unreal 5.2
template <typename FirstSameType, typename SecondSameType, typename Result>
using TEnableIfSameWithResult =
#if UE_VERSION_NEWER_THAN(5, 2, 0)
	typename TEnableIf<std::is_same<FirstSameType, SecondSameType>::value, Result>::Type;
#else
	typename TEnableIf<TIsSame<FirstSameType, SecondSameType>::Value, Result>::Type;
#endif

template <typename FirstSameType, typename SecondSameType>
using TEnableIfSame =
#if UE_VERSION_NEWER_THAN(5, 2, 0)
	typename TEnableIf<std::is_same<FirstSameType, SecondSameType>::value>::Type;
#else
	typename TEnableIf<TIsSame<FirstSameType, SecondSameType>::Value>::Type;
#endif
// SPLICED_DIVERGENCE_END

/**
 * Common functions that are used in tar operations
 */
namespace RuntimeArchiverTarOperations
{

	/**
	 * Round a number up by the specified increment
	 */
	template <typename IntegralType>
	FORCEINLINE typename TEnableIf<TIsIntegral<IntegralType>::Value, IntegralType>::Type
	RoundUp(IntegralType Number, IntegralType Increment)
	{
		return Number + (Increment - Number % Increment) % Increment;
	}

	/**
	 * Convert string containing octal number to decimal number
	 * This overload is for int32
	 */
	template <typename DecimalType, typename CharType>
	TEnableIfSameWithResult<DecimalType, int32, DecimalType> // SPLICED_DIVERGENCE - Aaron.Ruiz - 2024/10/29 Handle deprecation of TIsSame since Unreal 5.2
	OctalToDecimal(const CharType* OctalString)
	{
		return std::stoi(OctalString, 0, 8);
	}

	/**
	 * Convert string containing octal number to decimal number
	 * This overload is for int64
	 */
	template <typename DecimalType, typename CharType>
	TEnableIfSameWithResult<DecimalType, int64, DecimalType> // SPLICED_DIVERGENCE - Aaron.Ruiz - 2024/10/29 Handle deprecation of TIsSame since Unreal 5.2
	OctalToDecimal(const CharType* OctalString)
	{
		return std::stoll(OctalString, 0, 8);
	}

	/**
	 * Convert string containing octal number to decimal number
	 * This overload is for uint32
	 */
	template <typename DecimalType, typename CharType>
	TEnableIfSameWithResult<DecimalType, uint32, DecimalType> // SPLICED_DIVERGENCE - Aaron.Ruiz - 2024/10/29 Handle deprecation of TIsSame since Unreal 5.2
	OctalToDecimal(const CharType* OctalString)
	{
		return std::stoul(OctalString, 0, 8);
	}

	/**
	 * Convert decimal number to string containing octal number
	 * This overload is for int32
	 */
	template<typename DecimalType, typename CharType>
	TEnableIfSame<DecimalType, int64> // SPLICED_DIVERGENCE - Aaron.Ruiz - 2024/10/29 Handle deprecation of TIsSame since Unreal 5.2
	DecimalToOctal(DecimalType Decimal, CharType* Octal, int32 MaxLength)
	{
		TCString<CharType>::Sprintf(Octal, "%0*llo", MaxLength-1, Decimal);
	}

	/**
	 * Convert decimal number to string containing octal number
	 * This overload is for int32
	 */
	template<typename DecimalType, typename CharType>
	TEnableIfSame<DecimalType, uint32> // SPLICED_DIVERGENCE - Aaron.Ruiz - 2024/10/29 Handle deprecation of TIsSame since Unreal 5.2
	DecimalToOctal(DecimalType Decimal, CharType* Octal, int32 MaxLength)
	{
		TCString<CharType>::Sprintf(Octal, "%0*o", MaxLength-1, Decimal);
	}
}
