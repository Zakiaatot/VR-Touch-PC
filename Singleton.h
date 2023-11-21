#ifndef _SINGLETON_H_
#define _SINGLETON_H_

template <typename T>
class Singleton
{
public:
	static T& Instance()
	{
		static T instance;
		return instance;
	}

private:
	Singleton() {}
	~Singleton() {}
	const Singleton& operator=(const Singleton&);
	Singleton(const Singleton&);
};

#endif //!_SINGLETON_H_
