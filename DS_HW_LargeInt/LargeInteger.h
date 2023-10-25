#include<iostream>
using namespace std;

class LargeInteger {
public:
	LargeInteger(int size=10);
	LargeInteger(const LargeInteger& L);
	~LargeInteger();
	bool setNumber(string str);
	void read(istream& in);
	void write(ostream& out) const;

	LargeInteger operator+(const LargeInteger& L) const;
	LargeInteger operator-(const LargeInteger& L) const;

	LargeInteger operator*(const LargeInteger& L)const;
	const LargeInteger& operator=(const LargeInteger& L);
	bool operator==(const LargeInteger& L)const;
	bool operator < (const LargeInteger& L)const;
	bool operator > (const LargeInteger& L)const;
	//LargeInteger operator/(const LargeInteger& L) const;//doesn't done

	bool operator <= (const LargeInteger& L)const;
	bool operator >= (const LargeInteger& L)const;
	
private:
	short int* number;
	int length;
	int maxSize;
};