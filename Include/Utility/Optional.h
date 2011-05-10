#pragma once
#include <assert.h>
#include <new.h>

class OptionalEmpty
{
};

template <unsigned long size>
class OptionalBase
{
protected:
	bool _valid;
	char _data[size];	//storage space for T

public:
	//default - invalid
	OptionalBase() : _valid(false) {}
	OptionalBase& operator=(const OptionalBase& t)
	{
		_valid = t._valid;
		return *this;
	}
	OptionalBase(const OptionalBase& other) : _valid(other._valid)	{	}
	const bool Valid() const 
	{
		return _valid;
	}
	bool const Invalid() const
	{
		return !_valid;
	}
};

template<class T>
class Optional : public OptionalBase<sizeof(T)>
{
public:
	//default - invalid
	Optional() {}
	Optional(const T& t) 
	{
		Construct(t);
		_valid = true;
	}

	Optional(const OptionalEmpty&) {}
	Optional& operator=(const T& t)
	{
		if(_valid)
		{
			* GetT() = t;
		}
		else
		{
			Construct(t);
			_valid = true;	//order important for exception safety
		}
    return *this;
	}
	Optional(const Optional& other)
	{
		if(other._valid)
		{
			Construct(*other);
			_valid = true;
		}
	}
	Optional& operator=(const Optional& other)
	{
		assert(! (this == &other));	//don't copy over self
		if(_valid)
		{	//first destroy our original
			_valid = false;	//for exception safety if Destroy() throws (big trouble if this happens)
			Destroy();
		}
		if(other._valid)
		{
			Construct(*other);
			_valid = true;
		}
		return *this;
	}
  const bool operator==(const Optional& other) const
	{
		if((!Valid()) && (!other.Valid()))
			return true;
		if(Valid() ^ other.Valid())
			return false;
		return ((**this) == (*other));
	}
	const bool operator<(const Optional& other) const
	{
		//equally invalid - not smaller
		if((!Valid()) && (!other.Valid()))
			return false;
		//not valid, other must be smaller
		if(!Valid())
			return true;
		//valid, other is not valid, so this is larger
		if(!other.Valid())
			return false;

		return ((**this) < (*other));
	}
	~Optional()
	{
		if(_valid)
			Destroy();
	}

	//accessors
	T const& operator*() const
	{
		assert(_valid);
		return *GetT();
	}
	T& operator*()
	{
		assert(_valid);
		return *GetT();
	}
	T const * const operator->() const
	{
		assert(_valid);
		return GetT();
	}
	T* const operator->()
	{
		assert(_valid);
		return GetT();
	}

	//clears the value of this Optional and makes it invalid once again
	void Clear()
	{
		if(_valid)
		{
			_valid = false;
			Destroy();
		}
	}
	const bool Valid() const { return _valid;}
	const bool Invalid() const { return !_valid; }

private:
	T const * const GetT() const
	{
		return reinterpret_cast<T const * const>(_data);
	}
	T * const GetT()
	{
		return reinterpret_cast<T * const>(_data);
	}
	void Construct(const T& t)
	{
		new (GetT()) T(t);
	}
	void Destroy()
	{
		GetT()->~T();
	}
};