#include <stdio.h>

int length(char s[]) {
    int len = 0;
    while (s[len] != '\0') {
        len++;
    }
    return len;
}

void remove_newline(char str[]) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '\n') {
            str[i] = '\0';
            break;
        }
    }
}

void insertsub(char input[], char sub[], int pos, char res[]) {
    int i = 0, j = 0;

    while (i < pos) {
        res[i] = input[i];
        i++;
    }
    while (sub[j] != '\0') {
        res[i++] = sub[j++];
    }
    j = pos;
    while (input[j] != '\0') {
        res[i++] = input[j++];
    }
    res[i] = '\0';
}

void del_substring(char input[], char del[]) {
    int input_len = length(input);
    int del_len = length(del);
    int found = 0;

    for (int i = 0; i <= input_len - del_len; i++) {
        int match = 1;
        for (int j = 0; j < del_len; j++) {
            if (input[i + j] != del[j]) {
                match = 0;
                break;
            }
        }
        if (match) {
            found = 1;
            for (int k = i; k < input_len - del_len; k++) {
                input[k] = input[k + del_len];
            }
            input[input_len - del_len] = '\0';
            break;
        }
    }

    if (!found) {
        printf("Substring not found\n");
    }
}

int main() {
    char input[50];

    printf("Enter string: ");
    fgets(input, sizeof(input), stdin);
    remove_newline(input);

    printf("String entered is %s\n", input);
    printf("Length of the string is %d\n", length(input));

    char toadd[20];
    printf("Enter string to concatenate: ");
    fgets(toadd, sizeof(toadd), stdin);
    remove_newline(toadd);

    if (length(input) + length(toadd) < 49) {
        int i = 0;
        while (input[i] != '\0') {
            i++;
        }
        for (int j = 0; j < length(toadd); j++) {
            input[i++] = toadd[j];
        }
        input[i] = '\0';
        printf("Concatenated string %s\n", input);
    }
    else {
        char final[100];
        int i = 0;
        while (input[i] != '\0') {
            final[i] = input[i];
            i++;
        }
        int j = 0;
        while (toadd[j] != '\0') {
            final[i++] = toadd[j++];
        }
        final[i] = '\0';
        printf("Concatenated string %s\n", final);
    }

    char compare[50];
    printf("Enter string to compare: ");
    fgets(compare, sizeof(compare), stdin);
    remove_newline(compare);

    int i = 0;
    while (input[i] != '\0' && compare[i] != '\0') {
        if (input[i] > compare[i]) {
            printf("String 1 is bigger (higher ASCII value)\n");
            break;
        }
        else if (input[i] < compare[i]) {
            printf("String 1 is smaller (lower ASCII value)\n");
            break;
        }
        i++;
    }
    if(input[i]=='\0' && compare[i]=='\0'){
        printf("They are equal");
    }

    printf("Enter substring and position: ");
    char sub[50];
    int pos;
    char res[100];

    fgets(sub, sizeof(sub), stdin);
    remove_newline(sub);
    scanf("%d", &pos);
    getchar();

    if (pos < 0 || pos > length(input)) {
        printf("Invalid position! Using position 0.\n");
        pos = 0;
    }

    insertsub(input, sub, pos, res);
    printf("String after insertion %s\n", res);

    printf("Enter substring to delete: ");
    char del[50];

    fgets(del, sizeof(del), stdin);
    remove_newline(del);
    del_substring(res, del);
    printf("String after deletion %s\n", res);

    return 0;
}