#include "SMessage.h"
#include "SMessageQueue.h"

// Force symbol export in shared libraries built with gcc.
#if (__GNUC__ >= 4) && defined(SP_EXPORTS)
#define SP_API __attribute__ ((visibility("default")))
#else
#define SP_API
#endif

#define SPCALLCONV

extern "C" SP_API void SPCALLCONV newMessage(char* message);
extern "C" SP_API struct SMessageQueue SPCALLCONV retrieveMessages();
extern "C" SP_API void SPCALLCONV redistribute(<messageID>);
extern "C" SP_API void SPCALLCONV perserve(<messageID>
extern "C" SP_API void SPCALLCONV delete(<messageID>);
extern "C" SP_API void SPCALLCONV blockSource(<source>);
