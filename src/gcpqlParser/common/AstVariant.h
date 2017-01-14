#pragma once

#include <algorithm>
#include <string>
#include <typeinfo>
#include <type_traits>
#include <utility>

template <size_t arg1, size_t ... others>
struct static_max;


template <size_t arg>
struct static_max<arg>
{
	static const size_t value = arg;
};

template <size_t arg1, size_t arg2, size_t ... others>
struct static_max<arg1, arg2, others...>
{
	static const size_t value = arg1 >= arg2 ? static_max<arg1, others...>::value :
		static_max<arg2, others...>::value;
};

// Class represents result of AST expression execution
// Doesn't take ownership and doesn't release any resources
class AstVariant
{
private:
	typedef std::integral_constant<bool, true> true_type;
	typedef std::integral_constant<bool, false> false_type;

	template<class _Ty>	struct is_supported : false_type { };

	template<> struct is_supported<double> : true_type { };
	template<> struct is_supported<bool> : true_type { };
	template<> struct is_supported<int> : true_type { };
	template<> struct is_supported<long> : true_type { };
	template<> struct is_supported<long long> : true_type { };
	template<> struct is_supported<std::string*> : true_type { };
	template<> struct is_supported<char*> : true_type { };

	static const size_t data_size = static_max<sizeof(char*), sizeof(long long), sizeof(double), sizeof(int), sizeof(long), sizeof(bool), sizeof(std::string*)>::value;
	static const size_t data_align = static_max<sizeof(char*), alignof(long long), sizeof(double), sizeof(int), sizeof(long), sizeof(bool), sizeof(std::string*)>::value;

	using data_t = typename std::aligned_storage<data_size, data_align>::type;

	static inline size_t invalid_type() {
		return typeid(void).hash_code();
	}

	size_t type_id;
	data_t data;

public:
	AstVariant() : type_id(invalid_type()) {   }

	template<typename T>
	AstVariant(T value) : type_id(typeid(T).hash_code())
	{
		if (is_supported<T>::value)
		{
			T& real_data = reinterpret_cast<T&>(data);
			real_data = value;
		}
		else
			throw std::bad_cast();
	}

	AstVariant(const AstVariant& value) : type_id(value.type_id), data(value.data) { }

	AstVariant(AstVariant&& value) : type_id(value.type_id), data(value.data) { }

	AstVariant& operator= (AstVariant value)
	{
		type_id = value.type_id;
		data = value.data;
		return *this;
	}

	template<typename T>
	bool Is() const {
		return (type_id == typeid(T).hash_code());
	}

	bool IsTrue() const {
		if (type_id == typeid(bool).hash_code())
		{
			return reinterpret_cast<const bool&>(data);
		}
		if (type_id == typeid(std::string*).hash_code())
		{
			throw std::bad_cast();
		}
		return type_id == typeid(double).hash_code() ?
			reinterpret_cast<const double&>(data) != 0
			:
			reinterpret_cast<const long&>(data) != 0;
	}

	bool IsStringType() const{
		return (type_id == typeid(char*).hash_code()
			|| type_id == typeid(std::string*).hash_code());
	}

	bool IsNumericType() const {
		return (type_id == typeid(long long).hash_code()
			|| type_id == typeid(bool).hash_code()
			|| type_id == typeid(int).hash_code()
			|| type_id == typeid(long).hash_code());
	}

	bool Equal(AstVariant& variant) const {
		if (!IsCompatible(variant)) return false;
		if (this->IsStringType() && variant.IsStringType()) {
			const char* v1 = this->AsString();
			const char* v2 = variant.AsString();
			return strcmp(v1, v2) == 0;
		}
		if (IsNumericType() && variant.IsNumericType()) {
			return AsLong() == variant.AsLong();
		}
		
		auto v1 = AsDouble();
		auto v2 = variant.AsDouble();
		return (
			v1 == v2 ||
			std::abs(v1 - v2) < std::abs(std::min(v1, v2))*std::numeric_limits<double>::epsilon());
	}

	bool IsCompatible(AstVariant& variant) const {
		if (this->IsStringType() && variant.IsStringType()) {
			return true;
		}
		return (!this->IsStringType() && !variant.IsStringType());
	}

	bool Valid() const {
		return (type_id != invalid_type());
	}

	const char* AsString() const {
		if((type_id == typeid(char*).hash_code()))
			return Get<char*>();
		if ((type_id == typeid(std::string*).hash_code()))
		{
			auto strPtr = Get<std::string*>();
			if (strPtr == nullptr) return nullptr;
			return strPtr->c_str();
		}
		return nullptr;
	}

	long AsLong() const {
		if (type_id == typeid(std::string*).hash_code()
			|| type_id == typeid(char*).hash_code())
		{
			throw std::bad_cast();
		}
		if (type_id == typeid(bool).hash_code())
		{
			return reinterpret_cast<const bool&>(data) ? 1L : 0L;
		}
		return type_id == typeid(double).hash_code() ?
			(long)Get<double>() : reinterpret_cast<const long&>(data);
	}

	double AsDouble() const
	{
		if (type_id == typeid(std::string*).hash_code()
			|| type_id == typeid(char*).hash_code())
		{
			throw std::bad_cast();
		}
		if (type_id == typeid(bool).hash_code())
		{
			return reinterpret_cast<const bool&>(data) ? 1.0 : 0.0;
		}
		return type_id == typeid(double).hash_code() ?
			reinterpret_cast<const double&>(data) : reinterpret_cast<const long&>(data);
	}

	template<typename T>
	void Set(const T& value)
	{
		if (type_id == typeid(T).hash_code()) {
			T& real_data = reinterpret_cast<T&>(data);
			real_data = value;
		}
		else
			throw std::bad_cast();
	}

	template<typename T>
	const T& Get() const
	{
		// dynamic_cast-like behaviour
		if (type_id == typeid(T).hash_code())
			return *reinterpret_cast<const T*>(&data);
		else
			throw std::bad_cast();
	}

	~AstVariant() { }
};