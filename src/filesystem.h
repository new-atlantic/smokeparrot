
typedef FILE* TDatabaseHandle;

TDatabaseHandle getDatabaseHandle(const char* mode);

bool write(const SMessage& message, TDatabaseHandle handle);
bool read(const SMessage& message, TDatabaseHandle handle);

bool closeDatabaseHandle(TDatabaseHandle handle);
