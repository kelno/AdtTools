#ifndef H_CONSOLE_TOOL_TEMPLATE
#define H_CONSOLE_TOOL_TEMPLATE

#include <iostream>
#include <string>
#include <list>
#include <assert.h>

class adt;

/* Description of an argument to be given to a tool
*/
struct ToolArgument
{
    ToolArgument(std::string const& name, std::string const& description = "", bool required = true) :
        name(name),
        description(description),
        required(required)
    { };

    std::string name;
    std::string description;
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
    std::list<ToolArgument> const& GetArguments() const;
    
    /* Minimal argument count. This value is dynamically calculated from the argument list */
    unsigned int GetMinArgumentCount() const;
    /* Maximum argument count. This value is dynamically calculated from the argument list */
    unsigned int GetMaxArgumentCount() const;
    
    /* Main tool function, works as a main(...) 
    Note that the first command argument is at argv[2] (1 being the tool name)
    */
    virtual int Work(int argc, char* argv[]) = 0;

protected:
    /* Constructor
    @version Tool version
    @shortDescription A short description of the tool (this shouldn't exceed one sentence)
    @fullDescription An as long as you want description of the tool
    @arguments Argument list for this tool. The given container is copied in this class
    */
    ConsoleTool(std::string const& commandName, std::string const& version, std::string const& shortDescription, std::string const& fullDescription, std::list<ToolArgument> const& arguments);

    //helpers, use if you want
    /* try opening fileName into adt, return the file stream on success, else print an error and return an empty pointer. */
    std::fstream* OpenAdtFile(std::string fileName, adt*& adt);

private:
    std::string commandName;
    std::string version;
	std::string shortDescription;
    std::string fullDescription;
    std::list<ToolArgument> arguments;

};

#endif