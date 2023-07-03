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


    bool HandleProgramOptions(int argc, char **argv)
    {
        po::options_description desc("Allowed options");
        desc.add_options()
        ("help,h", "produce help message")
        ("baseFolder,p", po::value<string>()->default_value("."), "path of base folder")
        ("maxFolders,m", po::value<int>()->default_value(63), "set number of folders to create")
        ("depth,d", po::value<int>()->default_value(5), "set number of files to create")
        ("branchCount,b", po::value<int>()->default_value(2), "the number of branches to create at each node must be greater than 1.")
        ("branchCountRandomization,r", po::value<bool>()->default_value(false), "weather or not the number of branches should be randomized (always at least two)");
        po::positional_options_description p;
        p.add("baseFolder", 1);
        po::variables_map vm;
        po::store(po::parse_command_line(argc, argv, desc), vm);
        po::notify(vm);

        if (HandleHelpOption(argc, vm, desc))
            return true;

        
    }
}
    int main(int argc, char **argv)
    {
        return sw::arguments::HandleProgramOptions(argc, argv);
        string baseFolderName = "baseFolder";

        fs::path baseFolder = swfs::CreateBaseFolder(baseFolderName);
        swfs::FolderCreationSpec spec{10, 3, 200000};

        // Initialize the randomiser
        swr::Initialize();

        swp::Println(std::to_string(CreateFoldersRecursively(baseFolder, spec)));

        return 0;
    }

