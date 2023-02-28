#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

#define MAX_LENGTH 200

static const char *URL = "";
static const char *USERNAME = "";
static const char *PASSWORD = "";
static const char *PATH = "";

static size_t throw_away(void *ptr, size_t size, size_t nmemb, void *data);

int main(int argc, char *argv[])
{
    if (argv[1] != NULL && strlen(argv[1]) > 1
            && strlen(argv[1]) < MAX_LENGTH - (strlen(PATH))) {

        char full_path[MAX_LENGTH];
        strcpy(full_path, PATH);
        strcat(full_path, argv[1]);

        CURL *handler = curl_easy_init();

        if (handler) {
            curl_easy_setopt(handler, CURLOPT_URL, URL);
            curl_easy_setopt(handler, CURLOPT_PROTOCOLS, CURLPROTO_SFTP);
            curl_easy_setopt(handler, CURLOPT_PORT, 22);
            curl_easy_setopt(handler, CURLOPT_USERNAME, USERNAME);
            curl_easy_setopt(handler, CURLOPT_PASSWORD, PASSWORD);
            curl_easy_setopt(handler, CURLOPT_WRITEFUNCTION, throw_away);
            curl_easy_setopt(handler, CURLOPT_FILETIME, 1L);

            curl_easy_perform(handler);
            long lTimestamp = -1;
            curl_easy_getinfo(handler, CURLINFO_FILETIME, &lTimestamp);
            time_t t_filetimestamp = (time_t) lTimestamp;
            printf("%s;%s",argv[1],ctime(&t_filetimestamp));
            curl_easy_cleanup(handler);
        }
    }
    return 0;
}

static size_t throw_away(void *ptr, size_t size, size_t nmemb, void *data)
{
    (void) ptr;
    (void) data;
    return (size_t) (size * nmemb);
}


