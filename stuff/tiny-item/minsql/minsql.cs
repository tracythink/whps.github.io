/*
 * coding by whps 2014.7.11 12:00
 * come true a small database
 * named minsql
 * save data as char
 */
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Collections;
using System.IO;
using System.Text.RegularExpressions;

namespace minsql {
    class sql_main {
        const String HEADWORDS = "minsql>";
        static void Main(string[] args) {
            try {
                if (args.Length == 2) {
                    if (args[0] == "-f" && File.Exists(args[1])) {
                        File_sql_deal deal = new File_sql_deal();
                        deal.deal_input_file(args[1]);
                        Console.Read();
                        return;
                    } else {
                        Console.WriteLine("error: type like 'cmd -f filename' or path mistake");
                        return;
                    }
                } else {
                    String strln;
                    Sql_engine sql_lang = new Sql_engine();
                    File_sql_deal fsd = new File_sql_deal();
                    while (true) {// main loop deal evey input line
                        Console.Write(HEADWORDS);
                        strln = Console.ReadLine();
                        sql_lang.intf(strln);
                        fsd.record_log("data/minsql.log", strln);
                    }
                }
            } catch {
                Console.WriteLine("upexpected error; type any end");
                Console.Read();
            }
        }
    }
}
