#pragma once

#include <utility>
#include <typeinfo>
#include <type_traits>

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


class PODVariant
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

	static const size_t data_size = static_max<sizeof(long long), sizeof(double), sizeof(int), sizeof(long), sizeof(bool)>::value;
	static const size_t data_align = static_max<alignof(long long), sizeof(double), sizeof(int), sizeof(long), sizeof(bool)>::value;

	using data_t = typename std::aligned_storage<data_size, data_align>::type;

	static inline size_t invalid_type() {
		return typeid(void).hash_code();
	}

	size_t type_id;
	data_t data;

public:
	PODVariant() : type_id(invalid_type()) {   }

	template<typename T>
	PODVariant(T value) : type_id(typeid(T).hash_code())
	{
		if (is_supported<T>::value)
		{
			T& real_data = reinterpret_cast<T&>(data);
			real_data = value;
		}
		else
			throw std::bad_cast();
	}

	PODVariant(const PODVariant& value) : type_id(value.type_id), data(value.data) { }

	PODVariant(PODVariant&& value) : type_id(value.type_id), data(value.data) { }

	PODVariant& operator= (PODVariant value)
	{
		type_id = value.type_id;
		data = value.data;
		return *this;
	}

	template<typename T>
	bool Is() {
		return (type_id == typeid(T).hash_code());
	}

	bool IsTrue() {
		if (type_id == typeid(bool).hash_code())
		{
			return reinterpret_cast<bool&>(data);
		}
		return type_id == typeid(double).hash_code() ?
			reinterpret_cast<double&>(data) != 0
			:
			reinterpret_cast<long&>(data) != 0;
	}

	bool Valid() {
		return (type_id != invalid_type());
	}

	long GetIntegralValue() {
		if (type_id == typeid(bool).hash_code())
		{
			return reinterpret_cast<bool&>(data) ? 1L : 0L;
		}
		return type_id == typeid(double).hash_code() ?
			(long)Get<double>() : reinterpret_cast<long&>(data);
	}

	double GetDoubleValue()
	{
		if (type_id == typeid(bool).hash_code())
		{
			return reinterpret_cast<bool&>(data) ? 1.0 : 0.0;
		}
		return type_id == typeid(double).hash_code() ?
			reinterpret_cast<double&>(data) : reinterpret_cast<long&>(data);
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
	T& Get()
	{
		// It is a dynamic_cast-like behaviour
		if (type_id == typeid(T).hash_code())
			return *reinterpret_cast<T*>(&data);
		else
			throw std::bad_cast();
	}

	~PODVariant() { }
};