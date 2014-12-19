using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
namespace TrustMonitoringTools.Plugins.Machine
{
public class Check_Machine_Shared_Folders : IPlugins
{
private string resultString;
private ATypes warning;
private ATypes critical;
private bool checkArguments;
 public Check_Machine_Shared_Folders() 
{
warning = new ATypes(6);
critical = new ATypes(8);
checkArguments = false;
}
public Check_Machine_Shared_Folders(String w, String c)
{
warning = new ATypes(w);
critical = new ATypes(c);
checkArguments = true;
}
public bool failTest()
{
string file_path = Constants.PLUGIN_FAIL_TESTS_DIRECTORY + this.GetType().Name.ToLower() + ".txt";
if (Constants.FAIL_TEST_MODE && File.Exists(file_path))
{
int result = -1;
if ((new FileInfo(file_path).Length > 0))
{
string line = File.ReadAllText(file_path).Trim();
if (Int32.TryParse(line, out result))
{
result = Int32.Parse(line);
}
}
if (result == -1)
{
result = this.critical.getInt() + 1; 
}
resultString = String.Format("SHARED FOLDERS: Making test fail | metric=0.0 shared_folders={0};6;10", result);
return true;
}
else
return false;
}
public int executePlugin()
{
int retVal = 0;
if (failTest())
retVal = 2;
else
{
if (checkArguments)
{
if (!checkArgs()) return 3;
}
int shared_folders_counter = 0;
 using (System.Management.ManagementClass shareObj = new System.Management.ManagementClass("Win32_Share"))
{
System.Management.ManagementObjectCollection shares = shareObj.GetInstances();
foreach (System.Management.ManagementObject share in shares)
{
shared_folders_counter++;
}
}
String performance_data = " | shared_folders=" + shared_folders_counter + ";" + warning.getInt() + ";" + critical.getInt();
if (shared_folders_counter < warning.getInt())
{
 resultString = "Shared Folders OK: There are " + shared_folders_counter + " shared folders"+ performance_data + " metric=1.00";
retVal = 0;
}
else if ((warning.getInt() == critical.getInt() && warning.getInt() >= shared_folders_counter) || shared_folders_counter >= critical.getInt())
{
resultString = "Shared Folders CRITICAL: There are " + shared_folders_counter + "shared folders" + performance_data + " metric=0.00";
retVal = 2;
}
else if (shared_folders_counter >= warning.getInt() && shared_folders_counter < critical.getInt())
{
 resultString = "Shared Folders WARNING: There are " + shared_folders_counter + "shared folders" +performance_data + " metric=0.50";
 retVal = 1;
}
else
{
resultString = "Shared Folders UNKNOWN: Unable to get the shared folders | metric=0.00";
retVal = 3;
}
}
Console.WriteLine(resultString);
 return retVal;
}
public bool checkArgs()
{
if (warning.isEmptyOrNull() || critical.isEmptyOrNull())
{
 Console.WriteLine("Error: Warning or critical thresholds are empty!");
return false;
}
if (warning.getInt() > critical.getInt())
{
Console.WriteLine("Error: Critical threshold must be greater than warning threshold");
return false;
}
 if (warning.getInt() < 1 || critical.getInt() < 1)
{
Console.WriteLine("Error: Warning and/or critical thresholds must be greater than 0");
return false;
}
return true;
}
}
}
