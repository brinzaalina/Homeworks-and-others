using System.Diagnostics;
using A4.Implementation;

namespace A4;

public class Program
{
    static void Main()
    {
        Stopwatch stopwatch = new Stopwatch();
        var hosts = new List<string>
        {
            //"www.cs.ubbcluj.ro/~hfpop/teaching/pfl/requirements.html",
            "www.cs.ubbcluj.ro/~forest/newton/index.html",
            // "www.cs.ubbcluj.ro/~rlupsa/edu/pdp/index.html"
            // "www.columbia.edu/~fdc/sample.html"
        };
        
        Console.WriteLine("-----DIRECT CALLBACK-----");
        stopwatch.Start();
        DirectCallback.Run(hosts);
        stopwatch.Stop();
        TimeSpan directCallbackTime = stopwatch.Elapsed;
        
        Console.WriteLine("-----TASKS-----");
        stopwatch.Restart();
        TaskMechanism.Run(hosts);
        stopwatch.Stop();
        TimeSpan taskMechanismTime = stopwatch.Elapsed;
        
        
        Console.WriteLine("-----ASYNC/AWAIT TASKS-----");
        stopwatch.Restart();
        AsyncTaskMechanism.Run(hosts);
        stopwatch.Stop();
        TimeSpan asyncTaskMechanismTime = stopwatch.Elapsed;
        
        Console.WriteLine("Direct callback: {0}", directCallbackTime);
        Console.WriteLine("Task mechanism: {0}", taskMechanismTime);
        Console.WriteLine("Async task mechanism: {0}", asyncTaskMechanismTime);
    }
}