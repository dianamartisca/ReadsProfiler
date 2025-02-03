#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>
#include <arpa/inet.h>

/* codul de eroare returnat de anumite apeluri */
extern int errno;

/* portul de conectare la server */
int port;

void download_book(const char *buffer) 
{
    const char *title_start = buffer + 10;  
    const char *content_start = strchr(title_start, '\n');  

    // calculăm lungimea titlului și alocăm memorie pentru numele fișierului
    size_t title_length = content_start - title_start;
    char *filename = malloc(title_length + 5);  // +5 pentru ".txt" și null-terminator

    if (!filename) 
    {
        fprintf(stderr, "Eroare la alocarea memoriei pentru numele fișierului.\n");
        return;
    }

    strncpy(filename, title_start, title_length);
    filename[title_length] = '\0';  
    strcat(filename, ".txt");       

    // deschidem fișierul pentru scriere
    FILE *file = fopen(filename, "w");
    if (!file) 
    {
        fprintf(stderr, "Eroare la crearea fișierului '%s'.\n", filename);
        free(filename);
        return;
    }

    fprintf(file, "%s", content_start + 1);  
    fclose(file);

    printf("Carte salvată cu succes în fișierul '%s'.\n", filename);
    free(filename);
}

int main (int argc, char *argv[]) 
{
    int sd;                         // descriptorul de socket
    struct sockaddr_in server;      // structura folosită pentru conectare
    char buffer[2048];               // buffer pentru mesajele trimise/primite

    /* verifică dacă toate argumentele sunt prezente în linia de comandă */
    if (argc != 3) 
    {
        printf("Sintaxa: %s <adresă_server> <port>\n", argv[0]);
        return -1;
    }

    /* stabilim portul */
    port = atoi(argv[2]);

    /* creăm socketul */
    if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1) 
    {
        perror("[client] Eroare la socket().\n");
        return errno;
    }

    /* umplem structura pentru realizarea conexiunii cu serverul */
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(argv[1]);
    server.sin_port = htons(port);

    /* ne conectăm la server */
    if (connect(sd, (struct sockaddr *) &server, sizeof(struct sockaddr)) == -1) 
    {
        perror("[client] Eroare la connect().\n");
        return errno;
    }

    /* bucla pentru trimiterea mesajelor */
    while (1) 
    {
        /* citirea mesajului de la utilizator */
        printf("[client] Introduceți un mesaj (sau 'man' pentru a vizualiza manualul): ");
        fflush(stdout);
        bzero(buffer, sizeof(buffer)); // resetam buffer-ul
        fgets(buffer, sizeof(buffer) - 1, stdin);

        // eliminăm caracterul de newline de la sfârșitul mesajului, dacă există
        if (buffer[strlen(buffer) - 1] == '\n') 
        {
            buffer[strlen(buffer) - 1] = '\0';
        }

        /* trimiterea mesajului la server */
        if (write(sd, buffer, strlen(buffer)) <= 0) 
        {
            perror("[client] Eroare la write() spre server.\n");
            return errno;
        }

        // dacă utilizatorul introduce "quit", ieșim din buclă
        if (strcmp(buffer, "quit") == 0) 
        {
            printf("[client] Se închide conexiunea.\n");
            break;
        } 

        /* citirea răspunsului de la server */
        bzero(buffer, sizeof(buffer));
        if (read(sd, buffer, sizeof(buffer) - 1) < 0) 
        {
            perror("[client] Eroare la read() de la server.\n");
            return errno;
        }

        if(strncmp(buffer, "Download: ", 10)==0) 
        {
            // descărcăm cartea
            download_book(buffer);     
        }
        else
        {
            /* afișăm mesajul primit */
            printf("[client] Mesajul primit de la server: %s\n", buffer);
        }
    }

    /* închidem conexiunea */
    close(sd);
    return 0;
}
