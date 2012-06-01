
               File names


name.h         public declarations, intended for reading by Panda's user
name.inl       inline implementation
name.cpp       non-inline implementation (to include into lib-files)
name_*.h       implementation details headers and inlines, typically name_details.h

All implementation details wraps into Impl namespace.



               Subdirectories


config         helper files to detect compiler, declare namespace, etc

containers     containers, sequences, enumerators, etc

errors         errors and exceptions

logic          logical and null values

memory         memory addresses, range, buffers, allocation and deallocation

numerics       everything associated with numbers 

platform       platform dependent features and platform abstraction layer

strings        characters, strings, encodings

type           type properties, traits

utils          unclassified classes and functions
