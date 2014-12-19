using System;
using System.Collections.Generic;
using System.Linq;
using System.Linq;
using System.Text;
using System.Management;
using System.Diagnostics;
using System.IO;
namespace TrustMonitoringTools.Plugins.User
{
public class Check_User_Open_Processes : IPlugins
{
private string resultString;
private ATypes warning;
private ATypes critical;
private bool hasArgs;
public Check_User_Open_Processes()
{
warning = new ATypes(60);
critical = new ATypes(80);
hasArgs = false;
}
public Check_User_Open_Processes(String warning, String critical)
{
this.warning = new ATypes(warning);
this.critical = new ATypes(critical);
hasArgs = true;
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
resultString = String.Format("USER OPEN PROCESSES: Making Test fail | metric=0.0 users_open_processes={0};60;80", result);
return true;
}
else
return false;
}
 public int executePlugin()
{
int retVal = 3;
if (failTest())
retVal = 2;
else
{
if (hasArgs)
{
if (!this.checkArgs())
{
Console.WriteLine("Error: Check your arguments");
return 3;
}
}
string user = String.Empty;
int max = 0;
string performance_data = " ";
Dictionary<string, int> dic = this.getProcessOwner();
foreach(KeyValuePair<string, int> entry in dic) 
{
string key = entry.Key.Trim();
int value = entry.Value;
if (key.Contains(" ")) key = key.Replace(" ", "_");
if ((int)entry.Value > max)
{
max = value;
user = key;
}
performance_data += " " + key + "=" + value.ToString() + ";" + this.warning.getInt().ToString() + ";" + this.critical.getInt().ToString();
}
string metric_data = " | metric=";
double metric = 0.0;
ATypes a1 = new ATypes(max);
if (max < this.warning.getInt())
{
metric = 1.0;
resultString = "USER PROCESSES OK: No users exceeding thresholds" + metric_data + metric.ToString("N2") + performance_data;
retVal = 0;
}
else if (max >= this.warning.getInt() && max < this.critical.getInt())
{
metric = (1.0 / (this.warning.getDouble() - this.critical.getDouble())) * (a1.getDouble() - this.warning.getDouble()) + 1.0;
 resultString = "USER PROCESSES WARNING: User " + user + " found with " + max + " services " + metric_data + metric.ToString("N2") + performance_data;
 retVal = 1;
}
 else if (max >= this.critical.getInt())
{
 metric = 0.0;
resultString = "USER PROCESSES CRITICAL: User " + user + " found with " + max + " services " + metric_data + metric.ToString("N2") + performance_data;
retVal = 2;
}
else
{
resultString = "USER PROCESSES UNKNOWN: Unknown error";
retVal = 3;
}
}
Console.WriteLine(resultString);
return retVal;
}
public bool checkArgs()
{
if (this.warning.getInt() > this.critical.getInt())
{
 return false;
}
if (this.warning.getInt() <= 0 || this.critical.getInt() <= 0)
{
return false;
}
return true;
}
private Dictionary<string, int> getProcessOwner()
{
Dictionary<string, int> dic = new Dictionary<string, int>();
string query = "Select * From Win32_Process";
ManagementObjectSearcher searcher = new ManagementObjectSearcher(query);
ManagementObjectCollection processList = searcher.Get();
foreach (ManagementObject obj in processList)
{
string[] argList = new string[] { string.Empty, string.Empty };
int returnVal;
Console.WriteLine("");
try
{
returnVal = Convert.ToInt32(obj.InvokeMethod("GetOwner", argList));
}
 catch (Exception e)
{
continue;
}
if (returnVal == 0)
{
if (!dic.ContainsKey(argList[0].ToString()))
{
dic.Add(argList[0].ToString(), 1);
}
else
{
dic[argList[0].ToString()]++;
}
}
}
return dic;
}
}
}
