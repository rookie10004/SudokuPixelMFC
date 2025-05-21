#pragma once
#include <string>
#include <exception>

//Exception Klassen f�r entsprechende Fehlerbehandlungen(alle gleich man h�tte sich das sparen k�nnen... )
class FileException : public std::exception
{
private:
	std::string exception;

public:
	FileException(std::string exception) : exception(exception) { }

	const char* what() const override { return exception.c_str(); }
};

class SpriteException : public std::exception
{
private:
	std::string exception;

public:
	SpriteException(std::string exception) : exception(exception) { }

	const char* what() const override { return exception.c_str(); }
};

class OSException : public std::exception
{
private:
	std::string exception;

public:
	OSException(std::string exception) : exception(exception) {}

	const char* what() const override { return exception.c_str(); }
};