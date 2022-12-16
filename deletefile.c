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
 Node_t* temp = dict[index]; //First node of the ith list
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
