#include <stdio.h>
#include <string.h>

void edit_line(char* buffer, int current_line) {
    char* ptr = buffer;
    for (int i = 0; i < current_line; i++) {
        ptr = strchr(ptr, '\n');
        if (!ptr) return;  
        ptr++;
    }


    char* line_end = strchr(ptr, '\n');
    if (!line_end) line_end = ptr + strlen(ptr);


    char saved[1024] = {0};
    strcpy(saved, line_end);

    printf("Enter new text: ");
    fgets(ptr, (int)(line_end - ptr + 1), stdin);  
    ptr[strcspn(ptr, "\n")] = '\0'; 

    strcat(ptr, "\n");
    strcat(ptr, saved);
}

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    FILE* f = fopen(argv[1], "r");
    if (!f) {
        perror("File open failed");
        return 1;
    }

    char buffer[1024] = {0};
    fread(buffer, 1, sizeof(buffer) - 1, f);
    fclose(f);

    printf("Contents:\n%s\n", buffer);

    int current_line = 0;
    printf("Enter line number to edit (0-based): ");
    scanf("%d", &current_line);
    getchar();

    edit_line(buffer, current_line);

    f = fopen(argv[1], "w");
    if (!f) {
        perror("File write failed");
        return 1;
    }
    fwrite(buffer, 1, strlen(buffer), f);
    fclose(f);

    printf("Updated contents:\n%s\n", buffer);
    return 0;
}
