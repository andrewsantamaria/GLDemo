#ifndef SINGLETON_H
#define SINGLETON_H

template <class T>
class Singleton 
{
protected: // no creation anywhere else
	Singleton() {};
	Singleton(const Singleton<T> &) {};
	Singleton& operator=(const Singleton<T> &) {};

public:
	static T &getInstance()
	{
		static T theSingleton;
		return theSingleton;
	}
};

#endif