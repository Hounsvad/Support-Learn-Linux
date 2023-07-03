#include "../print/print.hpp"
#include "../random/random.hpp"

#include "folder_spam.hpp"
namespace strange_whiskers::folder_spam
{
    fs::path CreateBaseFolder(string &baseFolderName)
    {
        fs::path currentPath = fs::current_path();
        fs::path baseFolder = currentPath / baseFolderName;
        if (fs::exists(baseFolder))
        {
            strange_whiskers::print::Println("Base folder already exists");
            strange_whiskers::print::Println("Deleting base folder");
            fs::remove_all(baseFolder);
        }
        fs::create_directory(baseFolder);
        return baseFolder;
    }

    int CreateFoldersRecursively(fs::path &baseFolder, FolderCreationSpec &spec)
    {
        return CreateFolder(0, 0, baseFolder, spec);
    }

    int CreateFolder(int count, int depth, fs::path &parentFolder, FolderCreationSpec &spec)
    {
        if (depth > spec.maxDepth)
            return count;
        for (int i = 0; i < strange_whiskers::random::GetBoundedRandomInteger(2, spec.maxSubFolders); i++)
        {
            if (count == spec.maxFolders)
                return count;
            fs::path newFolder = parentFolder / std::to_string(count++);
            fs::create_directory(newFolder);
            count = CreateFolder(count, depth + 1, newFolder, spec);
        }
        return count;
    }
}