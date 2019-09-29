#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include "dictionary.h"

void print_hash_table(hashmap_t hash_table[]) {

    for (int i=0; i<HASH_SIZE; i++) {
		fprintf(stdout, "Bucket %d ===========\n", i);
		//hashmap_t probe_head = hash_table[1999];
		if ( hash_table[i] != NULL) {
			hashmap_t probe_head = hash_table[i];
			do {
				fprintf(stdout,"%s->", probe_head->word);
				probe_head = probe_head -> next;
			} while(probe_head->next != NULL);
			fprintf(stdout,"%s\n", probe_head->word);
			fflush(stdout);
			free(probe_head);
		} else {
			fprintf(stdout,"Bucket is empty\n");
		}
		fflush(stdout);
    }
}

void print_bucket(int bucket, hashmap_t hashtable[]) {
	hashmap_t temp = hashtable[bucket];
	if (temp != NULL) {
		do {
			fprintf(stdout,"%s->", temp->word);
			temp = temp -> next;
		} while(temp->next != NULL);
		fprintf(stdout,"%s\n", temp->word);
	} else {
		fprintf(stdout,"Bucket is empty");
	}
	
}

int check_words(FILE* fp, hashmap_t hashtable[], char * misspelled[]) {

	int result = EXIT_SUCCESS;
	return result;
}

bool check_word(const char* word, hashmap_t hashtable[]) {

	bool valid_word = true;

	return valid_word;
}

// Load into the hash dictionary
bool load_dictionary(const char* dictionary_file, hashmap_t hashtable[]) {

	bool load = false;
	FILE *dictionary = fopen(dictionary_file, "r");
	if ( dictionary == NULL ) {
		perror( "Dictionary file error" );
		return load;
	}
	for (int i=0; i< HASH_SIZE; i++) {
		hashtable[i] = NULL;
	}
	int max_buffer_size = LENGTH + 1;
	bool read_dictionary = true;
	int highest_bucket = 0;
	int word_count = 0;
	do {
		char buffer[max_buffer_size];
		while( fgets(buffer, max_buffer_size, dictionary) != NULL ) {
			word_count++;
			//buffer[strlen(buffer) - 1] = '\0';
			//fprintf(stdout, "%s\n", buffer);
			char *word = (char *)malloc(sizeof(strlen(buffer)));
			memcpy(word, buffer, strlen(buffer) + 1);
			word[strlen(word) - 1] = '\0';
			// fprintf(stdout, "%s\n", buffer);
			for (int loop=0; loop<strlen(word); loop++) {
				word[loop] = tolower(word[loop]);
			}
			int bucket_number = hash_function(word);
			if (bucket_number > highest_bucket)
				highest_bucket = bucket_number;
			// fprintf(stdout, "%s %d\n", buffer, bucket_number);
			int linked_list_pos = 0;
			hashmap_t probe_head = hashtable[bucket_number];
			if (probe_head != NULL) {
				// Append Node to end of the list when bucket is not empty
				while (probe_head->next != NULL) {
					//fprintf(stdout, "%s ->", probe_head->word);
					probe_head = probe_head->next;
					linked_list_pos++;
				}
				hashmap_t new_node = (node *)malloc(sizeof(node));
				new_node->next = NULL;
				//memcpy(probe_head->word, word, strlen(buffer));
				snprintf(new_node->word,sizeof(new_node->word),"%s", word);
				probe_head->next = new_node;
			} else {
				// Insert word into an empty bucket
				hashtable[bucket_number] = (node *)malloc(sizeof(node));
				hashtable[bucket_number]->next = NULL;
				snprintf(hashtable[bucket_number]->word,sizeof(hashtable[bucket_number]->word),"%s", word);
				//memcpy(probe_head->word, buffer, strlen(buffer));
			}
			fprintf(stdout, "%s %d %d\n", word, bucket_number, linked_list_pos);
			free(word);
		}
		fprintf(stdout, "Words counted %d\n", word_count);
		fprintf(stdout, "Highest bucket number %d\n", highest_bucket);
		fprintf(stdout, "Debug: read dictionary changed\n");
		read_dictionary = false;
	} while(read_dictionary);
	
	//print_bucket(802, hashtable);
	print_hash_table(hashtable);

	fprintf(stdout, "Debug: maximum Buffer size: %d\n", max_buffer_size);

	// if ( fclose(dictionary) != 0) {
	// 	perror("Dictionary closing error");
	// }
	load = true;
	return load;
}


