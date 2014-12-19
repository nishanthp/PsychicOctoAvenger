/*This is the header file which would contain all the required class definitions. Each class contains the following functions. 
1. contruct(), which will print all the required headers, namespace, class name, and the constructs of the class (required for the generated code).  
2. failTest(), which will print the failTest() method/function of the generated Code
3. checkArgs(), which will print the checkArgs() method/function which will be used to check the warning and critical values 
4. executePlugin(), which will print the executePlugin() method/function. The implementation of this method in the generated code is specific to its class.
*/
#ifndef Plugin_h
#define Plugin_h
#include "BON.h"
#include "BONImpl.h"
#include <ComponentConfig.h>


namespace PluginImpl
{
	/** CPU_Usage class is defined
	**/
	class CPU_Usage												
{
public:
	CPU_Usage();
	~CPU_Usage();
public:
	void construct(std::ofstream& outfile);						//outfile is passed as reference. Using this reference the code is generated on the test file.
	void failTest(std::ofstream& outfile);
	void checkArgs(std::ofstream& outfile);
	void executePlugin(std::ofstream& outfile);
};

	/**OpenProcess class is defined
	**/
class Open_Process
{
public:
	Open_Process();
	~Open_Process();
public:
	void construct(std::ofstream& outfile);
	void failTest(std::ofstream& outfile);
	void checkArgs(std::ofstream& outfile);
	void executePlugin(std::ofstream& outfile);
};

/** Memory_Load class is defined
	**/
class Memory_Load
{
	public:
		Memory_Load();
		~Memory_Load();
	public:
	void construct(std::ofstream& outfile);
	void failTest(std::ofstream& outfile);
	void checkArgs(std::ofstream& outfile);
	void executePlugin(std::ofstream& outfile);
};
/** Memory_Usage class is defined
	**/
class Memory_Usage
{
public:
	Memory_Usage();
	~Memory_Usage();
public:
	void construct(std::ofstream& outfile);
	void failTest(std::ofstream& outfile);
	void checkArgs(std::ofstream& outfile);
	void executePlugin(std::ofstream& outfile);
};
/** Shared_Folders class is defined
	**/
class Shared_Folders
{
public:
	Shared_Folders();
	~Shared_Folders();
public:
	void construct(std::ofstream& outfile);
	void failTest(std::ofstream& outfile);
	void checkArgs(std::ofstream& outfile);
	void executePlugin(std::ofstream& outfile);
};

};
#endif