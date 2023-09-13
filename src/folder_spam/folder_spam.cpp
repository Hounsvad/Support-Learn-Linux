#include <map>

#include "../print/print.hpp"
#include "../random/random.hpp"


#include "folder_spam.hpp"


namespace sw = strange_whiskers;
namespace swfs = sw::folder_spam;
namespace swr = sw::random;
namespace swp = sw::print;

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

    void SpreadFiles(int foldercount, string &filesToHide, string &fileLocation)
    {
        // Find number of files to hide
        int count = std::distance(fs::directory_iterator{fs::canonical(fs::path{filesToHide})}, fs::directory_iterator());
        std::map<int, fs::path> folderNumberToPath{};
        // Get the numbers for the folders to hide files in and assign them to a map with the files to hide
        for (auto const &entry : fs::directory_iterator{fs::canonical(fs::path{filesToHide})})
        {
            auto fileindex = swr::GetBoundedRandomInteger(foldercount / 1000, foldercount);
            folderNumberToPath[fileindex] = entry.path();
        }

        //Iterate over the large file tree and copy the files to the folders
        for (auto const &entry : fs::recursive_directory_iterator{fs::canonical(fs::path{fileLocation})})
        {
            int folderNumber = atoi(entry.path().filename().c_str());
            if(folderNumberToPath.find(folderNumber) != folderNumberToPath.end())
                fs::copy(folderNumberToPath.at(folderNumber), entry.path());
        }
        // Iterate the big folder tree and place files based on the created vector
        fs::recursive_directory_iterator dir_itr = fs::recursive_directory_iterator(".");
    }
}