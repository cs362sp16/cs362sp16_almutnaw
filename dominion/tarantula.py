#!/usr/bin/env python3
import sys

def parse_line(line):
  
    split_ln = line.split(':')

    if split_ln[0].strip(' ') in ('-','#####'):
        return None
    num_calls, line_no, line = [i.strip(' ') for i in split_ln]


    return (num_calls, line_no, line)


def parse_file(data, gcov_file, p_f):

    # check for first time creating database
    if "TOTAL" not in data.keys():
  
        data["TOTAL"] = [0, 0]
        data.sync()
    temp = data["TOTAL"]
    temp[p_f] += 1
    data["TOTAL"] = temp
    for line in gcov_file:
        result = parse_line(line)
        if result != None:
            num_calls, line_no, line = result
            if line_no not in data.keys():
                # initialize the line in the dict
                temp = [0, 0]
                temp[p_f] = 1
                data[line_no] = temp
                
            else:
                current_num = data[line_no][p_f]
                #check for security and sanity
                temp = data[line_no]
                temp[p_f] += 1
                data[line_no] = temp
                
    data.sync()


def print_results(data, max_lines=10):
    from operator import itemgetter
    results = {}
    for line in data.keys():
        if line != "TOTAL":
            
            tp = float(data["TOTAL"][0])
            tf = float(data["TOTAL"][1])
            lp = float(data[line][0])
            lf = float(data[line][1])

            
            
            try:
                results[line] = 1- ((lp/tp) / ((lp/tp) + (lf/tf)))
            except ZeroDivisionError:
                results[line] = 0

    print([(k, results[k]) for k in sorted(results, key=results.get, reverse=True)][:max_lines])

if __name__ == '__main__':
    # init stuff
    from getopt import getopt
    import shelve

    #check for commandline inputs
    if len(sys.argv) > 1:
        try:
            arg = getopt(sys.argv[1:], 'radh', ['help'])
            
        except:
            print("Invalid command parameters. Run as '" + sys.argv[0] + " -h' for more information")
            sys.exit(1)

        if len(arg[0]) > 2:
            print("Illegal combination of arguments. Please only use 1.")
            sys.exit(1)

        if arg[0][0][0] == '-r':
            
            with shelve.open("gcov_info_db") as db:
                # TEMP to get this to work
                db.sync()
                print_results(db)

        if arg[0][0][0] == '-a':
            
            if len(arg[1]) < 2:
                print("Illegal usage of -a. USAGE: -a filename pass/fail")
                sys.exit(1)

            p_f = arg[1][1]
            if p_f.lower() == "pass":
                p_f = 0
            elif p_f.lower() == "fail":
                p_f = 1
            else:
                print("Illegal usage of -a. USAGE: -a filename pass/fail")
                sys.exit(1)

            try:
                gcov_file = open(arg[1][0], mode='r')
            except:
                print("File not found")
                sys.exit(1)

            with shelve.open("gcov_info_db") as db:
                parse_file(db, gcov_file, p_f)

        elif arg[0][0][0] == '-h' or arg[0][0][0] == '--help':
            print("WElcome to the help menu...")

        elif arg[0][0][0] == '-d':
            answer = input("DELETING DATABASE. ARE YOU SURE? [y/n]") 
            if answer == 'y':
                with shelve.open("gcov_info_db") as db:
                    for key in db.keys():
                        del db[key]
            else:
                print("ABORTING")
    else:
        print("No parameters provided. Reading database by default...")
        with shelve.open("gcov_info_db") as db:
            print_results(db)
