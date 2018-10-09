#pragma once

class plane
{
public:
	plane(void);
	~plane(void);
	int x;
	int y;
	void draw(CDC* pDC);
};
