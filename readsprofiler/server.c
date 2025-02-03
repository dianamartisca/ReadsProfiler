#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <sqlite3.h>

/* portul folosit */
#define PORT 2909

/* codul de eroare returnat de anumite apeluri */
extern int errno;

int sd; //descriptorul de socket de ascultare

sqlite3 *db;

char* see_manual() 
{
    FILE *file;
    char *content = NULL;
    long size;
    file = fopen("manual.txt", "r");
    if (file == NULL) 
    {
        perror("Eroare la deschiderea fișierului.");
        return NULL;
    }
    fseek(file, 0, SEEK_END);  
    size = ftell(file);   
    rewind(file);             
    content = (char *)malloc((size + 1) * sizeof(char));
    if (content == NULL) 
    {
        perror("Eroare la alocarea memoriei.");
        fclose(file);
        return NULL;
    }
    size_t bytesRead = fread(content, sizeof(char), size, file);
    content[bytesRead] = '\0'; 
    fclose(file);
    return content;
}

char* search_title(const char* title, int id_user) 
{
    sqlite3_stmt *stmt;
    sqlite3_stmt *insert_stmt;
    const char *query = "select books.book_title, authors.name from books join authors on books.author_id = authors.author_id  where upper(books.book_title) like upper(?)";
    const char *insert_query = "insert into search_history (client_id, search_text, accessed_books, downloaded_book_id) values (?, ?, ?, NULL)";
    char *response = malloc(1024); 
    char *accessed_books = malloc(1024); 
    if (!response || !accessed_books) 
    {
        fprintf(stderr, "Eroare la alocarea memoriei.\n");
        free(response);
        free(accessed_books);
        return NULL;
    }
    strcpy(response, "Cărțile cu titlul căutat sunt:\n");
    strcpy(accessed_books, "");

    if (sqlite3_prepare_v2(db, query, -1, &stmt, NULL) != SQLITE_OK) 
    {
        fprintf(stderr, "Eroare la pregătirea interogării.\n");
        free(response);
        free(accessed_books);
        return NULL;
    }
    char search_pattern[256];
    snprintf(search_pattern, sizeof(search_pattern), "%%%s%%", title); 
    sqlite3_bind_text(stmt, 1, search_pattern, -1, SQLITE_STATIC);

    while (sqlite3_step(stmt) == SQLITE_ROW) 
    {
        const char *book_title = (const char *)sqlite3_column_text(stmt, 0);
        const char *author_name = (const char *)sqlite3_column_text(stmt, 1);
        char book_info[256];
        snprintf(book_info, sizeof(book_info), "%s, de %s\n", book_title, author_name);
        if (strlen(response) + strlen(book_info) + 1 > 1024) 
        {
            response = realloc(response, strlen(response) + strlen(book_info) + 1);
            if (!response) 
            {
                fprintf(stderr, "Eroare la realocarea memoriei.\n");
                sqlite3_finalize(stmt);
                free(accessed_books);
                return NULL;
            }
        }
        strcat(response, book_info);
        if (strlen(accessed_books) + strlen(book_title) + 2 > 1024) 
        {
            accessed_books = realloc(accessed_books, strlen(accessed_books) + strlen(book_title) + 2);
            if (!accessed_books) 
            {
                fprintf(stderr, "Eroare la realocarea memoriei.\n");
                sqlite3_finalize(stmt);
                free(response);
                return NULL;
            }
        }
        strcat(accessed_books, book_title);
        strcat(accessed_books, "; "); 
    }
    if (strcmp(response, "Cărțile cu titlul căutat sunt:\n") == 0) 
    {
        strcpy(response, "Nu s-au găsit cărți cu titlul căutat.");
        strcpy(accessed_books, "Nicio carte găsită.");
    }
    sqlite3_finalize(stmt);

    if (sqlite3_prepare_v2(db, insert_query, -1, &insert_stmt, NULL) != SQLITE_OK) 
    {
        fprintf(stderr, "Eroare la pregătirea inserării.\n");
        free(response);
        free(accessed_books);
        return NULL;
    }

    sqlite3_bind_int(insert_stmt, 1, id_user);
    sqlite3_bind_text(insert_stmt, 2, title, -1, SQLITE_STATIC);
    sqlite3_bind_text(insert_stmt, 3, accessed_books, -1, SQLITE_STATIC);
    if (sqlite3_step(insert_stmt) != SQLITE_DONE) 
    {
        fprintf(stderr, "Eroare la inserarea în search_history.\n");
    }
    sqlite3_finalize(insert_stmt);
    free(accessed_books);
    return response;
}

char* search_author(const char* author, int id_user) 
{
    sqlite3_stmt *stmt;
    sqlite3_stmt *insert_stmt;
    const char *query = "select books.book_title, authors.name from books join authors on books.author_id = authors.author_id  where upper(authors.name) like upper(?)";
    const char *insert_query = "insert into search_history (client_id, search_text, accessed_books, downloaded_book_id) values (?, ?, ?, NULL)";
    char *response = malloc(1024); 
    char *accessed_books = malloc(1024); 
    if (!response || !accessed_books) 
    {
        fprintf(stderr, "Eroare la alocarea memoriei.\n");
        free(response);
        free(accessed_books);
        return NULL;
    }
    strcpy(response, "Cărțile autorului căutat sunt:\n");
    strcpy(accessed_books, "");

    if (sqlite3_prepare_v2(db, query, -1, &stmt, NULL) != SQLITE_OK) 
    {
        fprintf(stderr, "Eroare la pregătirea interogării.\n");
        free(response);
        free(accessed_books);
        return NULL;
    }
    char search_pattern[256];
    snprintf(search_pattern, sizeof(search_pattern), "%%%s%%", author); 
    sqlite3_bind_text(stmt, 1, search_pattern, -1, SQLITE_STATIC);

    while (sqlite3_step(stmt) == SQLITE_ROW) 
    {
        const char *book_title = (const char *)sqlite3_column_text(stmt, 0);
        const char *author_name = (const char *)sqlite3_column_text(stmt, 1);
        char book_info[256];
        snprintf(book_info, sizeof(book_info), "%s, de %s\n", book_title, author_name);
        if (strlen(response) + strlen(book_info) + 1 > 1024) 
        {
            response = realloc(response, strlen(response) + strlen(book_info) + 1);
            if (!response) 
            {
                fprintf(stderr, "Eroare la realocarea memoriei.\n");
                sqlite3_finalize(stmt);
                free(accessed_books);
                return NULL;
            }
        }
        strcat(response, book_info);
        if (strlen(accessed_books) + strlen(book_title) + 2 > 1024) 
        {
            accessed_books = realloc(accessed_books, strlen(accessed_books) + strlen(book_title) + 2);
            if (!accessed_books) 
            {
                fprintf(stderr, "Eroare la realocarea memoriei.\n");
                sqlite3_finalize(stmt);
                free(response);
                return NULL;
            }
        }
        strcat(accessed_books, book_title);
        strcat(accessed_books, "; "); 
    }
    if (strcmp(response, "Cărțile autorului căutat sunt:\n") == 0) 
    {
        strcpy(response, "Nu s-au găsit cărți ale autorului căutat.");
        strcpy(accessed_books, "Nicio carte găsită.");
    }
    sqlite3_finalize(stmt);

    if (sqlite3_prepare_v2(db, insert_query, -1, &insert_stmt, NULL) != SQLITE_OK) 
    {
        fprintf(stderr, "Eroare la pregătirea inserării.\n");
        free(response);
        free(accessed_books);
        return NULL;
    }

    sqlite3_bind_int(insert_stmt, 1, id_user);
    sqlite3_bind_text(insert_stmt, 2, author, -1, SQLITE_STATIC);
    sqlite3_bind_text(insert_stmt, 3, accessed_books, -1, SQLITE_STATIC);
    if (sqlite3_step(insert_stmt) != SQLITE_DONE) 
    {
        fprintf(stderr, "Eroare la inserarea în search_history.\n");
    }
    sqlite3_finalize(insert_stmt);
    free(accessed_books);
    return response;
}

char* search_year(const char* year, int id_user) 
{
    sqlite3_stmt *stmt;
    sqlite3_stmt *insert_stmt;
    const char *query = "select books.book_title, authors.name from books join authors on books.author_id = authors.author_id  where cast(books.year as text) like ?";
    const char *insert_query = "insert into search_history (client_id, search_text, accessed_books, downloaded_book_id) values (?, ?, ?, NULL)";
    char *response = malloc(1024); 
    char *accessed_books = malloc(1024); 
    if (!response || !accessed_books) 
    {
        fprintf(stderr, "Eroare la alocarea memoriei.\n");
        free(response);
        free(accessed_books);
        return NULL;
    }
    strcpy(response, "Cărțile apărute în anul căutat sunt:\n");
    strcpy(accessed_books, "");

    if (sqlite3_prepare_v2(db, query, -1, &stmt, NULL) != SQLITE_OK) 
    {
        fprintf(stderr, "Eroare la pregătirea interogării.\n");
        free(response);
        free(accessed_books);
        return NULL;
    }
    char search_pattern[256];
    snprintf(search_pattern, sizeof(search_pattern), "%s", year); 
    sqlite3_bind_text(stmt, 1, search_pattern, -1, SQLITE_STATIC);

    while (sqlite3_step(stmt) == SQLITE_ROW) 
    {
        const char *book_title = (const char *)sqlite3_column_text(stmt, 0);
        const char *author_name = (const char *)sqlite3_column_text(stmt, 1);
        char book_info[256];
        snprintf(book_info, sizeof(book_info), "%s, de %s\n", book_title, author_name);
        if (strlen(response) + strlen(book_info) + 1 > 1024) 
        {
            response = realloc(response, strlen(response) + strlen(book_info) + 1);
            if (!response) 
            {
                fprintf(stderr, "Eroare la realocarea memoriei.\n");
                sqlite3_finalize(stmt);
                free(accessed_books);
                return NULL;
            }
        }
        strcat(response, book_info);
        if (strlen(accessed_books) + strlen(book_title) + 2 > 1024) 
        {
            accessed_books = realloc(accessed_books, strlen(accessed_books) + strlen(book_title) + 2);
            if (!accessed_books) 
            {
                fprintf(stderr, "Eroare la realocarea memoriei.\n");
                sqlite3_finalize(stmt);
                free(response);
                return NULL;
            }
        }
        strcat(accessed_books, book_title);
        strcat(accessed_books, "; "); 
    }
    if (strcmp(response, "Cărțile apărute în anul căutat sunt:\n") == 0) 
    {
        strcpy(response, "Nu s-au găsit cărți din anul căutat.");
        strcpy(accessed_books, "Nicio carte găsită.");
    }
    sqlite3_finalize(stmt);

    if (sqlite3_prepare_v2(db, insert_query, -1, &insert_stmt, NULL) != SQLITE_OK) 
    {
        fprintf(stderr, "Eroare la pregătirea inserării.\n");
        free(response);
        free(accessed_books);
        return NULL;
    }

    sqlite3_bind_int(insert_stmt, 1, id_user);
    sqlite3_bind_text(insert_stmt, 2, year, -1, SQLITE_STATIC);
    sqlite3_bind_text(insert_stmt, 3, accessed_books, -1, SQLITE_STATIC);
    if (sqlite3_step(insert_stmt) != SQLITE_DONE) 
    {
        fprintf(stderr, "Eroare la inserarea în search_history.\n");
    }
    sqlite3_finalize(insert_stmt);
    free(accessed_books);
    return response;
}

char* search_genre(const char* genre, int id_user) 
{
    sqlite3_stmt *stmt;
    sqlite3_stmt *insert_stmt;
    const char *query = "select books.book_title, authors.name from books join authors on books.author_id = authors.author_id join books_genres on books_genres.book_id = books.book_id join genres on genres.genre_id = books_genres.genre_id where upper(genres.name) like upper(?)";
    const char *insert_query = "insert into search_history (client_id, search_text, accessed_books, downloaded_book_id) values (?, ?, ?, NULL)";
    char *response = malloc(1024); 
    char *accessed_books = malloc(1024); 
    if (!response || !accessed_books) 
    {
        fprintf(stderr, "Eroare la alocarea memoriei.\n");
        free(response);
        free(accessed_books);
        return NULL;
    }
    strcpy(response, "Cărțile din genul căutat sunt:\n");
    strcpy(accessed_books, "");

    if (sqlite3_prepare_v2(db, query, -1, &stmt, NULL) != SQLITE_OK) 
    {
        fprintf(stderr, "Eroare la pregătirea interogării.\n");
        free(response);
        free(accessed_books);
        return NULL;
    }
    char search_pattern[256];
    snprintf(search_pattern, sizeof(search_pattern), "%s", genre); 
    sqlite3_bind_text(stmt, 1, search_pattern, -1, SQLITE_STATIC);

    while (sqlite3_step(stmt) == SQLITE_ROW) 
    {
        const char *book_title = (const char *)sqlite3_column_text(stmt, 0);
        const char *author_name = (const char *)sqlite3_column_text(stmt, 1);
        char book_info[256];
        snprintf(book_info, sizeof(book_info), "%s, de %s\n", book_title, author_name);
        if (strlen(response) + strlen(book_info) + 1 > 1024) 
        {
            response = realloc(response, strlen(response) + strlen(book_info) + 1);
            if (!response) 
            {
                fprintf(stderr, "Eroare la realocarea memoriei.\n");
                sqlite3_finalize(stmt);
                free(accessed_books);
                return NULL;
            }
        }
        strcat(response, book_info);
        if (strlen(accessed_books) + strlen(book_title) + 2 > 1024) 
        {
            accessed_books = realloc(accessed_books, strlen(accessed_books) + strlen(book_title) + 2);
            if (!accessed_books) 
            {
                fprintf(stderr, "Eroare la realocarea memoriei.\n");
                sqlite3_finalize(stmt);
                free(response);
                return NULL;
            }
        }
        strcat(accessed_books, book_title);
        strcat(accessed_books, "; "); 
    }
    if (strcmp(response, "Cărțile din genul căutat sunt:\n") == 0) 
    {
        strcpy(response, "Nu s-au găsit cărți din genul căutat.");
        strcpy(accessed_books, "Nicio carte găsită.");
    }
    sqlite3_finalize(stmt);

    if (sqlite3_prepare_v2(db, insert_query, -1, &insert_stmt, NULL) != SQLITE_OK) 
    {
        fprintf(stderr, "Eroare la pregătirea inserării.\n");
        free(response);
        free(accessed_books);
        return NULL;
    }

    sqlite3_bind_int(insert_stmt, 1, id_user);
    sqlite3_bind_text(insert_stmt, 2, genre, -1, SQLITE_STATIC);
    sqlite3_bind_text(insert_stmt, 3, accessed_books, -1, SQLITE_STATIC);
    if (sqlite3_step(insert_stmt) != SQLITE_DONE) 
    {
        fprintf(stderr, "Eroare la inserarea în search_history.\n");
    }
    sqlite3_finalize(insert_stmt);
    free(accessed_books);
    return response;
}

char* search_isbn(const char* isbn, int id_user) 
{
    sqlite3_stmt *stmt;
    sqlite3_stmt *insert_stmt;
    const char *query = "select books.book_title, authors.name from books join authors on books.author_id = authors.author_id where books.isbn like ?";
    const char *insert_query = "insert into search_history (client_id, search_text, accessed_books, downloaded_book_id) values (?, ?, ?, NULL)";
    char *response = malloc(1024); 
    char *accessed_books = malloc(1024); 
    if (!response || !accessed_books) 
    {
        fprintf(stderr, "Eroare la alocarea memoriei.\n");
        free(response);
        free(accessed_books);
        return NULL;
    }
    strcpy(response, "Cartea cu isbn-ul căutat este:\n");
    strcpy(accessed_books, "");

    if (sqlite3_prepare_v2(db, query, -1, &stmt, NULL) != SQLITE_OK) 
    {
        fprintf(stderr, "Eroare la pregătirea interogării.\n");
        free(response);
        free(accessed_books);
        return NULL;
    }
    char search_pattern[256];
    snprintf(search_pattern, sizeof(search_pattern), "%s", isbn); 
    sqlite3_bind_text(stmt, 1, search_pattern, -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) == SQLITE_ROW) 
    {
        const char *book_title = (const char *)sqlite3_column_text(stmt, 0);
        const char *author_name = (const char *)sqlite3_column_text(stmt, 1);
        char book_info[256];
        snprintf(book_info, sizeof(book_info), "%s, de %s\n", book_title, author_name);
        if (strlen(response) + strlen(book_info) + 1 > 1024) 
        {
            response = realloc(response, strlen(response) + strlen(book_info) + 1);
            if (!response) 
            {
                fprintf(stderr, "Eroare la realocarea memoriei.\n");
                sqlite3_finalize(stmt);
                free(accessed_books);
                return NULL;
            }
        }
        strcat(response, book_info);
        if (strlen(accessed_books) + strlen(book_title) + 2 > 1024) 
        {
            accessed_books = realloc(accessed_books, strlen(accessed_books) + strlen(book_title) + 2);
            if (!accessed_books) 
            {
                fprintf(stderr, "Eroare la realocarea memoriei.\n");
                sqlite3_finalize(stmt);
                free(response);
                return NULL;
            }
        }
        strcat(accessed_books, book_title);
        strcat(accessed_books, "; "); 
    }
    if (strcmp(response, "Cartea cu isbn-ul căutat este:\n") == 0) 
    {
        strcpy(response, "Nu s-a găsit nicio carte cu isbn-ul căutat.");
        strcpy(accessed_books, "Nicio carte găsită.");
    }
    sqlite3_finalize(stmt);

    if (sqlite3_prepare_v2(db, insert_query, -1, &insert_stmt, NULL) != SQLITE_OK) 
    {
        fprintf(stderr, "Eroare la pregătirea inserării.\n");
        free(response);
        free(accessed_books);
        return NULL;
    }

    sqlite3_bind_int(insert_stmt, 1, id_user);
    sqlite3_bind_text(insert_stmt, 2, isbn, -1, SQLITE_STATIC);
    sqlite3_bind_text(insert_stmt, 3, accessed_books, -1, SQLITE_STATIC);
    if (sqlite3_step(insert_stmt) != SQLITE_DONE) 
    {
        fprintf(stderr, "Eroare la inserarea în search_history.\n");
    }
    sqlite3_finalize(insert_stmt);
    free(accessed_books);
    return response;
}

char* search_rating(const char* rating, int id_user) 
{
    sqlite3_stmt *stmt;
    sqlite3_stmt *insert_stmt;
    const char *query = "select books.book_title, authors.name from books join authors on books.author_id = authors.author_id  where cast(books.rating as text) like ?";
    const char *insert_query = "insert into search_history (client_id, search_text, accessed_books, downloaded_book_id) values (?, ?, ?, NULL)";
    char *response = malloc(1024); 
    char *accessed_books = malloc(1024); 
    if (!response || !accessed_books) 
    {
        fprintf(stderr, "Eroare la alocarea memoriei.\n");
        free(response);
        free(accessed_books);
        return NULL;
    }
    strcpy(response, "Cărțile cu rating-ul căutat sunt:\n");
    strcpy(accessed_books, "");

    if (sqlite3_prepare_v2(db, query, -1, &stmt, NULL) != SQLITE_OK) 
    {
        fprintf(stderr, "Eroare la pregătirea interogării.\n");
        free(response);
        free(accessed_books);
        return NULL;
    }
    char search_pattern[256];
    snprintf(search_pattern, sizeof(search_pattern), "%s", rating); 
    sqlite3_bind_text(stmt, 1, search_pattern, -1, SQLITE_STATIC);

    while (sqlite3_step(stmt) == SQLITE_ROW) 
    {
        const char *book_title = (const char *)sqlite3_column_text(stmt, 0);
        const char *author_name = (const char *)sqlite3_column_text(stmt, 1);
        char book_info[256];
        snprintf(book_info, sizeof(book_info), "%s, de %s\n", book_title, author_name);
        if (strlen(response) + strlen(book_info) + 1 > 1024) 
        {
            response = realloc(response, strlen(response) + strlen(book_info) + 1);
            if (!response) 
            {
                fprintf(stderr, "Eroare la realocarea memoriei.\n");
                sqlite3_finalize(stmt);
                free(accessed_books);
                return NULL;
            }
        }
        strcat(response, book_info);
        if (strlen(accessed_books) + strlen(book_title) + 2 > 1024) 
        {
            accessed_books = realloc(accessed_books, strlen(accessed_books) + strlen(book_title) + 2);
            if (!accessed_books) 
            {
                fprintf(stderr, "Eroare la realocarea memoriei.\n");
                sqlite3_finalize(stmt);
                free(response);
                return NULL;
            }
        }
        strcat(accessed_books, book_title);
        strcat(accessed_books, "; "); 
    }
    if (strcmp(response, "Cărțile cu rating-ul căutat sunt:\n") == 0) 
    {
        strcpy(response, "Nu s-au găsit cărți cu rating-ul căutat.");
        strcpy(accessed_books, "Nicio carte găsită.");
    }
    sqlite3_finalize(stmt);

    if (sqlite3_prepare_v2(db, insert_query, -1, &insert_stmt, NULL) != SQLITE_OK) 
    {
        fprintf(stderr, "Eroare la pregătirea inserării.\n");
        free(response);
        free(accessed_books);
        return NULL;
    }

    sqlite3_bind_int(insert_stmt, 1, id_user);
    sqlite3_bind_text(insert_stmt, 2, rating, -1, SQLITE_STATIC);
    sqlite3_bind_text(insert_stmt, 3, accessed_books, -1, SQLITE_STATIC);
    if (sqlite3_step(insert_stmt) != SQLITE_DONE) 
    {
        fprintf(stderr, "Eroare la inserarea în search_history.\n");
    }
    sqlite3_finalize(insert_stmt);
    free(accessed_books);
    return response;
}

char* rate_book(const char* details, int id_user) 
{
    sqlite3_stmt *stmt, *insert_stmt;
    const char *query_select = "select book_id, rating from books where book_title = ? and author_id = (select author_id from authors where name = ?)";
    const char *query_update = "update books set rating = ? where book_id = ?";
    const char *query_insert = "insert into rating_history (client_id, book_id, rating) values (?, ?, ?)";

    char title[256], author[256];
    float new_rating, old_rating, avg_rating;

    // comanda pentru a extrage titlul, autorul și rating-ul
    if (sscanf(details, "%255[^_]_%255[^_]_%f", title, author, &new_rating) != 3) 
    {
        return "Comanda este invalidă.";
    }

    // caută ID-ul cărții și rating-ul vechi
    if (sqlite3_prepare_v2(db, query_select, -1, &stmt, NULL) != SQLITE_OK) 
    {
        return "Eroare la pregătirea interogării pentru selectarea cărții.";
    }
    char title_pattern[258], author_pattern[258];
    snprintf(title_pattern, sizeof(title_pattern), "%s", title); 
    sqlite3_bind_text(stmt, 1, title_pattern, -1, SQLITE_STATIC);

    snprintf(author_pattern, sizeof(author_pattern), "%s", author); 
    sqlite3_bind_text(stmt, 2, author_pattern, -1, SQLITE_STATIC);

    int book_id = -1;
    if (sqlite3_step(stmt) == SQLITE_ROW) 
    {
        book_id = sqlite3_column_int(stmt, 0);
        old_rating = (float)sqlite3_column_double(stmt, 1);  
    }
    sqlite3_finalize(stmt);

    // dacă nu am găsit cartea
    if (book_id == -1) 
    {
        return "Cartea nu a fost găsită.";
    }

    // calculează media rating-ului 
    avg_rating = (old_rating + new_rating) / 2.0;

    // actualizează rating-ul în baza de date
    if (sqlite3_prepare_v2(db, query_update, -1, &stmt, NULL) != SQLITE_OK) 
    {
        return "Eroare la pregătirea interogării pentru actualizarea rating-ului.";
    }

    sqlite3_bind_double(stmt, 1, avg_rating);  
    sqlite3_bind_int(stmt, 2, book_id);           

    if (sqlite3_step(stmt) != SQLITE_DONE) 
    {
        sqlite3_finalize(stmt);
        return "Eroare la actualizarea rating-ului.";
    }
    sqlite3_finalize(stmt);

    // inserează istoricul rating-ului în tabela rating_history
    if (sqlite3_prepare_v2(db, query_insert, -1, &insert_stmt, NULL) != SQLITE_OK) 
    {
        return "Eroare la pregătirea interogării pentru inserarea în rating_history.";
    }

    sqlite3_bind_int(insert_stmt, 1, id_user);            
    sqlite3_bind_int(insert_stmt, 2, book_id);            
    sqlite3_bind_double(insert_stmt, 3, new_rating);      

    if (sqlite3_step(insert_stmt) != SQLITE_DONE) 
    {
        sqlite3_finalize(insert_stmt);
        return "Eroare la inserarea în rating_history.";
    }
    sqlite3_finalize(insert_stmt);

    char *response="Cartea a fost evaluată cu succes.";
    return response;
}

char* download_book(const char* details, int id_user) 
{
    sqlite3_stmt *stmt, *insert_stmt;
    const char *query_select = "select book_id, book from books where book_title = ? and author_id = (select author_id from authors where name = ?)";
    const char *query_insert = "insert into search_history (client_id, search_text, accessed_books, downloaded_book_id) values (?, ?, NULL, ?)";

    char title[256], author[256];

    // comanda pentru a extrage titlul și autorul 
    if (sscanf(details, "%255[^_]_%255[^_]", title, author) != 2) 
    {
        return "Comanda este invalidă.";
    }

    // caută ID-ul cărții și conținutul ei
    if (sqlite3_prepare_v2(db, query_select, -1, &stmt, NULL) != SQLITE_OK) 
    {
        return "Eroare la pregătirea interogării pentru selectarea cărții.";
    }
    char title_pattern[258], author_pattern[258];
    snprintf(title_pattern, sizeof(title_pattern), "%s", title); 
    sqlite3_bind_text(stmt, 1, title_pattern, -1, SQLITE_STATIC);

    snprintf(author_pattern, sizeof(author_pattern), "%s", author); 
    sqlite3_bind_text(stmt, 2, author_pattern, -1, SQLITE_STATIC);

    int book_id = -1; char *book_content = NULL;
    if (sqlite3_step(stmt) == SQLITE_ROW) 
    {
        book_id = sqlite3_column_int(stmt, 0);
        const unsigned char *text = sqlite3_column_text(stmt, 1);

        if (text == NULL) 
        {
            printf("Eroare: conținutul cărții este NULL.\n");
        } 
        else 
        {
            book_content = malloc(strlen((const char *)text) + 1);
            if (book_content == NULL) 
            {
                printf("Eroare la alocarea memoriei.\n");
                sqlite3_finalize(stmt);
                return "Eroare la alocarea memoriei";
            }
            strcpy(book_content, (const char *)text);
        }
    }
    sqlite3_finalize(stmt);
    // dacă nu am găsit cartea
    if (book_id == -1) 
    {
        return "Cartea nu a fost găsită.";
    }

    // inserează istoricul descărcării în tabela search_history
    if (sqlite3_prepare_v2(db, query_insert, -1, &insert_stmt, NULL) != SQLITE_OK) 
    {
        return "Eroare la pregătirea interogării pentru inserarea în search_history.";
    }

    sqlite3_bind_int(insert_stmt, 1, id_user);            
    sqlite3_bind_text(insert_stmt, 2, details, -1, SQLITE_STATIC);            
    sqlite3_bind_int(insert_stmt, 3, book_id);      

    if (sqlite3_step(insert_stmt) != SQLITE_DONE) 
    {
        sqlite3_finalize(insert_stmt);
        return "Eroare la inserarea în search_history.";
    }
    sqlite3_finalize(insert_stmt);

    const char *prefix = "Download: ";
    size_t response_len = strlen(prefix) + strlen(title) + strlen(book_content) + 1; 

    char *response = malloc(response_len);
    if (!response) 
    {
        fprintf(stderr, "Eroare la alocarea memoriei.\n");
        return NULL;
    }

    strcpy(response, prefix);           
    strcat(response, title); 
    strcat(response, "\n"); 
    strcat(response, book_content);     
    return response;
}

char* recommend_books(int id_user) 
{
    sqlite3_stmt *stmt;
    const char *query = "select distinct b.book_title, a.name from books b join authors a on b.author_id = a.author_id join books_genres bg on b.book_id = bg.book_id join genres g on bg.genre_id = g.genre_id join authors_genres ag on a.author_id = ag.author_id where b.author_id in"
                        "(select b1.author_id from books b1 join search_history sh on sh.downloaded_book_id = b1.book_id where sh.client_id = ?) or bg.genre_id in"
                        "(select distinct bg2.genre_id from books_genres bg2 join search_history sh on sh.downloaded_book_id = bg2.book_id where sh.client_id = ?) or ag.genre_id in"
                        "(select bg3.genre_id from books_genres bg3 join authors_genres ag3 on bg3.genre_id = ag3.genre_id where ag3.author_id in (select b4.author_id from books b4 join search_history sh on sh.downloaded_book_id = b4.book_id where sh.client_id = ?)) or b.rating in"
                        "(select distinct b2.rating from books b2 join search_history sh on sh.downloaded_book_id = b2.book_id where sh.client_id = ?);";

    if (sqlite3_prepare_v2(db, query, -1, &stmt, NULL) != SQLITE_OK) 
    {
        return "Eroare la pregătirea interogării.";
    }

    sqlite3_bind_int(stmt, 1, id_user);
    sqlite3_bind_int(stmt, 2, id_user);
    sqlite3_bind_int(stmt, 3, id_user);
    sqlite3_bind_int(stmt, 4, id_user);

    size_t response_size = 1024; 
    char *response = malloc(response_size);
    if (!response) 
    {
        sqlite3_finalize(stmt);
        return "Eroare la alocarea memoriei.";
    }
    strcpy(response, "Cărți recomandate:\n");

    while (sqlite3_step(stmt) == SQLITE_ROW) 
    {
        const char *book_title = (const char *)sqlite3_column_text(stmt, 0);
        const char *author_name = (const char *)sqlite3_column_text(stmt, 1);

        size_t needed_size = strlen(response) + strlen(book_title) + strlen(author_name) + 10;
        if (needed_size > response_size) 
        {
            response_size = response_size + 1024;
            char *new_response = realloc(response, response_size);
            if (!new_response) 
            {
                free(response);
                sqlite3_finalize(stmt);
                return "Eroare la realocarea memoriei.";
            }
            response = new_response;
        }

        strcat(response, book_title);
        strcat(response, ", de ");
        strcat(response, author_name);
        strcat(response, "\n");
    }

    sqlite3_finalize(stmt);

    if (strlen(response) == strlen("Recomandări:\n")) 
    {
        strcpy(response, "Nu am găsit recomandări.");
    }
    return response;
}

int get_id_user(const char *username) 
{
    sqlite3_stmt *stmt;
    int user_id = -1;

    // caută utilizatorul în baza de date
    const char *query_select = "select client_id from clients where name = ?";
    if (sqlite3_prepare_v2(db, query_select, -1, &stmt, NULL) != SQLITE_OK) 
    {
        fprintf(stderr, "Eroare la pregătirea select.\n");
        return -1;
    }

    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) == SQLITE_ROW) 
    {
        user_id = sqlite3_column_int(stmt, 0);
    }
    sqlite3_finalize(stmt);

    // dacă utilizatorul nu există, inserează-l
    if (user_id == -1) 
    {
        const char *query_insert = "insert into clients (name) values (?)";
        if (sqlite3_prepare_v2(db, query_insert, -1, &stmt, NULL) != SQLITE_OK) 
        {
            fprintf(stderr, "Eroare la pregătirea insert.\n");
            return -1;
        }

        sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);

        if (sqlite3_step(stmt) != SQLITE_DONE) 
        {
            fprintf(stderr, "Eroare la executarea insert.\n");
            sqlite3_finalize(stmt);
            return -1;
        }
        sqlite3_finalize(stmt);

        // obține ultimul client_id generat
        user_id = (int)sqlite3_last_insert_rowid(db);
    }

    return user_id;
}

/* funcția care răspunde clientului */
void *treat(void *arg) 
{
    int cl = (int)(intptr_t)arg;
    char buffer[256]; // buffer pentru comenzi
    char response[2048];
    int ok=0; //utilizatorul nu e logat
    int id_user;
    while (1) 
    {
        bzero(buffer, sizeof(buffer));

        // citim mesajul de la client
        int bytesRead = read(cl, buffer, sizeof(buffer) - 1);
        if (bytesRead <= 0) 
        {
            printf("[Thread] Conexiunea cu clientul cu descriptorul %d s-a inchis.\n",cl);
            break;
        }

        printf("[Thread] Mesajul primit: %s\n", buffer);

        // verificăm dacă clientul a trimis comanda "quit"
        if (strncmp(buffer, "quit", 4) == 0) 
        {
            printf("[Thread] Clientul a trimis comanda 'quit'. Închidem conexiunea.\n");
            break;
        }
        if (strncmp(buffer, "man", 3) == 0) 
        {
            printf("[Thread] Clientul a trimis comanda 'man'. Trimitem manualul.\n");
            snprintf(response, sizeof(response), "%s", see_manual());
        }
        else
        if (strncmp(buffer, "login", 5) == 0) 
        {
            printf("[Thread] Clientul a trimis comanda 'login'.\n");
            if(ok==1)
            {
                strcpy(response, "Utilizatorul este deja logat."); 
            }
            else
            {
                ok=1;
                strcpy(response, "Utilizator logat cu succes."); 
                char username[256];
                strcpy(username, buffer+8);
                id_user=get_id_user(username); 
            }
        }
        else 
        {
            if(ok==0)
                strcpy(response, "Niciun utilizator logat. Utilizează login : <username>");
            else 
            {
                if(strncmp(buffer, "search-title", 12)==0) 
                {
                    printf("[Thread] Clientul a trimis comanda 'search-title'.\n");
                    char title[256];
                    strcpy(title, buffer+15);
                    snprintf(response, sizeof(response), "%s", search_title(title, id_user));
                }
                else
                if(strncmp(buffer, "search-author", 13)==0) 
                {
                    char author[256];
                    strcpy(author, buffer+16);
                    snprintf(response, sizeof(response), "%s", search_author(author, id_user));
                }
                else
                if(strncmp(buffer, "search-year", 11)==0) 
                {
                    char year[256];
                    strcpy(year, buffer+14);
                    snprintf(response, sizeof(response), "%s", search_year(year, id_user));
                }
                else
                if(strncmp(buffer, "search-genre", 12)==0) 
                {
                    char genre[256];
                    strcpy(genre, buffer+15);
                    snprintf(response, sizeof(response), "%s", search_genre(genre, id_user));
                }
                else
                if(strncmp(buffer, "search-isbn", 11)==0) 
                {
                    char isbn[256];
                    strcpy(isbn, buffer+14);
                    snprintf(response, sizeof(response), "%s", search_isbn(isbn, id_user));
                }
                else
                if(strncmp(buffer, "search-rating", 13)==0) 
                {
                    char rating[256];
                    strcpy(rating, buffer+16);
                    snprintf(response, sizeof(response), "%s", search_rating(rating, id_user));
                }
                else
                if(strncmp(buffer, "rate-book", 9)==0) 
                {
                    char details[256];
                    strcpy(details, buffer+12);
                    snprintf(response, sizeof(response), "%s", rate_book(details, id_user));

                }
                else
                if(strncmp(buffer, "download-book", 13)==0) 
                {
                    char details[256];
                    strcpy(details, buffer+16);
                    snprintf(response, sizeof(response), "%s", download_book(details, id_user));

                }
                else
                if(strncmp(buffer, "recommend-books", 15)==0) 
                {
                    snprintf(response, sizeof(response), "%s", recommend_books(id_user));
                }
                else
                if(strncmp(buffer, "logout", 6)==0) 
                {
                    ok=0;
                    strcpy(response, "Utilizator deconectat cu succes.");
                }
                else
                {
                    strcpy(response, "Comandă necunoscută. Verifică manualul.");
                }
            } 
        }
        if (write(cl, response, strlen(response)) <= 0) 
        {
            perror("[Thread] Eroare la write() către client.\n");
            break;
        } 
        else 
        {
            printf("[Thread] Mesajul a fost transmis cu succes.\n");
        }
    }
    /* am terminat cu acest client, închidem conexiunea */
    close(cl);
    return NULL;
}

/* funcție de convertire a adresei IP a clientului în șir de caractere */
char * conv_addr (struct sockaddr_in address)
{
  static char str[25];
  char port[7];

  /* adresa IP a clientului */
  strcpy (str, inet_ntoa (address.sin_addr));	
  /* portul utilizat de client */
  bzero (port, 7);
  sprintf (port, ":%d", ntohs (address.sin_port));	
  strcat (str, port);
  return (str);
}

int open_database(const char *filename) 
{
    if (sqlite3_open(filename, &db)) 
    {
        fprintf(stderr, "Eroare la deschiderea bazei de date: %s\n", sqlite3_errmsg(db));
        return 0;
    }
    return 1;
}

void close_database() 
{
    sqlite3_close(db);
}

int main ()
{
    open_database("database.db");
    struct sockaddr_in server;

    /* crearea unui socket */
    if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1) 
    {
        perror("[server] Eroare la socket().\n");
        return errno;
    }

    /* utilizarea opțiunii SO_REUSEADDR */
    int on = 1;
    setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));

    /* pregătirea structurilor de date */
    bzero(&server, sizeof(server));

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    server.sin_port = htons(PORT);

    /* atașăm socket-ul */
    if (bind(sd, (struct sockaddr *) &server, sizeof(struct sockaddr)) == -1) 
    {
        perror("[server] Eroare la bind().\n");
        return errno;
    }

    /* punem serverul să asculte dacă vin clienți să se conecteze */
    if (listen(sd, 2) == -1) 
    {
        perror("[server] Eroare la listen().\n");
        return errno;
    }

    printf("[server] Așteptăm la portul %d...\n", PORT);
    fflush(stdout);

    /* servim în mod concurent clienții...folosind thread-uri */
    while(1) 
    {
        struct sockaddr_in from;
        socklen_t length = sizeof(from);
        int client;

        /* acceptă o conexiune de la client */
        client = accept(sd, (struct sockaddr *) &from, &length);
        if (client < 0) 
        {
            perror("[server] Eroare la accept().\n");
            continue;
        }

        printf("[server] S-a conectat clientul cu descriptorul %d, de la adresa %s.\n",client, conv_addr (from));
        fflush(stdout);

        /* crearea unui nou thread pentru a gestiona clientul */
        pthread_t threadId;
        if (pthread_create(&threadId, NULL, &treat, (void *)(intptr_t)client) != 0) 
        {
            perror("[server] Eroare la crearea thread-ului.\n");
            close(client);
        } 
        else 
        {
            /* detașăm thread-ul pentru a nu necesita join */
            pthread_detach(threadId);
        }
    }
    close_database();
}