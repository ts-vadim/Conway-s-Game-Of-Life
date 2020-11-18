#include "Graphics.h"


COORD Graphics::GetConsoleSize()
{
	CONSOLE_SCREEN_BUFFER_INFO sbInfo;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &sbInfo);
	short width = sbInfo.srWindow.Right - sbInfo.srWindow.Left + 1;
	short height = sbInfo.srWindow.Bottom - sbInfo.srWindow.Top + 1;
	return { width, height };
}


Graphics::Graphics()
{
	m_hconsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD size = GetConsoleSize();
	m_frame.Create(size.X, size.Y);
	m_output_screen = new CHAR_INFO[m_frame.width * m_frame.height];
	workingArea = { 0, 0, (SHORT)m_frame.width, (SHORT)m_frame.height };
	Clear();
}


Graphics::~Graphics()
{
	delete[] m_output_screen;
}


void Graphics::SetWorkingArea(SMALL_RECT area)
{
	workingArea = {
		area.Left,
		area.Right,
		area.Right,
		area.Bottom
	};
}


void Graphics::Resize(COORD size)
{
	m_frame.Create(size.X, size.Y);
	delete[] m_output_screen;
	m_output_screen = new CHAR_INFO[m_frame.width * m_frame.height];
	SetWorkingArea({ workingArea.Left, workingArea.Top, (SHORT)m_frame.width, (SHORT)m_frame.height });
	
	FrameBuffer* tmp = m_rendertarget;
	SetRenderTarget(&m_frame);
	Clear();
	SetRenderTarget(tmp);
}


void Graphics::SetRenderTarget(FrameBuffer* frame)
{
	m_rendertarget = frame;
}


void Graphics::ReleaseRenderTarget()
{
	m_rendertarget = &m_frame;
}


void Graphics::Clear(char c)
{
	bool selfFrame = m_rendertarget == &m_frame;
	int maxi = m_rendertarget->width * m_rendertarget->height;

	for (int i = 0; i < maxi; i++)
	{
		m_rendertarget->buffer[i] = c;
		if (selfFrame)
		{
			m_output_screen[i].Attributes = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
			m_output_screen[i].Char.AsciiChar = m_frame.buffer[i];
		}
	}
}


void Graphics::Display()
{
	for (int i = 0; i < m_frame.width * m_frame.height; i++)
		m_output_screen[i].Char.AsciiChar = m_frame.buffer[i];
	SMALL_RECT screen_write_area = { 0, 0, m_frame.width, m_frame.height };
	WriteConsoleOutputA(m_hconsole, m_output_screen, { (SHORT)m_frame.width, (SHORT)m_frame.height }, { 0, 0 }, &screen_write_area);
}


void Graphics::Char(int x, int y, char c)
{
	m_rendertarget->SetChar(x, y, c);
}


void Graphics::Rect(RECT area, char fill, char stroke)
{
	for (int y = area.top; y < area.bottom; y++)
	{
		for (int x = area.left; x < area.right; x++)
		{
			char c = fill;
			if (x == area.left || x == area.right - 1 || y == area.top || y == area.bottom - 1)
				c = stroke;
			m_rendertarget->SetChar(x, y, c);
		}
	}
}


void Graphics::Text(int x, int y, const char* format, ...)
{
	va_list args;
	va_start(args, format);
	vsnprintf_s(m_text_buffer, max_text_length, format, args);
	va_end(args);

	int str_len = strlen(m_text_buffer);
	for (int i = 0; i < str_len; i++)
		m_rendertarget->SetChar(x + i, y, m_text_buffer[i]);
}


void Graphics::Text(int x, int y, int max_length, const char* format, ...)
{
	va_list args;
	va_start(args, format);
	vsnprintf_s(m_text_buffer, max_text_length, format, args);
	va_end(args);

	int str_len = strlen(m_text_buffer);
	for (int i = 0; i < str_len && i < max_length; i++)
		m_rendertarget->SetChar(x + i, y, m_text_buffer[i]);
}


void Graphics::Frame(FrameBuffer& frame, int x, int y)
{
	for (int py = 0; py < frame.height; py++)
		for (int px = 0; px < frame.width; px++)
			m_rendertarget->SetChar(x + px, y + py, frame.GetChar(px, py));
}


void Graphics::Draw(Drawable& drawable)
{
	SetRenderTarget(&drawable.frame);
	drawable.Draw(*this);
	ReleaseRenderTarget();

	Frame(drawable.frame, drawable.position.x, drawable.position.y);
}


void Graphics::Cursor(int x, int y)
{
	SetConsoleCursorPosition(m_hconsole, { (short)x, (short)y });
}
