#include"BoolVector.h"
#include"Enum.h"


BoolVector::BoolVector()
{
	len_ = 0;
	bv_ = new unsigned char[mem_ = 1];
	bv_[0] = 0;
}


BoolVector::BoolVector(int len, bool valueForAllDigits)
{
	if (len < 0)
		throw Invalid_size;
	len_ = len;
	bv_ = new unsigned char[mem_ = (len + BYTE - 1) / BYTE];
	if (valueForAllDigits) {
		for (int i = 0; i < mem_; i++)
			bv_[i] = 255; // 11111111
		if (len_ % BYTE) {
			unsigned char mask = 128; // 10000000
			for (int i = 0; i < BYTE - len_ % BYTE; i++) // обнуление первых бит в нулевом байте
				bv_[0] &= ~mask >> i;
		}
	}
	else
		for (int i = 0; i < mem_; i++)
			bv_[i] = 0;
}


BoolVector::BoolVector(const char* str)
{
	len_ = strlen(str);
	bv_ = new unsigned char[mem_ = (len_ + BYTE - 1) / BYTE];
	for (int i = 0; i < mem_; i++)
		bv_[i] = 0;
	for (int i = 0; i < len_; i++)
		if (str[i] != '0')
			set1(i);
}


BoolVector::BoolVector(const BoolVector& copyBV)
{
	bv_ = new unsigned char[mem_ = copyBV.mem_];
	len_ = copyBV.len_;
	for (int i = 0; i < mem_; i++)
		bv_[i] = copyBV.bv_[i];
}


BoolVector::~BoolVector()
{
	delete[] bv_;
}


std::istream& operator>>(std::istream& in, const BoolVector& bv)
{
	unsigned char c;
	int i = 0;
	for (i; i < bv.len_ % bv.BYTE; i++) { // Для нулевого байта, если он не полный(используются не все 8 бит)
		in >> c;
		if (c != '0')
			c = '1';
		bv.bv_[0] <<= 1;
		bv.bv_[0] |= c - '0';
	}
	if (i != 0) // Если изменился i, то мы обработали нулевой байт => идем к следующим
		i = 1;
	for (i; i < bv.mem_; i++)
		for (int j = 0; j < bv.BYTE; j++) {
			in >> c;
			if (c != '0')
				c = '1';
			bv.bv_[i] <<= 1;
			bv.bv_[i] |= c - '0';
		}
	return in;
}


std::ostream& operator<<(std::ostream& out, const BoolVector& bv)
{
	unsigned char mask;
	for (int i = 0; i < bv.mem_; i++) {
		mask = 128; // 10000000
		for (int j = 0; j < bv.BYTE; j++, mask >>= 1)
			if (bv.bv_[i] & mask)
				std::cout << 1;
			else
				out << 0;
		out << " ";
	}
	return out;
}


void BoolVector::set0(int index)
{
	if (index < 0 || index >= len_)
		throw Invalid_index;
	unsigned char mask = 128; // 10000000
	int byte = mem_ - 1 - (len_ - index - 1) / BYTE;
	if (byte) // отдельно для нулевого байта, если он не полный
		mask >>= (index - len_ % BYTE) % BYTE;
	else
		mask >>= BYTE - (len_ - (mem_ - 1) * BYTE) + index;
	bv_[byte] &= ~mask;
}


void BoolVector::set1(int index)
{
	if (index < 0 || index >= len_)
		throw Invalid_index;
	unsigned char mask = 128; // 10000000
	int byte = mem_ - 1 - (len_ - index - 1) / BYTE;
	if (byte) // отдельно для нулевого байта, если он не полный
		mask >>= (index - len_ % BYTE) % BYTE;
	else
		mask >>= BYTE - (len_ - (mem_ - 1) * BYTE) + index;
	bv_[byte] |= mask;
}


void BoolVector::fullSet0()
{
	for (int i = 0; i < mem_; i++)
		bv_[i] = 0;
}


void BoolVector::fullSet1()
{
	unsigned char mask = 128; // 10000000
	mask >>= BYTE - abs(len_ - (mem_ - 1) * BYTE);
	int i = 0;
	for (i; i < len_ % BYTE; i++)
		bv_[0] |= mask >> i;
	if (i != 0)
		i = 1;
	for (i; i < mem_; i++)
		bv_[i] = 255; // 11111111
}


void BoolVector::set0(int index, int value)
{
	if (index < 0 || index >= len_)
		throw Invalid_index;
	if (value <= 0 || value > len_)
		throw Invalid_size;
	if (len_ - index < value)
		value = len_ - index;
	if (value > 1) {
		unsigned char mask;
		for (int i = index; i < value + index; i++) {
			mask = 128; // 10000000
			int byte = mem_ - 1 - (len_ - i - 1) / BYTE;
			if (byte) // отдельно для нулевого байта, если он не полный
				mask >>= (i - len_ % BYTE) % BYTE;
			else
				mask >>= BYTE - (len_ - (mem_ - 1) * BYTE) + i;
			bv_[byte] &= ~mask;
		}
	}
	else
		set0(index);
}


void BoolVector::set1(int index, int value)
{
	if (index < 0 || index >= len_)
		throw Invalid_index;
	if (value <= 0 || value > len_)
		throw Invalid_size;
	if (len_ - index < value)
		value = len_ - index;
	if (value > 1) {
		unsigned char mask;
		for (int i = index; i < value + index; i++) {
			mask = 128; // 10000000
			int byte = mem_ - 1 - (len_ - i - 1) / BYTE;
			if (byte) // отдельно для нулевого байта, если он не полный
				mask >>= (i - len_ % BYTE) % BYTE;
			else
				mask >>= BYTE - (len_ - (mem_ - 1) * BYTE) + i;
			bv_[byte] |= mask;
		}
	}
	else
		set1(index);
}


void BoolVector::fullInversion()
{
	unsigned char mask;
	int i = 0;
	for (i; i < len_ % BYTE; i++) {
		mask = 128; // 10000000
		mask >>= BYTE - len_ % BYTE + i;
		bv_[0] ^= mask;
	}
	if (i != 0)
		i = 1;
	for (i; i < mem_; i++) {
		mask = 128; // 10000000
		for (int j = 0; j < BYTE; j++, mask >>= 1)
			bv_[i] ^= mask;
	}
}


void BoolVector::componentInversion(int index)
{
	if (index < 0 || index >= len_)
		throw Invalid_index;
	unsigned char mask = 128; // 10000000
	int byte = mem_ - 1 - (len_ - index - 1) / BYTE;
	if (byte) // отдельно для нулевого байта, если он не полный
		mask >>= (index - len_ % BYTE) % BYTE;
	else
		mask >>= BYTE - (len_ - (mem_ - 1) * BYTE) + index;
	bv_[byte] ^= mask;
}


bool BoolVector::getBit(int index)
{
	if (index < 0 || index >= len_)
		throw Invalid_index;
	unsigned char mask = 128; // 10000000
	int byte = mem_ - 1 - (len_ - index - 1) / BYTE;
	if (byte) // отдельно для нулевого байта, если он не полный
		mask >>= (index - len_ % BYTE) % BYTE;
	else
		mask >>= BYTE - (len_ - (mem_ - 1) * BYTE) + index;
	return bv_[byte] & mask;
}


int BoolVector::weight()
{
	int weight = 0, i = 0;
	unsigned char mask;
	for (i; i < len_ % BYTE; i++) {
		mask = 128; // 10000000
		mask >>= BYTE - len_ % BYTE + i;
		if (bv_[0] & mask)
			weight++;
	}
	if (i != 0)
		i = 1;
	for (i; i < mem_; i++) {
		mask = 128; // 10000000
		for (int j = 0; j < BYTE; j++, mask >>= 1)
			if (bv_[i] & mask)
				weight++;
	}
	return weight;
}


BoolVector BoolVector::operator~()
{
	BoolVector bv(*this);
	bv.fullInversion();
	return bv;
}


BoolVector& BoolVector::operator=(const BoolVector& other)
{
	if (this != &other) {
		delete[] bv_;
		bv_ = new unsigned char[mem_ = other.mem_];
		len_ = other.len_;
		for (int i = 0; i < mem_; i++)
			bv_[i] = other.bv_[i];
	}
	return *this;
}


BoolVector& BoolVector::operator>>=(int value)
{
	if (value <= 0)
		return *this;
	if (value >= len_)
		for (int i = 0; i < mem_; i++)
			bv_[i] = 0;
	unsigned char mask = 128; // 10000000
	for (int i = 0; i < value; i++) {
		for (int j = mem_ - 1; j > 0; j--) {
			bv_[j] >>= 1;
			if (bv_[j - 1] & 1)
				bv_[j] |= mask;
		}
		bv_[0] >>= 1;
	}
	return *this;
}


BoolVector BoolVector::operator>>(int value)
{
	return BoolVector(*this) >>= value;
}


BoolVector& BoolVector::operator<<=(int value)
{

	if (value <= 0)
		return *this;
	if (value >= len_)
		for (int i = 0; i < mem_; i++)
			bv_[i] = 0;
	unsigned char mask = 128; //10000000
	for (int i = 0; i < value; i++) {
		for (int j = 0; j < mem_ - 1; j++) {
			bv_[j] <<= 1;
			if (bv_[j + 1] & mask)
				bv_[j] |= 1;
		}
		bv_[mem_ - 1] <<= 1;
	}
	if (len_ % BYTE)
		for (int i = 0; i < BYTE - len_ % BYTE; i++) // обнуление первых бит в нулевом байте
			bv_[0] &= ~mask >> i;
	return *this;
}


BoolVector BoolVector::operator<<(int value)
{
	return BoolVector(*this) <<= value;
}


BoolVector& BoolVector::operator|=(const BoolVector& other)
{
	int min = mem_;
	if (mem_ > other.mem_)
		min = other.mem_;
	for (int i = 0; i < min; i++)
		bv_[mem_ - i - 1] |= other.bv_[other.mem_ - i - 1];
	return *this;
}


BoolVector BoolVector::operator|(const BoolVector& other)
{
	return BoolVector(*this) |= other;
}


BoolVector& BoolVector::operator&=(const BoolVector& other)
{
	int min = mem_;
	if (mem_ > other.mem_)
		min = other.mem_;
	for (int i = 0; i < min; i++)
		bv_[mem_ - i - 1] &= other.bv_[other.mem_ - i - 1];
	return *this;
}


BoolVector BoolVector::operator&(const BoolVector& other)
{
	return BoolVector(*this) &= other;
}


BoolVector& BoolVector::operator^=(const BoolVector& other)
{
	int min = mem_;
	if (mem_ > other.mem_)
		min = other.mem_;
	for (int i = 0; i < min; i++)
		bv_[mem_ - i - 1] ^= other.bv_[other.mem_ - i - 1];
	return *this;
}


BoolVector BoolVector::operator^(const BoolVector& other)
{
	return BoolVector(*this) ^= other;
}


BoolVectorComponent BoolVector::operator[](int index)
{
	unsigned char mask = 128; // 10000000
	int byte = mem_ - 1 - (len_ - index - 1) / BYTE;
	if (byte) // отдельно для нулевого байта, если он не полный
		mask >>= (index - len_ % BYTE) % BYTE;
	else
		mask >>= BYTE - (len_ - (mem_ - 1) * BYTE) + index;
	return BoolVectorComponent(this, index, (bv_[byte] & mask));
}