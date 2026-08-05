#pragma once
#include <string>
#include <atomic>

struct CRun {
    std::string path;
    std::atomic<bool> isBuild;
    bool logs;
    bool showResultCommand;
    struct parse {
        std::string compiler;
        std::string src;
        std::string option;
        std::string exec;
        std::string libs;
        bool start;
        
    } parse; 
};

extern CRun crun;