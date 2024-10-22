#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define MAX_BOOKS 10
#define FILENAME "booklibrary.bin"

// Enum to represent book categories
enum Category {
    Fictional = 1,
    Physics,
    History
};

// Structure to store book details
struct Book {
    int bookNumber;
    char bookTitle[50];
    char author[50];
    int numPages;
    enum Category category;
    float bookCost;
};

// Function declarations
void saveBookDetails(struct Book *books, int count);
void displayCategoryWiseList(struct Book *books, int count);
void displayCategoryWiseTotalAndAverage(struct Book *books, int count);
void displayBookDetails(struct Book *books, int count, int bookNumber);
void saveBookDetailsToFile(struct Book *books, int count);
int loadBookDetailsFromFile(struct Book *books);
void deleteBook(struct Book *books, int *count, int bookNumber);
void clearAllBooks(struct Book *books, int *count);

int main() {
	
	printf("\t\t\t###########################################################################");
    printf("\n\t\t\t############                                                   ############");
    printf("\n\t\t\t############      Library management System Project in C       ############");
    printf("\n\t\t\t############                                                   ############");
    printf("\n\t\t\t###########################################################################");
    printf("\n\t\t\t---------------------------------------------------------------------------\n");
    
    // Allocate memory for books
    
    struct Book *books = (struct Book *)malloc(MAX_BOOKS * sizeof(struct Book));
    int bookCount = 0;

    // Load existing book details from the binary file
    bookCount = loadBookDetailsFromFile(books);

    int choice;
    do {
        // Display menu
        printf("\n\t\t\t\t\t1. Add a Book\n");
        printf("\t\t\t\t\t2. Display Category-wise List\n");
        printf("\t\t\t\t\t3. Category-wise Total and Average Book Cost\n");
        printf("\t\t\t\t\t4. Display Book Details by Number\n");
        printf("\t\t\t\t\t5. Delete Book by Number\n");
        printf("\t\t\t\t\t6. Clear All Book Details\n");
        printf("\t\t\t\t\t7. Exit\n");
        printf("\t\t\t\t\tEnter your choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("\t\t\t\t\tInvalid input for choice. Please enter a valid number.\n");
            // Clear the input buffer
            while (getchar() != '\n');
            continue;
        }

        switch (choice) {
            case 1:
                saveBookDetails(books, bookCount);
                saveBookDetailsToFile(books, bookCount);  // Save to binary file after each addition
                bookCount++;
                break;
            case 2:
                displayCategoryWiseList(books, bookCount);
                break;
            case 3:
                displayCategoryWiseTotalAndAverage(books, bookCount);
                break;
            case 4: {
                int bookNumber;
                printf("\t\t\t\t\tEnter Book Number: ");
                if (scanf("%d", &bookNumber) != 1) {
                    printf("\t\t\t\t\tInvalid input for Book Number. Please enter a valid number.\n");
                    // Clear the input buffer
                    while (getchar() != '\n');
                    continue;
                }
                displayBookDetails(books, bookCount, bookNumber);
                break;
            }
            case 5: {
                int bookNumber;
                printf("\t\t\t\t\tEnter Book Number to delete: ");
                if (scanf("%d", &bookNumber) != 1) {
                    printf("\t\t\t\t\tInvalid input for Book Number. Please enter a valid number.\n");
                    // Clear the input buffer
                    while (getchar() != '\n');
                    continue;
                }
                deleteBook(books, &bookCount, bookNumber);
                saveBookDetailsToFile(books, bookCount);  // Save to binary file after deletion
                break;
            }
            case 6:
                clearAllBooks(books, &bookCount);
                saveBookDetailsToFile(books, bookCount);  // Save to binary file after clearing all books
                break;
            case 7:
                printf("\t\t\t\t\tExiting program.\n");
                free(books);
                break;
            default:
                printf("\t\t\t\t\tInvalid choice. Please enter a number between 1 and 7.\n");
        }
    } while (choice != 7);

    // Free dynamically allocated memory
    free(books);

    return 0;
}

// Function to save book details with input validation
void saveBookDetails(struct Book *books, int count) {
    if (count < MAX_BOOKS) {
        int bookNumber;
        printf("\t\t\t\t\tEnter Book Number: ");
        if (scanf("%d", &bookNumber) != 1) {
            printf("\t\t\t\t\tInvalid input for Book Number. Please enter a valid number.\n");
            // Clear the input buffer
            while (getchar() != '\n');
            return;
        }
        getch();

        // Validate that Book Number contains only numbers
        if (bookNumber < 0) {
            printf("\t\t\t\t\tInvalid input for Book Number. Please enter a non-negative number.\n");
            return;
        }

        int i;
        // Check if Book Number already exists
        for (i = 0; i < count; i++) {
            if (books[i].bookNumber == bookNumber) {
                printf("\t\t\t\t\tBook Number %d already exists. Please enter a different Number.\n", bookNumber);
                return;
            }
        }
        // Continue with other inputs if Book Number is valid
        books[count].bookNumber = bookNumber;
        
		printf("\t\t\t\t\tEnter Book Title: ");
		getchar();
		gets(books[count].bookTitle);
		
		printf("\t\t\t\t\tEnter Author: ");
		gets(books[count].author);
		getchar();
        printf("\t\t\t\t\tEnter Number of Pages: ");
        scanf("%d", &books[count].numPages);

        int categoryChoice;
        printf("\t\t\t\t\tEnter Category (1.Fictional / 2.Physics / 3.History): ");
        scanf("%d", &categoryChoice);
        // Validate that Category choice is 1, 2, or 3
        if (categoryChoice < 1 || categoryChoice > 3) {
            printf("\t\t\t\t\tInvalid input for Category. Please enter 1, 2, or 3.\n");
        }
        books[count].category = categoryChoice;

        printf("\t\t\t\t\tEnter Book Cost: ");
        scanf("%f", &books[count].bookCost);
    }
	else {
    	printf("\t\t\t\t\tMaximum number of books reached. Cannot add more books.\n");
    }
}

// Function to display category-wise list of books
void displayCategoryWiseList(struct Book *books, int count) {
    // Display category-wise list of books
    printf("\n\t\t\t\tCategory-wise List of Books:\n");
    printf("\t\t\t\t----------------------------------------------------------\n");
    printf("\t\t\t\t------------------------Fictional-------------------------\n");
    printf("\t\t\t\tBook Number\tBook Title\tAuthor              Pages     Cost\n");
    printf("\t\t\t\t-----------------------------------------------------------\n");
    int i;
    for ( i = 0; i < count; i++) {
        if (books[i].category == 1) {
            printf("\t\t\t\t%-10d\t%-15s\t%-15s\t    %-2d\t      %.2f\n", books[i].bookNumber, books[i].bookTitle, books[i].author,books[i].numPages, books[i].bookCost);
        }
    }
    printf("\t\t\t\t-------------------------Physics-------------------------\n");
    printf("\t\t\t\tBook Number\tBook Title\tAuthor              Pages     Cost\n");
    printf("\t\t\t\t----------------------------------------------------------\n");
    for ( i = 0; i < count; i++) {
        if (books[i].category == 2) {
            printf("\t\t\t\t%-10d\t%-15s\t%-15s\t    %-2d\t      %.2f\n", books[i].bookNumber, books[i].bookTitle, books[i].author,
                   books[i].numPages, books[i].bookCost);
        }
    }
    printf("\t\t\t\t-----------------------History----------------------------\n");
    printf("\t\t\t\tBook Number\tBook Title\tAuthor              Pages     Cost\n");
    printf("\t\t\t\t----------------------------------------------------------\n");
    for ( i = 0; i < count; i++) {
        if (books[i].category == 3) {
            printf("\t\t\t\t%-10d\t%-15s\t%-15s\t    %-2d\t      %.2f\n", books[i].bookNumber, books[i].bookTitle, books[i].author,
                   books[i].numPages, books[i].bookCost);
        }
    }
}

// Function to display category-wise total and average book cost
void displayCategoryWiseTotalAndAverage(struct Book *books, int count) {
    int categoryChoice;
    printf("\t\t\t\t\tEnter Category (1.Fictional / 2.Physics / 3.History): ");
    if (scanf("%d", &categoryChoice) != 1) {
        printf("\t\t\t\t\tInvalid input for Category. Please enter a valid number.\n");
        // Clear the input buffer
        while (getchar() != '\n');
        return;
    }

    // Validate that Category choice is 1, 2, or 3
    if (categoryChoice < 1 || categoryChoice > 3) {
        printf("\t\t\t\t\tInvalid input for Category. Please enter 1, 2, or 3.\n");
        return;
    }

    float totalCost = 0;
    int bookCount = 0;
    int i;

    // Calculate category-wise total cost and count of books
    for ( i = 0; i < count; i++) {
        if (books[i].category == categoryChoice) {
            totalCost += books[i].bookCost;
            bookCount++;
        }
    }

    if (bookCount > 0) {
        float averageCost = totalCost / bookCount;
        printf("\n\t\t\t\t\tCategory-wise Total and Average Book Cost:\n");
        printf("\t\t\t\t\t-----------------------------------------\n");
        printf("\t\t\t\t\tCategory: %d\n", categoryChoice);
        printf("\t\t\t\t\tTotal Cost: %.2f\n", totalCost);
        printf("\t\t\t\t\tAverage Cost: %.2f\n", averageCost);
    } else {
        printf("\t\t\t\t\tNo books found in the selected category.\n");
    }
}

// Function to display book details by book number
void displayBookDetails(struct Book *books, int count, int bookNumber) {
    int index = -1;
    int i;

    // Find the index of the book with the specified book number
    for ( i = 0; i < count; i++) {
        if (books[i].bookNumber == bookNumber) {
            index = i;
            break;
        }
    }

    if (index != -1) {
        // Display book details
        printf("\n\t\t\t\t\tBook Details:\n");
        printf("\t\t\t\t\t--------------\n");
        printf("\t\t\t\t\tBook Number: %d\n", books[index].bookNumber);
        printf("\t\t\t\t\tBook Title: %s\n", books[index].bookTitle);
        printf("\t\t\t\t\tAuthor: %s\n", books[index].author);
        printf("\t\t\t\t\tNumber of Pages: %d\n", books[index].numPages);
        printf("\t\t\t\t\tCategory: %d\n", books[index].category);
        printf("\t\t\t\t\tBook Cost: %.2f\n", books[index].bookCost);
    } else {
        printf("\t\t\t\t\tBook with the specified number not found.\n");
    }
}

// Function to save book details to binary file
void saveBookDetailsToFile(struct Book *books, int count) {
    FILE *file = fopen(FILENAME, "ab+");
    if (file != NULL) {
        fwrite(books, sizeof(struct Book), count, file);
        fclose(file);
    } else {
        printf("\t\t\t\t\tError opening the file %s for writing.\n", FILENAME);
    }
}

// Function to load book details from binary file
int loadBookDetailsFromFile(struct Book *books) {
    FILE *file = fopen(FILENAME, "rb");
    int count = 0;
    if (file != NULL) {
        while (fread(&books[count], sizeof(struct Book), 1, file) == 1) {
            count++;
        }
        fclose(file);
    }
    return count;
}

// Function to delete a book by book number
void deleteBook(struct Book *books, int *count, int bookNumber) {
    int index = -1;
    int i;

    // Find the index of the book with the specified book number
    for ( i = 0; i < *count; i++) {
        if (books[i].bookNumber == bookNumber) {
            index = i;
            break;
        }
    }

    if (index != -1) {
    	int i;
        // Shift elements to fill the gap left by the deleted book
        for ( i = index; i < *count - 1; i++) {
            books[i] = books[i + 1];
        }
        (*count)--;
        printf("\t\t\t\t\tBook with Book Number %d has been deleted.\n", bookNumber);
    } else {
        printf("\t\t\t\t\tBook with the specified number not found.\n");
    }
}

// Function to clear all book details
void clearAllBooks(struct Book *books, int *count) {
    *count = 0;
    printf("\t\t\t\t\tAll book details are cleared.\n");
}
