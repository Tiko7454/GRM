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

// Driver Code
int main(int argc, char** argv){
	char clone[100] = "git clone ";
	char* pull = "git pull";
	char* mode = argv[1];
	if(strcmp(mode, "install") == 0){
    	strcat(clone, argv[2]);
    	system(clone);
	}
    return 0;
}
