using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Text.RegularExpressions;
using System.IO;

namespace minsql {
    class Sql_engine_optional {
        public int optional_deal(String strln, String dbpath, ref String tb_name) {
            
            Match m;
            Regex r = new Regex(@"^show[ ]+databases$");
            m = r.Match(strln);
            if (m.Success) {
                if (Directory.Exists("data/")) {
                    display("data/", "databses");
                    return 0;
                } else {
                    Console.WriteLine("ERROR: (42)\n" + "no such work dir");
                    return 4;
                }
            }
            if (dbpath == "") {
                Console.WriteLine("ERROR: (40)\n" + "no database selected");
                return 1;
            }
            r = new Regex(@"^show[ ]+tables$");
            m = r.Match(strln);
            if (m.Success) {
                if (Directory.Exists(dbpath)) {
                    display(dbpath, "tables");
                    return 5;
                } else {
                    Console.WriteLine("ERROR: (41)\n" + "no such database");
                    return 2;
                }
            }
            r = new Regex(@"^show[ ]+create[ ]table[ ]+([\w]+)$");
            m = r.Match(strln);
            if (m.Success) {
                if (File.Exists(dbpath + '/' + m.Groups[1].Value)) {
                    tb_name = m.Groups[1].Value;
                    return 9;
                } else {
                    Console.WriteLine("ERROR: (44)\n" + "no such table");
                    return 7;
                }
            }
            Console.WriteLine("ERROR: (43)\n" + "check your 'show' sentence");
            return 3;
        }
        private void display(String path, String tit) {
            DirectoryInfo dirinfo = new DirectoryInfo(path);
            FileSystemInfo[] resl = dirinfo.GetFileSystemInfos();
            Console.WriteLine("-----------------------");
            Console.WriteLine(tit);
            Console.WriteLine("-----------------------");
            foreach (FileSystemInfo i in resl) {
                if (i.ToString().IndexOf('.') != -1) {
                    continue;
                }
                Console.WriteLine(i.ToString());
                Console.WriteLine("-----------------------");
            }
        }
    }
}
