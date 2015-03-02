using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Collections;
using System.IO;
using System.Text.RegularExpressions;

namespace minsql {
    class Sql_engine{// deal sql lang engine
        String dbpath = ""; //if 'use db_name' ch this work db
        const String NULL = "null"; //
        const String err_head = "ERROR: "; //
        const String rootpath = "data"; //
        const String undef_err = "check your sql version or type help for more info"; //
        const String query_ok = "query ok: "; //
        Hashtable ht = new Hashtable(); //int ->8, tinyint ->4, char ->128, varchar is var default 253
        Str_op strop = new Str_op();
        File_op fop = new File_op();
        Sql_engine_optional seop = new Sql_engine_optional();
        File_sql_deal fsd = new File_sql_deal();
        /**/
        public Sql_engine() {
            if (!Directory.Exists(rootpath)) {
                Directory.CreateDirectory(rootpath); // create main dir
            }
            /* do some map (ch if need) */
            ht.Add("int", 8);
            ht.Add("tinyint", 4);
            ht.Add("char", 128);
            ht.Add("varchar", 253);
        }
        /* @@@visit all ele creat table info */
        private void visit_all(List<ArrayList> lst) {
            foreach (ArrayList i in lst) {
                for (int j = 0; j < i.Count; j++) {
                    Console.Write(i[j] + " $ ");
                }
                Console.WriteLine();
            }
        }
        /* deal sql lang intface*/
        public void intf(String strln) {
            List<String> lnarr = strop.str_split(strln);
            if (lnarr.Count > 0) {
                which_query(lnarr, strln);
            }
        }
        /* get the fst word decide which query will go*/
        private void which_query(List<String> lnarr, String strln) {
            switch (lnarr[0]) {
                case "create":
                    if (lnarr.Count >= 3) {/* at least 3 words*/
                        create_deal(lnarr, strln);
                    } else {
                        Console.WriteLine(err_head + "(11)\n" + "args shorted in 'create' sentence");
                    }
                    break;
                case "insert":
                    insert_deal(strln);
                    break;
                case "delete":
                    delete_deal(strln);
                    break;
                case "update":
                    update_deal(strln);
                    break;
                case "select":
                    select_deal(strln);
                    break;
                case "use":
                    if (lnarr.Count == 2 && Directory.Exists(rootpath + "/" + lnarr[1])) {
                        dbpath = rootpath + "/" + lnarr[1];
                        Console.WriteLine(query_ok + "database " + lnarr[1] + " selected");
                        fsd.record_log("data/queryok.log", strln);
                    } else {
                        if (lnarr.Count != 2) {// use only allow 2 words
                            Console.WriteLine(err_head + "(0)\n" + "args shorted after 'use'");
                        } else {// no such db
                            Console.WriteLine(err_head + "(1)\n" + "no such database '" + lnarr[1] + "'");
                        }
                    }
                    break;
                case "show":
                    String tb_name = "";
                    int show_resl = -1;
                    show_resl = seop.optional_deal(strln, dbpath, ref tb_name);
                    if (show_resl == 9) {
                        String fst_line = fop.read_fst_line(dbpath + '/' + tb_name);
                        List<ArrayList> tb_info = new List<ArrayList>(create_table_deal(fst_line, false));
                        Console.WriteLine(fst_line);
                        visit_all(tb_info);
                    }
                    break;
                default: /* cant deal those */
                    Console.WriteLine(err_head + "(2)\n" + undef_err);
                    break;
            }
        }
        /**/
        private void create_deal(List<String> lnarr, String strln) {
            switch (lnarr[1]) {
                case "database":
                    if (lnarr.Count == 3) {// allow 3 words
                        if (Directory.Exists(rootpath + '/' + lnarr[2])){// is exist
                            Console.WriteLine(err_head + "(3)\n" + "database have existed");
                        } else {
                            Directory.CreateDirectory(rootpath + '/' + lnarr[2]);
                            Console.WriteLine(query_ok + "database '" + lnarr[2] + "' create");
                            fsd.record_log("data/queryok.log", strln);
                        }
                    } else {
                        if (lnarr.Count < 3) {
                            Console.WriteLine(err_head + "(4)\n" + "too many args in 'create' sentence");
                        } else {
                            Console.WriteLine(err_head + "(21)\n" + undef_err);
                        }
                    }
                    break;
                case "table":
                    create_table_deal(strln);
                    break;
                default:
                    Console.WriteLine(err_head + "(5)\n" + undef_err);
                    break;
            }
        }
        /* create tabele about deal (may append) */
        private List<ArrayList> create_table_deal(String strln = "", bool isself = true) {
            List<ArrayList> tb_info = new List<ArrayList>();
            try {
                ArrayList tmp_name_info = new ArrayList(); //table name info
                String front_tmp; // final sava type
                int varc_len = 0; // final save length (each char)
                bool is_set_varc_len = false;
                Regex reg = new Regex(@"\(([\w\(\), ]*)\)$");
                Match m = reg.Match(strln); // match str '(str)' like (col attr, col attr[, ...])
                String front = strln.Substring(0, strln.IndexOf('(')); // get the front part from whole sentence before '(' 
                List<String> partarr = strop.str_split(front); //
                if (partarr.Count == 3 && m.Success) {// match like 'create table mn (col attr, col attr[, ...])'
                    String incl = m.Groups[1].Value; //str like (col attr, col attr[, ...])
                    String[] inclarr = incl.Split(','); // split str with ','
                    tmp_name_info.Add(partarr[2]); // save name info
                    tb_info.Add(tmp_name_info); // save name info
                    foreach (String i in inclarr) {// deal each str like (col attr attr)
                        List<String> anyltmp = strop.str_split(i); // 
                        if (strop.is_in_array(tb_info, 1, anyltmp[0]) != -1) { //is col name unique 
                            Console.WriteLine(err_head + "(9)\n" + "col name is not unique");
                            tb_info.Clear();
                            return tb_info;
                        }
                        reg = new Regex(@"\(([0-9]*)\)$"); // match str like 'varchar(str)'
                        m = reg.Match(anyltmp[1]);
                        if (m.Success) {//if have str like 'varchar(str)'
                            front_tmp = anyltmp[1].Substring(0, anyltmp[1].IndexOf('('));
                            if (front_tmp == "varchar" && Convert.ToInt32(m.Groups[1].Value) <= 253) {
                                varc_len = Convert.ToInt32(m.Groups[1].Value);
                                is_set_varc_len = true;
                            }
                        } else {
                            front_tmp = anyltmp[1];
                        }
                        if (strop.is_in_array(front_tmp) == -1) {// is type in suprt_type
                            Console.WriteLine(err_head + "(10)\n" + "col type is undefined");
                            tb_info.Clear();
                            return tb_info;
                        }
                        if (!is_set_varc_len){// if not set user define length
                            varc_len = Convert.ToInt32(ht[front_tmp]);
                        }
                        ArrayList tmp_info = new ArrayList();/* save tb_info */
                        tmp_info.Add(anyltmp[0]);
                        tmp_info.Add(front_tmp);
                        tmp_info.Add(varc_len);
                        try {   /* try save nuique info */
                            if (anyltmp[2] == "unique"){
                                tmp_info.Add(anyltmp[2]);
                            }else{
                                tmp_info.Add(NULL);
                            }
                        }
                        catch{
                            tmp_info.Add(NULL);
                        }
                        tb_info.Add(tmp_info);
                    }
                    if (File.Exists(dbpath + "/" + partarr[2]) && isself) {// is table exist
                        Console.WriteLine(err_head + "(8)\n" + "table '" + partarr[2] + "' have created");
                    } else {
                        if (dbpath != "" && isself) {// is selected db
                            fop.wirte_fst_line(dbpath + '/' + partarr[2], strln);
                            Console.WriteLine(query_ok + "table '" + partarr[2] + "' created");
                            fsd.record_log("data/queryok.log", strln);
                        } else {
                            if (isself) {
                                Console.WriteLine(err_head + "(12)\n" + "no database selected");
                            }
                        }
                    }
                } else {
                    Console.WriteLine(err_head + "(20)\n" + undef_err);
                }
            }
            catch {
                Console.WriteLine(err_head + "(7)\n" + undef_err);
            }
            return tb_info;
        }
        /**/
        private int insert_deal(String strln, bool isinsert = true) {
            if (dbpath == "") { // use db
                Console.WriteLine(err_head + "(14)\n" + "no database selected");
                return 1;
            }
            Regex r;
            Match m;
            String tb_name;
            String cols = "";
            String values;
            String to_insrt = "";
            /* matcn str like 'insert into table_name (col, col[, ...]) values (val, val[, ...])' (first condtion) */
            r = new Regex(@"^insert[ ]+into[ ]+([\w]+)[ ]*\(([\w, ]+)\)[ ]*values[ ]*\(([\w, ]+)\)$");
            m = r.Match(strln);
            if (!m.Success) {/* (second condition) matcn str like 'insert into table_name values (val, val[, ...])' */
                r = new Regex(@"^insert[ ]+into[ ]+([\w]+)[ ]+values[ ]*\(([\w, ]+)\)$");
                m = r.Match(strln);
            }
            if (!m.Success){
                Console.WriteLine(err_head + "(13)\n" + "check you 'insert' stmt '()' and '()'");
                return 2;
            }
            tb_name = m.Groups[1].Value;
            if (!File.Exists(dbpath + '/' + tb_name)){ // is table exist
                Console.WriteLine(err_head + "(14)\n" + "no such table named '" + tb_name + "'");
                return 3;
            }
            //File_op fop = new File_op();/* get table info */
            List<ArrayList> tb_info = new List<ArrayList>(create_table_deal(fop.read_fst_line(dbpath + '/' + tb_name), false));
            if (m.Groups[3].Value == ""){// second condition
                values = m.Groups[2].Value;
            } else { // first condition
                cols = m.Groups[2].Value; // str like (col, col[, ...])
                values = m.Groups[3].Value; // str like (val, val[, ...])
                List<String> col_lst = new List<string>(strop.str_split(cols, ',')); // split cols with ',' get cols info
                if (col_lst.Count != (tb_info.Count - 1)){ // cols count is match with table info
                    Console.WriteLine(err_head + "(15)\n" + "cols is unmatched with def");
                    return 4;
                }
                for (int i = 1; i < col_lst.Count + 1; i++) {/* is tb_col_name equal with cols */
                    if (Convert.ToString(tb_info[i][0]) != col_lst[i - 1]){
                        Console.WriteLine(err_head + "(16)\n" + "cols name is wrong");
                        return 5;
                    }
                }
            }
            List<String> val_lst = new List<string>(strop.str_split(values, ',')); // split vals with ',' get vals info
            if (val_lst.Count != (tb_info.Count - 1)){// vals count is match with table info 
                Console.WriteLine(err_head + "(15)\n" + "values is unmatched with cols");
                return 6;
            }
            for (int i = 1; i < tb_info.Count; i++){/* check vals is legal */
                if (Convert.ToString(tb_info[i][1]) == "int" || Convert.ToString(tb_info[i][1]) == "tinyint"){
                    if (!strop.is_numric(val_lst[i - 1])){// is number or too large
                        Console.WriteLine(err_head + "(18)\n" + "you should type a int number or numb is too large");
                        return 7;
                    }
                } else {
                    if (val_lst[i - 1].Length > Convert.ToInt32(tb_info[i][2])){ // data length large than def
                        Console.WriteLine(err_head + "(19)\n" + "string data is too large");
                        return 8;
                    }
                }
            }
            for (int i = 1; i < tb_info.Count; i++){
                to_insrt += strop.format_save(Convert.ToString(tb_info[i][1]), val_lst[i - 1]); // get will save string
            }
            int check_length = Convert.ToInt32(tb_info[1][2]);
            if (tb_info[1][1].ToString() == "varchar"){ // deal special "varchar"
                check_length = 2;
            }
            int insert_resl = fop.insert_one_line(dbpath + '/' + tb_name, to_insrt, check_length, isinsert); // insert action
            if (insert_resl == 0 && isinsert) {
                Console.WriteLine("query ok:(0x0)\ninsert success");
                fsd.record_log("data/queryok.log", strln);
            }
            if (insert_resl == 0 || insert_resl == 2) {
                return 0;
            }
            return 9;
        }
        private void delete_deal(String strln){
            if (dbpath == "") { // use db
                Console.WriteLine(err_head + "(14)\n" + "no database selected");
                return;
            }
            Match m;
            Regex r = new Regex(@"^delete[ ]+from[ ]+([\w]+)[ ]+where[ ]+(.+)");
            m = r.Match(strln);
            if (m.Success) {
                /*
                (m.Groups[0].Value); // the whole sent
                (m.Groups[1].Value); // tb_name
                (m.Groups[2].Value); // where sub_sentence
                */
                if (File.Exists(dbpath + '/' + m.Groups[1].Value)) {
                    if (m.Groups[2].Value.Trim() == "1") {
                        fop.wirte_fst_line(dbpath + '/' + m.Groups[1].Value, fop.read_fst_line(dbpath + '/' + m.Groups[1].Value));
                        Console.WriteLine(query_ok + "(0x3)\n" + "all lines influenced");
                        return;
                    }
                    try {
                        List<ArrayList> tb_info = new List<ArrayList>(create_table_deal(fop.read_fst_line(dbpath + '/' + m.Groups[1].Value), false));// get tb_info
                        List<int> resl_lines = new List<int>(after_where_deal(tb_info, m.Groups[1].Value, m.Groups[2].Value)); //get meet condition lines 
                        for (int i = 0; i < resl_lines.Count; i++) {
                            //Console.WriteLine(resl_lines[i]);
                            fop.pack_line(dbpath + '/' + m.Groups[1].Value, "", resl_lines[i], false);
                            for (int j = i + 1; j < resl_lines.Count; j++) {
                                resl_lines[j] -= 1; // id delete one the rest line-num will be --
                            }
                        }
                        Console.WriteLine(query_ok + "(0x3)\n" + resl_lines.Count + " lines influenced");
                        fsd.record_log("data/queryok.log", strln);
                    } catch {
                        // do nothing
                    }
                } else { // table not exist
                    Console.WriteLine(err_head + "(24)\n" + "table '" + m.Groups[1].Value + "' not exist");
                }
            } else {
                Console.WriteLine(err_head + "(23)\n" + "check your 'delete' sentence");
            }
        }
        private void update_deal(String strln) {
            /*
            (m.Groups[1].Value); // tb_name
            (m.Groups[2].Value); // update cols
            (m.Groups[3].Value); // where sub_sentence
            */
            List<String> matcharr = new List<string>();
            String pattern = @"^update[ ]+([\w]+)[ ]+set[ ]+(.+)[ ]+where[ ]+(.+)";
            if (strop.pre_pattern(dbpath, pattern, strln, 1,ref matcharr) == 0) {
                int col_idx;
                List<String> after_set = strop.str_split(matcharr[2], '=');
                if (after_set.Count != 2) {
                    Console.WriteLine(err_head + "(29)\n" + "check your sentence after set");
                }
                List<ArrayList> tb_info = new List<ArrayList>(create_table_deal(fop.read_fst_line(dbpath + '/' + matcharr[1]), false));// get tb_info
                if ((col_idx = strop.is_in_array(tb_info, 1, after_set[0])) != -1) {
                    List<int> chlines = new List<int>(after_where_deal(tb_info, matcharr[1], matcharr[3]));
                    String insert_vals = ""; 
                    String insert_ln = "insert into " + matcharr[1] + " values";
                    String every_line = "";
                    if (chlines.Count > 2 && after_set[0] == Convert.ToString(tb_info[1][0])) {
                        Console.WriteLine(err_head + "(30)\n" + "Duplicate entry '"+ after_set[1] +"' for key 1 ");
                    }
                    for (int i = 0; i < chlines.Count; i++) {
                        
                        insert_ln = "insert into " + matcharr[1] + " values";
                        insert_vals = "";
                        every_line = fop.read_fst_line(dbpath + '/' + matcharr[1], chlines[i]);
                        List<String> valarr = new List<string>(strop.get_valarr(ref tb_info, matcharr[1], every_line, col_idx, true, after_set[1]));
                        foreach(String j in valarr) {
                            insert_vals += j + ',';
                        }
                        
                        fop.pack_line(dbpath + '/' + matcharr[1], "", chlines[i], false);
                        insert_ln += "(" + insert_vals.Substring(0, insert_vals.Length - 1) + ")";
                        
                        int update_resl = insert_deal(insert_ln, false);
                        if (update_resl != 0) {
                            fop.pack_line(dbpath + '/' + matcharr[1], every_line, chlines[i] - 1, true);
                            return;
                        } 
                        
                    }
                    Console.WriteLine(query_ok + "(0x4)\n" + "update success " + chlines.Count + " lines influenced");
                    fsd.record_log("data/queryok.log", strln);
                } else {
                    Console.WriteLine(err_head + "(29)\n" + "no such col named '" + after_set[0] +"'");
                }
            }
        }
        private void select_deal(String strln) {
            /*
             (m.Groups[1].Value); // show cols
             (m.Groups[2].Value); // tb_name
             (m.Groups[3].Value); // where sub_sentence
             */
            List<String> matcharr = new List<string>();
            int pre_resl = strop.pre_pattern(dbpath, @"^select[ ]+([\w, *]+)[ ]+from[ ]+([\w]+)[ ]+where[ ]+(.+)", strln, 2, ref matcharr);
            if (pre_resl == 0) {
                List<ArrayList> tb_info = new List<ArrayList>(create_table_deal(fop.read_fst_line(dbpath + '/' + matcharr[2]), false));// get tb_info
                List<String> cols_name = strop.str_split(matcharr[1], ',');
                List<int> cols_num = new List<int>();
                int col_n;
                if (matcharr[1].Trim() == "*") {
                    for (int i = 1; i < tb_info.Count; i++) {
                        cols_num.Add(i);
                    }
                } else{
                    if (cols_name.Count > tb_info.Count - 1) {
                        Console.WriteLine(err_head + "(32/n)" + "col-number is uncorrect");
                        return;
                    }
                    foreach (String i in cols_name) {
                        if ((col_n = strop.is_in_array(tb_info, 1, i)) == -1) {
                            Console.WriteLine(err_head + "(31)\n" + "col-name is uncorrect");
                            return;
                        }
                        cols_num.Add(col_n);
                    }
                }
                int resl_lines = after_where_deal(tb_info, matcharr[2], matcharr[3], cols_num).Count;
                Console.WriteLine(query_ok + "(0x4)\n" + query_ok + resl_lines + " lines influenced");
            }
        }
        private List<int> after_where_deal(List<ArrayList>tb_info, String tb_name,String after_where, List<int> cols_num = null) { // deal sentence like 'where xxx op yyy'
            List<int> resl = new List<int>(); // final result
            try {
                if (cols_num.Count > 0) {
                    Console.WriteLine("-----------------------");
                    foreach (int ii in cols_num) {
                        Console.Write(" $ " + tb_info[ii][0]);
                    }
                    Console.WriteLine("\n-----------------------");
                }
            } catch {
                //do nothing
            }
            if (after_where.Trim() == "1") {
                StreamReader org = new StreamReader(dbpath + '/' + tb_name);
                String every_line;
                int lines = 0;
                org.ReadLine();
                while ((every_line = org.ReadLine()) != null) {
                    lines++;
                    resl.Add(lines);
                    try {
                        if (cols_num.Count > 0) {
                            List<String> where_resl = new List<string>(strop.get_valarr(ref tb_info, tb_name, every_line));
                            foreach (int ii in cols_num) {
                                Console.Write(" $ " + where_resl[ii - 1]);
                            }
                            Console.Write("\n-----------------------\n");
                        }
                    } catch {
                        // do nothing
                    }
                }
                org.Close();
                return resl;
            }
            int check_len; // which col-indx in table-info
            String symbol = strop.which_symbol(after_where); // query 'where xxx op yyy' get op
            if (symbol != "") {
                List<String> awarr = new List<string>(strop.str_split(after_where, symbol.ToCharArray()));// query 'where xxx op yyy' get [xxx, yyy]
                if (awarr.Count == 2) { // only allow 2 op-obj     
                    if ((check_len = strop.is_in_array(tb_info, 1, awarr[0])) != -1) {// is in table-col-name
                        StreamReader org = new StreamReader(dbpath + '/' + tb_name); // read table data info
                        String every_line; // every time query one line
                        String cmp1 = ""; // compare obj given by user
                        String cmp2 = ""; // compare obj given by table
                        int  lines = 0; // offs: read offset, length: read length, lines: line-number counter
                        org.ReadLine(); // ignore fst-line  
                        while ((every_line = org.ReadLine()) != null) { // read every line
                            lines++;
                            strop.get_cmps(check_len, awarr[1], ref every_line, ref tb_info, ref cmp1, ref cmp2); // get 2 needed cmp obj
                            if (strop.is_meet_symbol(symbol, cmp2, cmp1)) {
                                resl.Add(lines);
                                try {
                                    if (cols_num.Count > 0) {
                                        List<String> where_resl = new List<string>(strop.get_valarr(ref tb_info, tb_name, every_line));
                                        foreach (int ii in cols_num) {
                                            Console.Write(" $ " + where_resl[ii - 1]);
                                        }
                                        Console.Write("\n-----------------------\n");
                                    }
                                } catch { 
                                    // do nothing
                                }
                            }
                        }
                        org.Close();
                    } else { // col name is wrong
                        Console.WriteLine(err_head + "(27)\n" + "no such col named '" + awarr[0] +"'");
                        return null;
                    }
                } else { // too many op-obj
                    Console.WriteLine(err_head + "(26)\n" + "check your sentence after where");
                    return null;
                }
            } else { // cant get op
                Console.WriteLine(err_head + "(25)\n" + "check your sentence after where");
                return null;
            }
            return resl;
        }
    }
}
