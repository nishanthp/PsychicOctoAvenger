using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Management;
using System.Management.Instrumentation;
using System.Reflection;
using OpenHardwareMonitor.Hardware;
using System.IO;
namespace TrustMonitoringTools.Plugins.Hardware
{
public class Check_Hardware_Memory_Load : IPlugins
{
ATypes warning;
ATypes critical;
bool hasArgs;
private string resultString;
public Check_Hardware_Memory_Load()
{
warning = new ATypes(90);
critical = new ATypes(95);
hasArgs = false;
loadOpenHardwareDll();
}
public Check_Hardware_Memory_Load(string warning, string critical)
{
this.warning = new ATypes(warning);
this.critical = new ATypes(critical);
hasArgs = true;
loadOpenHardwareDll();
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
resultString = String.Format("MEMORY LOAD: Making Test fail | metric=0.0 memory_load={0};0.8;1.0", result);
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
if (hasArgs)
{
if (!checkArgs())
{
Console.WriteLine("Error: Check your arguments!");
return 3;
}
}
Computer c1 = new Computer();
c1.RAMEnabled = true;
c1.Open();
double max_memory_load = 0;
bool has_memory_sensor = false;
foreach (var hardwareItem in c1.Hardware)
{
if (hardwareItem.HardwareType == HardwareType.RAM)
{
hardwareItem.Update();
foreach (var sensor in hardwareItem.Sensors)
{
if (sensor.SensorType == SensorType.Data)
{
 if (sensor.Name == "Used Memory")
{
has_memory_sensor = true;
max_memory_load = Convert.ToDouble(sensor.Value);
continue;
}
if (sensor.Name == "Available Memory")
{
max_memory_load = max_memory_load / (Convert.ToDouble(sensor.Value) + max_memory_load);
continue;
}
}
}
}
}
if (!has_memory_sensor)
{
resultString = "MEMORY LOAD OK: No sensors detected for this type of RAM | metric=1.00";
retVal = 0;
}
if ((max_memory_load * 100.0) < warning.getDouble())
{
 String performance_data = String.Format("memory_load={0};{1};{2}", max_memory_load.ToString("N2"), (warning.getDouble() / 100.0).ToString("N2"), (critical.getDouble() / 100.0).ToString("N2"));
resultString = "MEMORY LOAD OK: Memory load below thresholds | metric=1.00 " + performance_data;
 retVal = 0;
}
else if ((max_memory_load * 100.0) >= warning.getDouble() && (max_memory_load * 100.0) < critical.getDouble())
{
 ATypes a1 = new ATypes(max_memory_load * 100.0);
double temp1 = (1.0 / (this.warning.getDouble() - this.critical.getDouble())) * (a1.getDouble() - this.warning.getDouble()) + 1.0;
String performance_data = String.Format("memory_load={0};{1};{2}", max_memory_load.ToString("N2"), (warning.getDouble() / 100.0).ToString("N2"), (critical.getDouble() / 100.0).ToString("N2"));
resultString = String.Format("MEMORY LOAD WARNING: Found memory load above warning threshold: {0}% | metric={1} " + performance_data, max_memory_load.ToString("N2"), temp1.ToString("N2"));
retVal = 1;
}
else if ((max_memory_load * 100.0) >= critical.getDouble())
{
String performance_data = String.Format("memory_load={0};{1};{2}", max_memory_load.ToString("N2"), (warning.getDouble() / 100.0).ToString("N2"), (critical.getDouble() / 100.0).ToString("N2"));
resultString = "MEMORY LOAD CRITICAL: Memory load below thresholds | metric=0.00 " + performance_data;
retVal = 2;
}
else
{
resultString = "MEMORY LOAD UNKNOWN: This an unknown error";
retVal = 3;
}
}
Console.WriteLine(resultString);
 return retVal;
}
public bool checkArgs()
{
if (this.warning.getInt() <= 0 && this.critical.getInt() <= 0)
{
 return false;
}
if (this.warning.getInt() > this.critical.getInt())
{
 return false;
}
return true;
}
private void loadOpenHardwareDll()
{
EmbeddedAssembly.Load("TrustMonitoringTools.Libraries.OpenHardwareMonitorLib.dll", "OpenHardwareMonitorLib.dll");
AppDomain.CurrentDomain.AssemblyResolve += new ResolveEventHandler(CurrentDomain_AssemblyResolve);
}
private static Assembly CurrentDomain_AssemblyResolve(object sender, ResolveEventArgs args)
{
return EmbeddedAssembly.Get(args.Name);
}
}
}
