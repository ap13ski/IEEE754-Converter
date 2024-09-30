#include "converter.h"

namespace NS_IEEE754
{
	const char* CONVERTER_RESULTS_STATUS_OK = "Value";
	const char* CONVERTER_RESULTS_STATUS_FAIL = "ERROR: INVALID VALUE";
	
	//===================================================	
	std::string Converter::TrimZeros(const std::string& str_input)
	{
		int i = str_input.length() - 1;
		
		while (i >= 0 && str_input[i] == '0') { i--; }
		if (i >= 0 && str_input[i] == '.') { i--; }	
		
		return str_input.substr(0, i + 1);
	}

	std::string Converter::TrimZerosScientific(const std::string& str_input)
	{	
		int pos_left, pos_right;
		int i = str_input.length() - 1;
		
		while (i >= 0 && str_input[i] != 'e' && str_input[i] != 'E'){ i--; }
		pos_right = i;
		
		i--;
		while (i >= 0 && str_input[i] == '0'){ i--; }
		pos_left = i + 1;
		
		std::stringstream str_stream;	
		
		for (int j = 0; j < pos_left; ++j) { str_stream << str_input[j]; }
		for (int j = pos_right; j < str_input.length(); ++j) { str_stream << str_input[j]; }
		
		return str_stream.str();
	}

	//=====================
	std::string Converter::GetStringValue(float value)
	{
		std::stringstream str_stream;
		str_stream << value;
		return str_stream.str();
	}

	std::string Converter::GetStringValue(double value)
	{
		std::stringstream str_stream;
		str_stream << value;
		return str_stream.str();
	}

	//=====================
	std::string Converter::GetStringValueExact(float value, uint64_t precision)
	{
		std::stringstream str_stream;
		str_stream << std::fixed << std::setprecision(precision) << value;
		return str_stream.str();
	}

	std::string Converter::GetStringValueExact(double value, uint64_t precision)
	{
		std::stringstream str_stream;
		str_stream << std::fixed << std::setprecision(precision) << value;
		return str_stream.str();
	}

	//=====================
	std::string Converter::GetStringValueExactTrimmed(const std::string& str_input)
	{
		return Converter::TrimZeros(str_input);
	}

	//=====================
	std::string Converter::GetStringValueScientific(float value, uint64_t precision)
	{
		std::stringstream str_stream;
		str_stream << std::scientific << std::setprecision(precision) << value;
		return str_stream.str();
	}

	std::string Converter::GetStringValueScientific(double value, uint64_t precision)
	{
		std::stringstream str_stream;
		str_stream << std::scientific << std::setprecision(precision) << value;
		return str_stream.str();
	}

	//=====================
	std::string Converter::GetStringValueScientificTrimmed(const std::string& str_input)
	{
		std::string str_trimmed = Converter::TrimZerosScientific(str_input);
		return str_trimmed;
	}

	//=====================
	std::string Converter::GetStringValueHex(uint32_t value)
	{
		std::stringstream str_stream;
		str_stream << std::hex << value;
		return str_stream.str();
	}

	std::string Converter::GetStringValueHex(uint64_t value)
	{
		std::stringstream str_stream;
		str_stream << std::hex << value;
		return str_stream.str();
	}

	//=====================
	std::string Converter::GetStringUpper(const std::string& str_input)
	{
		std::string str_output = str_input;
		std::transform(str_output.cbegin(), str_output.cend(), str_output.begin(), ::toupper);

		return str_output;
	}

	//=====================

	std::string Converter::GetStringValueBinary(uint32_t value, FLOAT_BITS bits)
	{
		std::stringstream str_stream;
		
		switch (bits)
		{
			case FLOAT_SIGN:
				str_stream << std::bitset<FLOAT_SIGN>(value);	
				break;
			case FLOAT_EXPONENT:
				str_stream << std::bitset<FLOAT_EXPONENT>(value);	
				break;
			case FLOAT_MANTISSA:
				str_stream << std::bitset<FLOAT_MANTISSA>(value);	
				break;
			case FLOAT_TOTAL:
				str_stream << std::bitset<FLOAT_TOTAL>(value);	
				break;
			default:
				str_stream << std::bitset<FLOAT_TOTAL>(value);
		}		
		
		return str_stream.str();
	}

	std::string Converter::GetStringValueBinarySign(uint32_t value)
	{
		return Converter::GetStringValueBinary(value, FLOAT_SIGN);
	}

	std::string Converter::GetStringValueBinaryExponent(uint32_t value)
	{
		return Converter::GetStringValueBinary(value, FLOAT_EXPONENT);
	}

	std::string Converter::GetStringValueBinaryMantissa(uint32_t value)
	{
		return Converter::GetStringValueBinary(value, FLOAT_MANTISSA);
	}

	std::string Converter::GetStringValueBinaryTotal(uint32_t value)
	{	
		return Converter::GetStringValueBinary(value, FLOAT_TOTAL);
	}

	//=====================

	std::string Converter::GetStringValueBinary(uint64_t value, DOUBLE_BITS bits)
	{
		std::stringstream str_stream;
		
		switch (bits)
		{
			case DOUBLE_SIGN:
				str_stream << std::bitset<DOUBLE_SIGN>(value);	
				break;
			case DOUBLE_EXPONENT:
				str_stream << std::bitset<DOUBLE_EXPONENT>(value);	
				break;
			case DOUBLE_MANTISSA:
				str_stream << std::bitset<DOUBLE_MANTISSA>(value);	
				break;
			case DOUBLE_TOTAL:
				str_stream << std::bitset<DOUBLE_TOTAL>(value);	
				break;
			default:
				str_stream << std::bitset<DOUBLE_TOTAL>(value);
		}	
		
		return str_stream.str();
	}

	std::string Converter::GetStringValueBinarySign(uint64_t value)
	{
		return Converter::GetStringValueBinary(value, DOUBLE_SIGN);
	}

	std::string Converter::GetStringValueBinaryExponent(uint64_t value)
	{
		return Converter::GetStringValueBinary(value, DOUBLE_EXPONENT);
	}

	std::string Converter::GetStringValueBinaryMantissa(uint64_t value)
	{
		return Converter::GetStringValueBinary(value, DOUBLE_MANTISSA);
	}

	std::string Converter::GetStringValueBinaryTotal(uint64_t value)
	{	
		return Converter::GetStringValueBinary(value, DOUBLE_TOTAL);
	}


	//=====================
	

	bool Converter::IsValidFloat(const std::string& str_input)
	{	
		float f;
		
		try {
        f = std::stof(str_input);
		} catch (const std::invalid_argument& e) {
			return false;
		} catch (const std::out_of_range& e) {
			return false;
		}
				
		std::istringstream input_str_stream(str_input);
		return (input_str_stream >> f) && input_str_stream.eof();
	}

	bool Converter::IsValidDouble(const std::string& str_input)
	{
		double d;
		
		try {
        d = std::stod(str_input);
		} catch (const std::invalid_argument& e) {
			return false;
		} catch (const std::out_of_range& e) {
			return false;
		}

		std::istringstream input_str_stream(str_input);
		return (input_str_stream >> d) && input_str_stream.eof();
	}	
	
	
	void Converter::NullifySingle()
	{
		Converter::results.valueSingleBinarySign = "";
		Converter::results.valueSingleBinaryExponent = "";
		Converter::results.valueSingleBinaryMantissa = "";
		Converter::results.valueSingleBinaryTotal = "";
		Converter::results.valueSingleHex = "";
		Converter::results.valueSingleExactTrimmed = "";
		Converter::results.valueSingleScientificTrimmed = "";
	}
	
	void Converter::NullifyDouble()
	{		
		Converter::results.valueDoubleBinarySign = "";
		Converter::results.valueDoubleBinaryExponent = "";
		Converter::results.valueDoubleBinaryMantissa = "";
		Converter::results.valueDoubleBinaryTotal = "";
		Converter::results.valueDoubleHex = "";
		Converter::results.valueDoubleExactTrimmed = "";
		Converter::results.valueDoubleScientificTrimmed = "";
	}

	//===================================================
	
	void Converter::CalculateResults(const std::string& str_value)
	{
		std::string str = str_value;
		std::replace(str.begin(), str.end(), ',', '.');
		Converter::results.value = str;
		Converter::results.status = CONVERTER_RESULTS_STATUS_OK;
		bool isFloatChecked = false;
		bool isDoubleChecked = false;
		
		FLOAT_32 float32;
		if (Converter::IsValidFloat(Converter::results.value) == true)
		{
			float32.f = std::stof(Converter::results.value);			
			Converter::results.valueSingleBinarySign = Converter::GetStringValueBinarySign(float32.bits.sign);
			Converter::results.valueSingleBinaryExponent = Converter::GetStringValueBinaryExponent(float32.bits.exponent);
			Converter::results.valueSingleBinaryMantissa = Converter::GetStringValueBinaryMantissa(float32.bits.mantissa);
			Converter::results.valueSingleBinaryTotal = Converter::GetStringValueBinaryTotal(float32.i);
			Converter::results.valueSingleHex = Converter::GetStringUpper(Converter::GetStringValueHex(float32.i));
			Converter::results.valueSingleExactTrimmed = Converter::GetStringValueExactTrimmed(Converter::GetStringValueExact(float32.f, PRECISION_FLOAT));
			Converter::results.valueSingleScientificTrimmed = Converter::GetStringValueScientificTrimmed(Converter::GetStringValueScientific(float32.f, PRECISION_FLOAT));
			isFloatChecked = true;
		}
		else
		{
			NullifySingle();
		}
		
		DOUBLE_64 double64;
		if (Converter::IsValidDouble(Converter::results.value) == true)
		{
			double64.d = std::stod(Converter::results.value);
			Converter::results.valueDoubleBinarySign = Converter::GetStringValueBinarySign(double64.bits.sign);
			Converter::results.valueDoubleBinaryExponent = Converter::GetStringValueBinaryExponent(double64.bits.exponent);
			Converter::results.valueDoubleBinaryMantissa = Converter::GetStringValueBinaryMantissa(double64.bits.mantissa);
			Converter::results.valueDoubleBinaryTotal = Converter::GetStringValueBinaryTotal(double64.i);
			Converter::results.valueDoubleHex = Converter::GetStringUpper(Converter::GetStringValueHex(double64.i));
			Converter::results.valueDoubleExactTrimmed = Converter::GetStringValueExactTrimmed(Converter::GetStringValueExact(double64.d, PRECISION_DOUBLE));
			Converter::results.valueDoubleScientificTrimmed = Converter::GetStringValueScientificTrimmed(Converter::GetStringValueScientific(double64.d, PRECISION_DOUBLE));
			isDoubleChecked = true;
		}
		else
		{
			NullifyDouble();
		}

		if (isFloatChecked == false || isDoubleChecked == false)
		{
			Converter::results.status = CONVERTER_RESULTS_STATUS_FAIL;
		}
	}
	
	//===================================================
	std::string Converter::GetStringResults(const std::string& str_info)
	{
		std::string str_result;
		str_result += "Generated by IEEE 754 Converter:\t";
		str_result += str_info;
		str_result += "\r\n";
		str_result += "Entered value:\t" + Converter::results.value + "\r\n";
		str_result += "Single-precision binary:\t" + Converter::results.valueSingleBinaryTotal + "\r\n";
		str_result += "Single-precision hexadecimal:\t" + Converter::results.valueSingleHex + "\r\n";
		str_result += "Single-precision exact value:\t" + Converter::results.valueSingleExactTrimmed + "\r\n";
		str_result += "Single-precision exact value (scientific):\t" + Converter::results.valueSingleScientificTrimmed + "\r\n";	
		
		str_result += "Double-precision binary:\t" + Converter::results.valueDoubleBinaryTotal + "\r\n";
		str_result += "Double-precision hexadecimal:\t" + Converter::results.valueDoubleHex + "\r\n";
		str_result += "Double-precision exact value:\t" + Converter::results.valueDoubleExactTrimmed + "\r\n";
		str_result += "Double-precision exact value (scientific):\t" + Converter::results.valueDoubleScientificTrimmed + "\r\n";
		
		return str_result;
	}
	
	
	
	//===================================================
}