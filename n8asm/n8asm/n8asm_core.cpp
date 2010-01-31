#include "n8asm_core.h"

StringList string_tokenizer(String str)
{
	StringList tokens;
	String s;
	str.push_back(';');
	bool token_written=false;
	for (String::iterator i=str.begin();i!=str.end();i++)
	{
		if (isalnum(*i) || *i=='[' || *i==']')
		{
			token_written = true;
			s.push_back(*i);
		} else
		{
			if (token_written)
				tokens.push_back(s);
			s.clear();
			token_written = false;
		}
	}
	return tokens;
}

String uint_to_str(unsigned int n, unsigned int dynamic)
{
	String s;	
	unsigned int ctr=0;
	while (n!=0 && ctr<dynamic)
	{
		ctr++;
		if ((n&0x00000001)!=0)
			s = "1" + s;
		else
			s = "0" + s;

		n >>= 1;
	}
	for (unsigned int i=0;i<dynamic-ctr;i++)
		s = "0"+s;
	return s;
}

unsigned int str32_to_bin(String str32)
{
	String s;

	if (str32.size()>32)
		return 0;

	for (int i=0;i<32-str32.size();i++)
		s += "0";
	s+= str32;
	str32 = s;

	unsigned int n=0;
	for (int i=0;i<32;i++)
	{
		if (str32[i]=='1')
		{
			n <<= 1;
			n += 1;
		}	
		else
			n <<= 1;
	}

	unsigned int n2;
	unsigned char * bin = (unsigned char*)&n2;
	bin[0] = ((unsigned char*)&n)[3];
	bin[1] = ((unsigned char*)&n)[2];
	bin[2] = ((unsigned char*)&n)[1];
	bin[3] = ((unsigned char*)&n)[0];

	return n2;
}
