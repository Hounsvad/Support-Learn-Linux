#include <filesystem>
#include <string>

#define string std::string

namespace fs = std::filesystem;
namespace strange_whiskers::folder_spam {

struct FolderCreationSpec {
    int maxDepth {0};
    int maxSubFolders {0};
    int maxFolders {0};
};

fs::path CreateBaseFolder(string& baseFolderName);
    int CreateFoldersRecursively(fs::path& baseFolder, FolderCreationSpec& spec);
    int CreateFolder(int count, int depth, fs::path& parentFolder, FolderCreationSpec& spec);
}