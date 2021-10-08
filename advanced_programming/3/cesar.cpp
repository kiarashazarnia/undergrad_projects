#include "header.h"

Byte read_byte(ifstream& input)
{
	Byte byte;
	char temp;
	for(int i = 0; i < BYTELEN; i++)
	{
		input >> temp;
		if(temp == ONECH)
			byte[i] = 1;
		else if(temp == ZEROCH)
			byte[i] = 0;
		else
		{
			#ifdef ERROR_REP
				cerr << "Error: read_byte just read binary." << endl;
			#endif
		}
	}
	return byte;
}

void characterize_zero_one_file(ifstream& input, ofstream& output)
{
	Byte bytemp;
	char chtemp;
	input.clear();
	input.seekg(ZERO);
	while(!input.eof())
	{
		bytemp = read_byte(input);
		chtemp = bytemp.to_ulong();
		output << chtemp;
	}
}

void character_to_zero_one_file(ifstream& input, ofstream& output, int code_length)
{
	const int bitselect[8] = {1, 2, 4, 8, 16, 32, 64, 128};
	bool bit;
	char chtemp;
	int j = 0;
	input >> noskipws;
	input >> chtemp; // for endl after code_length
	while(!input.eof())
	{
		input >> chtemp;
		for(int i = 0; j < code_length && i < BYTELEN; i++, j++)
		{
			bit = bitselect[i] & chtemp;
			output << bit;	
		}
	}
}

void cezar(const char* file, int& key)
{
	ifstream input;
	ofstream output;
	input.open(file, ios::in);
	output.open(TEMP_FILE, ios::out | ios::trunc);
	char temp;
	input >> temp;
	input >> noskipws;
	while(!input.eof())
	{
		temp += key;
		output << temp;
		input >> temp;
	}
	input.close();
	output.close();
	copy_file(TEMP_FILE, file);
}

void decezar(const char* file, int& key)
{
	int return_key = - key;
	cezar(file, return_key);
}

void copy_file(const char* fromfile, const char* tofile)
{
	ifstream from;
	ofstream to;
	from.open(fromfile, ios::in);
	to.open(tofile, ios::out | ios::trunc);
	char temp;
	from >> noskipws;
	from >> temp;
	while(!from.eof())
	{
		to << temp;
		from >> temp;
	}
	from.close();
	to.close();
}

void append_file(const char* fromfile, const char* tofile)
{
	ifstream from;
	ofstream to;
	from.open(fromfile, ios::in);
	to.open(tofile, ios::app);
	char temp;
	from >> noskipws;
	from >> temp;
	while(!from.eof())
	{
		to << temp;
		from >> temp;
	}
	from.close();
	to.close();
}
