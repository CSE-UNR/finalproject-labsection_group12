//Author Isshin Furue
//This time I do not have a group partner due to the fact that my partner had not attended the Lab in the last 2 times. 
//So everythings were completed by myself. Although one of the 1101 Lab TA said that the collaboration part I will be 0 point, 
//I have talked with Erin, she said that do not have any penalty will happen. 
//And regarding the final project, the point of the lab section of Lab 11 - Final Group Project and Lab 12 - Checkpoint Demo will be adjusted.

#include <stdbool.h>
#include <stdio.h>




#define MAX_IMAGE_SIZE 100




char image[MAX_IMAGE_SIZE][MAX_IMAGE_SIZE];

int rows = 0;

int cols = 0;




void load_image();

void display_image();

void edit_image();

void save_image();

void exit_program();

void crop();

void dim();

void brighten();

void rotate();  




int main() {

    bool running = true;

    int choice;

    

    while (running) {

        printf("\nMain Menu:\n");

        printf("1. Load a new image\n");

        printf("2. Display the current image\n");

        printf("3. Edit the current image\n");

        printf("4. Exit the program\n");

        printf("Enter your choice: ");

        scanf("%d", &choice);




        switch (choice) {

            case 1:

                load_image();

                break;

            case 2:

                display_image();

                break;

            case 3:

                edit_image();

                break;

            case 4:

                exit_program();

                running = false;

                break;

            default:

                printf("Invalid choice, please try again.\n");

        }

    }

    return 0;

}




void load_image() {

    char filename[256];

    printf("Enter filename to load: ");

    scanf("%s", filename);

    FILE *file = fopen(filename, "r");

    if (!file) {

        printf("File could not be opened.\n");

        return;

    }

    char line[MAX_IMAGE_SIZE];

    rows = 0;

    while (fgets(line, sizeof(line), file) && rows < MAX_IMAGE_SIZE) {

        sscanf(line, "%s", image[rows]);

        if (rows == 0) {

            cols = strlen(image[0]);

        }

        rows++;

    }

    fclose(file);

    printf("Image loaded successfully.\n");

}




void display_image() {

    if (rows == 0) {

        printf("No image loaded.\n");

        return;

    }

    for (int i = 0; i < rows; i++) {

        printf("%s\n", image[i]);

    }

}




void edit_image() {

    int choice;

    printf("\nEdit Menu:\n");

    printf("1. Crop\n");

    printf("2. Dim\n");

    printf("3. Brighten\n");

    printf("4. Rotate (Extra Credit)\n");

    printf("Enter your choice: ");

    scanf("%d", &choice);




    switch (choice) {

        case 1:

            crop();

            break;

        case 2:

            dim();

            break;

        case 3:

            brighten();

            break;

        case 4:

            rotate();

            break;

        default:

            printf("Invalid choice, please try again.\n");

    }

    display_image();

    save_image();

}




void save_image() {

    char confirm;

    printf("Do you want to save the edited image? (y/n): ");

    scanf(" %c", &confirm);

    if (confirm == 'y' || confirm == 'Y') {

        char filename[256];

        printf("Enter filename to save: ");

        scanf("%s", filename);

        FILE *file = fopen(filename, "w");

        if (!file) {

            printf("File could not be opened for writing.\n");

            return;

        }

        for (int i = 0; i < rows; i++) {

            fprintf(file, "%s\n", image[i]);

        }

        fclose(file);

printf("Image saved as %s.\n", filename);

} else {

printf("Image not saved.\n");

}

}




void crop() {

int newTop, newLeft, newBottom, newRight;

printf("Enter new top, left, bottom, right boundaries: ");

scanf("%d %d %d %d", &newTop, &newLeft, &newBottom, &newRight);

if (newTop >= 0 && newLeft >= 0 && newBottom < rows && newRight < cols &&

    newBottom >= newTop && newRight >= newLeft) {

    char tempImage[MAX_IMAGE_SIZE][MAX_IMAGE_SIZE];

    int tempRows = 0;




    for (int i = newTop; i <= newBottom; i++) {

        int tempCols = 0;

        for (int j = newLeft; j <= newRight; j++) {

            tempImage[tempRows][tempCols++] = image[i][j];

        }

        tempImage[tempRows++][tempCols] = '\0'; // Null-terminate the row

    }




    // Copy tempImage back to image

    for (int i = 0; i < tempRows; i++) {

        for (int j = 0; tempImage[i][j] != '\0'; j++) {

            image[i][j] = tempImage[i][j];

        }

        image[i][cols] = '\0'; // Null-terminate the row

    }

    rows = tempRows; // Update rows to new height

    cols = newRight - newLeft + 1; // Update cols to new width

    printf("Image cropped successfully.\n");

} else {

    printf("Invalid crop boundaries provided.\n");

}

}




void dim() {

for (int i = 0; i < rows; i++) {

for (int j = 0; j < cols; j++) {

if (image[i][j] > '0') image[i][j]--; // Decrease character value to dim

}

}

printf("Image has been dimmed.\n");

}




void brighten() {

for (int i = 0; i < rows; i++) {

for (int j = 0; j < cols; j++) {

if (image[i][j] < '9') image[i][j]++; // Increase character value to brighten

}

}

printf("Image is brighter.\n");

}



void rotate() {
    if (cols > MAX_IMAGE_SIZE || rows > MAX_IMAGE_SIZE) {
        printf("Rotation failed: Image dimensions exceed the maximum allowed size.\n");
        return;
    }

    char tempImage[MAX_IMAGE_SIZE][MAX_IMAGE_SIZE];
    int newCols = rows;  // The number of rows becomes the number of columns
    int newRows = cols;  // The number of columns becomes the number of rows

    // Zero out the tempImage to avoid junk characters
    memset(tempImage, 0, sizeof(tempImage));

    // Perform the rotation into a temporary image
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            tempImage[j][newRows - i - 1] = image[i][j];
            printf("Moving image[%d][%d] -> tempImage[%d][%d]\n", i, j, j, newRows - i - 1);
        }
    }

    // Copy tempImage back to image with updated dimensions
    for (int i = 0; i < newRows; i++) {
        for (int j = 0; j < newCols; j++) {
            image[i][j] = tempImage[i][j];
        }
        image[i][newCols] = '\0';  // Ensure null-termination
    }

    // Update global rows and cols
    rows = newRows;
    cols = newCols;

    printf("Image has been rotated 90 degrees clockwise.\n");
    printf("New dimensions: %d rows x %d cols\n", rows, cols);
}





void exit_program() {

printf("Exiting the program.\n");


}

