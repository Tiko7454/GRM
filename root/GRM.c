// C program to create loading bar
#include <stdio.h>
#include <string.h>
#include <windows.h>

// Function to creating loading bar
void loadingBar(){
  
    // Initialize char for printing
    // loading bar
    char a = '.', b = '*';
    printf("[");
  
    // Print initial loading bar
    for (int i = 0; i < 26; i++)
        printf("%c", a);
    printf("]");
  
    // Set the cursor again starting
    // point of loading bar
    printf("\r");
    printf("[");
    // Print loading bar progress
    for (int i = 0; i < 26; i++) {
        printf("%c", b);
    }
}

int is_link(char* x){
    if(strlen(x) < 8)
        return 0;
    char prefix[9];
    for(int i = 0; i < 8; i++)
        prefix[i] = x[i];
    return strcmp(prefix, "https://") == 0;
}

// Syntax
// grm install ...
int main(int argc, char** argv){
    char github_prefix[100] = "https://github.com/"
	char clone[100] = "git clone ";
	char* pull = "git pull";
	char* mode = argv[1];
	if(strcmp(mode, "install") == 0){
    	strcat(clone, argv[2]);
    	system(clone);
	}
    return 0;
}
