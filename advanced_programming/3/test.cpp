#include "header.h"
#include "test.h"
#include <cstdlib>

void test()
{
    
}

void test_print_bitcode_of_letter(Letter* root)
{
    if(root -> characterized)
	{
	    cout<<root -> character<<" "<<root -> iteration;
		test_print_bitcode(*(root -> huffman_code));
	}
}

void test_print_iterateds(Dictionary& dictionary)
{
    for(int i = 0;i < CHARNUMBER;i++)
    {
        if(dictionary[i].iteration == 0)
            continue;
        else
            cout<<dictionary[i].character<<" "<<dictionary[i].iteration<<endl;
    }
}

void test_print_dictionary(Dictionary& dictionary)
{
    for(int i = 0; i < dictionary.size(); i++)
    {
        cout<<"let "<<i<<"#"<<endl;
        test_print_letter(dictionary[i]);
        cout<<endl;
    }
}

void test_print_letter(Letter& let)
{
    cout<<"tree: "<<let.inserted_in_tree<<"\tcharacterized: "<<let.characterized;
    
    if(let.characterized)
    cout<<"\tcharacter: "<<let.character<<"\t";
    else
    cout<<"           "<<"\t";
    
    cout<<"iter:\t"<<let.iteration<<endl;
}

void test_print_bitcode(BitCode bitcode)
{
    for(int i = 0; i < bitcode.size(); i++)
        cout<<bitcode.at(i);
    cout<<endl;
}

void test_char_first_pos()
{
	char c= -128;
	do
	{
		cout<<" "<<int(c)<<" "<<char_first_pos(c)<<" "<<c<<endl;
		c++;
	}while(c!=-128);
}


void test_print_rapid_let(RapidLet &let)
{
    cout<<"char: "<<let.character<<endl;
	test_print_bitcode(let.huffman_code);
	cout<<endl;
}

void test_print_rapid_dic(RapidDic &rapid_dic)
{
	for(int i = 0;i < rapid_dic.size();i++)	
		test_print_rapid_let(rapid_dic[i]);
}

bool test_validate_nodes(Dictionary& dictionary)
{
	bool valid = 1;
	for(int i = 0; i < dictionary.size(); i++)
	{
		valid &= (!dictionary.at(i).characterized && dictionary.at(i).right && dictionary.at(i).left) ||
				  (dictionary.at(i).characterized && !dictionary.at(i).right && !dictionary.at(i).left);
		if(!valid)
			break;
	}
	return valid;
}

void test_print_not_inserted(Dictionary& dictionary)
{
	for(int i = 0; i < dictionary.size(); i++)
	{
		if(!dictionary.at(i).inserted_in_tree)
			cout<<i<<" not_inserted"<<endl;
	}
}

void test_print_tree(Letter *root)
{
	if(!root)
		return;
	test_print_letter(*root);
	test_print_tree(root -> right);
	test_print_tree(root -> left);
}

bool test_invalid_pointer(Letter* let, int& level)
{
	if(let -> right == NULL && let -> right == NULL && let -> characterized)
		return 1;
	return test_invalid_pointer(let -> right, ++level) && test_invalid_pointer(let -> left, ++level);
}

bool test_invalid_pointer(Letter* let, int& level, int& index)
{
	if(let -> right == NULL && let -> right == NULL && let -> characterized)
		return 1;
	return test_invalid_pointer(let -> right, ++level, index) && test_invalid_pointer(let -> left, ++level, index);
}