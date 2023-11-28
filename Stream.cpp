#include "Stream.h"

InStream::InStream(const char* const data)
	: data_(data), dataPos_(0)
{
}

InStream::~InStream()
{
}

void InStream::Reset(const char* const data)
{
	data_ = data;
	RePosition(0);
}

void InStream::RePosition(uint16_t pos)
{
	dataPos_ = pos;
}

InStream& InStream::operator>>(char* str)
{
	const char* p = data_ + dataPos_;
	while (*p != '\0' && *p != ' ')
	{
		*str++ = *p++;
		dataPos_++;
	}
	*str = '\0';
	return *this;
}

InStream& InStream::operator>>(uint8_t& num)
{
	num = *((uint8_t*)(data_ + dataPos_));
	dataPos_ += sizeof(uint8_t);
	return *this;
}

InStream& InStream::operator>>(uint16_t& num)
{
	num = *((uint16_t*)(data_ + dataPos_));
	dataPos_ += sizeof(uint16_t);
	return *this;
}

InStream& InStream::operator>>(int& num)
{
	num = *((int*)(data_ + dataPos_));
	dataPos_ += sizeof(int);
	return *this;
}

InStream& InStream::operator>>(uint32_t& num)
{
	num = *((uint32_t*)(data_ + dataPos_));
	dataPos_ += sizeof(uint32_t);
	return *this;
}

OutStream::OutStream(uint32_t dSize)
	: data_(0),
	dataSize_(0), dataPos_(0)
{
	data_ = AutoPtrArray<char>(new char[dSize] {0});
}

OutStream::~OutStream()
{
}

const char* const OutStream::Data() const
{
	return const_cast<const char* const>(data_.Get());
}

size_t OutStream::Len() const
{
	return dataSize_;
}

void OutStream::Append(const char* const data, size_t len)
{
	WriteByte(data, len);
}

void OutStream::Append(void* const data, size_t len)
{
	Append(static_cast<const char* const>(data), len);
}

void OutStream::WriteByte(const char* const data, size_t len)
{
	memcpy(data_.Get() + dataPos_, data, len);
	Skip(len);
}

void OutStream::WriteByte(void* const data, size_t len)
{
	WriteByte(static_cast<const char* const>(data), len);
}

void OutStream::Skip(size_t len)
{
	dataPos_ += len;
	if (dataPos_ > dataSize_)
		dataSize_ = dataPos_;
}

void OutStream::RePosition(size_t pos)
{
	dataPos_ = pos;
}

void OutStream::RePositionEnd()
{
	dataPos_ = dataSize_;
}

void OutStream::clear()
{
	dataPos_ = 0;
	dataSize_ = 0;
}

OutStream& OutStream::operator<<(const char* const str)
{

	Append(str, strlen(str));
	return *this;
}

OutStream& OutStream::operator<<(const uint8_t num)
{
	Append(reinterpret_cast<const char* const>(&num), sizeof(uint8_t));
	return *this;
}

OutStream& OutStream::operator<<(const uint16_t num)
{
	Append(reinterpret_cast<const char* const>(&num), sizeof(uint16_t));
	return *this;
}

OutStream& OutStream::operator<<(const int num)
{
	Append(reinterpret_cast<const char* const>(&num), sizeof(int));
	return *this;
}

OutStream& OutStream::operator<<(const uint32_t num)
{
	Append(reinterpret_cast<const char* const>(&num), sizeof(uint32_t));
	return *this;
}
