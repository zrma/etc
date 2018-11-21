using System;
using System.Collections.Generic;
using System.Linq;

namespace RiderSample
{
    internal static class Program
    {
        private static void Test(IEnumerable<int> container)
        {
            container.ToList().ForEach(Console.WriteLine);
        }
        
        public static void Main()
        {
            Test(Enumerable.Range(1, 10).Select(x => x * x));
        }
    }
}