#ifndef H_DATABASE
#define H_DATABASE

int database(int proc, const gchar * user, const gchar * password, const gchar * email, const gchar * title);

unsigned char * fetch_database_data(int proc, const gchar * user,  const gchar * password);

void databaseT(int proc, char *user, char *password);

#endif
