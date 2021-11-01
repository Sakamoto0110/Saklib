#pragma once
#include "../Containers/Object.h"
#include "../Containers/Map.h"


using ObjectStackA = ARRAY_t<Object>;


// Generic function container interface
// Not binded to any function signature   
typedef class ICALLABLE_OBJECT_t
{
public:
	virtual Object Invoke(ObjectStackA stack) = 0;
}*LPCallableObject, ICallableObject;




//********************************
//
// FUNCTION OBJECT CONTAINER
//
//********************************

template <typename ... Tx>
class ACTION_t final : public ICALLABLE_OBJECT_t
{
public:

	ACTION_t<Tx...>() : _actionTx(nullptr) { }
	ACTION_t<Tx...>(const LPActionTxA<Tx...>& func) : _actionTx(func) { }

	Object Invoke(ObjectStackA stack) override {
		_actionTx((Tx)stack.Pop()...);
		return 0;
	}
	operator const LPActionTxA<Tx...>() { return _actionTx; }

private:
	LPActionTxA<Tx...> _actionTx;
};


template <typename Tout, typename ... Tx>
class FUNCTION_t final : public ICALLABLE_OBJECT_t
{
public:
	FUNCTION_t<Tout, Tx...>() : _functionTx(nullptr) { }
	FUNCTION_t<Tout, Tx...>(const LPFunctionTxA<Tout, Tx...>& func) : _functionTx(func) { }

	Object Invoke(ObjectStackA stack) override {
		return _functionTx((Tx)stack.Pop()...);
	}
	operator const LPFunctionTxA<Tout, Tx...>() { return _functionTx; }

private:
	LPFunctionTxA<Tout, Tx...> _functionTx;
};


template <typename ... Tx> using Action = ACTION_t<Tx...>;
template <typename ... Tx> using Function = FUNCTION_t<Tx...>;


//********************************
//
// FUNCTOR OBJECT CONTAINER
//
//********************************

typedef class FUNCTOR_t
{
protected:
	FUNCTOR_t(ICALLABLE_OBJECT_t* func) : _functorPtr(func) {}


public:

	template <typename ... Tx>
	FUNCTOR_t(const LPActionTxA<Tx...>& func) :
		_functorPtr(new ACTION_t<Tx...>(func))
	{}

	template <typename Tout, typename ... Tx>
	FUNCTOR_t(const LPFunctionTxA<Tout, Tx...>& func) :
		_functorPtr(new FUNCTION_t<Tout, Tx...>(func))
	{}


	template <typename ... Tx>
	FUNCTOR_t& operator=(const LPActionTxA<Tx...>& func) {
		return *this(func);
	}

	template <typename Tout, typename ... Tx>
	FUNCTOR_t& operator=(const LPFunctionTxA<Tout, Tx...>& func) {
		return *this(func);
	}



	operator ICALLABLE_OBJECT_t* () {
		return _functorPtr;
	}

protected:



	LPCallableObject _functorPtr;
private:

}Functor;









//********************************
//
// INVOKER OBJECT
//
//********************************

// Invoker ( base )
// Direct Invoker
// Single Invoker
// Model  Invoker




typedef class INVOKER_t : public ICALLABLE_OBJECT_t
{
protected:
	INVOKER_t(const FUNCTOR_t& functor, int flags = 0) :_flags(flags), _functor(functor) {  }
	Object Invoke(ObjectStackA stk) override {
		return ((ICALLABLE_OBJECT_t*)_functor)->Invoke(stk);

	}

	int _flags;
private:
	Functor _functor;
}InvokerBase;

typedef class DIRECT_INVOKER_t : public InvokerBase
{
public:
	DIRECT_INVOKER_t(const FUNCTOR_t& functor, int flags = 0) : INVOKER_t(functor, flags) {  }

	template<typename...Tx> Object operator()(Tx...args) {
		return Invoke(args...);
	}

protected:
	template<typename...Tx> Object Invoke(Tx...args) {
		return InvokerBase::Invoke({ args... });
	}

}DirectInvoker, Di;



typedef class SINGLE_INVOKER_t : public InvokerBase
{
public:
	SINGLE_INVOKER_t(const FUNCTOR_t& functor, int flags = 0) : INVOKER_t(functor, flags) {  }

	template<typename...Tx> void SetParams(Tx...args) {
		_SetParams({ args... });
	}

	template<typename...Tx> Object operator()(Tx...args) {
		_SetParams({ args... });
		return (*(DIRECT_INVOKER_t*)this)(args...);
	}

	Object operator()() {
		return _Invoke();
	}

private:

	Object _Invoke() {
		return InvokerBase::Invoke(_params);
	}

	void _SetParams(const ObjectStackA& stk) {
		_params = stk;
	}
	ObjectStackA _params{};
}SingleInvoker, Si;



typedef class MODEL_INVOKER_t : public SingleInvoker
{
public:
	typedef StringMap<ObjectStackA> ModelMap;
	typedef ModelMap::TKey ModelKeyT;
	typedef ModelMap::TVal ModelValueT;

	MODEL_INVOKER_t(const Functor& f, int flags = 1) : SingleInvoker(f, flags) {  }


	void AddParams(const ModelValueT& dat, ModelKeyT label) {
		(*(SINGLE_INVOKER_t*)this).SetParams(dat);
		_StringObjectListMap.SetOrInsert(label, dat);
	}

	SingleInvoker& operator[](ModelKeyT label) {
		(*(SINGLE_INVOKER_t*)this).SetParams(_StringObjectListMap[label]);
		return *this;
	}

	ARRAY_t<ModelMap::TNode>& GetModelList() {
		return _StringObjectListMap.GetNodes();
	}

	bool HaveArgsSuport() const { return _flags == 1; }

private:

	ModelMap _StringObjectListMap{};
}ModelInvoker, Mi;
















//
//
// WARNING: UPCAST WILL RESULT IN EXCEPTION!!
template<typename T> T& As(LPCallableObject);

template<>
inline InvokerBase& As(LPCallableObject obj) {
	return *(InvokerBase*)obj;
}
template<>
inline DirectInvoker& As(LPCallableObject obj) {
	return *(Di*)obj;
}
template<>
inline SingleInvoker& As(LPCallableObject obj) {
	return *(Si*)obj;
}
template<>
inline ModelInvoker& As(LPCallableObject obj) {
	return *(Mi*)obj;
}




