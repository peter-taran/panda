
#pragma once



struct Uninitialized {};
static const Uninitialized uninitialized = Uninitialized();


struct Null {};
static const Null null = Null();


struct Dontcheck {};
static const Dontcheck dontcheck = Dontcheck();
