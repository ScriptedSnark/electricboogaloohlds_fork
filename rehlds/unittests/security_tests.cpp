#include "precompiled.h"
#include "rehlds_tests_shared.h"
#include "cppunitlite/TestHarness.h"

TEST(IsSafeFileExtension, SecurityChecks, 1000)
{
	struct testdata_t
	{
		const char* filename;
		bool safe;
	};

	testdata_t testdata[] = {
		{"radio/go.wav", true},
		{"radio/go.WAV", true},
		{"textures.wad", true},
#ifdef REHLDS_FIXES
		{"!QWERTY", true},
		// TODO:
		//{"file.dll2", true},
		//{"noext", false},
		//{".hidden", false},
		//{"subdir/.hidden", false},
#else
		{"file.dll2", false},
#endif
		{"../file.txt", false},
		{"/home/file.txt", false},
		{"C:/Windows/file.txt", false},
		{"models\\terror.mdl", false},
		{"file~.mdl", false},
		{"file.wav.", false},
		{"file.dll.txt", false},
		{"halflife.wad", false},
		{"pak0.pak", false},
		{"xeno.wad", false},
		{"file.cfg", false},
		{"file.lst", false},
		{"file.exe", false},
		{"file.vbs", false},
		{"file.com", false},
		{"file.bat", false},
		{"file.dll", false},
		{"file.ini", false},
		{"file.log", false},
		{"file.so", false},
		{"file.dylib", false},
		{"file.sys", false},
		{"file.SYS", false},
	};

	for (int i = 0; i < ARRAYSIZE(testdata); i++) {
		testdata_t* d = &testdata[i];
		bool result = IsSafeFileToDownload(d->filename);

		char msg[256];
		Q_snprintf(msg, sizeof msg, "IsSafeFileToDownload(%s) check", d->filename);
		CHECK(msg, result == d->safe);
	}

}
