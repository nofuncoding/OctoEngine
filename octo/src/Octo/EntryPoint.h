#pragma once

#if (defined _WIN32) || (defined __linux__)

extern Octo::Application* Octo::CreateApplication();

int main(int argc, char** argv)
{
    // TODO: Move these things away
    Octo::Log::Init();

    auto app = Octo::CreateApplication();
    app->Run();
    delete app;
}

#endif