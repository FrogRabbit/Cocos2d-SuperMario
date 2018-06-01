#pragma once
#include "define.h"
#include <stdio.h>

class FileIO
{
private:
	static FileIO* m_this;
	FILE* fp;
	FileIO();
public:
	static FileIO* GetInstance()
	{
		if (m_this == NULL)
		{
			m_this = new FileIO();
		}
		return m_this;
	}
	char* FileOpen();
	void FileSave(char* buffer);
	~FileIO();
};

