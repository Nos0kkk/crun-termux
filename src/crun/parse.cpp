#include "parse.hpp"

void parse() {
    if (crun.path[0] != '/') {
        crun.path = std::filesystem::current_path().string() + "/" + crun.path;
    }

    if (crun.path[crun.path.length()] != '/') crun.path += '/';

    if (crun.logs) std::cout << "[CRUN][INFO]: get path to build.crun: '" << crun.path << "'" << std::endl;

    if (crun.logs) {
        for (int i = 0; i < crun.path.length(); i++) {
            if (crun.path[i] == '/' && crun.path[i + 1] == '/') {
                std::cout << "[CRUN][WARNING] maybe error in path: '" << crun.path << "'" << std::endl;
                break;
            }
        }
    }

    if (crun.logs) std::cout << "[CRUN][INFO]: open build.crun..." << std::endl;
    std::ifstream read(crun.path + "build.crun");
    if (!read.is_open()) {
        if (crun.logs) std::cerr << "[CRUN][ERROR]: cannot open build.crun. Please check path or file" << std::endl;
        std::cerr << "crun: error: the build.crun not found" << std::endl;
        return;
    }

    if (crun.logs) std::cout << "[CRUN][INFO]: parse build.crun..." << std::endl;

    std::string line;
    std::regex temp(R"(\w+=\{(.*)\})");
    std::smatch match;
    int lc = 1;
    while (std::getline(read, line)) {
        if (line.empty()) {
            if (crun.logs) std::cout << "[CRUN][PARSE][INFO]: current string is empty. Skip" << std::endl;
            lc++;
            continue;
        }
        if (line[0] == '#') {
            if (crun.logs) std::cout << "[CRUN][PARSE][INFO]: current string is comment. Skip" << std::endl;
            lc++;
            continue;
        }

        if (line.substr(0, line.find('=')) == "COMPILER") {
            crun.parse.compiler = line.substr(line.find('=') + 1, line.length());
            if (crun.logs) std::cout << "[CRUN][PARSE][INFO]: set compiler: '" << crun.parse.compiler << "'" << std::endl;
        } else if (line.substr(0, line.find('=')) == "EXEC") {
            crun.parse.exec = line.substr(line.find('=') + 1, line.length());
            if (crun.logs) std::cout << "[CRUN][PARSE][INFO]: set a name is executable: '" << crun.parse.exec << "'" << std::endl;
        } else if (line.substr(0, line.find('=')) == "START") {
            if (line.substr(line.find('=') + 1, line.length()) != "ON" && line.substr(line.find('=') + 1, line.length()) != "OFF") {
                if (crun.logs) std::cout << "[CRUN][PARSE][ERROR]: cannot argument '" << line.substr(line.find('='), line.length()) << "' in operation START" << std::endl;
                std::cerr << "crun: syntax error: cannot argument is '" << line.substr(line.find('=') + 1, line.length()) << "' in operation START" << std::endl;
                return;
            } else {
                if (line.substr(line.find('=') + 1, line.length()) == "ON") crun.parse.start = true;
                else crun.parse.start = false;
                if (crun.logs) std::cout << "[CRUN][PARSE][INFO]: set a flag START of " << (crun.parse.start ? "true" : "false") << std::endl;
            }
        } else if (line.substr(0, line.find('=')) == "SRC") { // regex operation
            if (std::regex_match(line, match, temp)) {
                std::string&& s = match.str(1);
                std::vector<std::string> fs;

                bool more = false;
                for (int i = 0; i < s.length(); i++) {
                    if (s[i] == ',') {
                        more = true;
                        break;
                    }
                }

                if (more) {
                    fs.push_back(s.substr(0, s.find(',')));
                    for (int i = 0; i < s.length(); i++) {
                        if (s[i] == ',') {
                            std::string s2;
                            for (int j = 0; j < s.length(); j++) {
                                if (s[i + j] == s[s.length()]) break;
                                if (s[i + j] != ',') s2 += s[i + j];
                                if (s[i + j + 1] == ',' ) break;
                                
                            }
                            fs.push_back(s2);
                        }
                    }
                } else {
                    fs.push_back(match.str(1));
                }

                for (const auto& f : fs) {
                    crun.parse.src += crun.path + f + " ";
                }
                if (crun.logs) std::cout << "[CRUN][PARSE][INFO]: set a source(s) file(s). List: '" << crun.parse.src << "'" << std::endl;
            } else {
                if (crun.logs) std::cerr << "[CRUN][PARSE][ERROR]: syntax error in line: " << lc << ": '" << line << "'" << std::endl;
                std::cerr << "crun: syntax error in line: " << lc << ": '" << line << "'" << std::endl;
                return;
            }
        } else if (line.substr(0, line.find('=')) == "OPTION") {
            if (std::regex_match(line, match, temp)) {
                std::string&& o = match.str(1);
                for (int i = 0; i < o.length(); i++) {
                    if (o[i] ==  ',') o[i] = ' ';
                }
                crun.parse.option = o;
                if (crun.logs) std::cout << "[CRUN][PARSE][INFO]: set a option(s). List: '" << crun.parse.option << "'" << std::endl;
            } else {
                if (crun.logs) std::cerr << "[CRUN][PARSE][ERROR]: syntax error in line: " << lc << ": '" << line << "'" << std::endl;
                std::cerr << "crun: syntax error in line: " << lc << ": '" << line << "'" << std::endl;
                return;
            }
        } else if (line.substr(0, line.find('=')) == "LIBS") {
            if (std::regex_match(line, match, temp)) {
                std::string&& l = match.str(1);
                for (int i = 0; i < l.length(); i++) {
                    if (l[i] == ',') l[i] = ' ';
                }
                crun.parse.libs = l;
                if (crun.logs) std::cout << "[CRUN][PARSE][INFO]: set a lib(s). List: '" << crun.parse.libs << "'" << std::endl;
            } else {
                if (crun.logs) std::cerr << "[CRUN][PARSE][ERROR]: syntax error in line: " << lc << ": '" << line << "'" << std::endl;
                std::cerr << "crun: syntax error in line: " << lc << ": '" << line << "'" << std::endl;
                return;
            }
        } else {
            if (crun.logs) std::cerr << "[CRUN][PARSE][ERROR]: in line: " << lc << ": '" << line << "' cannot operation" << std::endl;
            std::cerr << "crun: error: in line: " << lc << ": '" << line << "' cannot operation" << std::endl;
            return;
        }
        lc++;
    }
    std::string fullcommand = crun.parse.compiler + " " + crun.parse.src + " " + crun.parse.option + " " + crun.parse.exec + " " + crun.parse.libs;
    if (crun.showResultCommand) {
        std::cout << fullcommand << std::endl;
        return;
    }
    
    if (crun.logs) std::cout << "[CRUN][INFO]: the result command: '" << fullcommand << "'" << std::endl;
    if (crun.logs) std::cout << "[CRUN][INFO]: compiling..." << std::endl;

    crun.isBuild = true;
    std::thread([]{
        while (crun.isBuild) {
            std::cout << "\r / " << std::flush;
            std::this_thread::sleep_for(std::chrono::milliseconds(300));
            std::cout << "\r - " << std::flush;
            std::this_thread::sleep_for(std::chrono::milliseconds(300));
            std::cout << "\r \\ " << std::flush;
            std::this_thread::sleep_for(std::chrono::milliseconds(300));
            std::cout << "\r | " << std::flush;
            std::this_thread::sleep_for(std::chrono::milliseconds(300));
            std::cout << "\r / " << std::flush;
            std::this_thread::sleep_for(std::chrono::milliseconds(300));
        }
    }).detach();

    
    std::system(fullcommand.c_str());
    crun.isBuild = false;

    if (crun.parse.start) {
        if (crun.logs) std::cout << "[CRUN][INFO]: start program..." << std::endl;
        std::string sc = "./" + crun.parse.exec;
        std::system(sc.c_str());
    }
}