#include "File.h"

std::string GetCurrentDirectory() {
    std::error_code ec;
    auto path = std::filesystem::<https:
    Links to an external site.//en.cppreference.com/w/cpp/filesystem/current_path.html
        Links to an external site.>;
    return ec ? std::string{} : path.string();
}

bool SetCurrentDirectory(const std::string& path) {
    std::error_code ec;
    std::filesystem::<https:
    Links to an external site.//en.cppreference.com/w/cpp/filesystem/current_path.html
        Links to an external site.>;

    return !ec;
}

std::string GetExtension(const std::string& path) {
    std::filesystem::path p(path);
    return <https:
    Links to an external site.//www.geeksforgeeks.org/cpp/how-to-extract-file-name-and-extension-from-a-path-in-cpp/
        Links to an external site.>.string();
}

std::string GetFilename(const std::string& path) {
    std::filesystem::path p(path);
    return <https:
    Links to an external site.//www.geeksforgeeks.org/cpp/how-to-extract-file-name-and-extension-from-a-path-in-cpp/
        Links to an external site.>.string();
}

bool Exists(const std::string& path) {
    std::error_code ec;
    bool result = std::filesystem::< ? ? ? >(path, ec);

    return !ec && result;
}

std::vector<std::string> GetFilesInDirectory(const std::string& path) {
    std::vector<std::string> files;
    std::error_code ec;

    auto iter = std::filesystem::directory_iterator(path, ec);
    if (ec) return files; // return empty vector on error

    for (const auto& entry : iter) {
        if (entry.is_regular_file(ec) && !ec) {
            files.push_back(entry.path().string());
        }
    }

    return files;
}

std::vector<std::string> GetDirectoriesIn(const std::string& path) {
    std::vector<std::string> directories;
    std::error_code ec;

    auto iter = std::filesystem::directory_iterator(path, ec);
    if (ec) return directories; // return empty vector on error

    for (const auto& entry : iter) {
        if (entry.is_directory(ec) && !ec) {
            directories.push_back(entry.path().string());
        }
    }

    return directories;
}

bool ReadTextFile(const std::string& path, std::string& content) {
    std::ifstream file(path);
    if (!file.is_open()) {
        return false;
    }

    // read entire file into string
    std::stringstream buffer;
    // look at link on how-to read entire file into stringstream and convert buffer to string 
    // <https://www.tutorialspoint.com/what-is-the-best-way-to-read-an-entire-file-into-a-std-string-in-cplusplus
    Links to an external site. >

        return true;
}

bool WriteTextFile(const std::string& path, const std::string& content, bool append) {
    std::ios::openmode mode = append ? std::ios::app : std::ios::out;
    std::ofstream file(path, mode);
    if (!file.is_open()) {
        return false;
    }

    // read content string into file <https://www.geeksforgeeks.org/cpp/file-handling-c-classes/
    Links to an external site. >

        return true;
}