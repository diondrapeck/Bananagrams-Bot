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
    // Initialize an array of words
    char words[][77] = {"an", "apple", "acorn", "bye", "baby", "bubble", 
	"candy", "crush", "cat", "dad", "dead", "day", "end", "earth", "eye"
	"feel", "form", "fate", "god", "game", "gift", "head", "he", "hat",
    "is", "ice", "idea", "jump", "juice", "jeans", "kite", "kick",
    "lemon", "lame", "look", "man", "me", "mean", "new", "no", "note", "open",
    "old", "onion", "peel", "pop", "pea", "quiet", "quick", "qi", "rest", 
    "run", "rum", "see", "song", "settle", "talk", "time", "tabulate", "under",
    "uncle", "us", "very", "voter", "vibe", "we", "welcome", "weekend", 
    "xylophone", "xylem", "you", "yellow", "yes", "zoo", "zoom", "zip"};
 
    struct trieNode *root = newNode();
 
    // Populate dictionary 
    int i;
    for (i = 0; i < ARRAY_SIZE(words); i++)
        insert(root, words[i]);
 
    // Test functionality
    char output[][32] = {"Not present in trie", "Present in trie"};

    printf("%s --- %s\n", "zip", output[search(root, "zip")] );
    printf("%s --- %s\n", "these", output[search(root, "these")] );
    printf("%s --- %s\n", "uncle", output[search(root, "uncle")] );
    printf("%s --- %s\n", "kitten", output[search(root, "kitten")] );
	
	insert(root, "a");
	insert(root, "kitten");
	
	printf("%s --- %s\n", "kitten", output[search(root, "kitten")]);
 
    return 0;
}
