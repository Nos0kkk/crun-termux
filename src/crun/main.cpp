#include "libs.hpp"
#include "parse.hpp"

int main(int argc, char** argv)  {
    CLI::App app{"CRun - simple and easy builder for C/C++ project"};

    crun.logs = false;
    crun.showResultCommand = false;

    CLI::Option* crun_path = app.add_option("-p,--parse,parse", crun.path, "parse build.crun")->type_name("<path>")->check(CLI::ExistingPath);
    CLI::Option* logs_flg = app.add_flag("-l,--logs", crun.logs, "show runtime logs")->needs(crun_path);
    CLI::Option* start_flg = app.add_flag("-s,--start", crun.parse.start, "auto start is result program")->needs(crun_path);
    CLI::Option* see_result_command = app.add_flag("-m,--show-result-command", crun.showResultCommand, "show is result command for build")->excludes(start_flg)->needs(crun_path);
    

    try {
        app.parse(argc, argv);
    } catch (CLI::ParseError& e) {
        return app.exit(e);
    }

    if (crun_path->count() > 0) parse();

    return 0;
}