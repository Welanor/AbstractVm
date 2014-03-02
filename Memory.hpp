#ifndef _MEMORY_H_
# define _MEMORY_H_

# include <list>
# include <iterator>
# include "Exception.hpp"
template <class T>
class Memory
{
public:
  Memory();
  virtual ~Memory();

  void push(T val);
  T pop();
  const size_t &size() const;
  void clear();

  typename std::list<T>::const_iterator begin() const;
  typename std::list<T>::const_iterator end() const;
private:
  std::list<T> _mem;
  size_t       _size;
};

template <typename T>
Memory<T>::Memory(): _mem(), _size(0)
{

}

template <typename T>
Memory<T>::~Memory()
{
  if (!_mem.empty())
    {
      while (!_mem.empty())
	{
	  delete _mem.front();
	  _mem.pop_front();
	}
    }
}

template <typename T>
void Memory<T>::push(T val)
{
  _mem.push_front(val);
  ++_size;
}

template <typename T>
T Memory<T>::pop()
{
  if (_mem.empty())
    throw(Exception("The Memory is empty", __FILE__ ": line " TOSTRING(__LINE__)));
  T ret;

  ret = _mem.front();
  _mem.pop_front();
  --_size;
  return (ret);
}

template <typename T>
const size_t &Memory<T>::size() const
{
  return (_size);
}

template <typename T>
void Memory<T>::clear()
{
  if (!_mem.empty())
    {
      while (!_mem.empty())
	{
	  delete _mem.front();
	  _mem.pop_front();
	}
    }
}

template <typename T>
typename std::list<T>::const_iterator Memory<T>::begin() const
{
  return (_mem.begin());
}

template <typename T>
typename std::list<T>::const_iterator Memory<T>::end() const
{
  return (_mem.end());
}

#endif /* _MEMORY_H_ */
