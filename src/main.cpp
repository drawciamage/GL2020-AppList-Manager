#include "main.hpp"
#include "File.cpp"
#include "patch.cpp"
#include "argparser.cpp"
#include "NewChar.cpp"

int main(int argc, char * argv[])
{
    const auto argcv = argv+argc;
    FileExplorer Index(IndexFile, INDEXNAME);
    
    std::cout << "  GL2020 AppList Manager" << "\n";

    if(cmdOptionExists(argv, argcv, "-v"))
    {
        std::cout << "      Version: " << VERSION << "\n";
        return 0;
    }

    if(cmdOptionExists(argv, argcv, "-a"))
    {
        std::cout << "\n" << "      Arbitrary AppList." << "\n" << "\n";
        
        const unsigned short param = atoi(getCmdOption(argv, argcv, "-a"));
        
        if(!param) return 0;
        if(param >= INDEXLIMIT) return 0;
        if(cmdOptionExists(argv, argcv, "-D")) deleteAppList();

        addToAppList(param);
        
        return 0;
    }

    if(cmdOptionExists(argv, argcv, "-D"))
    {
        deleteAppList();
    } else std::cout << "       Populating AppList..." << "\n";

    addToAppList(0);

    return 0;
}

void deleteAppList()
{
    std::cout << "      Deleting AppList..." << "\n";

    for (unsigned short item = 0; item < INDEXLIMIT; ++item)
    {
        std::string cppString = "AppList/" + patch::toString(item) + ".txt";
        char* cString;
        NewChar StringToChar(cString, cppString.length() + 1);
        strcpy(cString, cppString.c_str());

        if (remove( cString ) != 0) continue;
    }

    std::cout << "      AppList deleted." << "\n" << "\n"
              << "      Repopulating AppList..." << "\n"
              << "      Populating AppList..." << "\n"; 
}

void addToAppList(const unsigned short initialIndex)
{
    for (unsigned short indexTotal = initialIndex; indexTotal < INDEXLIMIT; ++indexTotal)
    {
        std::string line;
        std::getline( IndexFile, line );

        if (line == "") break;

        std::ofstream addApp;
        std::string addAppName = "AppList/" + patch::toString(indexTotal) + ".txt";
        addApp.open(addAppName, std::ios::out | std::ios::trunc | std::ios::in);

        if (addApp.is_open())
        {
            addApp << std::stoi(parserIndex(line, INDEXSYMBOL));
            addApp.close();
        } else { std::cout << "     Unable to save file"; return; }
    }

    std::cout << "Done!";
}