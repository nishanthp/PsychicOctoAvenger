/*This is the header file which would contain all the required class definitions. Each class contains the following functions. 
1. contruct(), which will print all the required headers, namespace, class name, and the constructs of the class (required for the generated code).  
2. failTest(), which will print the failTest() method/function of the generated Code
3. checkArgs(), which will print the checkArgs() method/function which will be used to check the warning and critical values 
4. executePlugin(), which will print the executePlugin() method/function. The implementation of this method in the generated code is specific to its class.
*/


#include "StdAfx.h"
#include "Plugin.h"

#include <Console.h>
#include "BON2Component.h"

#include <sstream>
#include  <fstream>
#include <string>
#include <iostream>
#include <stdio.h>
#include <cstddef>



namespace PluginImpl
{
	/*The below code contains the implementations of the functions/methods for each class defined in the Plugin.h (header) file
	*/
	Open_Process::Open_Process()
	{
		
		
	}

	Open_Process::~Open_Process()
	{
	
	}

	void Open_Process::construct(std::ofstream& outfile)

	{
		outfile<<"using System;"<<std::endl;
		outfile<<"using System.Collections.Generic;"<<std::endl;
		outfile<<"using System.Linq;"<<std::endl;
		outfile<<"using System.Linq;"<<std::endl;
		outfile<<"using System.Text;"<<std::endl;
		outfile<<"using System.Management;"<<std::endl;
		outfile<<"using System.Diagnostics;"<<std::endl;
		outfile<<"using System.IO;"<<std::endl;
		outfile<<"namespace TrustMonitoringTools.Plugins.User"<<std::endl;
		outfile<<"{"<<std::endl;
		outfile<<"public class Check_User_Open_Processes : IPlugins"<<std::endl;
		outfile<<"{"<<std::endl;
		outfile<<"private string resultString;"<<std::endl;
		outfile<<"private ATypes warning;"<<std::endl;
		outfile<<"private ATypes critical;"<<std::endl;
		outfile<<"private bool hasArgs;"<<std::endl;
		outfile<<"public Check_User_Open_Processes()"<<std::endl;
		outfile<<"{"<<std::endl;
		outfile<<"warning = new ATypes(60);"<<std::endl;
		outfile<<"critical = new ATypes(80);"<<std::endl;
		outfile<<"hasArgs = false;"<<std::endl;
		outfile<<"}"<<std::endl;
		outfile<<"public Check_User_Open_Processes(String warning, String critical)"<<std::endl;
		outfile<<"{"<<std::endl;
		outfile<<"this.warning = new ATypes(warning);"<<std::endl;
		outfile<<"this.critical = new ATypes(critical);"<<std::endl;
		outfile<<"hasArgs = true;"<<std::endl;
		outfile<<"}"<<std::endl;
	}
	void Open_Process::failTest(std::ofstream& outfile)

	{
		outfile<<"public bool failTest()"<<std::endl;
		outfile<<"{"<<std::endl;
		outfile<<"string file_path = Constants.PLUGIN_FAIL_TESTS_DIRECTORY + this.GetType().Name.ToLower() + \".txt\";"<<std::endl;
		outfile<<" if (Constants.FAIL_TEST_MODE && File.Exists(file_path))"<<std::endl;
		outfile<<"{"<<std::endl;
		outfile<<"int result = -1;"<<std::endl;
		outfile<<"if ((new FileInfo(file_path).Length > 0))"<<std::endl;
		outfile<<"{"<<std::endl;
		outfile<<" string line = File.ReadAllText(file_path).Trim();"<<std::endl;
		outfile<<" if (Int32.TryParse(line, out result))"<<std::endl;
		outfile<<"{"<<std::endl;
		outfile<<"  result = Int32.Parse(line);"<<std::endl;
		outfile<<"}"<<std::endl;
		outfile<<"}"<<std::endl;
		outfile<<"if (result == -1)"<<std::endl;
		outfile<<"{"<<std::endl;
		outfile<<"result = this.critical.getInt() + 1;"<<std::endl;
		outfile<<"}"<<std::endl;
		outfile<<"resultString = String.Format(\"USER OPEN PROCESSES: Making Test fail | metric=0.0 users_open_processes={0};60;80\", result);"<<std::endl;
		outfile<<"return true;"<<std::endl;
		outfile<<"}"<<std::endl;
		outfile<<"else"<<std::endl;
		outfile<<"return false;"<<std::endl;
		outfile<<"}"<<std::endl;
		


	}
	void Open_Process::executePlugin(std::ofstream& outfile)
	{
		outfile<<" public int executePlugin()"<<std::endl;
		outfile<<"{"<<std::endl;
		outfile<<"int retVal = 3;"<<std::endl;
		outfile<<"if (failTest())"<<std::endl;
		outfile<<"retVal = 2;"<<std::endl;
		outfile<<"else"<<std::endl;
		outfile<<"{"<<std::endl;
		outfile<<"if (hasArgs)"<<std::endl;
		outfile<<"{"<<std::endl;
		outfile<<"if (!this.checkArgs())"<<std::endl;
		outfile<<"{"<<std::endl;
		outfile<<"Console.WriteLine(\"Error: Check your arguments\");"<<std::endl;
		outfile<<"return 3;"<<std::endl;
		outfile<<"}"<<std::endl;
		outfile<<"}"<<std::endl;
		outfile<<"string user = String.Empty;"<<std::endl;
		outfile<<"int max = 0;"<<std::endl;
		outfile<<"string performance_data = \" \";"<<std::endl;
		outfile<<"Dictionary<string, int> dic = this.getProcessOwner();"<<std::endl;
		outfile<<"foreach(KeyValuePair<string, int> entry in dic) "<<std::endl;
		outfile<<"{"<<std::endl;
		outfile<<"string key = entry.Key.Trim();"<<std::endl;
		outfile<<"int value = entry.Value;"<<std::endl;
		outfile<<"if (key.Contains(\" \")) key = key.Replace(\" \", \"_\");"<<std::endl;
		outfile<<"if ((int)entry.Value > max)"<<std::endl;
		outfile<<"{"<<std::endl;
		outfile<<"max = value;"<<std::endl;
		outfile<<"user = key;"<<std::endl;
		outfile<<"}"<<std::endl;
		outfile<<"performance_data += \" \" + key + \"=\" + value.ToString() + \";\" + this.warning.getInt().ToString() + \";\" + this.critical.getInt().ToString();"<<std::endl;
		outfile<<"}"<<std::endl;
		outfile<<"string metric_data = \" | metric=\";"<<std::endl;
		outfile<<"double metric = 0.0;"<<std::endl;
		outfile<<"ATypes a1 = new ATypes(max);"<<std::endl;
		outfile<<"if (max < this.warning.getInt())"<<std::endl;
		outfile<<"{"<<std::endl;
		outfile<<"metric = 1.0;"<<std::endl;
		outfile<<"resultString = \"USER PROCESSES OK: No users exceeding thresholds\" + metric_data + metric.ToString(\"N2\") + performance_data;"<<std::endl;
		outfile<<"retVal = 0;"<<std::endl;
		outfile<<"}"<<std::endl;
		outfile<<"else if (max >= this.warning.getInt() && max < this.critical.getInt())"<<std::endl;
		outfile<<"{"<<std::endl;
		outfile<<"metric = (1.0 / (this.warning.getDouble() - this.critical.getDouble())) * (a1.getDouble() - this.warning.getDouble()) + 1.0;"<<std::endl;
		outfile<<" resultString = \"USER PROCESSES WARNING: User \" + user + \" found with \" + max + \" services \" + metric_data + metric.ToString(\"N2\") + performance_data;"<<std::endl;
		outfile<<" retVal = 1;"<<std::endl;
		outfile<<"}"<<std::endl;
		outfile<<" else if (max >= this.critical.getInt())"<<std::endl;
		outfile<<"{"<<std::endl;
		outfile<<" metric = 0.0;"<<std::endl;
		outfile<<"resultString = \"USER PROCESSES CRITICAL: User \" + user + \" found with \" + max + \" services \" + metric_data + metric.ToString(\"N2\") + performance_data;"<<std::endl;
		outfile<<"retVal = 2;"<<std::endl;
		outfile<<"}"<<std::endl;
		outfile<<"else"<<std::endl;
		outfile<<"{"<<std::endl;
		outfile<<"resultString = \"USER PROCESSES UNKNOWN: Unknown error\";"<<std::endl;
		outfile<<"retVal = 3;"<<std::endl;
		outfile<<"}"<<std::endl;
		outfile<<"}"<<std::endl;
		outfile<<"Console.WriteLine(resultString);"<<std::endl;
		outfile<<"return retVal;"<<std::endl;
		outfile<<"}"<<std::endl;
		
		
	}
	void Open_Process::checkArgs(std::ofstream& outfile)

	{
		outfile<<"public bool checkArgs()"<<std::endl;
		outfile<<"{"<<std::endl;
		outfile<<"if (this.warning.getInt() > this.critical.getInt())"<<std::endl;
		outfile<<"{"<<std::endl;
		outfile<<" return false;"<<std::endl;
		outfile<<"}"<<std::endl;
		outfile<<"if (this.warning.getInt() <= 0 || this.critical.getInt() <= 0)"<<std::endl;
		outfile<<"{"<<std::endl;
		outfile<<"return false;"<<std::endl;
		outfile<<"}"<<std::endl;
		outfile<<"return true;"<<std::endl;
		outfile<<"}"<<std::endl;
		outfile<<"private Dictionary<string, int> getProcessOwner()"<<std::endl;
		outfile<<"{"<<std::endl;
		outfile<<"Dictionary<string, int> dic = new Dictionary<string, int>();"<<std::endl;
		outfile<<"string query = \"Select * From Win32_Process\";"<<std::endl;
		outfile<<"ManagementObjectSearcher searcher = new ManagementObjectSearcher(query);"<<std::endl;
		outfile<<"ManagementObjectCollection processList = searcher.Get();"<<std::endl;
		outfile<<"foreach (ManagementObject obj in processList)"<<std::endl;
		outfile<<"{"<<std::endl;
		outfile<<"string[] argList = new string[] { string.Empty, string.Empty };"<<std::endl;
		outfile<<"int returnVal;"<<std::endl;
		outfile<<"Console.WriteLine(\"\");"<<std::endl;
		outfile<<"try"<<std::endl;
		outfile<<"{"<<std::endl;
		outfile<<"returnVal = Convert.ToInt32(obj.InvokeMethod(\"GetOwner\", argList));"<<std::endl;
		outfile<<"}"<<std::endl;
		outfile<<" catch (Exception e)"<<std::endl;
		outfile<<"{"<<std::endl;
		outfile<<"continue;"<<std::endl;
		outfile<<"}"<<std::endl;
		outfile<<"if (returnVal == 0)"<<std::endl;
		outfile<<"{"<<std::endl;
		outfile<<"if (!dic.ContainsKey(argList[0].ToString()))"<<std::endl;
		outfile<<"{"<<std::endl;
		outfile<<"dic.Add(argList[0].ToString(), 1);"<<std::endl;
		outfile<<"}"<<std::endl;
		outfile<<"else"<<std::endl;
		outfile<<"{"<<std::endl;
		outfile<<"dic[argList[0].ToString()]++;"<<std::endl;
		outfile<<"}"<<std::endl;
		outfile<<"}"<<std::endl;
		outfile<<"}"<<std::endl;
		outfile<<"return dic;"<<std::endl;
		outfile<<"}"<<std::endl;
		outfile<<"}"<<std::endl;
		outfile<<"}"<<std::endl;
		
	}
	Memory_Load::Memory_Load()
	{
	
	}
	Memory_Load::~Memory_Load()
	{
	
	}
void Memory_Load::construct(std::ofstream& outfile)
{
	outfile<<"using System;"<<std::endl;
	outfile<<"using System.Collections.Generic;"<<std::endl;
	outfile<<"using System.Linq;"<<std::endl;
	outfile<<"using System.Text;"<<std::endl;
	outfile<<"using System.Management;"<<std::endl;
	outfile<<"using System.Management.Instrumentation;"<<std::endl;
	outfile<<"using System.Reflection;"<<std::endl;
	outfile<<"using OpenHardwareMonitor.Hardware;"<<std::endl;
	outfile<<"using System.IO;"<<std::endl;
	outfile<<"namespace TrustMonitoringTools.Plugins.Hardware"<<std::endl;
	outfile<<"{"<<std::endl;
	outfile<<"public class Check_Hardware_Memory_Load : IPlugins"<<std::endl;

	outfile<<"{"<<std::endl;
	outfile<<"ATypes warning;"<<std::endl;
	outfile<<"ATypes critical;"<<std::endl;
	outfile<<"bool hasArgs;"<<std::endl;
	outfile<<"private string resultString;"<<std::endl;
	outfile<<"public Check_Hardware_Memory_Load()"<<std::endl;
	outfile<<"{"<<std::endl;
	outfile<<"warning = new ATypes(90);"<<std::endl;
	outfile<<"critical = new ATypes(95);"<<std::endl;
	outfile<<"hasArgs = false;"<<std::endl;
	outfile<<"loadOpenHardwareDll();"<<std::endl;
	outfile<<"}"<<std::endl;
	outfile<<"public Check_Hardware_Memory_Load(string warning, string critical)"<<std::endl;
	outfile<<"{"<<std::endl;
	outfile<<"this.warning = new ATypes(warning);"<<std::endl;
	outfile<<"this.critical = new ATypes(critical);"<<std::endl;
	outfile<<"hasArgs = true;"<<std::endl;

	outfile<<"loadOpenHardwareDll();"<<std::endl;
	outfile<<"}"<<std::endl;
}
void Memory_Load::failTest(std::ofstream& outfile)
{
	outfile<<"public bool failTest()"<<std::endl;
	outfile<<"{"<<std::endl;
	outfile<<" string file_path = Constants.PLUGIN_FAIL_TESTS_DIRECTORY + this.GetType().Name.ToLower() + \".txt\";"<<std::endl;
	outfile<<" if (Constants.FAIL_TEST_MODE && File.Exists(file_path))"<<std::endl;
	outfile<<"{"<<std::endl;
	outfile<<"int result = -1;"<<std::endl;
	outfile<<"if ((new FileInfo(file_path).Length > 0))"<<std::endl;
	outfile<<"{"<<std::endl;
	outfile<<"string line = File.ReadAllText(file_path).Trim();"<<std::endl;
	outfile<<"if (Int32.TryParse(line, out result))"<<std::endl;
	outfile<<"{"<<std::endl;
	outfile<<"result = Int32.Parse(line);"<<std::endl;
	outfile<<"}"<<std::endl;
	outfile<<"}"<<std::endl;
	outfile<<"if (result == -1)"<<std::endl;
	outfile<<"{"<<std::endl;
	outfile<<"result = this.critical.getInt() + 1;"<<std::endl;
	outfile<<"}"<<std::endl;
	outfile<<"resultString = String.Format(\"MEMORY LOAD: Making Test fail | metric=0.0 memory_load={0};0.8;1.0\", result);"<<std::endl;
	outfile<<"return true;"<<std::endl;
	outfile<<"}"<<std::endl;
	outfile<<"else"<<std::endl;
	outfile<<"return false;"<<std::endl;
	outfile<<"}"<<std::endl;

}

void Memory_Load::executePlugin(std::ofstream& outfile)
{
	outfile<<"public int executePlugin()"<<std::endl;
	outfile<<"{"<<std::endl;
	outfile<<"int retVal = 0;"<<std::endl;
	outfile<<"if (failTest())"<<std::endl;
	outfile<<"retVal = 2;"<<std::endl;
	outfile<<"else"<<std::endl;
	outfile<<"{"<<std::endl;
	outfile<<"if (hasArgs)"<<std::endl;
	outfile<<"{"<<std::endl;
	outfile<<"if (!checkArgs())"<<std::endl;
	outfile<<"{"<<std::endl;
	outfile<<"Console.WriteLine(\"Error: Check your arguments!\");"<<std::endl;
	outfile<<"return 3;"<<std::endl;
	outfile<<"}"<<std::endl;
	outfile<<"}"<<std::endl;
	outfile<<"Computer c1 = new Computer();"<<std::endl;
	outfile<<"c1.RAMEnabled = true;"<<std::endl;
	outfile<<"c1.Open();"<<std::endl;
	outfile<<"double max_memory_load = 0;"<<std::endl;
	outfile<<"bool has_memory_sensor = false;"<<std::endl;
	outfile<<"foreach (var hardwareItem in c1.Hardware)"<<std::endl;
	outfile<<"{"<<std::endl;
	outfile<<"if (hardwareItem.HardwareType == HardwareType.RAM)"<<std::endl;
	outfile<<"{"<<std::endl;
	outfile<<"hardwareItem.Update();"<<std::endl;
	outfile<<"foreach (var sensor in hardwareItem.Sensors)"<<std::endl;
	outfile<<"{"<<std::endl;
	outfile<<"if (sensor.SensorType == SensorType.Data)"<<std::endl;
	outfile<<"{"<<std::endl;
	outfile<<" if (sensor.Name == \"Used Memory\")"<<std::endl;
	outfile<<"{"<<std::endl;
	outfile<<"has_memory_sensor = true;"<<std::endl;
	outfile<<"max_memory_load = Convert.ToDouble(sensor.Value);"<<std::endl;
	outfile<<"continue;"<<std::endl;
	outfile<<"}"<<std::endl;
	outfile<<"if (sensor.Name == \"Available Memory\")"<<std::endl;
	outfile<<"{"<<std::endl;
	outfile<<"max_memory_load = max_memory_load / (Convert.ToDouble(sensor.Value) + max_memory_load);"<<std::endl;
	outfile<<"continue;"<<std::endl;
	outfile<<"}"<<std::endl;
	outfile<<"}"<<std::endl;
	outfile<<"}"<<std::endl;
	outfile<<"}"<<std::endl;
	outfile<<"}"<<std::endl;
	outfile<<"if (!has_memory_sensor)"<<std::endl;
	outfile<<"{"<<std::endl;
	outfile<<"resultString = \"MEMORY LOAD OK: No sensors detected for this type of RAM | metric=1.00\";"<<std::endl;
	outfile<<"retVal = 0;"<<std::endl;
	outfile<<"}"<<std::endl;
	outfile<<"if ((max_memory_load * 100.0) < warning.getDouble())"<<std::endl;
	outfile<<"{"<<std::endl;
	outfile<<" String performance_data = String.Format(\"memory_load={0};{1};{2}\", max_memory_load.ToString(\"N2\"), (warning.getDouble() / 100.0).ToString(\"N2\"), (critical.getDouble() / 100.0).ToString(\"N2\"));"<<std::endl;
	outfile<<"resultString = \"MEMORY LOAD OK: Memory load below thresholds | metric=1.00 \" + performance_data;"<<std::endl;
	outfile<<" retVal = 0;"<<std::endl;
	outfile<<"}"<<std::endl;
	outfile<<"else if ((max_memory_load * 100.0) >= warning.getDouble() && (max_memory_load * 100.0) < critical.getDouble())"<<std::endl;
	outfile<<"{"<<std::endl;
	outfile<<" ATypes a1 = new ATypes(max_memory_load * 100.0);"<<std::endl;
	outfile<<"double temp1 = (1.0 / (this.warning.getDouble() - this.critical.getDouble())) * (a1.getDouble() - this.warning.getDouble()) + 1.0;"<<std::endl;
	outfile<<"String performance_data = String.Format(\"memory_load={0};{1};{2}\", max_memory_load.ToString(\"N2\"), (warning.getDouble() / 100.0).ToString(\"N2\"), (critical.getDouble() / 100.0).ToString(\"N2\"));"<<std::endl;
	outfile<<"resultString = String.Format(\"MEMORY LOAD WARNING: Found memory load above warning threshold: {0}% | metric={1} \" + performance_data, max_memory_load.ToString(\"N2\"), temp1.ToString(\"N2\"));"<<std::endl;
	outfile<<"retVal = 1;"<<std::endl;
	outfile<<"}"<<std::endl;
	outfile<<"else if ((max_memory_load * 100.0) >= critical.getDouble())"<<std::endl;
	outfile<<"{"<<std::endl;
	outfile<<"String performance_data = String.Format(\"memory_load={0};{1};{2}\", max_memory_load.ToString(\"N2\"), (warning.getDouble() / 100.0).ToString(\"N2\"), (critical.getDouble() / 100.0).ToString(\"N2\"));"<<std::endl;
	outfile<<"resultString = \"MEMORY LOAD CRITICAL: Memory load below thresholds | metric=0.00 \" + performance_data;"<<std::endl;
	outfile<<"retVal = 2;"<<std::endl;
	outfile<<"}"<<std::endl;


	outfile<<"else"<<std::endl;
	outfile<<"{"<<std::endl;
	outfile<<"resultString = \"MEMORY LOAD UNKNOWN: This an unknown error\";"<<std::endl;
	outfile<<"retVal = 3;"<<std::endl;
	outfile<<"}"<<std::endl;
	outfile<<"}"<<std::endl;
	outfile<<"Console.WriteLine(resultString);"<<std::endl;
	outfile<<" return retVal;"<<std::endl;
	outfile<<"}"<<std::endl;
	
}
void Memory_Load::checkArgs(std::ofstream& outfile)
{
	outfile<<"public bool checkArgs()"<<std::endl;
	outfile<<"{"<<std::endl;
	outfile<<"if (this.warning.getInt() <= 0 && this.critical.getInt() <= 0)"<<std::endl;
	outfile<<"{"<<std::endl;
	outfile<<" return false;"<<std::endl;
	outfile<<"}"<<std::endl;
	outfile<<"if (this.warning.getInt() > this.critical.getInt())"<<std::endl;
	outfile<<"{"<<std::endl;
	outfile<<" return false;"<<std::endl;
	outfile<<"}"<<std::endl;
	outfile<<"return true;"<<std::endl;
	outfile<<"}"<<std::endl;
	outfile<<"private void loadOpenHardwareDll()"<<std::endl;
	outfile<<"{"<<std::endl;
	outfile<<"EmbeddedAssembly.Load(\"TrustMonitoringTools.Libraries.OpenHardwareMonitorLib.dll\", \"OpenHardwareMonitorLib.dll\");"<<std::endl;
	outfile<<"AppDomain.CurrentDomain.AssemblyResolve += new ResolveEventHandler(CurrentDomain_AssemblyResolve);"<<std::endl;
	outfile<<"}"<<std::endl;
	outfile<<"private static Assembly CurrentDomain_AssemblyResolve(object sender, ResolveEventArgs args)"<<std::endl;
	outfile<<"{"<<std::endl;
	outfile<<"return EmbeddedAssembly.Get(args.Name);"<<std::endl;
	outfile<<"}"<<std::endl;
	outfile<<"}"<<std::endl;
	outfile<<"}"<<std::endl;
}
Memory_Usage::Memory_Usage()
{

}
Memory_Usage::~Memory_Usage()
{

}
void  Memory_Usage::construct(std::ofstream& outfile)
{
	outfile<<"using System;"<<std::endl;
	outfile<<"using System.Collections.Generic;"<<std::endl;
	outfile<<"using System.Linq;"<<std::endl;
	outfile<<"using System.Text;"<<std::endl;
	outfile<<"using System.IO;"<<std::endl;
	outfile<<"namespace TrustMonitoringTools.Plugins.User"<<std::endl;
	outfile<<"{"<<std::endl;
	outfile<<"public class Check_User_Used_Memory : IPlugins"<<std::endl;
	outfile<<"{"<<std::endl;
	outfile<<"private string resultString;"<<std::endl;
	outfile<<"private ATypes warning;"<<std::endl;
	outfile<<"private ATypes critical;"<<std::endl;
	outfile<<"private bool hasArgs;"<<std::endl;
	outfile<<"private List<string> users_exclusions;"<<std::endl;
	outfile<<"private bool exclude_system_accounts = true;"<<std::endl;
	outfile<<"public Check_User_Used_Memory()"<<std::endl;
	outfile<<"{"<<std::endl;
	outfile<<"warning = new ATypes(\"500\");"<<std::endl;
	outfile<<"critical = new ATypes(\"1000\");"<<std::endl;
	outfile<<"hasArgs = false;"<<std::endl;
	outfile<<"initializeUserExclusions();"<<std::endl;
	outfile<<"}"<<std::endl;
	outfile<<"public Check_User_Used_Memory(string w, string c)"<<std::endl;
	outfile<<"{"<<std::endl;
	outfile<<"warning = new ATypes(w);"<<std::endl;
	outfile<<"critical = new ATypes(c);"<<std::endl;
	outfile<<"hasArgs = true;"<<std::endl;
	outfile<<"initializeUserExclusions();"<<std::endl;
	outfile<<"}"<<std::endl;

	
}
void  Memory_Usage::failTest(std::ofstream& outfile)
{
	outfile<<"public bool failTest()"<<std::endl;
	outfile<<"{"<<std::endl;
	outfile<<"string file_path = Constants.PLUGIN_FAIL_TESTS_DIRECTORY + this.GetType().Name.ToLower() + \".txt\";"<<std::endl;
	outfile<<"if (Constants.FAIL_TEST_MODE && File.Exists(file_path))"<<std::endl;
	outfile<<"{"<<std::endl;
	outfile<<"int result = -1;"<<std::endl;
	outfile<<"if ((new FileInfo(file_path).Length > 0))"<<std::endl;
	outfile<<"{"<<std::endl;
	outfile<<"string line = File.ReadAllText(file_path).Trim();"<<std::endl;
	outfile<<"if (Int32.TryParse(line, out result))"<<std::endl;
	outfile<<"{"<<std::endl;
	outfile<<"result = Int32.Parse(line);"<<std::endl;
	outfile<<"}"<<std::endl;
	outfile<<"}"<<std::endl;
	outfile<<"if (result == -1)"<<std::endl;
	outfile<<"{"<<std::endl;
	outfile<<"result = this.critical.getInt() + 1; "<<std::endl;
	outfile<<"}"<<std::endl;
	outfile<<"String all = String.Format(\"USER USED MEMORY: Making Test fail | metric=0.0 user_used_memory={0};65;75\", result);"<<std::endl;
	outfile<<"Console.WriteLine(all);"<<std::endl;
	outfile<<"return true;"<<std::endl;
	outfile<<"}"<<std::endl;
	outfile<<"else"<<std::endl;
	outfile<<"return false;"<<std::endl;
	outfile<<"}"<<std::endl;
	
}
void  Memory_Usage::executePlugin(std::ofstream& outfile)
{
	outfile<<"public int executePlugin()"<<std::endl;
	outfile<<"{"<<std::endl;
	outfile<<"int retVal = 3;"<<std::endl;
	outfile<<"if (failTest())"<<std::endl;
	outfile<<"retVal = 2;"<<std::endl;
	outfile<<"else"<<std::endl;
	outfile<<"{"<<std::endl;
	outfile<<"if (hasArgs)"<<std::endl;
	outfile<<"{"<<std::endl;
	outfile<<"if (!checkArgs())"<<std::endl;
	outfile<<"{"<<std::endl;
	outfile<<"Console.WriteLine(\"Check your arguments!\");"<<std::endl;
	outfile<<"return 3;"<<std::endl;
	outfile<<"}"<<std::endl;
	outfile<<"}"<<std::endl;
	outfile<<"UserUtilities s1 = new UserUtilities();"<<std::endl;
	outfile<<"Dictionary<string, List<StoreUserProcesses>> processes = s1.GetUsersProcessesInfo();"<<std::endl;
	outfile<<"Dictionary<string, long> user_memory = new Dictionary<string, long>();"<<std::endl;
	outfile<<"foreach (KeyValuePair<string, List<StoreUserProcesses>> user in processes)"<<std::endl;
	outfile<<"{"<<std::endl;
	outfile<<"if (!user_memory.ContainsKey(user.Key)) user_memory[user.Key] = 0;"<<std::endl;
	
	outfile<<"foreach (StoreUserProcesses process in user.Value)"<<std::endl;
	outfile<<"{"<<std::endl;
	outfile<<"user_memory[user.Key] += process.memory_load;"<<std::endl;
	outfile<<"}"<<std::endl;
	outfile<<"}"<<std::endl;
	outfile<<"string output_data = \"\";"<<std::endl;
	outfile<<"string performance_data = \"\";"<<std::endl;
	outfile<<" string metric_data = \" | metric=\";"<<std::endl;
	outfile<<"bool is_critical = false;"<<std::endl;
	outfile<<"bool is_warning = false;"<<std::endl;
	outfile<<"long largest_memory_found = 0;"<<std::endl;
	outfile<<"foreach (var x in user_memory)"<<std::endl;
	outfile<<"{"<<std::endl;
	outfile<<"if (exclude_system_accounts)"<<std::endl;
	outfile<<"{"<<std::endl;
	outfile<<"if (users_exclusions.Contains(x.Key)) continue;"<<std::endl;
	outfile<<"}"<<std::endl;
	outfile<<"string user = x.Key.Contains(\" \")? x.Key.Replace(\" \", \"_\") : x.Key;"<<std::endl;
	outfile<<"long current_memory = x.Value / (1024 * 1024);"<<std::endl;
	outfile<<"performance_data += String.Format(\"{0}={1};{2};{3} \", user,current_memory,warning.getInt(),critical.getInt());"<<std::endl;
	outfile<<"if (current_memory > largest_memory_found) largest_memory_found = current_memory;"<<std::endl;
	outfile<<"if (current_memory >= critical.getLong())"<<std::endl;
	outfile<<"{"<<std::endl;
	outfile<<"is_critical = true;"<<std::endl;
	outfile<<"output_data += String.Format(\"User {0} has {1} MB \", user, current_memory);"<<std::endl;

	outfile<<"continue;"<<std::endl;
	outfile<<"}"<<std::endl;

	outfile<<"if (current_memory >= warning.getLong())"<<std::endl;
	outfile<<"{"<<std::endl;
	outfile<<"is_warning = true;"<<std::endl;
	outfile<<" output_data += String.Format(\"User {0} has {1} MB \", user, current_memory);"<<std::endl;
	outfile<<"continue;"<<std::endl;
	outfile<<"}"<<std::endl;


	outfile<<"}"<<std::endl;

	outfile<<" if (is_critical)"<<std::endl;
	outfile<<"{"<<std::endl;
	outfile<<"string metric = metric_data + \"0.00\";"<<std::endl;

	outfile<<"resultString = \"USER MEMORY CRITICAL: \" + output_data.Trim() + \" memory in use\" + metric + performance_data;"<<std::endl;
	outfile<<"retVal = 2;"<<std::endl;
	outfile<<"}"<<std::endl;
	outfile<<" else if (is_warning)"<<std::endl;
	outfile<<"{"<<std::endl;
	outfile<<"ATypes a1 = new ATypes(largest_memory_found);"<<std::endl;
	outfile<<"double metric = (1.0 / (this.warning.getDouble() - this.critical.getDouble())) * (a1.getDouble() - this.warning.getDouble()) + 1.0;"<<std::endl;
	outfile<<"resultString = \"USER MEMORY WARNING: \" + output_data.Trim() + \" memory in use\" + metric_data + metric.ToString(\"N2\") + \" \" + performance_data;"<<std::endl;
	outfile<<"retVal = 1;"<<std::endl;
	outfile<<"}"<<std::endl;
	outfile<<" else if (!is_warning && !is_critical)"<<std::endl;
	outfile<<"{"<<std::endl;
	outfile<<"string metric = \"1.00 \";"<<std::endl;
	outfile<<"resultString = \"USER MEMORY OK: All users are within thresholds\" + metric_data + metric + performance_data;"<<std::endl;
	outfile<<"retVal = 0;"<<std::endl;
	outfile<<"}"<<std::endl;
	outfile<<"else"<<std::endl;
	outfile<<"{"<<std::endl;
	outfile<<"resultString =\"USER MEMORY UNKNOWN: Unknown error\";"<<std::endl;
	outfile<<"retVal = 3;"<<std::endl;
	outfile<<"}"<<std::endl;
	outfile<<"}"<<std::endl;
	outfile<<"Console.WriteLine(resultString);"<<std::endl;
	outfile<<" return retVal;"<<std::endl;
	outfile<<"}"<<std::endl;
	
	
}
void  Memory_Usage::checkArgs(std::ofstream& outfile)
{
	outfile<<"public bool checkArgs()"<<std::endl;
	outfile<<"{"<<std::endl;
	outfile<<"if (warning.getInt() <= 0 || critical.getInt() <= 0)"<<std::endl;

	outfile<<"{"<<std::endl;
	outfile<<"return false;"<<std::endl;
	outfile<<"}"<<std::endl;
	outfile<<"if (warning.getInt() > critical.getInt())"<<std::endl;
	outfile<<"{"<<std::endl;
	outfile<<"return false;"<<std::endl;
	outfile<<"}"<<std::endl;
	outfile<<"return true;"<<std::endl;
	outfile<<"}"<<std::endl;
	outfile<<"private void initializeUserExclusions()"<<std::endl;
	outfile<<"{"<<std::endl;
	outfile<<"users_exclusions = new List<string>();"<<std::endl;
	outfile<<"users_exclusions.Add(\"SYSTEM\");"<<std::endl;
	outfile<<"users_exclusions.Add(\"NETWORK SERVICE\");"<<std::endl;
	outfile<<"users_exclusions.Add(\"LOCAL SERVICE\");"<<std::endl;
	outfile<<"}"<<std::endl;
	outfile<<"}"<<std::endl;
	outfile<<"}"<<std::endl;


}
Shared_Folders::Shared_Folders()
{

}
Shared_Folders::~Shared_Folders()
{


}
void Shared_Folders::construct(std::ofstream& outfile)
{
	outfile<<"using System;"<<std::endl;
	outfile<<"using System.Collections.Generic;"<<std::endl;
	outfile<<"using System.Linq;"<<std::endl;
	outfile<<"using System.Text;"<<std::endl;
	outfile<<"using System.IO;"<<std::endl;
	outfile<<"namespace TrustMonitoringTools.Plugins.Machine"<<std::endl;
	outfile<<"{"<<std::endl;
	outfile<<"public class Check_Machine_Shared_Folders : IPlugins"<<std::endl;
	outfile<<"{"<<std::endl;
	outfile<<"private string resultString;"<<std::endl;
	outfile<<"private ATypes warning;"<<std::endl;
	outfile<<"private ATypes critical;"<<std::endl;
	outfile<<"private bool checkArguments;"<<std::endl;
	outfile<<" public Check_Machine_Shared_Folders() "<<std::endl;
	outfile<<"{"<<std::endl;
	outfile<<"warning = new ATypes(6);"<<std::endl;
	outfile<<"critical = new ATypes(8);"<<std::endl;
	outfile<<"checkArguments = false;"<<std::endl;
	outfile<<"}"<<std::endl;
	outfile<<"public Check_Machine_Shared_Folders(String w, String c)"<<std::endl;
	outfile<<"{"<<std::endl;
	outfile<<"warning = new ATypes(w);"<<std::endl;
	outfile<<"critical = new ATypes(c);"<<std::endl;
	outfile<<"checkArguments = true;"<<std::endl;
	outfile<<"}"<<std::endl;

}
void Shared_Folders::failTest(std::ofstream& outfile)
{
	outfile<<"public bool failTest()"<<std::endl;
	outfile<<"{"<<std::endl;
	outfile<<"string file_path = Constants.PLUGIN_FAIL_TESTS_DIRECTORY + this.GetType().Name.ToLower() + \".txt\";"<<std::endl;
	outfile<<"if (Constants.FAIL_TEST_MODE && File.Exists(file_path))"<<std::endl;
	outfile<<"{"<<std::endl;
	outfile<<"int result = -1;"<<std::endl;
	outfile<<"if ((new FileInfo(file_path).Length > 0))"<<std::endl;
	outfile<<"{"<<std::endl;
	outfile<<"string line = File.ReadAllText(file_path).Trim();"<<std::endl;
	outfile<<"if (Int32.TryParse(line, out result))"<<std::endl;
	outfile<<"{"<<std::endl;
	outfile<<"result = Int32.Parse(line);"<<std::endl;
	outfile<<"}"<<std::endl;
	outfile<<"}"<<std::endl;
	outfile<<"if (result == -1)"<<std::endl;
	outfile<<"{"<<std::endl;
	outfile<<"result = this.critical.getInt() + 1; "<<std::endl;
	outfile<<"}"<<std::endl;
	outfile<<"resultString = String.Format(\"SHARED FOLDERS: Making test fail | metric=0.0 shared_folders={0};6;10\", result);"<<std::endl;
	outfile<<"return true;"<<std::endl;
	outfile<<"}"<<std::endl;
	outfile<<"else"<<std::endl;
	outfile<<"return false;"<<std::endl;
	outfile<<"}"<<std::endl;
	

}
void Shared_Folders::executePlugin(std::ofstream& outfile)
{
	outfile<<"public int executePlugin()"<<std::endl;
	outfile<<"{"<<std::endl;
	outfile<<"int retVal = 0;"<<std::endl;
	outfile<<"if (failTest())"<<std::endl;
	outfile<<"retVal = 2;"<<std::endl;
	outfile<<"else"<<std::endl;
	outfile<<"{"<<std::endl;
	outfile<<"if (checkArguments)"<<std::endl;
	outfile<<"{"<<std::endl;
	outfile<<"if (!checkArgs()) return 3;"<<std::endl;
	outfile<<"}"<<std::endl;
	outfile<<"int shared_folders_counter = 0;"<<std::endl;
	outfile<<" using (System.Management.ManagementClass shareObj = new System.Management.ManagementClass(\"Win32_Share\"))"<<std::endl;
	outfile<<"{"<<std::endl;
	outfile<<"System.Management.ManagementObjectCollection shares = shareObj.GetInstances();"<<std::endl;
	outfile<<"foreach (System.Management.ManagementObject share in shares)"<<std::endl;
	outfile<<"{"<<std::endl;
	outfile<<"shared_folders_counter++;"<<std::endl;
	outfile<<"}"<<std::endl;
	outfile<<"}"<<std::endl;
	outfile<<"String performance_data = \" | shared_folders=\" + shared_folders_counter + \";\" + warning.getInt() + \";\" + critical.getInt();"<<std::endl;
	outfile<<"if (shared_folders_counter < warning.getInt())"<<std::endl;
	outfile<<"{"<<std::endl;
	outfile<<" resultString = \"Shared Folders OK: There are \" + shared_folders_counter + \" shared folders\"+ performance_data + \" metric=1.00\";"<<std::endl;
	outfile<<"retVal = 0;"<<std::endl;
	outfile<<"}"<<std::endl;
	outfile<<"else if ((warning.getInt() == critical.getInt() && warning.getInt() >= shared_folders_counter) || shared_folders_counter >= critical.getInt())"<<std::endl;
	outfile<<"{"<<std::endl;
	outfile<<"resultString = \"Shared Folders CRITICAL: There are \" + shared_folders_counter + \"shared folders\" + performance_data + \" metric=0.00\";"<<std::endl;
	outfile<<"retVal = 2;"<<std::endl;
	outfile<<"}"<<std::endl;
	outfile<<"else if (shared_folders_counter >= warning.getInt() && shared_folders_counter < critical.getInt())"<<std::endl;
	outfile<<"{"<<std::endl;
	outfile<<" resultString = \"Shared Folders WARNING: There are \" + shared_folders_counter + \"shared folders\" +performance_data + \" metric=0.50\";"<<std::endl;
	outfile<<" retVal = 1;"<<std::endl;
	outfile<<"}"<<std::endl;
	outfile<<"else"<<std::endl;
	outfile<<"{"<<std::endl;
	outfile<<"resultString = \"Shared Folders UNKNOWN: Unable to get the shared folders | metric=0.00\";"<<std::endl;
	outfile<<"retVal = 3;"<<std::endl;
	outfile<<"}"<<std::endl;
	outfile<<"}"<<std::endl;
	outfile<<"Console.WriteLine(resultString);"<<std::endl;
	outfile<<" return retVal;"<<std::endl;
	outfile<<"}"<<std::endl;
	
}
void Shared_Folders::checkArgs(std::ofstream& outfile)
{
	outfile<<"public bool checkArgs()"<<std::endl;
	outfile<<"{"<<std::endl;
	outfile<<"if (warning.isEmptyOrNull() || critical.isEmptyOrNull())"<<std::endl;
	outfile<<"{"<<std::endl;
	outfile<<" Console.WriteLine(\"Error: Warning or critical thresholds are empty!\");"<<std::endl;
	outfile<<"return false;"<<std::endl;
	outfile<<"}"<<std::endl;
	outfile<<"if (warning.getInt() > critical.getInt())"<<std::endl;
	outfile<<"{"<<std::endl;
	outfile<<"Console.WriteLine(\"Error: Critical threshold must be greater than warning threshold\");"<<std::endl;
	outfile<<"return false;"<<std::endl;
	outfile<<"}"<<std::endl;
	outfile<<" if (warning.getInt() < 1 || critical.getInt() < 1)"<<std::endl;
	outfile<<"{"<<std::endl;
	outfile<<"Console.WriteLine(\"Error: Warning and/or critical thresholds must be greater than 0\");"<<std::endl;
	outfile<<"return false;"<<std::endl;
	outfile<<"}"<<std::endl;
	outfile<<"return true;"<<std::endl;
	outfile<<"}"<<std::endl;
	outfile<<"}"<<std::endl;
	outfile<<"}"<<std::endl;

	
}
CPU_Usage::CPU_Usage()
{

}
CPU_Usage::~CPU_Usage()
{

}
void CPU_Usage::construct(std::ofstream& outfile)
{
	outfile<<"using System;"<<std::endl;
	outfile<<"using System.Collections.Generic;"<<std::endl;
	outfile<<"using System.Linq;"<<std::endl;
	outfile<<"using System.Text;"<<std::endl;
	outfile<<"using System.IO;"<<std::endl;
	outfile<<"namespace TrustMonitoringTools.Plugins.User"<<std::endl;
	outfile<<"{"<<std::endl;
	outfile<<"public class Check_User_Cpu_Usage : IPlugins"<<std::endl;
	outfile<<"{"<<std::endl;
	outfile<<"private string resultString;"<<std::endl;
	outfile<<"private ATypes warning;"<<std::endl;
	outfile<<"private ATypes critical;"<<std::endl;
	outfile<<"private bool hasArgs;"<<std::endl;
	outfile<<"private List<string> users_exclusions;"<<std::endl;
	outfile<<"private bool exclude_system_accounts = false;"<<std::endl;
	outfile<<" public Check_User_Cpu_Usage()"<<std::endl;
	outfile<<"{"<<std::endl;
	outfile<<"warning = new ATypes(\"40\"); "<<std::endl;
	outfile<<"critical = new ATypes(\"50\");"<<std::endl;
	outfile<<"hasArgs = false;"<<std::endl;
	outfile<<" initializeUserExclusions();"<<std::endl;
	outfile<<"}"<<std::endl;
	outfile<<"public Check_User_Cpu_Usage(string w, string c)"<<std::endl;
	outfile<<"{"<<std::endl;
	outfile<<" warning = new ATypes(w);"<<std::endl;
	outfile<<"critical = new ATypes(c);"<<std::endl;
	outfile<<"hasArgs = true;"<<std::endl;
	outfile<<"initializeUserExclusions();"<<std::endl;
	outfile<<"}"<<std::endl;
}
void CPU_Usage::failTest(std::ofstream& outfile)
{
	outfile<<" public bool failTest()"<<std::endl;
	outfile<<"{"<<std::endl;
	outfile<<"string file_path = Constants.PLUGIN_FAIL_TESTS_DIRECTORY + this.GetType().Name.ToLower() + \".txt\";"<<std::endl;
	outfile<<"if (Constants.FAIL_TEST_MODE && File.Exists(file_path))"<<std::endl;
	outfile<<"{"<<std::endl;
	outfile<<"int result = -1;"<<std::endl;
	outfile<<"if ((new FileInfo(file_path).Length > 0))"<<std::endl;
	outfile<<"{"<<std::endl;
	outfile<<"string line = File.ReadAllText(file_path).Trim();"<<std::endl;
	outfile<<"if (Int32.TryParse(line, out result))"<<std::endl;
	outfile<<"{"<<std::endl;
	outfile<<" result = Int32.Parse(line);"<<std::endl;
	outfile<<"}"<<std::endl;
	outfile<<"}"<<std::endl;
	outfile<<"if (result == -1)"<<std::endl;
	outfile<<"{"<<std::endl;
	outfile<<" result = this.critical.getInt() + 1;"<<std::endl;
	outfile<<"}"<<std::endl;
	outfile<<"resultString = String.Format(\"USER CPU USAGE: Making Test fail | metric=0.0 user_cpu_usage={0};40;50\", result);"<<std::endl;
	outfile<<"return true;"<<std::endl;
	outfile<<"}"<<std::endl;
	outfile<<"else"<<std::endl;
	outfile<<"return false;"<<std::endl;
	outfile<<"}"<<std::endl;
}
void CPU_Usage::executePlugin(std::ofstream& outfile)
{
	outfile<<"public int executePlugin() "<<std::endl;
	outfile<<"{"<<std::endl;
	outfile<<"int retVal = 3;"<<std::endl;
	outfile<<"if (failTest())"<<std::endl;
	outfile<<"retVal = 2;"<<std::endl;
	outfile<<"else"<<std::endl;
	outfile<<"{"<<std::endl;
	outfile<<"if (hasArgs)"<<std::endl;
	outfile<<"{"<<std::endl;
	outfile<<"if (!checkArgs())"<<std::endl;
	outfile<<"{"<<std::endl;
	outfile<<"Console.WriteLine(\"Check your arguments!\");"<<std::endl;
	outfile<<"return 3;"<<std::endl;
	outfile<<"}"<<std::endl;
	outfile<<"}"<<std::endl;
	outfile<<" UserUtilities s1 = new UserUtilities();"<<std::endl;
	outfile<<"Dictionary<string, List<StoreUserProcesses>> processes = s1.GetUsersProcessesInfo();"<<std::endl;
	outfile<<"Dictionary<string, float> user_memory = new Dictionary<string, float>();"<<std::endl;
	outfile<<"foreach (KeyValuePair<string, List<StoreUserProcesses>> user in processes)"<<std::endl;
	outfile<<"{"<<std::endl;
	outfile<<"if (!user_memory.ContainsKey(user.Key)) user_memory[user.Key] = 0;"<<std::endl;
	outfile<<"foreach (StoreUserProcesses process in user.Value)"<<std::endl;
	outfile<<"{"<<std::endl;
	outfile<<"user_memory[user.Key] += process.cpu_load;"<<std::endl;
	outfile<<"}"<<std::endl;
	outfile<<"}"<<std::endl;
	outfile<<"string output_data = \"\";"<<std::endl;
	outfile<<"string performance_data = \"\";"<<std::endl;
	outfile<<"string metric_data = \" | metric=\";"<<std::endl;
	outfile<<"bool is_critical = false;"<<std::endl;
	outfile<<"bool is_warning = false;"<<std::endl;
	outfile<<"float largest_cpu_load_found = 0;"<<std::endl;
	outfile<<"foreach (var x in user_memory)"<<std::endl;
	outfile<<"{"<<std::endl;
	outfile<<"if (exclude_system_accounts)"<<std::endl;
	outfile<<"{"<<std::endl;
	outfile<<" if (users_exclusions.Contains(x.Key)) continue;"<<std::endl;
	outfile<<"}"<<std::endl;
	outfile<<"string user = x.Key.Contains(\"  \") ? x.Key.Replace(\" \", \"_\") : x.Key;"<<std::endl;
	outfile<<"float current_cpu_load = x.Value;"<<std::endl;
	outfile<<" performance_data += String.Format(\"{0}={1};{2};{3} \", user, current_cpu_load.ToString(\"N2\"), warning.getDouble().ToString(\"N2\"), critical.getDouble().ToString(\"N2\"));"<<std::endl;
	outfile<<"if (current_cpu_load > largest_cpu_load_found) largest_cpu_load_found = current_cpu_load;"<<std::endl;
	outfile<<"if (current_cpu_load >= critical.getLong())"<<std::endl;
	outfile<<"{"<<std::endl;
	outfile<<" is_critical = true;"<<std::endl;
	outfile<<"output_data += String.Format(\"User {0} has {1} %/sec \", user, current_cpu_load.ToString(\"N2\"));"<<std::endl;
	outfile<<"continue;"<<std::endl;
	outfile<<"}"<<std::endl;
	outfile<<"if (current_cpu_load >= warning.getLong())"<<std::endl;
	outfile<<"{"<<std::endl;
	outfile<<"is_warning = true;"<<std::endl;
	outfile<<" output_data += String.Format(\"User {0} has {1} %/sec \", user, current_cpu_load.ToString(\"N2\"));"<<std::endl;
	outfile<<"continue;"<<std::endl;
	outfile<<"}"<<std::endl;
	outfile<<"}"<<std::endl;
	outfile<<" if (is_critical)"<<std::endl;
	outfile<<"{"<<std::endl;
	outfile<<" string metric = metric_data + \"0.00 \";"<<std::endl;
	outfile<<" resultString = \"USER CPU LOAD CRITICAL: \" + output_data.Trim() + \" cpu in use\" + metric + performance_data;"<<std::endl;
	outfile<<" retVal = 2;"<<std::endl;
	outfile<<"}"<<std::endl;
	outfile<<" else if (is_warning)"<<std::endl;
	outfile<<"{"<<std::endl;
	outfile<<"ATypes a1 = new ATypes(largest_cpu_load_found);"<<std::endl;
	outfile<<"double metric = (1.0 / (this.warning.getDouble() - this.critical.getDouble())) * (a1.getDouble() - this.warning.getDouble()) + 1.0;"<<std::endl;
	outfile<<"resultString = \"USER CPU LOAD WARNING: \" + output_data.Trim() + \" cpu in use\" + metric_data + metric.ToString(\"N2\") + \" \" + performance_data;"<<std::endl;
	outfile<<"retVal = 1;"<<std::endl;
	outfile<<"}"<<std::endl;
	outfile<<"else if (!is_warning && !is_critical)"<<std::endl;
	outfile<<"{"<<std::endl;
	outfile<<"string metric = \"1.00 \";"<<std::endl;
	outfile<<"resultString = \"USER CPU LOAD OK: All users are within thresholds\" + metric_data + metric + performance_data;"<<std::endl;
	outfile<<" retVal = 0;"<<std::endl;
	outfile<<"}"<<std::endl;
	outfile<<"else"<<std::endl;
	outfile<<"{"<<std::endl;
	outfile<<" resultString = \"USER CPU LOAD UNKNOWN: Unknown error\";"<<std::endl;
	outfile<<"retVal = 3;"<<std::endl;
	outfile<<"}"<<std::endl;
	outfile<<"}"<<std::endl;

	outfile<<"Console.WriteLine(resultString);"<<std::endl;
	outfile<<"return retVal;"<<std::endl;
	outfile<<"}"<<std::endl;
}
void CPU_Usage::checkArgs(std::ofstream& outfile)
{
	outfile<<"public bool checkArgs()"<<std::endl;
	outfile<<"{"<<std::endl;
	outfile<<"if (warning.getInt() <= 0 || critical.getInt() <= 0)"<<std::endl;
	outfile<<"{"<<std::endl;
	outfile<<"return false;"<<std::endl;
	outfile<<"}"<<std::endl;
	outfile<<"if (warning.getInt() > critical.getInt())"<<std::endl;
	outfile<<"{"<<std::endl;
	outfile<<"return false;"<<std::endl;

	outfile<<"}"<<std::endl;
	outfile<<"return true;"<<std::endl;
	outfile<<"}"<<std::endl;
	outfile<<"private void initializeUserExclusions()"<<std::endl;
	outfile<<"{"<<std::endl;
	outfile<<"users_exclusions = new List<string>();"<<std::endl;
	outfile<<"users_exclusions.Add(\"SYSTEM\");"<<std::endl;
	outfile<<"users_exclusions.Add(\"NETWORK SERVICE\");"<<std::endl;
	outfile<<"users_exclusions.Add(\"LOCAL SERVICE\");"<<std::endl;
	outfile<<"}"<<std::endl;
	outfile<<"}"<<std::endl;
	outfile<<"}"<<std::endl;
}



};