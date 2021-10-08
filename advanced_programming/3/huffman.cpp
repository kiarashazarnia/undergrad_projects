#include "header.h"
#include "test.h"
#include <algorithm>

void set_letter_character(Letter& letter,  char& inserting_char)
{
    letter.character = inserting_char;
    letter.characterized = 1;
}

void set_letter_pointer_NULL(Letter& letter)
{
    letter.right = NULL;
    letter.left = NULL;
}

void set_letter_uncharacterized(Letter& letter)
{
    letter.characterized = 0;
}

void set_letter_iteration_zero(Letter& letter)
{
    letter.iteration = 0;
}

void set_letter_inserted_in_tree_zero(Letter& letter)
{
    letter.inserted_in_tree = 0;
}

int char_first_pos( char& searching_char)
{
	int pos = int(searching_char);
	return pos + CHARNUMBER/2;
}

bool is_char_in_its_first_pos_in_rapid_dic(RapidDic rapid_dic,  char& searching_char)
{
    int guessing_index = char_first_pos(searching_char);
    if(guessing_index > CHARNUMBER || guessing_index < CHARNUMBER)
    {
		return 0;
    }
    return rapid_dic[char_first_pos(searching_char)].character == searching_char;
}


bool is_char_in_its_first_pos( Dictionary& dictionary,  char& searching_char)
{
    int guessing_index = char_first_pos(searching_char);
    if(guessing_index > CHARNUMBER || guessing_index < CHARNUMBER)
    {
        return 0;
    }
    return dictionary[char_first_pos(searching_char)].character == searching_char;
}

bool is_char_in_its_first_pos(Letter* dictionary,  char& searching_char)
{
    int guessing_index = char_first_pos(searching_char);
    if(guessing_index > CHARNUMBER || guessing_index < CHARNUMBER)
    {
        #ifdef ERRORREP
            cerr<<"Error: char is out of dictionary."<<endl;
        #endif
        return 0;
    }
    return dictionary[char_first_pos(searching_char)].character == searching_char;
}

int search_character_pos_in_rapid_dic(RapidDic rapid_dic,  char& searching_char)
{
    if(is_char_in_its_first_pos_in_rapid_dic(rapid_dic, searching_char))
        return char_first_pos(searching_char);
    for(int i = 0; i < rapid_dic.size(); i++)
        if(rapid_dic[i].character == searching_char)
            return i;
    #ifdef ERRORREP
        cerr<<"Error: char not found."<<endl;
    #endif
    return rapid_dic.size();
}

int search_character_pos_in_dictionary(Dictionary& dictionary,  char& searching_char)
{
    if(is_char_in_its_first_pos(dictionary, searching_char))
        return char_first_pos(searching_char);
    for(int i = 0; i < dictionary.size(); i++)
        if(dictionary[i].character == searching_char)
            return i;
    #ifdef ERRORREP
        cerr<<"Error: char not found."<<endl;
    #endif
    return dictionary.size();
}

int search_character_pos_in_dictionary(Letter* dictionary,  char& searching_char)
{
    if(is_char_in_its_first_pos(dictionary, searching_char))
        return char_first_pos(searching_char);
    for(int i = 0; i < CHARNUMBER; i++)
        if(dictionary[i].characterized && dictionary[i].character == searching_char)
            return i;
    
    #ifdef ERRORREP
        cerr<<"Error: char not found."<<endl;
    #endif
    return NONE;
}

RapidLet search_letter_by_character(RapidDic& rapid_dic,  char& searching_char)
{
    int index = search_character_pos_in_rapid_dic(rapid_dic, searching_char);
    return rapid_dic[index];
}

void initial_dictionary(Dictionary& dictionary)
{
    char temp;
    for(int i = 0; i < CHARNUMBER; i++)
    {
		temp = i + CHARNUMBER/2;
        set_letter_character(dictionary[i], temp);
        set_letter_pointer_NULL(dictionary[i]);
        set_letter_iteration_zero(dictionary[i]);
        set_letter_inserted_in_tree_zero(dictionary[i]);
    }
}

Letter* initial_dictionary()
{
    Letter* root = new Letter[CHARNUMBER];
    char temp;
    for(int i = 0; i < CHARNUMBER; i++)
    {
        temp = char(i);
        set_letter_character(root[i], temp);
        set_letter_pointer_NULL(root[i]);
        set_letter_iteration_zero(root[i]);
        set_letter_inserted_in_tree_zero(root[i]);
    }
	return root;
}

void count_dictionary_iterations(Dictionary& dictionary, ifstream& file)
{
    char iterated_char;
    int iterated_letter_index;
	file >> noskipws;
	file >> iterated_char;
    while(!file.eof())
    {
        iterated_letter_index = search_character_pos_in_dictionary(dictionary, iterated_char);
        dictionary[iterated_letter_index].iteration++;
		file >> iterated_char;
    }
}

bool are_letters_dictionary( Dictionary& letters)
{
    return letters.size() == CHARNUMBER;
}

bool is_less_iterative(Letter& first,  Letter& second)
{
    return first.iteration < second.iteration;
}

bool is_less_rapid_letter( RapidLet& first,  RapidLet& second)
{
	return first.character < second.character;
}

bool is_most_iterative(Letter* greater, Letter* less)
{
    return greater -> iteration > less -> iteration;
}

void sort_by_iteration(Dictionary& dictionary)
{
    sort(dictionary.begin(), dictionary.end(), is_less_iterative);
}

void sort_by_iteration(Letter* dictionary)
{
    sort(dictionary , dictionary + CHARNUMBER, is_less_iterative);
}

void sort_by_character(RapidDic& rapid_dic)
{
    sort(rapid_dic.begin(), rapid_dic.end(), is_less_rapid_letter);
}

Letter* new_letter()
{
    Letter* new_let = new Letter;
    set_letter_uncharacterized(*new_let);
    set_letter_pointer_NULL(*new_let);
    set_letter_iteration_zero(*new_let);
    set_letter_inserted_in_tree_zero(*new_let);
    return new_let;
}


void initial_letter(Letter *new_let)
{
    set_letter_uncharacterized(*new_let);
    set_letter_pointer_NULL(*new_let);
    set_letter_iteration_zero(*new_let);
    set_letter_inserted_in_tree_zero(*new_let);
}

void merge_two_letters(Letter* parent_node, Letter *first, Letter *second)
{
    parent_node -> iteration = first -> iteration + second -> iteration;
    parent_node -> left = first;
    parent_node -> right = second;
}

bool all_characters_are_inserted(Dictionary& dictionary)
{
	int not_inserted = 0;
    for(int i = dictionary.size() - 1; i >= 0 && not_inserted < 2; i--)
	{
		if(!dictionary[i].inserted_in_tree)
            not_inserted++;
	}
	return not_inserted == 1;
}

void set_letters_child_inserted_in_tree(Letter* super_letter)
{
    super_letter -> left -> inserted_in_tree = 1;
    super_letter -> right -> inserted_in_tree = 1;
}

void set_letter_inserted_in_tree(Letter* letter)
{
    letter -> inserted_in_tree = 1;
}

Letter* less_iterative_from_pos( Dictionary& dictionary, int from_pos)
{
    int min_index = from_pos;
    int min_iteration = dictionary[from_pos].iteration;
    for(int i = from_pos;i < dictionary.size(); i++)
        if(min_iteration > dictionary[from_pos].iteration)
            min_index = i;
    return &dictionary[min_index];
}

Letter* less_iterative_not_inserted_from_pos( Dictionary& dictionary, int from_pos)
{
    int min_index, min_iteration;
    for(;from_pos < dictionary.size(); from_pos++)
    {
        if(!dictionary[from_pos].inserted_in_tree)
            break;
    }
    min_index = from_pos;
    min_iteration = dictionary[from_pos].iteration;
    for(int i = from_pos;i < dictionary.size(); i++)
    {
        if(dictionary[from_pos].inserted_in_tree)
            continue;
        if(min_iteration > dictionary[from_pos].iteration)
            min_index = i;
    }
    return dictionary[min_index].inserted_in_tree? NULL : &dictionary[min_index];
}

Letter* second_min( Dictionary& dictionary, int pos)
{
    if(dictionary.size() == CHARNUMBER)
        return &dictionary[pos+1];
    Letter* added_letters_min = less_iterative_not_inserted_from_pos(dictionary, CHARNUMBER);
    return less_iterative_not_inserted_of_two_letters(added_letters_min, &dictionary[pos+1]);
}

Letter* less_iterative_of_two_letters(Letter* first, Letter* second)
{
    if(!first)
        return second;
    if(!second)
        return first;
    return is_most_iterative(first, second)? second : first;
}

Letter* less_iterative_not_inserted_of_two_letters(Letter* first, Letter* second)
{
    if(is_most_iterative(first, second) && !second -> inserted_in_tree)
			return second;
	else if(!first -> inserted_in_tree)
			return first;
	return NULL;
}

Letter* min_iteration_from_pos(Dictionary& dictionary, int pos)
{
    int min_index, min_iteration;
    while(pos < dictionary.size())
    {
        if(!dictionary[pos].inserted_in_tree)
            break;
		pos++;
    }
    min_index = pos;
    min_iteration = dictionary[pos].iteration;
    for(int i = pos; i < dictionary.size(); i++)
    {
        if(dictionary[i].inserted_in_tree)
            continue;
        if(min_iteration > dictionary[i].iteration)
            min_index = i;
    }
    return dictionary[min_index].inserted_in_tree? NULL : &dictionary[min_index];
}

Letter* min_iteration_from_pos(Letter* dictionary, int pos, int size)
{
    int min_index, min_iteration;
    while(pos < size)
    {
        if(!dictionary[pos].inserted_in_tree)
            break;
		pos++;
    }
    min_index = pos;
    min_iteration = dictionary[pos].iteration;
    for(int i = pos; i < size; i++)
    {
         if(dictionary[i].inserted_in_tree)
            continue;
        if(min_iteration > dictionary[i].iteration)
            min_index = i;
    }
    return dictionary[min_index].inserted_in_tree? NULL : &dictionary[min_index];
}

int first_not_inserted_index(Dictionary& dictionary)
{
	for(int i = 0; i < dictionary.size(); i++)
		if(!dictionary[i].inserted_in_tree)
			return i;
	return NONE;
}

int min_iteration_not_inserted(Dictionary& dictionary)
{
	int min_iteration = first_not_inserted_index(dictionary);
	if(min_iteration == NONE)
		return NONE;
	for(int i = min_iteration + 1; i < dictionary.size(); i++)
	{
		if(dictionary[i].inserted_in_tree)
			continue;
		if(dictionary[i].iteration < dictionary[min_iteration].iteration)
			min_iteration = i;
	}
	return min_iteration;
}

void copy_letter(Letter* from, Letter* to)
{
    to -> characterized = from -> characterized;
    to -> character = from -> character;
    to -> inserted_in_tree = from -> inserted_in_tree;
    to -> right = from -> right;
    to -> left = from -> left;
    to -> iteration = from -> iteration;
    to -> huffman_code = from -> huffman_code;
}

void swap_letter(Letter* fst, Letter* snd)
{
    Letter* tmp = new_letter();
    copy_letter(fst, tmp);
    copy_letter(snd, fst);
    copy_letter(tmp, snd);
}

void swap_pointer(Letter** fst, Letter** snd)
{
    Letter* tmp = *fst;
    *fst = *snd;
    *snd = tmp;
}

int huffman_root(Dictionary& dictionary)
{
    for(int i = 0; i < dictionary.size(); i++)
        if(!dictionary[i].inserted_in_tree)
            return i;
	return NONE;
}

int form_huffman_tree(Dictionary& dictionary)
{
   	if(all_characters_are_inserted(dictionary))
		return huffman_root(dictionary);
    
	int first_min_iter = min_iteration_not_inserted(dictionary);
	set_letter_inserted_in_tree(&dictionary[first_min_iter]);
    int second_min_iter = min_iteration_not_inserted(dictionary);
	set_letter_inserted_in_tree(&dictionary[second_min_iter]);
    Letter super_letter;
   	super_letter.iteration = dictionary[first_min_iter].iteration + dictionary[second_min_iter].iteration;
    super_letter.left_index = first_min_iter;
    super_letter.right_index = second_min_iter;
	dictionary.push_back(super_letter);
    return form_huffman_tree(dictionary);
}

void assign_bitcode(BitCode& first, BitCode& second)
{
    first.assign(second.begin(), second.end());
}

void clean_bitcode(BitCode& dirty_bitcode)
{
    dirty_bitcode.erase(dirty_bitcode.begin(), dirty_bitcode.end());
}

void fill_huffman_code_in_rapid_dic_continue_from(Dictionary& dictionary, RapidDic& rapid_dic, int root_index, BitCode& huffman_code)
{
	if(root_index == NONE)
	{
		huffman_code.pop_back();
		return;
	}
	dictionary[root_index].huffman_code = new BitCode;
	*dictionary[root_index].huffman_code = huffman_code;
    #ifdef REPCODE
		test_print_bitcode(huffman_code);
    #endif
    if(dictionary[root_index].characterized)
    {
		RapidLet rapid_let;
		rapid_let.character = dictionary[root_index].character;
		rapid_let.huffman_code = huffman_code;
		rapid_dic.push_back(rapid_let);
		huffman_code.pop_back();
		return;
    }
    huffman_code.push_back(RIGHT);
	fill_huffman_code_in_rapid_dic_continue_from(dictionary, rapid_dic, dictionary[root_index].right_index, huffman_code);
	huffman_code.push_back(LEFT);
	fill_huffman_code_in_rapid_dic_continue_from(dictionary, rapid_dic, dictionary[root_index].left_index, huffman_code);
	huffman_code.pop_back();
	return;
}

void fill_huffman_code_in_rapid_dic(Dictionary& dictionary, RapidDic& rapid_dic, int root_index)
{
	BitCode empty;
    fill_huffman_code_in_rapid_dic_continue_from(dictionary, rapid_dic, root_index, empty);
}

void convert_huffman_to_character_by_tree(Letter* root,  BitCode& huff, char& character)
{
    Letter* let_finder = root;
    for(int i = 0;i < BYTELEN;i++)
    {
        if(let_finder == NULL)
        {
            #ifdef ERRORREP
                cerr<<"Error: huffman code not found in tree."<<endl;
            #endif
            break;
        }
        if(huff.at(i) == RIGHT)
            let_finder = let_finder -> right;
        else if(huff.at(i) == LEFT)
            let_finder = let_finder -> left;
    }
    if(let_finder -> characterized)
        character = let_finder -> character;
    else
    {
        #ifdef ERRORREP
            cerr<<"Error: found not characterized node."<<endl;
        #endif
    }     
}

void convert_character_to_huffman_by_rapid_dic(RapidDic& rapid_dic, char& character, BitCode& huff)
{
    clean_bitcode(huff);
    RapidLet let = search_letter_by_character(rapid_dic, character);
    assign_bitcode(huff, let.huffman_code);
}

void make_huffman_code(Dictionary& dictionary, RapidDic& rapid_dic, ifstream& input)
{
	initial_dictionary(dictionary);
	count_dictionary_iterations(dictionary, input);
	int root_index = form_huffman_tree(dictionary);
	fill_huffman_code_in_rapid_dic(dictionary, rapid_dic, root_index);
	sort_by_character(rapid_dic);
	#ifdef TEST
		test_print_rapid_dic(rapid_dic);
	#endif
}

void write_bitcode(BitCode& bitcode, ofstream& output)
{
	for(int i = 0; i < bitcode.size(); i++)
		output << bitcode.at(i);
}

void make_file_8multip(char* filename)
{
	ofstream output;
	ifstream input;
	input.open(filename, ios::in);
	input.seekg(ZERO, ios::end);
	int length = input.tellg();
	input.close();
	int unit = BYTELEN;
	output.open(filename, ios::app);
	for(int i = 0; i < unit - length % unit; i++)
		output<<ZERO;
	output.close();
}

void write_rapid_dic(RapidDic& rapid_dic, ofstream& output)
{
	for(int i = 0; i < CHARNUMBER; i++)
	{
		write_bitcode(rapid_dic[i].huffman_code, output);
		output << SPACE;
	}
}

long long length_of_file(char* filename)
{
	long long length;
	ifstream input;
	input.open(filename, ios::in);
	input.seekg(ZERO, input.end);
	length = input.tellg();
	input.close();
	return length;
}

void fill_huffman_code_in_rapid_dic(RapidDic& rapid_dic, ifstream& input)
{
	char temp;
	for(int i = 0; i < CHARNUMBER; i++)
	{
		input.read(&temp, sizeof(temp));
		rapid_dic[i].character = i + CHARNUMBER/2;
		while(temp != SPACE)
		{
			if(temp == ONECH)	
				rapid_dic[i].huffman_code.push_back(ONE);
			else
				rapid_dic[i].huffman_code.push_back(ZERO);
			input.read(&temp, sizeof(temp));
		}
	}
}

bool search_in_rapid_dic(RapidDic& rapid_dic, BitCode& huffman_code, char& character)
{
	for(int i = 0; i < CHARNUMBER; i++)
		if(rapid_dic[i].huffman_code == huffman_code)
		{
			character = rapid_dic[i].character;
			return 1;
		}
	return 0;
}

void compress_only(const char* inputname, const char* outputname)
{
	Dictionary dictionary(CHARNUMBER);
	RapidDic rapid_dic;
	ifstream input;
	ofstream output;
	char character;
    BitCode huffman_code;
	long long code_length;
    input.open(inputname, ios::in);
	make_huffman_code(dictionary, rapid_dic, input);
    output.open(TEMP_FILE, ios::out | ios::trunc);
	input.clear();
	input.seekg(ZERO);
	input >> noskipws;
	input >> character;
    while(!input.eof())
    {
	convert_character_to_huffman_by_rapid_dic(rapid_dic, character, huffman_code);
	write_bitcode(huffman_code, output);
	input >> character;
    }
	output.close();
	code_length = length_of_file(TEMP_FILE);
	make_file_8multip(TEMP_FILE);
	input.close();
	input.open(TEMP_FILE, ios::in);
	output.open(outputname, ios::out | ios::trunc);
	write_rapid_dic(rapid_dic, output);
	output << code_length << endl;
	characterize_zero_one_file(input, output);
	input.close();
	output.close();
	remove(TEMP_FILE);
}

void decompress_only(const char* input_file_name, const char* output_file_name)
{
	bool found;
	Dictionary dictionary(CHARNUMBER);
	RapidDic rapid_dic(CHARNUMBER);
	ifstream input;
	ofstream output;
	char character;
    BitCode huffman_code;
	int code_length;
	input.open(input_file_name, ios::in);
	fill_huffman_code_in_rapid_dic(rapid_dic, input);
	sort_by_character(rapid_dic);
	input >> code_length;
	output.open(TEMP_FILE, ios::out);
	character_to_zero_one_file(input, output, code_length);
	input.close();
	output.close();
	input.open(TEMP_FILE, ios::in);
	output.open(output_file_name, ios::out);
	while(true)
	{
		found = 0;
		clean_bitcode(huffman_code);
		while(!found)
		{
			input >> character;
			if(character == ONECH)
				huffman_code.push_back(ONE);
			else
				huffman_code.push_back(ZERO);
			found = search_in_rapid_dic(rapid_dic, huffman_code, character);
			if(input.eof())
				break;
		}
		if(!found)
			break;
		output << character;
	}
	input.close();
	output.close();
	remove(TEMP_FILE);
}