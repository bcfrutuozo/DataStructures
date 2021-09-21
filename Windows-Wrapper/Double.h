#pragma once

#include "ValueType.h"

#include "ValueType.h"
#include "IConvertible.h"

struct Double : public ValueType<Double, double>, public IConvertible
{
public:

	constexpr Double(double value);

	inline constexpr TypeCode GetTypeCode() const noexcept override { return TypeCode::Double; }

	Boolean ToBoolean(IFormatProvider* provider) const override;
	Char ToChar(IFormatProvider* provider) const override;
	SByte ToSByte(IFormatProvider* provider) const override;
	Byte ToByte(IFormatProvider* provider) const override;
	Int16 ToInt16(IFormatProvider* provider) const override;
	UInt16 ToUInt16(IFormatProvider* provider) const override;
	Int32 ToInt32(IFormatProvider* provider) const override;
	UInt32 ToUInt32(IFormatProvider* provider) const override;
	Int64 ToInt64(IFormatProvider* provider) const override;
	UInt64 ToUInt64(IFormatProvider* provider) const override;
	Single ToSingle(IFormatProvider* provider)const override;
	Double ToDouble(IFormatProvider* provider) const override;
	Decimal ToDecimal(IFormatProvider* provider) const override;
	DateTime ToDateTime(IFormatProvider* provider) const override;
	//String ToString(IFormatProvider provider) const override;
	Object ToType(Type conversionType, IFormatProvider* provider) const override;

	static Double MinValue() { return static_cast<double>(-1.7976931348623157E+308); }
	static Double Epsilon() { return static_cast<double>(4.9406564584124654E-324); }
	static Double MaxValue() { return static_cast<double>(1.7976931348623157E+308); }
	static Double PositiveInfinity() { return static_cast<double>(1.0) / static_cast<double>(0.0); }
	static Double NegativeInfinity() { return static_cast<double>(-1.0) / static_cast<double>(0.0); }
	static Double NaN() { return static_cast<double>(0.0) / static_cast<double>(0.0); }
};