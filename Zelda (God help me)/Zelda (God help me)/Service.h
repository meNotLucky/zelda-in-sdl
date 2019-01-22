#pragma once

template <typename T>
class Service
{
private:
	static T* m_instance;
	Service() {};

public:
	static void Set(T* p_instance) { m_instance = p_instance; }
	static T*  Get() { return m_instance; }
};

template <typename T>
T* Service<T>::m_instance = nullptr;