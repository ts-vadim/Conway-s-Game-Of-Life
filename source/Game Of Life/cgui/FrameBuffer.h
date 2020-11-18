#pragma once



class FrameBuffer
{
public:
	char* buffer = nullptr;
	unsigned short width = 0;
	unsigned short height = 0;

	FrameBuffer()
	{
	}
	FrameBuffer(unsigned short w, unsigned short h)
	{
		Create(w, h);
	}
	~FrameBuffer()
	{
		Delete();
	}

	void Create(unsigned short w, unsigned short h)
	{
		delete[] buffer;
		buffer = new char[w * h];
		for (int i = 0; i < w * h; i++)
			buffer[i] = ' ';
		width = w;
		height = h;
	}

	void Delete()
	{
		delete[] buffer;
		width = 0;
		height = 0;
	}

	void Copy(FrameBuffer& other)
	{
		for (int x = 0; x < width; x++)
		{
			for (int y = 0; y < height; y++)
			{
				char c = GetChar(x, y);
				if (c != -1)
					other.SetChar(x, y, c);
			}
		}
	}

	void SetChar(int x, int y, char c)
	{
		if (OnFrame(x, y))
			buffer[x + y * width] = c;
	}

	char GetChar(int x, int y)
	{
		return (OnFrame(x, y)) ? buffer[x + width * y] : -1;
	}

	bool OnFrame(int x, int y)
	{
		return x >= 0 && x < width && y >= 0 && y < height;
	}

	bool operator==(FrameBuffer& other)
	{
		if (width != other.width || height != other.height)
			return false;
		for (int i = 0; i < width * height; i++)
			if (buffer[i] != other.buffer[i])
				return false;
		return true;
	}
};
