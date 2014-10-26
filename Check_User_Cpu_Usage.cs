using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;

namespace TrustMonitoringTools.Plugins.User
{
    public class Check_User_Cpu_Usage : IPlugins
    {
        private string resultString;
        private ATypes warning;
        private ATypes critical;
        private bool hasArgs;

        private List<string> users_exclusions;
        private bool exclude_system_accounts = false;

        // Max memory per user
        public Check_User_Cpu_Usage()
        {
            warning = new ATypes("40"); // In % per second
            critical = new ATypes("50"); // In % per second
            hasArgs = false;
            initializeUserExclusions();
        }

        public Check_User_Cpu_Usage(string w, string c)
        {
            warning = new ATypes(w);
            critical = new ATypes(c);
            hasArgs = true;
            initializeUserExclusions();
        }

        public bool failTest()
        {
            string file_path = Constants.PLUGIN_FAIL_TESTS_DIRECTORY + this.GetType().Name.ToLower() + ".txt";
            if (Constants.FAIL_TEST_MODE && File.Exists(file_path))
            {
                // Analog, read the value
                int result = -1;

                // If file size is greater than 0

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
                    result = this.critical.getInt() + 1; // This makes sure that is greater than critical
                }

                // Critical state
                resultString = String.Format("USER CPU USAGE: Making Test fail | metric=0.0 user_cpu_usage={0};40;50", result);

                return true;
            }
            else
                return false;
        }

        public int executePlugin() 
        {
            int retVal = 3;

            // check whether to fail test
            if (failTest())
                retVal = 2;
            else
            {
                if (hasArgs)
                {
                    if (!checkArgs())
                    {
                        Console.WriteLine("Check your arguments!");
                        return 3;
                    }
                }

                UserUtilities s1 = new UserUtilities();
                Dictionary<string, List<StoreUserProcesses>> processes = s1.GetUsersProcessesInfo();

                Dictionary<string, float> user_memory = new Dictionary<string, float>(); // used to store info temporary

                foreach (KeyValuePair<string, List<StoreUserProcesses>> user in processes)
                {

                    // Add it to our list
                    if (!user_memory.ContainsKey(user.Key)) user_memory[user.Key] = 0;

                    // Iterate through each users process
                    foreach (StoreUserProcesses process in user.Value)
                    {
                        user_memory[user.Key] += process.cpu_load;
                    }
                }

                string output_data = "";
                string performance_data = "";
                string metric_data = " | metric=";

                bool is_critical = false;
                bool is_warning = false;

                float largest_cpu_load_found = 0;

                foreach (var x in user_memory)
                {
                    if (exclude_system_accounts)
                    {
                        // Exclude the user
                        if (users_exclusions.Contains(x.Key)) continue;
                    }

                    // Make sure to substitute the space by underscore if the user contains space
                    string user = x.Key.Contains(" ") ? x.Key.Replace(" ", "_") : x.Key;

                    float current_cpu_load = x.Value; // In MB

                    performance_data += String.Format("{0}={1};{2};{3} ", user, current_cpu_load.ToString("N2"), warning.getDouble().ToString("N2"), critical.getDouble().ToString("N2"));

                    if (current_cpu_load > largest_cpu_load_found) largest_cpu_load_found = current_cpu_load;

                    if (current_cpu_load >= critical.getLong())
                    {
                        is_critical = true;
                        output_data += String.Format("User {0} has {1} %/sec ", user, current_cpu_load.ToString("N2"));
                        continue;
                    }
                    if (current_cpu_load >= warning.getLong())
                    {
                        is_warning = true;
                        output_data += String.Format("User {0} has {1} %/sec ", user, current_cpu_load.ToString("N2"));
                        continue;
                    }
                }

                // Printing the output starts here
                if (is_critical)
                {
                    string metric = metric_data + "0.00 ";
                    resultString = "USER CPU LOAD CRITICAL: " + output_data.Trim() + " cpu in use" + metric + performance_data;
                    retVal = 2;
                }
                else if (is_warning)
                {
                    ATypes a1 = new ATypes(largest_cpu_load_found);
                    double metric = (1.0 / (this.warning.getDouble() - this.critical.getDouble())) * (a1.getDouble() - this.warning.getDouble()) + 1.0;
                    resultString = "USER CPU LOAD WARNING: " + output_data.Trim() + " cpu in use" + metric_data
                                    + metric.ToString("N2") + " " + performance_data;
                    retVal = 1;
                }

                else if (!is_warning && !is_critical)
                {
                    string metric = "1.00 ";
                    resultString = "USER CPU LOAD OK: All users are within thresholds" + metric_data + metric + performance_data;
                    retVal = 0;
                }
                else
                {
                    resultString = "USER CPU LOAD UNKNOWN: Unknown error";
                    retVal = 3;
                }
            }

            Console.WriteLine(resultString);
            return retVal;

        }

        public bool checkArgs()
        {
            if (warning.getInt() <= 0 || critical.getInt() <= 0)
            {
                return false;
            }

            if (warning.getInt() > critical.getInt())
            {
                return false;
            }

            return true;
        }

        // Add any other user to exclude
        private void initializeUserExclusions()
        {
            users_exclusions = new List<string>();
            users_exclusions.Add("SYSTEM");
            users_exclusions.Add("NETWORK SERVICE");
            users_exclusions.Add("LOCAL SERVICE");
        }
    }
}