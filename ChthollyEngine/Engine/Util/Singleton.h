#ifndef _SINGLETON_H_
#define _SINGLETON_H_

namespace ktl
{
template<class T>
class Singleton final
{
public:
	static T& Get();
private:
	struct SingletonAutoRelease final
	{
		~SingletonAutoRelease()
		{
			delete SingletonInstance;
			SingletonInstance = nullptr;
		};	
	};
	static T* SingletonInstance;
};
}

template<class T>
T* ktl::Singleton<T>::SingletonInstance = nullptr;

template<class T>
inline T& ktl::Singleton<T>::Get()
{
	if(!SingletonInstance)
	{
		static SingletonAutoRelease GC;
		SingletonInstance = new T();
	}
	return *SingletonInstance;
}

#define SINGLETON_REGISTER(className) \
static inline className& Get() { return ktl::Singleton<className>::Get(); } \
friend class Singleton<className>;

#endif