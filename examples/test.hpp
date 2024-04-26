#pragma once

#include <cstdlib>

#define TEST(__expr__) if (!(__expr__)) { printf("%s:%d => Expression failed \"%s\"\n", __FILE__, __LINE__, #__expr__); abort(); }