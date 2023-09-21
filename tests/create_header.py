import re
import sys

input_filename="/home/andrey/Desktop/OTUS_HW2/tests/globals.py"
output_filename="/home/andrey/Desktop/OTUS_HW2/tests/globals.h"


#a="asd"
#res=a.isdigit()
#print(res)


def _is_float(string):
    try:
        float(string)
        #print("float")
    except ValueError:
        return False
    else:
        return True
def _is_int(string):
    try:
        int(string)
        #print("int")
    except ValueError:
        return False
    else:
        return True
def _is_string(string):
    try:
        str(string)
        print("string")
    except ValueError:
        return False
    else:
        return True

# Define a function for identifying a Digit
def is_int(string):
    # Make a regular expression for identifying a digit
    regex = '^[0-9]+$'
     # pass the regular expression
     # and the string in search() method
    if(re.search(regex, string)):
        print("int")
    else:
        print("Not an int")
def is_float(string):
    print("is_float: %s"%string)
    # Compile a regular expression pattern to match valid float values
    pattern = r"^[-+]?[0-9]*\.?[0-9]+$"

    # Use re.match to check if the string matches the pattern
    # Returns a match object if there is a match, else None
    match = re.match(pattern, string)

    # Convert the match object to a boolean value
    # Returns True if there is a match, else False
    return bool(match)
def is_float(string):
    print("is_float: %s"%string)
    # Compile a regular expression pattern to match valid float values
    pattern = r"^[-+]?[0-9]*\.?[0-9]+$"

    # Use re.match to check if the string matches the pattern
    # Returns a match object if there is a match, else None
    match = re.match(pattern, string)

    # Convert the match object to a boolean value
    # Returns True if there is a match, else False
    return bool(match)
# Using regular expression without anchors and allowing exponent notation :
# https://www.geeksforgeeks.org/python-check-for-float-string/
def is_float_v2(string):
    pattern = r"[-+]?(\d+(\.\d*)?|\.\d+)([eE][-+]?\d+)?"
    match = re.match(pattern, string)
    return bool(match)

globals = {}
with open(input_filename, 'r') as myfile:
    for line in myfile:
        name, var = line.partition("=")[::2]
        #var = ''.join(var.split())
        var = re.sub(r"\s+", "", var, flags=re.UNICODE)
        #var.replace(" ", "")
        res=is_float(var)
        print("isdigit=%s %s %s"%(res, name, var));
        if _is_int(var):#var.isdigit() == False:#if type(var) == str:
            print("int name=%s"%(var))
            globals[name.strip()] = int(var)
        elif _is_float(var):#elif type(var) == float:
            print("float name=%s"%(var))
            globals[name.strip()] = float(var)
        elif _is_string(var):#elif type(var) == float:
            print("str name=%s"%(var))
            globals[name.strip()] = str(var)
        else:
            print("no")
print(globals)
lines = []
keys=globals.keys()
for key in globals.keys():
    print(key," ->", globals[key])
    type=""
    if isinstance(globals[key], int):
        type="int"
    elif isinstance(globals[key], float):
        type="double"
    elif isinstance(globals[key], str):
        type="std::string"
    var_name=key.replace('var_', ' ')
    line="const " + type + " " + var_name + " = " + str(globals[key]) + ";" +"\n"
    print("line=%s"%(line))
    lines.append("  " + line)

with open(output_filename, "w") as file1:
    # Writing data to a file
    file1.write("#pragma once\n")
    file1.write("namespace globals {\n")
    #sys.exit()
    file1.writelines(lines)
    file1.write("}\n")
    print("END of write to file globals.py")

# Reading from file
with open(output_filename, "r+") as file1:
    # Reading from a file
    print(file1.read())


