
#ifdef PANDACFG_NAMESPACE

	namespace PANDACFG_NAMESPACE {

#endif

#ifndef PANDACFG_DEFAULT_ENCODING
    #define PANDACFG_DEFAULT_ENCODING Encoding_UTF8
#endif

// supress warning about changing alignment after including header — it's OK here
#pragma warning(disable: 4103)

// Panda classes manually alignmented right way
#pragma pack(push, 1)
