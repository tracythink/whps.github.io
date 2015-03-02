using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Collections;
using System.IO;
using System.Text.RegularExpressions;

namespace minsql {
    class File_op {
        /* read the first line from a file */
        public String read_fst_line(String path, int lines = 0) {
            String line;
            StreamReader file = new StreamReader(path);
            line = file.ReadLine();
            for (int i = 0; i < lines; i++) {
                line = file.ReadLine();
            }
            file.Close();
            return line;
        }
        /* write a line as a fst_line in a file */
        public void wirte_fst_line(String path, String fst_line) {
            StreamWriter sw = new StreamWriter(path);
            sw.WriteLine(fst_line);
            sw.Close();
        }
        /* insert only one line into a file order by primary (primary is the first col default) */
        /* path: @, to_save:which string to save inthe file; check_length: how long to read the compare part*/
        public int insert_one_line(String path, String to_save, int check_length, bool isinsert = true) {
            StreamReader org = new StreamReader(path); // read table
            String every_line = ""; // every time deal one line
            int cmp_resl; // the compare reslut
            int lines = 0; // line number counter
            int to_save_cl; // read to-save-string length

            org.ReadLine(); // ignore to fst line

            while ((every_line = org.ReadLine()) != null){ // find which line to insert
                if (check_length == 2) {// if varchar
                    check_length = Convert.ToInt32((every_line.Substring(0, 2)), 16);
                    to_save_cl = Convert.ToInt32((to_save.Substring(0, 2)), 16);
                    cmp_resl = string.Compare(every_line.Substring(2, check_length), to_save.Substring(2, to_save_cl));
                } else {
                    to_save_cl = check_length;
                    cmp_resl = string.Compare(every_line.Substring(0, check_length), to_save.Substring(0, to_save_cl));
                }
                if (cmp_resl == 0) { // primary unique
                    org.Close();
                    Console.WriteLine("ERROR:(22)\n" + "primary not unique");
                    return 1;
                } else if (cmp_resl == -1) {// find line which is big than to_save line
                    lines++;
                } else {
                    org.Close();
                    pack_line(path, to_save, lines);
                    return 0;
                }
            }
            org.Close();
            add_last_line(path, to_save); // if the correct position is file-end
            if (isinsert) {
                Console.WriteLine("query ok:(0x1)\ninsert success");
            }
            return 2;
        }
        /* write to the end line in a file */
        private void add_last_line(String path, String to_save) {
            StreamWriter sw = new StreamWriter(path, true);
            sw.WriteLine(to_save);
            sw.Close();
        }
        /* (write to the mid line in a file) divide two part and write 2 files and add $ front-file + to-write-line + back-file $ */
        public void pack_line(String path, String to_save, int ln, bool isself = true)   {
            int front_end;
            String tmp_path_back = path + "tmpback";
            String tmp_path_front = path + "tmpfront";
            String every_line;
            StreamReader org = new StreamReader(path);
            StreamWriter front = new StreamWriter(tmp_path_front);
            StreamWriter back = new StreamWriter(tmp_path_back);
            if (isself) {
                front_end = ln + 1;
            } else {
                front_end = ln;
            }
            for (int i = 0; i < front_end; i++) {
                every_line = org.ReadLine();
                front.WriteLine(every_line);
            }
            if (!isself) {
                org.ReadLine();
            }
            while ((every_line = org.ReadLine()) != null && every_line != "\n") {
                back.WriteLine(every_line);
            }
            org.Close();
            front.Close();
            back.Close();
            StreamWriter worg = new StreamWriter(path);
            StreamReader rfront = new StreamReader(tmp_path_front);
            StreamReader rback = new StreamReader(tmp_path_back);

            while ((every_line = rfront.ReadLine()) != null && every_line != "\n") {
                worg.WriteLine(every_line);
            }
            if (to_save != "") {
                worg.WriteLine(to_save);
            }
            while ((every_line = rback.ReadLine()) != null && every_line != "\n"){
                worg.WriteLine(every_line);
            }
            worg.Close();
            rfront.Close();
            rback.Close();
            File.Delete(tmp_path_front);
            File.Delete(tmp_path_back);
        }
        /**/
        /*
        public void update_one(String path, String to_save, int ln) {
            pack_line(path, "", ln, false);
            pack_line(path, to_save, ln - 1);
        }  
        */
    }
}