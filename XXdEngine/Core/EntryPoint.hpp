#ifndef ENTRY_POINT_HPP
#define ENTRY_POINT_HPP

extern xxd::Application* xxd::CreateApplication();

int main(int argc, const char* argv[])
{
	auto App = xxd::CreateApplication();
	App->Run();
	delete App;
	return 0;
}

#endif
