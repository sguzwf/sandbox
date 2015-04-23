using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

// source: https://vivekcek.wordpress.com/2012/08/26/c-async-helloworld/
public static class Program
{
  public static void Main ()
  {
    //Calculate();
    Calculate();
    Console.WriteLine("Asychronous Execution Started");
    Console.ReadLine();
  }

  public static async void Calculate ()
  {
    Task<int> t = Task<int>.Factory.StartNew(() =>
      {
        int i = 0;
        for (; i < 100; ++i)
        {
          System.Threading.Thread.Sleep(10);
        }
        return i;
      });
    await t;
    Console.WriteLine(t.Result);
  }
}
