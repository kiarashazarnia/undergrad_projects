#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cassert>
#include <bitset>
#define ERRORREP
//#define REPMERG
//#define REPCODE
//#define TEST

using namespace std;

//******************** program flow ********************

enum Command
{
    Encode = 0,
    Decode = 1,
    CompressOnly = 2,
    DecompressOnly = 3,
    Invalid = 99
};

#define ENCODE "encode"
#define DECODE "decode"
#define COMP "compress_only"
#define DECOMP "decompress_only"
#define TEMP_FILE "temp.txt"
#define HELP_FILE "help.txt"

typedef vector<string> CommandLine;

void represent_array_in_string(char* char_pointer, string& word);
void represent_command_line_to_string(int argc, char** argv, CommandLine& command_line);
Command what_commanded(string& command_name);

//******************** cezar ********************
#define ZEROCH '0'
#define ONECH '1'
#define SPACE ' '

typedef bitset<8> Byte;
Byte read_byte(ifstream& input);
void copy_file(const char* fromfile, const char* tofile);
void append_file(const char* fromfile, const char* tofile);
void characterize_zero_one_file(ifstream& input, ofstream& output);
void character_to_zero_one_file(ifstream& input, ofstream& output, int code_length);
void cezar(const char* file, int& key);
void decezar(const char* file, int& key);

//******************** huffman ********************
#define CHARNUMBER 256
#define RIGHT 1
#define LEFT 0
#define BYTELEN 8
#define NONE -1
#define ZERO 0
#define ONE 1

typedef vector<bool> BitCode;

struct Letter
{
	Letter(): inserted_in_tree(0), characterized(0), character('0'), iteration(ZERO), huffman_code(NULL),right_index(NONE), left_index(NONE){}
    bool inserted_in_tree;
    bool characterized;
    char character;
    int iteration;
    BitCode* huffman_code;
    int right_index;
    int left_index;
	Letter* right;
	Letter* left;
};

struct RapidLet
{
    char character;
    BitCode huffman_code;
};

typedef vector<Letter> Dictionary;
typedef vector<RapidLet> RapidDic;

long long length_of_file(char* filename);
void write_rapid_dic(RapidDic& rapid_dic, ofstream& output);
void clean_bitcode(BitCode& dirty_bitcode);
void assign_bitcode(BitCode& first, BitCode& second);
void set_letter_character(Letter& letter, char& inserting_char);
void set_letter_uncharacterized(Letter& letter);
void set_letter_iteration_zero(Letter& letter);
void set_letter_inserted_in_tree_zero(Letter& letter);
int char_first_pos(char& searching_char);
bool is_char_in_its_first_pos(Dictionary& dictionary, char& searching_char);
bool is_char_in_its_first_pos_in_rapid_dic(RapidDic rapid_dic, char& searching_char);
int search_character_pos_in_dictionary(Dictionary& dictionary, char& searching_char);
int search_character_pos_in_rapid_dic(RapidDic rapid_dic, char& searching_char);
Letter search_letter_by_character(Dictionary& dictionary, char& searching_char);
RapidLet search_letter_by_character(RapidDic& rapid_dic, char& searching_char);
void initial_dictionary(Dictionary& dictionary);
Letter* initial_dictionary();
void count_dictionary_iterations(Dictionary& dictionary, ifstream& file);
bool are_letters_dictionary(Dictionary& letters);
bool is_less_iterative(Letter& first,  Letter& second);
bool is_less_rapid_letter(RapidLet& first,  RapidLet& second);
bool is_most_iterative(Letter* greater, Letter* less);
void sort_by_iteration(Dictionary& dictionary);
void sort_by_iteration(Letter* dictionary);
void sort_by_character(RapidDic& rapid_dic);
Letter* new_letter();
void initial_letter(Letter* new_let);
void merge_two_letters(Letter* parent_node, Letter *first, Letter *second);
bool all_characters_are_inserted(Dictionary& dictionary);
void set_child_letters_inserted_in_tree(Letter* super_letter);
Letter* less_iterative_from_pos( Dictionary& dictionary, int from_pos);
Letter* less_iterative_not_inserted_from_pos( Dictionary& dictionary, int from_pos);
Letter* second_min( Dictionary& dictionary, int pos);
Letter* less_iterative_of_two_letters( Letter* first,  Letter* second);
Letter* less_iterative_not_inserted_of_two_letters(Letter* first, Letter* second);
int form_huffman_tree(Dictionary& dictionary);
void fill_huffman_code_in_rapid_dic_continue_from(Dictionary& dictionary, RapidDic& rapid_dic, int root_index, BitCode& huffman_code);
void fill_huffman_code_in_rapid_dic(Dictionary& dictionary, RapidDic& rapid_dic, int root_index);
void fill_huffman_code_in_rapid_dic(RapidDic& rapid_dic, ifstream& input);
void convert_character_to_huffman_by_rapid_dic(RapidDic& rapid_dic, char& character, BitCode& huff);
void convert_huffman_to_character_by_tree(Letter* root,  BitCode& huff, char& character);
void make_huffman_code(Dictionary& dictionary, RapidDic& rapid_dic, ifstream& input);
void write_bitcode(BitCode& bitcode, ofstream& output);
void make_file_8multip(char* filename);
bool search_in_rapid_dic(RapidDic& rapid_dic, BitCode& huffman_code, char& character);
void compress_only(const char* inputname, const char* outputname);
void decompress_only(const char* input_file_name, const char* output_file_name);

//******************** hash ********************
long long sdbm(const char* filename);
void hash_sdbm(const char* filename);
long long read_hash(const char* filename);
void remove_hash_n_copy(const char* fromfile, const char* tofile);
//******************** lz77 ********************
//******************** test ********************
void test_print_letter( Letter& let);
void test_print_dictionary( Dictionary& dictionary);
