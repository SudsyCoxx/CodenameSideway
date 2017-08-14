#pragma once

class Renderer {
public:
	virtual void Setup() = 0;
	virtual void Destroy() = 0;
	virtual void Draw() = 0;

private:

protected:
};