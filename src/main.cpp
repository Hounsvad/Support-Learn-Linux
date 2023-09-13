#include <filesystem>
#include <string>
#include <iostream>
#include <boost/program_options.hpp>

#include "random/random.hpp"
#include "print/print.hpp"
#include "folder_spam/folder_spam.hpp"

namespace fs = std::filesystem;
namespace po = boost::program_options;

namespace sw = strange_whiskers;
namespace swfs = sw::folder_spam;
namespace swr = sw::random;
namespace swp = sw::print;

#define string std::string
#define ri(l, u) strange_whiskers::random::GetBoundedRandomInteger(l, u)

namespace strange_whiskers::arguments
{
    struct program_options_return
    {
        bool requestedHelp;
        po::variables_map vm;
    };

    bool HandleHelpOption(int argc, po::variables_map &vm, po::options_description &desc)
    {
        if (argc == 1 || vm.count("help"))
        {
            std::stringstream stringStream;
            desc.print(stringStream);
            swp::Println(stringStream.str());
            return true;
        }
        return false;
    }

    program_options_return HandleProgramOptions(int argc, char **argv)
    {
        program_options_return result;
        result.requestedHelp = false;
        po::options_description desc("Allowed options");
        desc.add_options()("help,h", "produce help message")
        ("filesToHide,f", po::value<string>(), "files to hide in the folders")
        ("baseFolder,p", po::value<string>()->default_value("."), "path of base folder")
        ("maxFolders,m", po::value<int>()->default_value(200000), "set number of folders to create")
        ("depth,d", po::value<int>()->default_value(10), "set number of files to create")
        ("branchCount,b", po::value<int>()->default_value(3), "the number of branches to create at each node must be greater than 1.")
        ("branchCountRandomization,r", po::value<bool>()->default_value(false), "Whether or not the number of branches should be randomized (always at least two)");

        po::positional_options_description p;
        p.add("baseFolder", 1);
        po::variables_map vm;
        po::store(po::parse_command_line(argc, argv, desc), vm);
        po::notify(vm);

        if (HandleHelpOption(argc, vm, desc))
            return result;
        result.vm = vm;
        return result;
    }
}



int main(int argc, char **argv)
{
    auto options = sw::arguments::HandleProgramOptions(argc, argv);
    auto baseFolderName = options.vm["baseFolder"].as<string>();
    auto maxDepth = options.vm["depth"].as<int>();
    auto maxSubFolders = options.vm["branchCount"].as<int>();
    auto maxFolders = options.vm["maxFolders"].as<int>();



    fs::path baseFolder = swfs::CreateBaseFolder(baseFolderName);
    swfs::FolderCreationSpec spec{10, 3, 200000};

    // Initialize the randomiser
    swr::Initialize();

    int createdFolderCount = CreateFoldersRecursively(baseFolder, spec);

    // Create the folders
    swp::Println(std::to_string(createdFolderCount));

    // Spread the files
    auto filesToHide = options.vm["filesToHide"].as<string>();
    strange_whiskers::folder_spam::SpreadFiles(createdFolderCount, filesToHide, baseFolderName);

    return 0;
}
