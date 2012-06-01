
               Config macros


PANDACFG_NAMESPACE

Name of namespace to include all Panda's declarations in. All Panda's names are global
if PANDACFG_NAMESPACE is undefined.


PANDACFG_BOOST_UTF_INCLUDE_IMPLEMENTATION

Uses internally by unit testing system.


PANDACFG_INT_ARITHMETIC

Default arithmetic for integers:
- PANDA_INT_ARITHMETIC_CYCLIC    default for CPU, overfloats allowed
- PANDA_INT_ARITHMETIC_BOUNDED   exceptions at overfloat
- user-defined class, having _plus and _minus static methods


PANDACFG_DEFAULT_ENCODING

Encoding class, used by characters and strings by default.
Encoding_UTF8 if unspecified.
