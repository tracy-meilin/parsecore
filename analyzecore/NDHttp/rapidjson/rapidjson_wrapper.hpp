#pragma once

#include <string>
#include "rapidjson/document.h"
#include "rapidjson/pointer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"

namespace rjwrapper
{
	using namespace rapidjson;

#pragma region string
	template <typename GenValue>
	std::basic_string<typename GenValue::Ch> GetStringByKey(const GenValue& rv, const std::basic_string<typename GenValue::Ch>& key, const std::basic_string<typename GenValue::Ch>& def = std::basic_string<typename GenValue::Ch>())
	{
		if (rv.IsObject())
		{
			GenValue::ConstMemberIterator it = rv.FindMember(key);
			if (it != rv.MemberEnd() && it->value.IsString())
			{
				return std::basic_string<typename GenValue::Ch >(it->value.GetString(), it->value.GetStringLength());
			}
		}

		return def;
	}

	template <typename GenValue>
	std::basic_string<typename GenValue::Ch> GetStringByPointer(const GenValue& rv, const std::basic_string<typename GenValue::Ch>& path, const std::basic_string<typename GenValue::Ch>& def = std::basic_string<typename GenValue::Ch>())
	{
		GenericPointer<GenValue::ValueType> point(path);
		if (point.IsValid())
		{
			const GenValue::ValueType* valuePath = point.Get(rv);
			if (valuePath && valuePath->IsString())
			{
				return std::basic_string<typename GenValue::Ch >(valuePath->GetString(), valuePath->GetStringLength());
			}
		}

		return def;
	}

	template <typename GenValue>
	std::basic_string<typename GenValue::Ch> GetString(const GenValue& rv, const std::basic_string<typename GenValue::Ch>& def = std::basic_string<typename GenValue::Ch>())
	{
		if (rv.IsString())
		{
			return std::basic_string<typename GenValue::Ch >(rv.GetString(), rv.GetStringLength());
		}

		return def;
	}

#pragma endregion string

#pragma region bool
	template <typename GenValue>
	bool GetBooleanByKey(const GenValue& rv, const std::basic_string<typename GenValue::Ch>& key, bool def = false)
	{
		bool result = def;
		if (rv.IsObject())
		{
			GenValue::ConstMemberIterator it = rv.FindMember(key);
			if (it != rv.MemberEnd() && it->value.IsBool())
			{
				result = it->value.GetBool();
			}
		}

		return result;
	}

	template <typename GenValue>
	bool GetBooleanByPointer(const GenValue& rv, const std::basic_string<typename GenValue::Ch>& path, bool def = false)
	{
		bool result = def;
		GenericPointer<GenValue::ValueType> point(path);
		if (point.IsValid())
		{
			const GenValue::ValueType* valuePath = point.Get(rv);
			if (valuePath && valuePath->IsBool())
			{
				result = valuePath->GetBool();
			}
		}

		return result;
	}

	template <typename GenValue>
	bool GetBoolean(const GenValue& rv, bool def = false)
	{
		bool result = def;
		if (rv.IsBool())
		{
			result = rv.GetBool();
		}

		return result;
	}

#pragma endregion bool

#pragma region int
	template <typename GenValue>
	int GetIntByKey(const GenValue& rv, const std::basic_string<typename GenValue::Ch>& key, int def = 0)
	{
		int result = def;
		if (rv.IsObject())
		{
			GenValue::ConstMemberIterator it = rv.FindMember(key);
			if (it != rv.MemberEnd() && it->value.IsInt())
			{
				result = it->value.GetInt();
			}
		}

		return result;
	}

	template <typename GenValue>
	int GetIntByPointer(const GenValue& rv, const std::basic_string<typename GenValue::Ch>& path, int def = 0)
	{
		int result = def;
		GenericPointer<GenValue::ValueType> point(path);
		if (point.IsValid())
		{
			const GenValue::ValueType* valuePath = point.Get(rv);
			if (valuePath && valuePath->IsInt())
			{
				result = valuePath->GetInt();
			}
		}

		return result;
	}

	template <typename GenValue>
	int GetInt(const GenValue& rv, int def = 0)
	{
		int result = def;
		if (rv.IsInt())
		{
			result = rv.GetInt();
		}

		return result;
	}

#pragma endregion int

#pragma region uint
	template <typename GenValue>
	unsigned GetUintByKey(const GenValue& rv, const std::basic_string<typename GenValue::Ch>& key, unsigned def = 0)
	{
		unsigned result = def;
		if (rv.IsObject())
		{
			GenValue::ConstMemberIterator it = rv.FindMember(key);
			if (it != rv.MemberEnd() && it->value.IsUint())
			{
				result = it->value.GetUint();
			}
		}

		return result;
	}

	template <typename GenValue>
	unsigned GetUintByPointer(const GenValue& rv, const std::basic_string<typename GenValue::Ch>& path, unsigned def = 0)
	{
		unsigned result = def;
		GenericPointer<GenValue::ValueType> point(path);
		if (point.IsValid())
		{
			const GenValue::ValueType* valuePath = point.Get(rv);
			if (valuePath && valuePath->IsUint())
			{
				result = valuePath->GetUint();
			}
		}

		return result;
	}

	template <typename GenValue>
	unsigned GetUint(const GenValue& rv, unsigned def = 0)
	{
		unsigned result = def;
		if (rv.IsUint())
		{
			result = rv.GetUint();
		}

		return result;
	}

#pragma endregion uint

#pragma region int64
	template <typename GenValue>
	int64_t GetInt64ByKey(const GenValue& rv, const std::basic_string<typename GenValue::Ch>& key, int64_t def = 0)
	{
		int64_t result = def;
		GenValue::ConstMemberIterator it = rv.FindMember(key);
		if (it != rv.MemberEnd() && it->value.IsInt64())
		{
			result = it->value.GetInt64();
		}

		return result;
	}

	template <typename GenValue>
	int64_t GetInt64ByPointer(const GenValue& rv, const std::basic_string<typename GenValue::Ch>& path, int64_t def = 0)
	{
		int64_t result = def;
		GenericPointer<GenValue::ValueType> point(path);
		if (point.IsValid())
		{
			const GenValue::ValueType* valuePath = point.Get(rv);
			if (valuePath && valuePath->IsInt64())
			{
				result = valuePath->GetInt64();
			}
		}

		return result;
	}

	template <typename GenValue>
	int64_t GetInt64(const GenValue& rv, int64_t def = 0)
	{
		int64_t result = def;
		if (rv.IsInt64())
		{
			result = rv.GetInt64();
		}

		return result;
	}

#pragma endregion int64

#pragma region uint64
	template <typename GenValue>
	uint64_t GetUint64ByKey(const GenValue& rv, const std::basic_string<typename GenValue::Ch>& key, uint64_t def = 0)
	{
		uint64_t result = def;
		if (rv.IsObject())
		{
			GenValue::ConstMemberIterator it = rv.FindMember(key);
			if (it != rv.MemberEnd() && it->value.IsUint64())
			{
				result = it->value.GetUint64();
			}
		}

		return result;
	}

	template <typename GenValue>
	uint64_t GetUint64ByPointer(const GenValue& rv, const std::basic_string<typename GenValue::Ch>& path, uint64_t def = 0)
	{
		uint64_t result = def;
		GenericPointer<GenValue::ValueType> point(path);
		if (point.IsValid())
		{
			const GenValue::ValueType* valuePath = point.Get(rv);
			if (valuePath && valuePath->IsUint64())
			{
				result = valuePath->GetUint64();
			}
		}

		return result;
	}

	template <typename GenValue>
	uint64_t GetUint64(const GenValue& rv, uint64_t def = 0)
	{
		uint64_t result = def;
		if (rv.IsUint64())
		{
			result = rv.GetUint64();
		}

		return result;
	}

#pragma endregion uint64

#pragma region double
	template <typename GenValue>
	double GetDoubleByKey(const GenValue& rv, const std::basic_string<typename GenValue::Ch>& key, double def = 0)
	{
		double result = def;
		if (rv.IsObject())
		{
			GenValue::ConstMemberIterator it = rv.FindMember(key);
			if (it != rv.MemberEnd() && it->value.IsDouble())
			{
				result = it->value.GetDouble();
			}
		}

		return result;
	}

	template <typename GenValue>
	double GetDoubleByPointer(const GenValue& rv, const std::basic_string<typename GenValue::Ch>& path, double def = 0)
	{
		double result = def;
		GenericPointer<GenValue::ValueType> point(path);
		if (point.IsValid())
		{
			const GenValue::ValueType* valuePath = point.Get(rv);
			if (valuePath && valuePath->IsDouble())
			{
				result = valuePath->GetDouble();
			}
		}

		return result;
	}

	template <typename GenValue>
	double GetDouble(const GenValue& rv, double def = 0)
	{
		double result = def;
		if (rv.IsDouble())
		{
			result = rv.GetDouble();
		}

		return result;
	}

#pragma endregion double

#pragma region object
	//只支持读取对象
	template <typename GenValue>
	typename GenValue::ConstObject GetObjectByKey(const GenValue& rv, const std::basic_string<typename GenValue::Ch>& key)
	{
		if (rv.IsObject())
		{
			GenValue::ConstMemberIterator it = rv.FindMember(key);
			if (it != rv.MemberEnd() && it->value.IsObject())
			{
				return it->value.GetObject();
			}
		}

		static char buffer[sizeof(GenValue::ValueType)];
		static const GenValue::ValueType* p = new (buffer) GenValue::ValueType(kObjectType);

		return p->GetObject();
	}

	//只支持读取对象
	template <typename GenValue>
	typename GenValue::ConstObject GetObjectByPointer(const GenValue& rv, const std::basic_string<typename GenValue::Ch>& path)
	{
		GenericPointer<GenValue::ValueType> point(path);
		if (point.IsValid())
		{
			const GenValue::ValueType* valuePath = point.Get(rv);
			if (valuePath && valuePath->IsObject())
			{
				return valuePath->GetObject();
			}
		}

		static char buffer[sizeof(GenValue::ValueType)];
		static const GenValue::ValueType* p = new (buffer) GenValue::ValueType(kObjectType);

		return p->GetObject();
	}

	//只支持读取对象
	template <typename GenValue>
	typename GenValue::ConstObject GetObject(const GenValue& rv)
	{
		if (rv.IsObject())
		{
			return rv.GetObject();
		}

		static char buffer[sizeof(GenValue::ValueType)];
		static const GenValue::ValueType* p = new (buffer) GenValue::ValueType(kObjectType);

		return p->GetObject();
	}

#pragma endregion object

#pragma region array
	//只支持读取数据元素
	template <typename GenValue>
	typename GenValue::ConstArray GetArrayByKey(const GenValue& rv, const std::basic_string<typename GenValue::Ch>& key)
	{
		if (rv.IsObject())
		{
			GenValue::ConstMemberIterator it = rv.FindMember(key);
			if (it != rv.MemberEnd() && it->value.IsArray())
			{
				return it->value.GetArray();
			}
		}

		static char buffer[sizeof(GenValue::ValueType)];
		static const GenValue::ValueType* p = new (buffer) GenValue::ValueType(kArrayType);

		return p->GetArray();
	}

	//只支持读取数据元素
	template <typename GenValue>
	typename GenValue::ConstArray GetArrayByPointer(const GenValue& rv, const std::basic_string<typename GenValue::Ch>& path)
	{
		GenericPointer<GenValue::ValueType> point(path);
		if (point.IsValid())
		{
			const GenValue::ValueType* valuePath = point.Get(rv);
			if (valuePath && valuePath->IsArray())
			{
				return valuePath->GetArray();
			}
		}

		static char buffer[sizeof(GenValue::ValueType)];
		static const GenValue::ValueType* p = new (buffer) GenValue::ValueType(kArrayType);

		return p->GetArray();
	}

	//只支持读取数据元素
	template <typename GenValue>
	typename GenValue::ConstArray GetArray(const GenValue& rv)
	{
		if (rv.IsArray())
		{
			return rv.GetArray();
		}

		static char buffer[sizeof(GenValue::ValueType)];
		static const GenValue::ValueType* p = new (buffer) GenValue::ValueType(kArrayType);

		return p->GetArray();
	}

#pragma endregion array
}