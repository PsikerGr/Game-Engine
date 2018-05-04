#pragma once
#include <unordered_map>
#include <cassert>
#include <vector>

#include "../Macro.h"

template <typename T>
class Event {};

template <typename ReturnType, typename... Args>
class ENGINE_DLL Event<ReturnType(Args...)>
{
	typedef void* InstancePtr;
	typedef ReturnType(*InternalFunction)(InstancePtr, Args...);
	typedef std::vector<std::pair<InstancePtr, InternalFunction>> Stub;

	template <ReturnType(*Function)(Args...)>
	inline static ReturnType FunctionStub(InstancePtr, Args... args)
	{
		return (Function)(args...);
	}

	template <class C, ReturnType(C::*Function)(Args...)>
	inline static ReturnType ClassMethodStub(InstancePtr instance, Args... args)
	{
		return (static_cast<C*>(instance)->*Function)(args...);
	}

public:
	Event(void)
	{
	}

	~Event()
	{
		for (std::vector<std::pair<InstancePtr, InternalFunction>>::iterator iter = m_stub.begin(); iter != m_stub.end(); iter++)
		{
			(*iter).first = nullptr;
			(*iter).second = nullptr;
		}
		m_stub.clear();
	}

	template <ReturnType(*Function)(Args...)>
	void Bind(void)
	{
		std::pair<InstancePtr, InternalFunction> t_stub;

		t_stub.first = nullptr;
		t_stub.second = &FunctionStub<Function>;
		m_stub.push_back(t_stub);
		
	}

	template <class C, ReturnType(C::*Function)(Args...)>
	void Bind(C* instance)
	{
		std::pair<InstancePtr, InternalFunction> t_stub;
		t_stub.first = instance;
		t_stub.second = &ClassMethodStub<C, Function>;
		m_stub.push_back(t_stub);
	}

	ReturnType Invoke(Args... args)
	{
		
		for (std::vector<std::pair<InstancePtr, InternalFunction>>::iterator iter = m_stub.begin(); iter != m_stub.end(); iter++)
		{			
			(*iter).second((*iter).first, args...);
		}
		
	}

private:
	Stub m_stub;
};

