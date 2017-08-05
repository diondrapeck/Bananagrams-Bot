#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
 
#define ARRAY_SIZE(a) sizeof(a)/sizeof(a[0])
#define ALPHABET_SIZE (26)
#define CHAR_TO_INDEX(c) ((int)c - (int)'a') // Converts key current character into index (only 'a' through 'z' and lower case)
 
struct trieNode
{
    struct trieNode *letters[ALPHABET_SIZE];
    bool isWord;
};
 
// Returns new trie node (initialized to NULLs)
struct trieNode *newNode(void)
{
    struct trieNode *pNode = NULL;
 
    pNode = (struct trieNode *)malloc(sizeof(struct trieNode));
 
    if (pNode)
    {
        int i;
 
        pNode->isWord = false;
 
        for (i = 0; i < ALPHABET_SIZE; i++)
            pNode->letters[i] = NULL;
    }
 
    return pNode;
}
 
// If not present, inserts word into trie
// If the word is prefix of trie node, just marks leaf node
int insert(struct trieNode *root, const char *key)
{
    int level;
    int index;
    int length = strlen(key);
    
    if (length < 2) {
        printf("All words must be at least two letters long.\n");
        return 1;
    }
 
    struct trieNode *pCrawl = root;
 
    for (level = 0; level < length; level++)
    {
        index = CHAR_TO_INDEX(key[level]);
        if (!pCrawl->letters[index])
            pCrawl->letters[index] = newNode();
 
        pCrawl = pCrawl->letters[index];
    }
 
    // mark last node as a word
    pCrawl->isWord = true;
    
    // add word to words.txt
    FILE *f = fopen("words.txt", "a");
    
    if (f == NULL)
    {
        printf("Error opening file!\n");
        return 1;
    }
    else {
        fprintf(f, " %s", key);
        printf("Added %s to game dictionary!\n", key);
		fclose(f);
    }
    
    return 0;
}
 
// Returns true if word is present in trie, else false
bool search(struct trieNode *root, const char *key)
{
    int level;
    int length = strlen(key);
    int index;
    struct trieNode *pCrawl = root;
 
    for (level = 0; level < length; level++)
    {
        index = CHAR_TO_INDEX(key[level]);
 
        if (!pCrawl->letters[index])
            return false;
 
        pCrawl = pCrawl->letters[index];
    }
 
    return (pCrawl != NULL && pCrawl->isWord);
}
 

int main()
{
    // Populate dictionary
    struct trieNode *root = newNode();

	FILE *f = fopen("words.txt", "r");
    const char str[25];
    int c;

    if (f != NULL) {
        while ((c = fgetc(f)) != EOF) {
        	fscanf(f, "%s", str);
        	printf("%s\n", str);
        	insert(root, str);
        }
        
        fclose(f);
    }

    // Test functionality
    char output[][32] = {"Not present in trie", "Present in trie"};

    printf("%s --- %s\n", "zip", output[search(root, "zip")] );
    printf("%s --- %s\n", "these", output[search(root, "these")] );
    printf("%s --- %s\n", "uncle", output[search(root, "uncle")] );
    printf("%s --- %s\n", "crush", output[search(root, "crush")] );
    printf("%s --- %s\n", "kitten", output[search(root, "kitten")] );

	insert(root, "kitten");
	
	printf("%s --- %s\n", "kitten", output[search(root, "kitten")]);
 
    return 0;
}