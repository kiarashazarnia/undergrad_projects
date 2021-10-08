#include "header.h"

long long sdbm(const char* filename)
{
	ifstream input;
	input.open(filename, ios::in);
	char temp;
	long long hash = ZERO;
	input >> temp;
	while(!input.eof())
	{
		hash = temp + (hash << 6) + (hash << 12) - hash;
		input >> temp;
	}
	input.close();
	return hash;
}

void hash_sdbm(const char* filename)
{
	ofstream output;
	long long hash = sdbm(filename);
	copy_file(filename, TEMP_FILE);
	output.open(filename, ios::out | ios::trunc);
	output << hash << endl;
	output.close();
	append_file(TEMP_FILE, filename);
}

long long read_hash(const char* filename)
{
	ifstream input;
	long long hash;
	input.open(filename, ios::in);
	input >> hash;
	input.close();
	return hash;
}

void remove_hash_n_copy(const char* fromfile, const char* tofile)
{
	ifstream from;
	ofstream to;
	char temp;
	from.open(fromfile, ios::in);
	to.open(tofile, ios::out | ios::trunc);
	from >> noskipws;
	from >> temp;
	while(temp != '\n')
		from >> temp;
	from >> temp;
	while(!from.eof())
	{
		to << temp;
		from >> temp;
	}
	from.close();
	to.close();
}