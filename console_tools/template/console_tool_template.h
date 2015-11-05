#ifndef H_CONSOLE_TOOL_TEMPLATE
#define H_CONSOLE_TOOL_TEMPLATE

#include <iostream>
#include <string>
#include <vector>

/* Description of an argument to be given to a tool
*/
struct ToolArgument
{
    ToolArgument(std::string const& name, bool required = true) :
        name(name),
        required(required)
    { };

    std::string name = "";
    bool required = false;
};


/* All tools mother class
*/
class ConsoleTool
{
public:
    /* Returns the name of the tool */
    std::string const& GetCommandName() const;
    /* Returns the version of the tool */
    std::string const& GetVersion() const;
    /* Returns a short description of the tool */
    std::string const& GetShortDescription() const;
    /* Returns the full description of the tool */
    std::string const& GetFullDescription() const;
    /* Get arguments list for this tool */
    std::vector<ToolArgument> const& GetArguments() const;
    
    /* Minimal argument count. This value is dynamically calculated from the argument list */
    unsigned int GetMinArgumentCount() const;
    /* Maximum argument count. This value is dynamically calculated from the argument list */
    unsigned int GetMaxArgumentCount() const;
    
    /* Main tool function, works as a main(...) */
    virtual int Work(int argc, char* argv[]) = 0;

protected:
    /* Constructor
    @version Tool version
    @shortDescription A short description of the tool (this shouldn't exceed one sentence)
    @fullDescription An as long as you want description of the tool
    @arguments Argument list for this tool. The given container is copied in this class
    */
    ConsoleTool(std::string const& commandName, std::string const& version, std::string const& shortDescription, std::string const& fullDescription, std::vector<ToolArgument> const& arguments);

private:
    std::string commandName;
    std::string version;
	std::string shortDescription;
    std::string fullDescription;
    std::vector<ToolArgument> arguments;
};

#endif