// VINAY LOHANA (LOHVD1701)
// KIMIA HASHEMI (HASKD1702)

#include <iostream>


using namespace std;

class String
{
public:
	~String(); // Destructor
	String(); // Default Constructor
	String(const char*); // Constructor char array
	String(char ch); // Constructor char
	String(const String&);// Copy Constructor
	
	friend ostream& operator << (ostream& out, const String& s);
	friend bool operator == (const String&, const String&);
	friend String operator + (const String& s1, const String& s2);
	friend String operator += (String &s1, const String &s2);
	String& operator = (const String&);
	char& operator [] (int i) const { return str[i]; }
	
	int substring(const String& s) const;
	int position(char ch) const;
	int length() const { return len; }
	String upper() const;
	String substr(int start, int length) const;
	bool empty() const;

private:
	char* str;
	int len;
};

// Destructor
String::~String()
{ 
	delete[] str; 
}

String::String() // Default Constructor
{
	len = 0;
	str = NULL;
}

String::String(const char* cString) // Constructor char array
{
	len = 0;
	while (cString[len] != '\0')
	{
		len++;
	}
	str = new char[len];
	for (int i = 0; i < len; i++)
	{
		str[i] = cString[i];
	}
}

String::String(char ch) // Constructor char
{
	len = 1;
	str = new char[len];
	str[0] = ch;
}

String::String(const String& arr) // Copy Constructor
{
	len = arr.len;
	str = new char[len];
	for (int i = 0; i < len; i++)
	{
		str[i] = arr.str[i];
	}
}

ostream& operator << (ostream& out, const String& s)
{
	for (int i = 0; i < s.len; i++)
	{
		out << s.str[i];
	}
	return out;
}

bool operator == (const String& s1, const String& s2)
{
	if (s1.len != s2.len)
		return 0;

	for (int i = 0; i < s1.len; i++)
	{
		if (s1.str[i] != s2.str[i])
			return 0;
	}

	return 1;

}

String operator + (const String& s1, const String& s2)
{
	String addS;

	addS.len = s1.len + s2.len;
	addS.str = new char[addS.len];
	for (int i = 0; i < s1.len; i++)
		addS.str[i] = s1.str[i];

	int j = 0;

	for (int i = s1.len; i < addS.len; i++)
	{
		addS.str[i] = s2.str[j];
		j++;
	}
	return addS;
}

String operator += (String &s1, const String &s2)
{
	s1 = s1 + s2;
	return s1;
}

String& String::operator = (const String& s)
{
	if (len != s.len)
	{
		delete[] str;
		str = new char[s.len];
	}
	len = s.len;
	for (int i = 0; i < s.len; i++)
	{
		str[i] = s.str[i];
	}
	return *this;
}

int String::substring(const String &s) const
{
	if (s.empty())
		return 0;

	int count = 0, i = 0;

	for (int j = 0; j < len; j++)
	{
		if (s.str[i] == str[j])
		{
			for (int k = j, l = 0; (k < len && l < s.len); k++, l++)
			{
				if (s.str[l] == str[k])
				{
					count++;
				}
			}
			if (count == s.len)
			{
				return j;
			}
			else
			{
				count = 0;
			}
		}
	}
	return -1;

}

int String::position(char ch) const
{
	int index = -1;
	for (int i = 0; i < len; i++)
	{
		if (str[i] == ch)
		{
			return i;
		}
	}
	return index;
}

String String::upper() const
{
	String upperS;
	upperS.len = len;
	upperS.str = new char[upperS.len];
	for (int i = 0; i < len; i++)
	{
		upperS.str[i] = str[i];
	}

	for (int i = 0; i < len; i++)
	{
		if (upperS.str[i] >= 'a' && upperS.str[i] <= 'z')
			upperS.str[i] -= 32;
	}

	return upperS;
}

String String::substr(int start, int length) const
{
	if (start >= len)
		return String("");

	int j = 0;
	String subString;
	if (length >= len)
	{
		subString.str = new char[len - start];
		subString.len = len - start;
		for (int i = start; i < len; i++)
		{
			subString.str[j] = str[i];
			j++;
		}
	}
	else
	{
		subString.len = length;
		subString.str = new char[length];

		for (int i = start; i < length + start; i++)
		{
			subString.str[j] = str[i];
			j++;
		}

	}

	return subString;
}

bool String::empty() const
{
	if ((len == 0) && (str == NULL))
		return 1;
	return 0;
}

String reversedString(const String& orgStr)
{
	int j = orgStr.length() - 1;
	char* reverseStr = new char[orgStr.length() + 1];
	int i;
	for (i = 0; i < orgStr.length(); i++)
	{
		reverseStr[i] = orgStr[j];
		j--;
	}
	reverseStr[i] = '\0';
	return String(reverseStr);
}

int compareStrings(const String& s1, const String& s2)
{
	if (s1 == s2)
		return 0;
	
	for (int i = 0; i < s1.length() && i < s2.length(); i++)
	{
		if (s1[i] > s2[i])
			return 1;
		if (s1[i] < s2[i])
			return -1;
	}

	if (s1.length() > s2.length())
		return 1;
	else
		return -1;
}

// CMPT135 J. Ye   Assignment 1 sample testing code and the expected output

int main()
{
	String s1, s2;
	cout << "s1 is empty? " << s1.empty() << endl;
	cout << "s2 is empty? " << s2.empty() << endl;
	String s3 = "Hello";
	s1 = s2 = s3;
	cout << s1 << '\t' << s2 << '\t' << s3 << endl;
	if (s1 == s2)
		cout << "s1 and s2 are equal\n";
	else
		cout << "s1 and s2 are not equal\n";

	s1 = s1;
	cout << "\nIs there any problem here? " << s1 << endl << endl;

	s2 = "hi";
	s3 = s2;
	cout << s1 << '\t' << s2 << '\t' << s3 << endl;
	cout << "Now s1 is empty? " << s1.empty() << endl;
	cout << s1.length() << '\t' << s2.length() << '\t' << s3.length() << endl;

	cout << "--------------- 0 ---------------" << endl << endl;

	if (s1 == s2)
		cout << "They are equal\n";
	else
		cout << "They are not equal\n";

	if (s2 == "Hello")
		cout << "They are equal\n";
	else
		cout << "They are not equal\n";

	s1[0] = 'H';
	s1[1] = s1[4];
	for (int i = 0; i < s3.length(); ++i)
		cout << s3[i] << " ";
	cout << endl;
	cout << "s1 is " << s1 << endl;
	cout << "s2 is " << s2 << endl;

	cout << "--------------- 1 ---------------" << endl << endl;

	String s4;
	String space(" ");

	s4 = s1 + space + s2;
	cout << s4 << endl;

	cout << "s4 length is " << s4.length() << endl;
	if (s4 == s4)
		cout << "s4 equals s4\n";
	else
		cout << "s4 not equals s4\n";
	cout << endl;

	s3 = "Monday";
	cout << "s3 is " << s3 << endl;
	s3 = "";
	cout << "s3 is " << s3 << endl;
	String friday = "Friday";
	s3 = s3 + friday;
	cout << "s3 is " << s3 << endl;
	s3 = "SundaySunday";
	s3 = s3 + "   hahaha";
	cout << "s3 is " << s3 << endl;

	cout << "--------------- 2 ---------------" << endl << endl;

	String s5;
	cout << "Do we have output here? " << endl << endl;
	for (int i = 0; i < s5.length(); ++i)
		cout << s5[i] << '?';

	cout << "s4 is " << s4 << endl;
	cout << s4.upper() << endl;
	cout << s4 << endl;

	cout << "The index of l in " << s4 << " is " << s4.position('l') << endl;
	cout << "The index of k in " << s4 << " is " << s4.position('k') << endl;

	cout << "--------------- 3 ---------------" << endl << endl;

	cout << "s1 is: " << s1 << endl;
	char char_o = 'o';
	s1 += char_o;
	String str_o = "o";
	s1 += str_o;
	cout << "s1 now is: " << s1 << endl;
	String str;
	cout << "str is " << str << endl;
	char ch = 'A';
	for (int i = 0; i < 10; ++i)
	{
		str += ch;
		ch++;
	}
	String more = "...MORE";
	str += more;
	cout << "Now str is " << str << endl;

	cout << "--------------- 4 ---------------" << endl << endl;

	cout << "str length: " << str.length() << endl;
	cout << "substring starting at 2 with size 5 is " << str.substr(2, 5) << endl;
	cout << "substring starting at 2 with size 20 is " << str.substr(2, 20) << endl;
	cout << "substring starting at 7 with size 1 is " << str.substr(7, 1) << endl;
	cout << "substring starting at 20 with size 5 is " << str.substr(20, 5) << "empty string!" << endl;

	cout << "--------------- 5 ---------------" << endl << endl;

	s3 = "Hi";
	int index = s1.substring(s3);
	if (index >= 0)
		cout << "1) " << s3 << " is a substring of " << s1 << ", starting from index " << index << endl;
	else
		cout << "1) " << s3 << " is not a substring of " << s1 << endl;

	index = s1.substring("lo");
	if (index >= 0)
		cout << "2) " << "lo is a substring of " << s1 << ", starting from index " << index << endl;
	else
		cout << "2) " << "lo is not a substring of " << s1 << endl << endl;

	String s6;
	index = s1.substring(s6);
	if (index >= 0)
		cout << "3) " << s6 << " is a substring of " << s1 << ", starting from index " << index << endl;
	else
		cout << "3) " << s6 << " is not a substring of " << s1 << endl;


	String s = "aabcccdefefg";
	index = s.substring("bdg");
	if (index >= 0)
		cout << "4) bdg is a substring of " << s << ", starting from index " << index << endl;
	else
		cout << "4) bdg is not a substring of " << s << endl;

	index = s.substring("cde");
	if (index >= 0)
		cout << "5) cde is a substring of " << s << ", starting from index " << index << endl;
	else
		cout << "5) cde is not a substring of " << s << endl;

	s = "aabc";
	s1 = "aabc ";
	index = s.substring(s1);
	if (index >= 0)
		cout << "6) " << s1 << " is a substring of " << s << ", starting from index " << index << endl;
	else
		cout << "6) " << s1 << " is not a substring of " << s << endl;

	index = s.substring(s);
	if (index >= 0)
		cout << "7) " << s << " is a substring of " << s << ", starting from index " << index << endl;
	else
		cout << "7) " << s << " is not a substring of " << s << endl;


	cout << "--------------- 6 ---------------" << endl << endl;
	s1 = "hello";
	s2 = "hi";
	s3 = "he";
	s4 = "hello";
	s5 = "";
	cout << compareStrings(s1, s2) << endl; // the behavior of this function is the same as strcmp
	cout << compareStrings(s1, s3) << endl;
	cout << compareStrings(s1, s4) << endl;
	cout << compareStrings(s5, s2) << endl;
	cout << compareStrings(s2, s5) << endl;
	cout << compareStrings(s1, s1) << endl << endl;

	cout << s1 << endl;
	String reversed = reversedString(s1);
	cout << "The reversed string is " << reversed << endl;
	cout << "The original string is " << s1 << endl;

	if (reversedString(s1) == reversedString(s4))
		cout << "Yes, equal!" << endl;
	else
		cout << "No, not equal!" << endl;

	system("pause");
	return 0;
}

/* Output for String testing code:

s1 is empty? 1
s2 is empty? 1
Hello   Hello   Hello
s1 and s2 are equal

Is there any problem here? Hello

Hello   hi      hi
Now s1 is empty? 0
5       2       2
--------------- 0 ---------------

They are not equal
They are not equal
h i
s1 is Hollo
s2 is hi
--------------- 1 ---------------

Hollo hi
s4 length is 8
s4 equals s4

s3 is Monday
s3 is
s3 is Friday
s3 is SundaySunday   hahaha
--------------- 2 ---------------

Do we have output here?

s4 is Hollo hi
HOLLO HI
Hollo hi
The index of l in Hollo hi is 2
The index of k in Hollo hi is -1
--------------- 3 ---------------

s1 is: Hollo
s1 now is: Hollooo
str is
Now str is ABCDEFGHIJ...MORE
--------------- 4 ---------------

str length: 17
substring starting at 2 with size 5 is CDEFG
substring starting at 2 with size 20 is CDEFGHIJ...MORE
substring starting at 7 with size 1 is H
substring starting at 20 with size 5 is empty string!
--------------- 5 ---------------

1) Hi is not a substring of Hollooo
2) lo is a substring of Hollooo, starting from index 3
3)  is a substring of Hollooo, starting from index 0
4) bdg is not a substring of aabcccdefefg
5) cde is a substring of aabcccdefefg, starting from index 5
6) aabc  is not a substring of aabc
7) aabc is a substring of aabc, starting from index 0
--------------- 6 ---------------

-1
1
0
-1
1
0

hello
The reversed string is olleh
The original string is hello
Yes, equal!
*/