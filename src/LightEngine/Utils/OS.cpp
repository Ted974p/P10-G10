#include "OS.h"

#pragma region External Dependencies

#include <windows.h>
#include <string>
#include <locale>
#include <codecvt>

#include <filesystem>
#include <string>
#include <vector>

#pragma endregion

namespace fs = std::filesystem;

std::string OS::GetExecutablePath() {
    wchar_t path[MAX_PATH];
    DWORD length = GetModuleFileName(NULL, path, MAX_PATH);

    if (length == 0) {
        return "";
    }

    int bufferSize = WideCharToMultiByte(CP_UTF8, 0, path, -1, NULL, 0, NULL, NULL);
    if (bufferSize == 0) {
        return "";
    }

    std::string result(bufferSize - 1, '\0');
    WideCharToMultiByte(CP_UTF8, 0, path, -1, &result[0], bufferSize, NULL, NULL);

    for (char& ch : result) {
        if (ch == '\\') {
            ch = '/';
        }
    }

    size_t pos = result.find_last_of("/");
    if (pos != std::string::npos) {
        result = result.substr(0, pos);
    }

    return result;
}

std::string OS::GetAbsolutePath(std::string path) {
   return fs::absolute(path).generic_string(); 
}

std::vector<std::string> OS::GetFilesInDirectory(std::string path, std::string extension) {
    std::vector<std::string> files;

    fs::path directoryPath(path);

    for (const auto& entry : fs::recursive_directory_iterator(directoryPath)) {
        if (fs::is_regular_file(entry) && entry.path().extension() == extension) {
            files.push_back(entry.path().string());
        }
    }

    return files;
}