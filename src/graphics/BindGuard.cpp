#include <funnan/graphics/BindGuard.h>

using namespace funnan::graphics;

BindGuard::BindGuard(const Bindable& x) : bindable{x}
{
	this->bindable.bind();
}

BindGuard::~BindGuard()
{
	this->bindable.unbind();
}
