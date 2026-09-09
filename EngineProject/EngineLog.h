#pragma once

#include "Engine.h"

#define LOG(Verbosity, ...) \
    Engine::GetConsolePanel()->AddLog(ELogVerbosity::Verbosity, __VA_ARGS__);