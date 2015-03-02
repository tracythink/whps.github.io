using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;

namespace minsql {
    class File_sql_deal {
        public void record_log(String path, String strln){
            StreamWriter sw = new StreamWriter(path, true);
            sw.WriteLine(strln);
            sw.Close();
        }
        public void deal_input_file(String path) {
            Sql_engine reboot = new Sql_engine();
            StreamReader rder = new StreamReader(path);
            String every_line = "";
            while ((every_line = rder.ReadLine()) != null){
                reboot.intf(every_line);
            }
            rder.Close();
        }
    }
}
