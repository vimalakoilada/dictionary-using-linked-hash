void addWordToDict()
{
	WordMeaning	record;
	printf("Adding new word to Dictionary \n");
	printf("Enter the word : ");
	scanf(" %s", record.word);
	
	printf("Enter the meaing : ");
	std::cin.getline(record.meaning);	//100 is the size of meaning.
	scanf(" %s", record.meaning);
	char firstChar = toupper(record.word[0]);
	int index = firstChar - 'A';
	dict[index] = insertOrder(dict[index], record);
}