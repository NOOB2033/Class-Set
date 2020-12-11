#include"Set.h"


Set::Set() :BoolVector(256, 0)
{
	power_ = 0;
}


Set::Set(const char* s) :BoolVector(256, 0)
{
	for (int i = 0; i < strlen(s); i++)
		set1(s[i]);
	power_ = weight();
}


Set::Set(const Set& other) :BoolVector(other)
{
	power_ = other.power_;
}


Set::~Set()
{}


std::istream& operator>>(std::istream& in, const Set& set)
{
	char symbol;
	for (; (symbol = getchar()) != '\n';) {
		int byte = symbol / set.BYTE;
		unsigned char mask = (128 >> symbol % set.BYTE);
		set.bv_[byte] |= mask;
	}
	int byte = symbol / set.BYTE; // for \ n
	unsigned char mask = (128 >> symbol % set.BYTE);
	set.bv_[byte] |= mask;
	return in;
}


std::ostream& operator<<(std::ostream& out, const Set& set)
{
	for (int i = 0, byte = 0; i < set.mem_; i++) {
		unsigned char mask = 128;
		for (int j = 0; j < set.BYTE; j++)
			if (set.bv_[i] & mask >> j)
				out << char(j + byte) << " ";
		byte += set.BYTE;
	}
	return out;
}


bool Set::find(char symbol)
{
	if (getBit(symbol))
		return true;
	return false;
}


char Set::min()
{
	for (int i = 0; i < len_; i++)
		if (getBit(i))
			return (char)i;
	std::cout << "Min not found";
}


char Set::max()
{
	for (int i = len_ - 1; i >= 0; i--)
		if (getBit(i))
			return (char)i;
	std::cout << "Max not found";
}


int Set::getPower()
{
	return power_;
}


bool Set::operator==(const Set& other)
{
	for (int i = 0; i < mem_; i++)
		if (bv_[i] != other.bv_[i])
			return false;
	return true;
}


bool Set::operator!=(const Set& other)
{
	for (int i = 0; i < mem_; i++)
		if (bv_[i] != other.bv_[i])
			return true;
	return false;
}


Set Set::operator~()
{
	Set set(*this);
	for (int i = 0; i < mem_; i++)
		set.bv_[i] = ~set.bv_[i];
	set.power_ = set.weight();
	return set;
}


Set& Set::operator=(const Set& other)
{
	if (this != &other) {
		delete[] bv_;
		bv_ = new unsigned char[mem_ = other.mem_];
		len_ = other.len_;
		for (int i = 0; i < mem_; i++)
			bv_[i] = other.bv_[i];
		power_ = other.power_;
	}
	return *this;
}


Set& Set::operator|=(const Set& other)
{
	for (int i = 0; i < mem_; i++)
		bv_[i] |= other.bv_[i];
	power_ = weight();
	return *this;
}


Set Set::operator|(const Set& other)
{
	return Set(*this) |= other;
}


Set& Set::operator&=(const Set& other)
{
	for (int i = 0; i < mem_; i++)
		bv_[i] &= other.bv_[i];
	power_ = weight();
	return *this;
}


Set Set::operator&(const Set& other)
{
	return Set(*this) &= other;
}


Set& Set::operator/=(const Set& other)
{
	for (int i = 0; i < mem_; i++)
		bv_[i] ^= bv_[i] & other.bv_[i];
	power_ = weight();
	return *this;
}


Set Set::operator/(const Set& other)
{
	return Set(*this) /= other;
}


Set& Set::operator+=(char symbol)
{
	set1(symbol);
	power_ = weight();
	return *this;
}


Set Set::operator+(char symbol)
{
	return Set(*this) += symbol;
}


Set& Set::operator-=(char symbol)
{
	set0(symbol);
	power_ = weight();
	return *this;
}


Set Set::operator-(char symbol)
{
	return Set(*this) -= symbol;
}