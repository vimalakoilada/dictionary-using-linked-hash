#include <iostream>
#include <stdio.h>
#include <string.h>

#define FILENAME "dict.dat"

typedef struct 
{
	char word[20];
	char meaning[100];
}WordMeaning;

typedef struct Node
{
	WordMeaning data;
	Node* link;
}Node_t;

Node_t* dict[26];	//Header nodes one list for each word.

Node_t* insertOrder(Node_t* first, WordMeaning ele)
{
	Node_t* newnode = (Node_t*)malloc(sizeof(Node_t));
    
	if (newnode == NULL)
	{
		return NULL;
	}
	newnode->data = ele;
	newnode->link = NULL;
	if (first == NULL)
		first = newnode;
	else if (strcmp(ele.word , first->data.word) < 0)
	{
		newnode->link = first;
		first = newnode;
	}
	else
	{
		Node_t* temp = first;
		Node_t* prev = first;
		while (temp != NULL && strcmp(temp->data.word , ele.word) <= 0)
		{
			prev = temp;
			temp = temp->link;
		}
		prev->link = newnode;
		newnode->link = temp;
	}
	return first;
}


void load_dictionary()
{
	FILE* fp = NULL;
	fp=fopen(FILENAME, "rb");	//Need to change this line if working with gcc
	if (fp == NULL)
	{
		//File does not exist, create new file.
		printf("Dictionary file does not exist..., creating new file \n");
		fp=fopen(FILENAME, "wb");
		if (fp == NULL) {
			fprintf(stderr, "Unable to open file... ");
			exit(EXIT_FAILURE);
		}
	}
	WordMeaning	record;
	while (fread(&record, sizeof(record), 1, fp) != 0)
	{
		//get the first character of word
		char firstChar = toupper(record.word[0]);
		int index = firstChar - 'A';
		dict[index] = insertOrder(dict[index], record);
	}
	fclose(fp);
}

void display(Node_t *first)
{
	Node_t* temp = first;
	//printf("%p-->" , temp);
	while (temp != NULL)
	{
		printf("[%10s	%20s] \n", temp->data.word, temp->data.meaning);
		temp = temp->link;
	}
}
void addWordToDict()
{
	WordMeaning	record;
	printf("Adding new word to Dictionary \n");
	printf("Enter the word : ");
	scanf(" %s", record.word);
	
	printf("Enter the meaing : ");
	//std::cin.getline(record.meaning , 100);	//100 is the size of meaning.
	scanf(" %s", record.meaning);
	char firstChar = toupper(record.word[0]);
	int index = firstChar - 'A';
	dict[index] = insertOrder(dict[index], record);
}
void save_dictionary()
{
	FILE* fp = NULL;
	fp=fopen(FILENAME, "wb");	
	if (fp != NULL) {
		for (int i = 0; i < 26; i++)
		{
			Node_t* temp = dict[i];
			while (temp != NULL)
			{
				fwrite(&(temp->data), sizeof(WordMeaning), 1, fp);
				temp = temp->link;
			}
		}
		fclose(fp);
	}
}
Node_t* search(Node_t* first,const char *wordToSearch)
{
	Node_t* temp = first;
	while (temp != NULL)
	{
		if (strcmp(temp->data.word, wordToSearch) == 0)
			break;
		temp = temp->link;
	}
	return temp;
}
void deleteWord(const char* wordToDelete)
{
	char firstChar = toupper(wordToDelete[0]);
	int index = firstChar - 'A';

	Node_t *ptr = search(dict[index] , wordToDelete);
	if (ptr != NULL)
	{
		printf("%s %s \n", ptr->data.word, ptr->data.meaning);
		if (ptr == dict[index])
		{
			dict[index]->link = dict[index]->link->link;
		}
		else
		{
			Node_t* temp = dict[index];	//First node of the ith list
			while (temp->link != ptr)
			{
				temp = temp->link;
			}
			temp->link = ptr->link;
			
		}
	}
	else
	{
		printf("No Such word \n");
	}
}
int main()
{
	load_dictionary();	// Load the current words in dictionary.
	printf("Existing words in Dictionary \n");
	for (int i = 0; i < 26; i++)
	{
		display(dict[i]);
	}

	for(int i = 0 ; i < 2 ; i++)
		addWordToDict();

	for (int i = 0; i < 26; i++)
	{
		display(dict[i]);
	}

	char wordToDelete[20];
	printf("Enter the word to delete \n");
	std::cin >> wordToDelete;
	deleteWord(wordToDelete);	//Delete a word from Dictionary.
	
	for (int i = 0; i < 26; i++)
	{
		display(dict[i]);
	}
	save_dictionary();
}



