using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Collections;
using System.IO;
using System.Text.RegularExpressions;

namespace minsql {
    class Str_op {
        const String err_head = "ERROR: "; //
        const String undef_err = "check your sql version or type help for more info"; //
        String[] supr_symbol = { ">=", "<=", "!=", ">", "<", "=" };
        String[] supr_type = { "int", "tinyint", "char", "varchar" }; // 
        Hashtable ht = new Hashtable(); //int ->8, tinyint ->4, char ->128, varchar is var default 253
        public Str_op() {
            ht.Add("int", 8);
            ht.Add("tinyint", 4);
            ht.Add("char", 128);
            ht.Add("varchar", 253);
        }
        /* is suport symbol */
        public String which_symbol(String after_where){
            foreach (String i in supr_symbol) {
                if (after_where.IndexOf(i) != -1) {
                    return i;
                }
            }
            return "";
        }
        /* split str with char[] {'a','b'[, ...]} and remove null*/
        public List<String> str_split(String str, char[] split) {
            List<String> lnarr = new List<String>(str.Split(split));
            for (int i = 0; i < lnarr.Count(); i++) {
                lnarr[i] = lnarr[i].Trim();
                if (lnarr[i] == "" || lnarr[i] == " ") {
                    lnarr.RemoveAt(i);
                }
            }
            return lnarr;
        }
        /* split str with 'split' and remove null*/
        public List<String> str_split(String str, char split = ' ') {
            List<String> lnarr = new List<String>(str.Split(split));
            for (int i = 0; i < lnarr.Count(); i++) {
                lnarr[i] = lnarr[i].Trim();
                if (lnarr[i] == "" || lnarr[i] == " ") {
                    lnarr.RemoveAt(i);
                }
            }
            return lnarr;
        }
        /* is suprt_type */
        public int is_in_array(String mch) {
            for (int i = 0; i < supr_type.Count(); i++) {
                if (mch == supr_type[i])  {
                    return i;
                }
            }
            return -1;
        }
        /* is unique col name */
        public int is_in_array(List<ArrayList> al, int s, String mch) {
            for (int i = s; i < al.Count; i++) {
                if (mch == Convert.ToString(al[i][0])) {
                    return i;
                }
            }
            return -1;
        }
        /* get the minsql_def save_format */
        public String format_save(String type, String str) {
            switch (type) {
                /* save as hex (if shrted add "0")*/
                case "tinyint":
                case "int":
                    String asist = "";
                    String save = int.Parse(str).ToString("x");
                    for (int i = 0; i < Convert.ToInt32(ht[type]) - save.Length; i++) {
                        asist += "0";
                    }
                    return asist + save;
                /* save as char (if shrted add " ")*/
                case "char":
                    asist = "";
                    for (int i = 0; i < Convert.ToInt32(ht[type]) - str.Length; i++) {
                        asist += " ";
                    }
                    return str + asist;
                /* save as uer_def but save 2 char record how long of the string */
                case "varchar":
                    String record_byte = "";
                    if (str.Length.ToString("x").Length < 2) {
                        record_byte = "0" + str.Length.ToString("x");
                    } else {
                        record_byte = str.Length.ToString("x");
                    }
                    return record_byte + str;
                default:
                    break;
            }
            return "";
        }
        public String decode_save_str(String type, String str) {
            switch (type) {
                case "tinyint":
                case "int":
                    int resl = Convert.ToInt32(str, 16);
                    return resl.ToString();
                /* save as char (if shrted add " ")*/
                case "char":
                    return str.Trim();
                default:
                    break;
            }
            return "";
        }
        /* check str is numric or too large */
        public bool is_numric(String s) {
            try {
                int.Parse(s);
                return true;
            }
            catch {
                return false;
            }
        }
        /**/
        public bool is_meet_symbol(String symbol, String cmp1, String cmp2) {
            switch (symbol) { 
                case "=":
                    if (string.Compare(cmp1, cmp2) == 0) {
                        return true;
                    }
                    return false;
                case ">":
                    if (string.Compare(cmp1, cmp2) == 1) {
                        return true;
                    }
                    return false;
                case "<":
                    if (string.Compare(cmp1, cmp2) == -1) {
                        return true;
                    }
                    return false;
                case ">=":
                    if (string.Compare(cmp1, cmp2) == 1 || string.Compare(cmp1, cmp2) == 0) {
                        return true;
                    }
                    return false;
                case "<=":
                    if (string.Compare(cmp1, cmp2) == -1 || string.Compare(cmp1, cmp2) == 0) {
                        return true;
                    }
                    return false;
                case "!=":
                    if (string.Compare(cmp1, cmp2) == 1 || string.Compare(cmp1, cmp2) == -1) {
                        return true;
                    }
                    return false;
                default:
                    return false;
            }
        }
        /**/
        public int pre_pattern(String dbpath, String pattern, String strln, int tb_name_idx, ref List<String> matcharr) {
            if (dbpath == "") { // use db
                Console.WriteLine(err_head + "(14)\n" + "no database selected");
                return 1;
            }
            Match m;
            Regex r = new Regex(pattern);
            m = r.Match(strln);
            if (m.Success) {
                if (File.Exists(dbpath + "/" + m.Groups[tb_name_idx].Value)) {
                    for (int i = 0; i < m.Groups.Count; i++) {
                        matcharr.Add(m.Groups[i].Value);
                    }
                    return 0;
                } else {
                    Console.WriteLine(err_head + "(24)\n" + "table '" + m.Groups[tb_name_idx].Value + "' not exist");
                    return 2;
                }
            } else {
                Console.WriteLine(err_head + "(28)\n" + undef_err);
                return 3;
            }
            
        }
        /**/
        public void get_cmps(int check_len, String val,ref String every_line, ref List<ArrayList> tb_info, ref String cmp1, ref String cmp2){
            int offs, length;
            offs = length = 0;
            for (int i = 1; i < check_len; i++) {
                if (Convert.ToString(tb_info[i][1]) == "varchar") {
                    offs += Convert.ToInt32(every_line.Substring(offs, 2), 16) + 2;
                } else {
                    offs += Convert.ToInt32(tb_info[i][2]);
                }
            }
            if (Convert.ToString(tb_info[check_len][1]) == "varchar") { 
                length = Convert.ToInt32(every_line.Substring(offs, 2), 16);
                offs += 2;
                cmp1 = val;
            } else {
                length = Convert.ToInt32(tb_info[check_len][2]);
                cmp1 = format_save(Convert.ToString(tb_info[check_len][1]), val);
            }
            cmp2 = every_line.Substring(offs, length);
        }
        /**/
        public List<String> get_valarr(ref List<ArrayList> tb_info, String tb_name, String every_line, int idx = -1, bool is_update = false, String new_val = "") {
            List<String> valarr = new List<string>();
            int offs = 0;
            for (int i = 1; i < tb_info.Count; i++) {
                if (Convert.ToString(tb_info[i][1]) == "varchar") {
                    valarr.Add(every_line.Substring(offs + 2, Convert.ToInt32(every_line.Substring(offs, 2), 16)));
                    offs += Convert.ToInt32(every_line.Substring(offs, 2), 16) + 2;
                } else {
                    valarr.Add(decode_save_str(Convert.ToString(tb_info[i][1]), every_line.Substring(offs, Convert.ToInt32(tb_info[i][2]))));
                    offs += Convert.ToInt32(tb_info[i][2]);
                }
            }
            if (is_update) {
                valarr[idx - 1] = new_val;
            }
            return valarr;
        }
    }
}
