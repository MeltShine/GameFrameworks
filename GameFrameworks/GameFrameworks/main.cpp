#include "Application.h"
#include "Core.h"

using namespace meltshine;
int main()
{
	auto app = meltshine::Application::GetInstance();
	app->Init(800, 600, TEXT("HelloWorld"));
	auto core = Core::Create();
	core->Init(app->GetWindowHandle(), app->GetInstanceHandle());
	app->SetOnRunCallback(std::bind(&Core::Run, core));
	return app->Run();
}