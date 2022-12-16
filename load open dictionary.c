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
