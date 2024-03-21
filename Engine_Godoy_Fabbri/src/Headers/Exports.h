#pragma once

#ifdef EXPORTS
#define TOTO_API __declspec(dllexport)
#else
#define TOTO_API __declspec(dllimport)
#endif