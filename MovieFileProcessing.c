/*
Name: Estevan Cisneros
Description: Movie Information System using a binary file. This program allows the user to add, delete, update, and display
movies stored in a binary file. Each movie includes a title and number of downloads.
*/

#include <stdio.h>
#include <string.h>

// structure for movie
typedef struct
{
    char title[26];
    int downloads;
} movie_t;

// function prototypes
FILE* openFile();
int displayMenu();
void addMovie(FILE *fp);
void deleteMovie(FILE *fp);
void updateMovie(FILE *fp);
void displayMovieInfo(FILE *fp);

int main()
{
    FILE *fp = openFile();
    int choice = displayMenu();

    while (choice != 5)
    {
        switch (choice)
        {
            case 1:
                addMovie(fp);
                break;
            case 2:
                deleteMovie(fp);
                break;
            case 3:
                updateMovie(fp);
                break;
            case 4:
                displayMovieInfo(fp);
                break;
            default:
                printf("Invalid option\n");
        }
        choice = displayMenu();
    }

    fclose(fp);
    return 0;
}

// openFile function
FILE* openFile()
{
    FILE *fp;
    movie_t blank = {"", 0};

    // create file with 10 blank records
    fp = fopen("movies.dat", "wb");
    if (fp == NULL)
    {
        printf("Error opening file\n");
        return NULL;
    }

    for (int i = 0; i < 10; i++)
    {
        fwrite(&blank, sizeof(movie_t), 1, fp);
    }

    fclose(fp);

    // reopen for reading/writing
    fp = fopen("movies.dat", "rb+");
    if (fp == NULL)
    {
        printf("Error opening file\n");
    }

    return fp;
}

// displayMenu function
int displayMenu()
{
    int choice;

    printf("Movie Information System\n");
    printf("1. Add a movie\n");
    printf("2. Delete a movie\n");
    printf("3. Update a movie\n");
    printf("4. Display all movies\n");
    printf("5. Exit\n");
    printf("Your choice: ");
    scanf("%d", &choice);
    while (getchar() != '\n');

    return choice;
}

// addMovie function
void addMovie(FILE *fp)
{
    movie_t m;
    movie_t temp;
    char buffer[100];

    printf("Title of movie (max 25 chars): ");
    fgets(buffer, 100, stdin);

    buffer[strcspn(buffer, "\n")] = '\0';

    if (strlen(buffer) > 25)
    {
        printf("Title exceeds 25 characters and will be truncated\n");
    }

    strncpy(m.title, buffer, 25);
    m.title[25] = '\0';

    printf("Number of downloads: ");
    scanf("%d", &m.downloads);
    while (getchar() != '\n');

    rewind(fp);

    for (int i = 0; i < 10; i++)
    {
        fread(&temp, sizeof(movie_t), 1, fp);

        if (temp.title[0] == '\0')
        {
            fseek(fp, -sizeof(movie_t), SEEK_CUR);
            fwrite(&m, sizeof(movie_t), 1, fp);
            printf("Movie added successfully\n");
            return;
        }
    }

    printf("No space available in file\n");
}

// deleteMovie function
void deleteMovie(FILE *fp)
{
    int rec;
    movie_t blank = {"", 0};
    movie_t temp;

    do
    {
        printf("Movie to delete: ");
        scanf("%d", &rec);
        while (getchar() != '\n');
    } while (rec < 1 || rec > 10);

    fseek(fp, (rec - 1) * sizeof(movie_t), SEEK_SET);
    fread(&temp, sizeof(movie_t), 1, fp);

    if (temp.title[0] == '\0')
    {
        printf("That movie does not exist\n");
        return;
    }

    fseek(fp, -sizeof(movie_t), SEEK_CUR);
    fwrite(&blank, sizeof(movie_t), 1, fp);

    printf("Movie deleted successfully\n");
}

// updateMovie function
void updateMovie(FILE *fp)
{
    int rec;
    movie_t m;
    char buffer[100];

    do
    {
        printf("Movie to update: ");
        scanf("%d", &rec);
        while (getchar() != '\n');
    } while (rec < 1 || rec > 10);

    fseek(fp, (rec - 1) * sizeof(movie_t), SEEK_SET);
    fread(&m, sizeof(movie_t), 1, fp);

    if (m.title[0] == '\0')
    {
        printf("That movie does not exist\n");
        return;
    }

    printf("Current title: %s\n", m.title);
    printf("Current downloads: %d\n", m.downloads);

    printf("Updated title: ");
    fgets(buffer, 100, stdin);

    buffer[strcspn(buffer, "\n")] = '\0';

    if (strlen(buffer) > 25)
    {
        printf("Title exceeds 25 characters and will be truncated\n");
    }

    strncpy(m.title, buffer, 25);
    m.title[25] = '\0';

    printf("Updated downloads: ");
    scanf("%d", &m.downloads);
    while (getchar() != '\n');

    fseek(fp, -sizeof(movie_t), SEEK_CUR);
    fwrite(&m, sizeof(movie_t), 1, fp);

    printf("Movie updated successfully\n");
}

// displayMovieInfo function
void displayMovieInfo(FILE *fp)
{
    movie_t m;

    rewind(fp);

    printf("Number Title                     Downloads\n");
    printf("===== ========================= =========\n");

    for (int i = 0; i < 10; i++)
    {
        fread(&m, sizeof(movie_t), 1, fp);

        if (m.title[0] != '\0')
        {
            printf("%-6d %-25s %-10d\n", i + 1, m.title, m.downloads);
        }
    }
}