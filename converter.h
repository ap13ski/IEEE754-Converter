#ifndef CONVERTER_H
#define CONVERTER_H
//#############################################################################


#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include <bitset>
#include <cctype>
#include <algorithm>

namespace NS_IEEE754
{
	//===================================================
	enum PRECISION
	{
		PRECISION_FLOAT = 32,
		PRECISION_DOUBLE = 300
	};

	enum FLOAT_BITS
	{
		FLOAT_SIGN = 1,
		FLOAT_EXPONENT = 8,
		FLOAT_MANTISSA = 23,
		FLOAT_TOTAL = 32
	};

	enum DOUBLE_BITS
	{
		DOUBLE_SIGN = 1,
		DOUBLE_EXPONENT = 11,
		DOUBLE_MANTISSA = 52,
		DOUBLE_TOTAL = 64
	};

	union FLOAT_32
	{
		float f;
		uint32_t i;
		
		struct {
			uint32_t mantissa : FLOAT_MANTISSA;
			uint32_t exponent : FLOAT_EXPONENT;
			uint32_t sign : 	FLOAT_SIGN;
		} bits;	
	};

	union DOUBLE_64
	{
		double d;
		uint64_t i;
		
		struct {
			uint64_t mantissa : DOUBLE_MANTISSA;
			uint64_t exponent : DOUBLE_EXPONENT;
			uint64_t sign : 	DOUBLE_SIGN;
		} bits;
	};
	
	//===================================================
	class Converter
	{
		public:
		struct
		{
			std::string value;
			std::string status;			
			
			std::string valueSingleBinarySign;
			std::string valueSingleBinaryExponent;
			std::string valueSingleBinaryMantissa;
			std::string valueSingleBinaryTotal;
			std::string valueSingleHex;
			std::string valueSingleExact;
			std::string valueSingleExactTrimmed;
			std::string valueSingleScientific;
			std::string valueSingleScientificTrimmed;
			
			std::string valueDoubleBinarySign;
			std::string valueDoubleBinaryExponent;
			std::string valueDoubleBinaryMantissa;
			std::string valueDoubleBinaryTotal;
			std::string valueDoubleHex;
			std::string valueDoubleExact;
			std::string valueDoubleExactTrimmed;
			std::string valueDoubleScientific;
			std::string valueDoubleScientificTrimmed;
			
		} results;		
		
		private:
		std::string TrimZeros(const std::string& str_input);
		std::string TrimZerosScientific(const std::string& str_input);		
		std::string GetStringValueBinary(uint32_t value, FLOAT_BITS bits);
		std::string GetStringValueBinary(uint64_t value, DOUBLE_BITS bits);
		std::string GetStringUpper(const std::string& str_input);
		std::string GetStringValue(float value);
		std::string GetStringValue(double value);
		std::string GetStringValueExact(float value, uint64_t precision);
		std::string GetStringValueExact(double value, uint64_t precision);
		std::string GetStringValueExactTrimmed(const std::string& str_input);
		std::string GetStringValueScientific(float value, uint64_t precision);
		std::string GetStringValueScientific(double value, uint64_t precision);
		std::string GetStringValueScientificTrimmed(const std::string& str_input);
		std::string GetStringValueHex(uint32_t value);
		std::string GetStringValueHex(uint64_t value);
		std::string GetStringValueBinarySign(uint32_t value);
		std::string GetStringValueBinaryExponent(uint32_t value);
		std::string GetStringValueBinaryMantissa(uint32_t value);
		std::string GetStringValueBinaryTotal(uint32_t value);
		std::string GetStringValueBinarySign(uint64_t value);
		std::string GetStringValueBinaryExponent(uint64_t value);
		std::string GetStringValueBinaryMantissa(uint64_t value);
		std::string GetStringValueBinaryTotal(uint64_t value);
		bool IsValidFloat(const std::string& str_input);
		bool IsValidDouble(const std::string& str_input);
		void NullifySingle();
		void NullifyDouble();
		
		public:
		void CalculateResults(const std::string& str_value);
		std::string GetStringResults(const std::string& str_info);
	};
	//===================================================
}


//#############################################################################
#endif