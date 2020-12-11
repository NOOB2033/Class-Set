#pragma once
#include"BoolVector.h"


class Set : public BoolVector
{
private:
	int power_;
public:
	Set();
	Set(const char*);
	Set(const Set&);
	~Set();
	friend std::istream& operator>>(std::istream&, const Set&); //
	friend std::ostream& operator<<(std::ostream&, const Set&); //
	bool find(char);
	char min();
	char max();
	int getPower();
	bool operator==(const Set&);
	bool operator!=(const Set&);
	Set operator~();
	Set& operator=(const Set&);
	Set& operator|=(const Set&);
	Set operator|(const Set&);
	Set& operator&=(const Set&);
	Set operator&(const Set&);
	Set& operator/=(const Set&);
	Set operator/(const Set&);
	Set& operator+=(char);
	Set operator+(char);
	Set& operator-=(char);
	Set operator-(char);
};