#include"BoolVector.h"


BoolVectorComponent::BoolVectorComponent(BoolVector* bv, int index, int value)
{
	bv_ = bv;
	index_ = index;
	if (value)
		value = 1;
	value_ = value;
}


BoolVectorComponent::BoolVectorComponent(const BoolVectorComponent& other)
{
	bv_ = new BoolVector(*(other.bv_));
	index_ = other.index_;
	value_ = other.value_;
	flag_ = true;
}


BoolVectorComponent::~BoolVectorComponent()
{
	if (flag_)
		delete bv_;
}


std::ostream& operator<<(std::ostream& out, const BoolVectorComponent& bvcomponent)
{
	out << bvcomponent.value_;
	return out;
}


BoolVectorComponent& BoolVectorComponent::operator=(int value)
{
	if (value)
		bv_->set1(index_);
	else
		bv_->set0(index_);
	return *this;
}


BoolVectorComponent& BoolVectorComponent::operator=(const BoolVectorComponent& other)
{
	if (other.value_)
		bv_->set1(index_);
	else
		bv_->set0(index_);
	return *this;
}


BoolVectorComponent& BoolVectorComponent::operator|=(int value)
{
	if (value_ || value) {
		bv_->set1(index_);
		value_ = 1;
	}
	else {
		bv_->set0(index_);
		value_ = 0;
	}
	return *this;
}


BoolVectorComponent BoolVectorComponent::operator|(int value)
{
	return BoolVectorComponent(*this) |= value;
}


BoolVectorComponent& BoolVectorComponent::operator&=(int value)
{
	if (value_ && value) {
		bv_->set1(index_);
		value_ = 1;
	}
	else {
		bv_->set0(index_);
		value_ = 0;
	}
	return *this;
}


BoolVectorComponent BoolVectorComponent::operator&(int value)
{
	return BoolVectorComponent(*this) &= value;
}


BoolVectorComponent& BoolVectorComponent::operator^=(int value)
{
	if (value_ ^ value) {
		bv_->set1(index_);
		value_ = 1;
	}
	else {
		bv_->set0(index_);
		value_ = 0;
	}
	return *this;
}


BoolVectorComponent BoolVectorComponent::operator^(int value)
{
	return BoolVectorComponent(*this) ^= value;
}


BoolVectorComponent& BoolVectorComponent::operator|=(const BoolVectorComponent& other)
{
	return *this |= other.value_;
}


BoolVectorComponent BoolVectorComponent::operator|(const BoolVectorComponent& other)
{
	return BoolVectorComponent(*this) |= other.value_;
}


BoolVectorComponent& BoolVectorComponent::operator&=(const BoolVectorComponent& other)
{
	return *this &= other.value_;
}


BoolVectorComponent BoolVectorComponent::operator&(const BoolVectorComponent& other)
{
	return BoolVectorComponent(*this) &= other.value_;
}


BoolVectorComponent& BoolVectorComponent::operator^=(const BoolVectorComponent& other)
{
	return *this ^= other.value_;
}


BoolVectorComponent BoolVectorComponent::operator^(const BoolVectorComponent& other)
{
	return BoolVectorComponent(*this) ^= other.value_;
}


BoolVectorComponent BoolVectorComponent::operator~()
{
	if (value_) {
		bv_->set0(index_);
		value_ = 0;
	}
	else {
		bv_->set1(index_);
		value_ = 1;
	}
	return *this;
}