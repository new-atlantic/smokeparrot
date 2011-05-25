//# Local system interface.
//# To use the library only this file needs to be included
// (though the files it includes need to be available).

#include "SNode.h"
#include "SMessage.h"
#include "SMessageQueue.h"

// Force symbol export in shared libraries built with gcc.
#if (__GNUC__ >= 4) && defined(SP_EXPORTS)
#define SP_API __attribute__ ((visibility("default")))
#else
#define SP_API
#endif

#define SPCALLCONV

extern "C" SP_API void SPCALLCONV createMessage(char* message, const unsigned int length);
extern "C" SP_API struct SMessageQueue SPCALLCONV retrieveMessages();
extern "C" SP_API void SPCALLCONV redistribute(TMessageIdentifier id);
extern "C" SP_API void SPCALLCONV perserve(TMessageIdentifier id);
extern "C" SP_API void SPCALLCONV delete(TMessageIdentifier id);
extern "C" SP_API void SPCALLCONV blockSource(TNodeIdentifier id);
