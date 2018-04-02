#include "vector.h"
#include "../ds_routines.h"
#include <cstdlib>
#include <cstring>

namespace structures {

	Vector::Vector(size_t size) :
		memory_(calloc(size, 1)),
		size_(size)
	{
	}

	Vector::Vector(const Vector& other) :
		Vector(other.size_)
	{
		
		memcpy(memory_, other.memory_, size_);
		
	}

	Vector::~Vector()
	{
		free(memory_);
		memory_ = nullptr;
	}

	Structure* Vector::clone() const
	{
		return new Vector(*this);
	}

	size_t Vector::size() const
	{
		return size_;
	}

	Structure & Vector::operator=(const Structure & other)
	{
		if (this != &other)
		{
			*this = dynamic_cast<const Vector&>(other);
		}
		return *this;
	}

	Vector& Vector::operator=(const Vector& other)
	{
		if (this != &other) {
			size_ = other.size_;
			realloc(memory_, size_);
			memcpy(memory_, other.memory_,size_);
		}
		return *this;
		
	}

	bool Vector::operator==(const Vector& other) const 
	{
		
			
		return size_ == other.size_ && (memcmp(memory_, other.memory_, size_) == 0);
		
	}

	byte& Vector::operator[](const int index) //vracia pôvodny objekt 
	{
		DSRoutines::rangeCheckExcept(index, size_ , "Invalid index"); //ci ten index je od 0 po size a ak nie vyhodi vynimku s tam tym textom
		return *(reinterpret_cast <byte *>(memory_) + index); //pretypovanie na byte lebo keby tam vlozime void tak to neni definovane 
	}

	byte Vector::operator[](const int index) const  // vrati nam kopiu objektu. keby to chcem zmenit tak to pôvodne nezmenim
	{
		DSRoutines::rangeCheckExcept(index, size_, "Invalid index");
		return *(reinterpret_cast <byte *>(memory_) + index);

		
	}

	byte& Vector::readBytes(const int index, const int count, byte& dest)
	{
		
		if (count != 0) {
			DSRoutines::rangeCheckExcept(index, size_, "Error.");
			DSRoutines::rangeCheckExcept(index + count - 1, size_, "Error.");
			DSRoutines::rangeCheckExcept(count - 1, size_, "Error.");
			byte * start = reinterpret_cast<byte *>(memory_) + index;
			byte * end = start + count - 1;
			if ((&dest >= start && &dest <= end) || (&dest + count -1 >= start && &dest + count -1 <= end)) {
				memmove(&dest, start, count);
			}
			else {
				memcpy(&dest, start, count);
			}

		}
		return dest;


	}

	void Vector::copy(const Vector& src, const int srcStartIndex, Vector& dest, const int destStartIndex, const int length)
	{
		if (length != 0) {
			DSRoutines::rangeCheckExcept(srcStartIndex, src.size_, "Invalid Source start index.");
			DSRoutines::rangeCheckExcept(srcStartIndex + length - 1, src.size_, "Invalid Source start index.");
			DSRoutines::rangeCheckExcept(destStartIndex, dest.size_, "Invalid Dest start index.");
			DSRoutines::rangeCheckExcept(destStartIndex + length - 1, dest.size_, "Invalid Dest start index.");
			DSRoutines::rangeCheckExcept(length - 1, src.size_, "Invalid length.");

			byte * src_start = reinterpret_cast<byte *>(src.memory_) + srcStartIndex;
			byte * src_end = src_start + length - 1;
			byte * dest_start = reinterpret_cast<byte *>(dest.memory_) + destStartIndex;
			byte * dest_end = dest_start + length - 1;
			
			if ((src_start >= dest_start && src_start <= dest_end) || (src_end >= dest_start && src_end <= dest_end)) {
				memmove(dest_start, src_start, length);
			} else {
				memcpy(dest_start, src_start, length);
			}
		}
		
	}

	byte* Vector::getBytePointer(const int index) const
	{
		DSRoutines::rangeCheckExcept(index, size_, "Invalid index");
		return (reinterpret_cast <byte *>(memory_) + index);
		
	}

}