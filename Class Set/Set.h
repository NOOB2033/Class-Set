#pragma once
#include"BoolVector.h"


class Set : public BoolVector
{
private:
	int power_;
public:
	Set(int);
	Set(const char*);
	Set(const Set&);
	~Set();
	friend std::istream& operator>>(std::istream&, Set&);
	friend std::ostream& operator<<(std::ostream&, const Set&);
	bool find(char);
	bool min(char&);
	bool max(char&);
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