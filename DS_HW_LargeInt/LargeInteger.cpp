#include"LargeInteger.h"


LargeInteger::LargeInteger(int size){
	maxSize = size;
	length = 0;
	number = new short int[maxSize];
	for (int i = 0; i < maxSize; i++)
	{
		number[i] = 0;
	}

}

LargeInteger::LargeInteger(const LargeInteger& L){
	maxSize = L.maxSize;
	length = L.length;
	number = new short int[maxSize];
	for (int i = 0; i < maxSize; i++)
	{
		number[i] = L.number[i];
	}

}

LargeInteger ::~LargeInteger(){
	if(number!=NULL)
	delete[]number;
}

bool LargeInteger :: setNumber(string str){
	if (str.empty()) {
		for (int i = 0; i < maxSize; i++)
		{
			number[i] = 0;
		}
		length = 0;
		return false;
	}

	int Length = str.length();

	//is Valed number
	for (int i = 0; i < Length; i++)
	{
		if ((str[i] < '0') || (str[i] > '9'))
		{
			for (int i = 0; i < maxSize; i++)
			{
				number[i] = 0;
			}
			length = 0;
			return false;
		}
	}

	length = Length;
	if (Length > maxSize)
	{
		maxSize = Length;//If we wont to set max size Length*2 we can as the user wont 
		if (number != NULL)
		delete[]number;
		number = new short int[maxSize];
	}
	
	for (int i = 0, j = Length - 1; i < Length; i++, j--)
	{
		number[i] = (str[j] - '0');
	}

	return true;
}

void LargeInteger :: read(istream& in){
	string str;
	in >> str;
	if (setNumber(str)) {
		cout << "Number read successfully." << endl;
	}
	else {
		cout << "Invalid number input." << endl;
	}
}

void LargeInteger :: write(ostream& out) const{
	if (length == 0) {
		out << "0";
	}
	else {
		for (int i = length - 1; i >= 0; i--) {
			out << number[i];
		}
	}
	out << endl;

}


LargeInteger LargeInteger::operator+(const LargeInteger& L) const {
	int maxLength = max(length, L.length) + 1; 
	LargeInteger result(maxLength);

	int carry = 0;
	for (int i = 0; i < maxLength; i++) {
		int digit1 = (i < length) ? number[i] : 0;
		int digit2 = (i < L.length) ? L.number[i] : 0;

		int sum = digit1 + digit2 + carry;
		result.number[i] = sum % 10; 
		carry = sum / 10; 
	}
	result.length = maxLength;
	while (result.length > 1 && result.number[result.length - 1] == 0) {
		result.length--;
	}

	return result;
}


LargeInteger LargeInteger::operator-(const LargeInteger& L) const {
	LargeInteger result;
	if (*this > L)
	{
		result = *this;
		for (int i = 0; i < result.length; i++)
		{
			if (result.number[i] < L.number[i])
			{
				result.number[i] += 10 - L.number[i];
				result.number[i + 1] -= 1;
			}
			else {
				result.number[i] -= L.number[i];
			}
		}

	}
	if (L > *this)
	{
		result = L;
		for (int i = 0; i < result.length; i++)
		{
			if (result.number[i] < number[i])
			{
				result.number[i] += 10 - number[i];
				result.number[i + 1] -= 1;
			}
			else {
				result.number[i] -= number[i];
			}
		}
	}
	return result;
	
	
	
}

LargeInteger LargeInteger::operator*(const LargeInteger& L) const {
	int resultSize = length + L.length;
	LargeInteger result(resultSize);

	// Perform long multiplication
	for (int i = 0; i < length; i++) {
		int carry = 0;
		for (int j = 0; j < L.length; j++) {
			int product = number[i] * L.number[j] + result.number[i + j] + carry;
			result.number[i + j] = product % 10;
			carry = product / 10;
		}

		if (carry > 0) {
			result.number[i + L.length] += carry;
		}
	}

	// Find the length of the result
	for (int i = resultSize - 1; i >= 0; i--) {
		if (result.number[i] != 0) {
			result.length = i + 1;
			break;
		}
	}

	return result;
}


const LargeInteger& LargeInteger :: operator=(const LargeInteger& L){
	if (this == &L) {
		return *this;
	}

	maxSize = L.maxSize;
	length = L.length;

	delete[] number;

	number = new short int[maxSize];

	for (int i = 0; i < maxSize; i++) {
		number[i] = L.number[i];
	}

	return *this;
}

bool LargeInteger :: operator==(const LargeInteger& L)const{
	if (length != L.length) {
		return false;
	}

	for (int i = 0; i < length; i++) {
		if (number[i] != L.number[i]) {
			return false;
		}
	}

	return true;
}

bool LargeInteger :: operator < (const LargeInteger& L)const{
	if (length < L.length) return true;
	
    if (length > L.length) return false;

	for (int i = length - 1; i >= 0; i--) {
		if (number[i] < L.number[i]) {
			return true;
		}
		else if (number[i] > L.number[i]) {
			return false;
		}
	}

	return false;
	
}

bool LargeInteger :: operator > (const LargeInteger& L)const{
	if (length > L.length) {
		return true;
	}
	if (length < L.length) {
		return false;
	}

	for (int i = length - 1; i >= 0; i--) {
		if (number[i] > L.number[i]) {
			return true;
		}
		else if (number[i] < L.number[i]) {
			return false;
		}
	}

	return false;
}

bool LargeInteger :: operator <= (const LargeInteger& L)const {
	
	if ((*this < L) || (*this == L))
		return true;
	return false;
}
bool LargeInteger :: operator >= (const LargeInteger& L)const {
	if ((*this > L) || (*this == L))
		return true;
	return false;

}




/*
* work at it ....
LargeInteger LargeInteger::operator/(const LargeInteger& L) const {
	//if the second number = 0 ......
	
	if (L == LargeInteger(0)) {
		cout << "Error: Division by zero." <<endl;
		return LargeInteger(0); 
	}

	LargeInteger quotient(maxSize); 
	LargeInteger dividend(*this);

	while (dividend >= L) {
		int count = 0;
		while (dividend >= L * (count + 1)) {
			count++;
		}

		dividend = dividend - L * count;
		quotient = quotient + LargeInteger(count);
	}

	while (quotient.length > 1 && quotient.number[quotient.length - 1] == 0) {
		quotient.length--;
	}

	return quotient;
}

*/

/*LargeInteger myMax(const LargeInteger& a, const LargeInteger& b) {
	if (a > b)
		return a;
	return b;
}*/