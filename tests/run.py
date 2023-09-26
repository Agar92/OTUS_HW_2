print("Python")
print("===========================")

from vars import *
print(var_a)
print(var_b)
print(var_c)

print("@@@")

#https://stackoverflow.com/questions/19009932/import-arbitrary-python-source-file-python-3-3 :
import importlib.machinery
loader=importlib.machinery.SourceFileLoader('vars', '/home/runner/work/OTUS_HW_2/OTUS_HW_2/tests/vars.py')
vars = loader.load_module()
print(vars.var_a)
print(vars.var_b)
print(vars.var_c)
print(var_a)
print(var_b)
print(var_c)

import os
print(os.getcwd())

myvars = {}
with open('/home/runner/work/OTUS_HW_2/OTUS_HW_2/tests/vars.py') as myfile:
    for line in myfile:
        name, var = line.partition("=")[::2]
        if isinstance(var, str):#if type(var) == str:
            print("name=%s"%(name))
            myvars[name.strip()] = str(var)
        elif isinstance(var, float):#elif type(var) == float:
            print("name=%f"%(var))
            myvars[name.strip()] = float(var)
print(myvars["var_a"])
print(myvars)


#one more approach to xml file:
import configparser
config = configparser.ConfigParser()
config.read('/home/runner/work/OTUS_HW_2/OTUS_HW_2/tests/vars.txt')
var_a = config.get("myvars", "var_a")
var_b = config.get("myvars", "var_b")
var_c = config.get("myvars", "var_c")
