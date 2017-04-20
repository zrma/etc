using System;
using System.IO;

namespace RiderSample
{
    internal class Program
    {
        public static void Main(string[] args)
        {
            // Put all file names in root directory into array.
            var array1 = Directory.GetFiles("/");

            // Display all files.
            Console.WriteLine("--- Files: ---");
            foreach (var name in array1)
            {
                Console.WriteLine(name);
            }
        }
    }
}