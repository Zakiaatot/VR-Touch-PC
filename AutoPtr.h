#ifndef _AUTO_PTR_H_
#define _AUTO_PTR_H_

template <typename T>
class AutoPtr
{
public:
	AutoPtr(T* p = 0)
		: rawPtr_(p)
	{
	}

	AutoPtr(AutoPtr<T>& other)
		: rawPtr_(other.Release())
	{
	}

	~AutoPtr()
	{
		delete rawPtr_;
	}

	T* Release()
	{
		T* p = rawPtr_;
		rawPtr_ = 0;
		return p;
	}

	void Reset(T* ptr = 0)
	{
		if (rawPtr_ != ptr)
		{
			delete rawPtr_;
		}
		rawPtr_ = ptr;
	}

	T* Get() const
	{
		return rawPtr_;
	}

	AutoPtr<T>& operator=(AutoPtr<T>&& other)
	{
		Reset(other.Release());
		return *this;
	}

	AutoPtr<T>& operator=(AutoPtr<T>& other)
	{
		Reset(other.Release());
		return *this;
	}

	T& operator*() const
	{
		return *Get();
	}

	T* operator->() const
	{
		return Get();
	}

private:
	T* rawPtr_;
};

template <typename T>
class AutoPtrArray
{
public:
	AutoPtrArray(T* p = 0)
		: rawPtr_(p)
	{
	}

	AutoPtrArray(AutoPtrArray<T>& other)
		: rawPtr_(other.Release())
	{
	}

	~AutoPtrArray()
	{
		delete[] rawPtr_;
	}

	T* Release()
	{
		T* p = rawPtr_;
		rawPtr_ = 0;
		return p;
	}

	void Reset(T* ptr = 0)
	{
		if (rawPtr_ != ptr)
		{
			delete[] rawPtr_;
		}
		rawPtr_ = ptr;
	}

	T* Get() const
	{
		return rawPtr_;
	}

	AutoPtrArray<T>& operator=(AutoPtrArray<T>&& other)
	{
		Reset(other.Release());
		return *this;
	}

	AutoPtrArray<T>& operator=(AutoPtrArray<T>& other)
	{
		Reset(other.Release());
		return *this;
	}

	T& operator*() const
	{
		return *Get();
	}

	T* operator->() const
	{
		return Get();
	}

private:
	T* rawPtr_;
};

#endif //!_AUTO_PTR_H_