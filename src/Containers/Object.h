#pragma once
typedef unsigned char Byte;
typedef int Int;
typedef unsigned int Uint;
typedef double Double;
typedef void* LPVoid;
typedef unsigned char* LPByte;
typedef char* LPChar;
typedef const char* LPCChar;

template <typename ... Tx>
using LPActionTxA = void(*)(Tx ...);
template <typename Tout, typename ... Tx>
using LPFunctionTxA = Tout(*)(Tx ...);
template <typename ... Tx>
using LPPredicateTxA = bool(*)(Tx ...);
typedef class OBJECT_t
{
	union
	{
		Byte uByte;
		Int uInt;
		Uint uUint;
		Double uDouble;
		LPVoid uPtr;
		LPCChar uCcharPtr;
		LPChar uCharPtr;
	};

	enum TYPE_e
	{
		eNullobj = 0,
		eByte,
		eInt,
		eUint,
		eDouble,
		eLPVoid,
		eLPCChar,
		eLPChar
	};

	typedef enum class eTYPEID : char {
		objNULL = 0,
		objCHAR = 1,
		objBYTE = 2,
		objSHORT = 3,
		objINT = 4,
		objUINT = 5,
		objFLOAT = 6,
		objDOUBLE = 7,
		objHANDLE = 8,
		objCCHAR = 9,
		objPCHAR = 10,
		objUNDEFINED = 255
	};


public:
	Byte type;
	bool valid;

	inline OBJECT_t()
	{
		*this = 0;
		this->type = 0;
		this->valid = false;
	}

	inline bool IsEquals(OBJECT_t other)
	{
		if (this->type == other.type)
		{
			switch (this->type)
			{
			case eByte: return (Byte)*this == (Byte)other;
			case eInt: return (Int)*this == (Int)other;
			case eUint: return (Uint)*this == (Uint)other;
			case eDouble: return (Double)*this == (Double)other;
			case eLPVoid: return (LPVoid)*this == (LPVoid)other;
			case eLPCChar: return (LPCChar)*this == (LPCChar)other;
			case eLPChar: return (LPChar)*this == (LPChar)other;
			}
		}
		return false;
	}
	// Implicit type casts
	// * * *
	// ReSharper disable CppNonExplicitConvertingConstructor
	// ReSharper disable CppNonExplicitConversionOperator

	// * * *
	inline OBJECT_t(const int v) : uInt(v), type(eInt), valid(true) { }
	inline operator int() const { return uInt; }


	bool IsValid() const
	{
		return valid;
	}

	OBJECT_t& operator=(const OBJECT_t obj)
	{
		switch (obj.type)
		{
		case eByte: return *this = static_cast<Byte>(obj);
		case eInt: return *this = static_cast<Int>(obj);
		case eUint: return *this = static_cast<Uint>(obj);
		case eDouble: return *this = static_cast<Double>(obj);
		case eLPVoid: return *this = static_cast<LPVoid>(obj);
		case eLPCChar: return *this = static_cast<LPCChar>(obj);
		case eLPChar: return *this = static_cast<LPChar>(obj);
		}
		return *this;
	}

	OBJECT_t& operator=(const Byte v)
	{
		this->uByte = v;
		this->type = eByte;
		this->valid = true;
		return *this;
	}

	OBJECT_t& operator=(const Int v)
	{
		this->uInt = v;
		this->type = eInt;
		this->valid = true;
		return *this;
	}

	OBJECT_t& operator=(const Uint v)
	{
		this->uUint = v;
		this->type = eUint;
		this->valid = true;
		return *this;
	}

	OBJECT_t& operator=(const Double v)
	{
		this->uDouble = v;
		this->type = eDouble;
		this->valid = true;
		return *this;
	}

	OBJECT_t& operator=(const LPVoid v)
	{
		this->uPtr = v;
		this->type = eLPVoid;
		this->valid = true;
		return *this;
	}
	OBJECT_t& operator=(const LPChar v)
	{
		this->uCharPtr = v;
		this->type = eLPChar;
		this->valid = true;
		return *this;
	}
	OBJECT_t& operator=(const LPCChar v)
	{
		this->uCcharPtr = v;
		this->type = eLPCChar;
		this->valid = true;
		return *this;
	}



	OBJECT_t(const Byte v) : uByte(v), type(eByte), valid(true) { }             // NOLINT(cppcoreguidelines-pro-type-member-init)
	operator Byte() const { return uByte; }
	//
	// * * * * *
	//
	//OBJECT_t::OBJECT_t(const int v) : uInt(v), type(eInt), valid(true) { }                // NOLINT(cppcoreguidelines-pro-type-member-init)
	//OBJECT_t::operator int() const { return uInt; }
	//
	// * * * * *
	//
	OBJECT_t(const Uint v) : uUint(v), type(eUint), valid(true) { }             // NOLINT(cppcoreguidelines-pro-type-member-init)
	operator Uint() const { return uUint; }
	//
	// * * * * *
	//
	OBJECT_t(const Double v) : uDouble(v), type(eDouble), valid(true) { }       // NOLINT(cppcoreguidelines-pro-type-member-init)
	operator Double() const { return uDouble; }
	//
	// * * * * *
	//
	OBJECT_t(LPVoid v) : uPtr(v), type(eLPVoid), valid(true) { }                // NOLINT(cppcoreguidelines-pro-type-member-init)
	operator LPVoid () const { return uPtr; }
	//
	// * * * * *
	//
	OBJECT_t(LPChar v) : uCharPtr(v), type(eLPChar), valid(true) { }            // NOLINT(cppcoreguidelines-pro-type-member-init)
	operator LPChar () const { return uCharPtr; }
	////
	//// * * * * *
	////
	OBJECT_t(LPCChar v) : uCcharPtr(v), type(eLPCChar), valid(true) { }         // NOLINT(cppcoreguidelines-pro-type-member-init)
	operator LPCChar () const { return uCcharPtr; }

	// * * *
	template<typename T>
	operator T& () { return *((T*)uPtr); }
	//template<typename T> inline operator T* () { return (T*)_ptr; }
	// * * *
	// ReSharper restore CppNonExplicitConvertingConstructor
	// ReSharper restore CppNonExplicitConversionOperator
}Object;

