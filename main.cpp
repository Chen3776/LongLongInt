#include <cstring>
#include <iostream>
using namespace std;

class LongLongInt
{
private:
	char* num;
public:
	LongLongInt(const char* n = "");
	LongLongInt(const LongLongInt&);
	~LongLongInt() { delete num; }
	void print() const;
	void add(const LongLongInt&, const LongLongInt&);
	void assign(const LongLongInt&);
	bool equal(const LongLongInt&) const;
	bool unEqual(const LongLongInt&) const;
	bool greater(const LongLongInt&)const;
	bool greater_or_equal(const LongLongInt&)const;
	bool less(const LongLongInt&) const;
	bool less_or_equal(const LongLongInt&)const;
};

LongLongInt::LongLongInt(const char* n)
{
	int len = strlen(n);
	num = new char[len + 1];
	for (int i = 0; i < len; i++)
	{
		num[len - i - 1] = n[i];
	}
	num[len] = 0;
}

LongLongInt::LongLongInt(const LongLongInt& other)
{
	num = new char[strlen(other.num) + 1];
	strcpy_s(num,strlen(other.num) + 1, other.num);
}

void LongLongInt::print() const
{
	for (int i = strlen(num); i >= 0; --i)
		cout << num[i];
	if (strlen(num) == 0)
		cout << 0;
}

void LongLongInt::add(const LongLongInt& n1, const LongLongInt& n2)
{
	int i = 0;
	int len1 = strlen(n1.num), len2 = strlen(n2.num);
	int minlen = (len1 > len2 ? len2 : len1);
	int len = (len1 > len2 ? len1 : len2) + 1;
	int carry = 0, result;							//carry是进位
	
	num = new char[len + 1];
	for (i = 0; i < minlen; ++i)				//n1与n2都有数字
	{
		result = n1.num[i] - '0' + n2.num[i] - '0' + carry;
		num[i] = result % 10 + '0';
		carry = result / 10;
	}

	while (i < len1)								//n2已结束
	{
		result = n1.num[i] - '0' + carry;
		num[i] = result % 10 + '0';
		carry = result / 10;
		++i;
	}

	while (i < len2)									//n1已结束
	{
		result = n2.num[i] - '0' + carry;
		num[i] = result % 10 + '0';
		carry = result / 10;
		++i;
	}

	if (carry != 0)										//最高位进位
		num[i++] = carry + '0';
	num[i] = 0;
	if (i != len)										//最高位无进位处理
	{
		char* tmp = num;
		num = new char[len];
		strcpy_s(num,strlen(tmp) + 1, tmp);
		delete tmp;
	}
}

void LongLongInt::assign(const LongLongInt& right)
{
	if (this == &right)
		return;

	delete num;
	num = new char[strlen(right.num) + 1];
	strcpy_s(num,strlen(right.num) + 1, right.num);
}

bool LongLongInt::equal(const LongLongInt& n) const
{
	return strcmp(num, n.num) == 0;
}

bool LongLongInt::unEqual(const LongLongInt& n) const
{
	return strcmp(num, n.num) != 0;
}

bool LongLongInt::greater(const LongLongInt& n) const
{
	int len1 = strlen(num), len2 = strlen(n.num);
	if (len1 > len2) return true;
	else if (len1 < len2) return false;

	for (int i = len1 - 1; i >= 0; --i)
	{
		if (num[i] > n.num[i]) return true;
		else if (num[i] < n.num[i]) return false;
	}

	return false;
}

bool LongLongInt::greater_or_equal(const LongLongInt& n) const
{
	int len1 = strlen(num), len2 = strlen(n.num);
	if (len1 > len2) return true;
	else if (len1 < len2) return false;

	for (int i = len1 - 1; i >= 0; --i)
	{
		if (num[i] > n.num[i]) return true;
		else if (num[i] < n.num[i]) return false;
	}
	
	return true;
}

bool LongLongInt::less(const LongLongInt& n)const
{
	return !greater_or_equal(n);
}
bool LongLongInt::less_or_equal(const LongLongInt& n)const
{
	return !greater(n);
}