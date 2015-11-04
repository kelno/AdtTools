#ifndef H_CONSOLE_TOOL_TEMPLATE
#define H_CONSOLE_TOOL_TEMPLATE

#include <iostream>
#include <string>
#include <vector>

struct ToolArgument
{
    ToolArgument(std::string const& name, bool required = true) :
        name(name),
        required(required)
    { };

    std::string name = "";
    bool required = false;
};


class ConsoleTool
{
public:
    std::string const& GetVersion() const;
    std::string const& GetQuickDescription() const;
    std::string const& GetFullDescription() const;
    std::vector<ToolArgument> const& GetArguments() const;

    unsigned int GetMinArgumentCount() const;
    unsigned int GetMaxArgumentCount() const;
    
    virtual int Work(int argc, char* argv[]) { return 0; };
protected:
    ConsoleTool(std::string const& version, std::string const& quickDescription, std::string const& fullDescription, std::vector<ToolArgument> const& arguments);

private:
    std::string version;
	std::string quickDescription;
    std::string fullDescription;
    std::vector<ToolArgument> arguments;
};

#endif