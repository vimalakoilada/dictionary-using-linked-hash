void save_dictionary()
{
	FILE* fp = NULL;
	fp = fopen(FILENAME, "wb");	
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
