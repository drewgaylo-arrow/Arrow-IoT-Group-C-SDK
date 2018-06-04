import sys
import os
from subprocess import call

build_dir = "build"
#release_dir = "release_atollic"
release_dir = "release_SAMD21"

library = "libacnsdkc.a"
lib_path = build_dir+"/"+library


#call(["rm","release/libacnsdkc_ARM_O*"])


lst = []
lst.append(["LIBDIR="+build_dir,"OPT=-O0","WOLFSSL=no","libacnsdkc_ARM_O0_HARD_NOSSL.a"])
lst.append(["LIBDIR="+build_dir,"OPT=-O1","WOLFSSL=no","libacnsdkc_ARM_O1_HARD_NOSSL.a"])
lst.append(["LIBDIR="+build_dir,"OPT=-O2","WOLFSSL=no","libacnsdkc_ARM_O2_HARD_NOSSL.a"])
lst.append(["LIBDIR="+build_dir,"OPT=-O3","WOLFSSL=no","libacnsdkc_ARM_O3_HARD_NOSSL.a"])
lst.append(["LIBDIR="+build_dir,"OPT=-Os","WOLFSSL=no","libacnsdkc_ARM_Os_HARD_NOSSL.a"])
lst.append(["LIBDIR="+build_dir,"OPT=-Og","WOLFSSL=no","libacnsdkc_ARM_Og_HARD_NOSSL.a"])

for i in lst:
	print "call(make,clean)"
	call(["make","clean"])
	print "call(make,all,"+i[0]+")"
	call(["make","all",i[0],i[1],i[2]])
	out_path = release_dir+"/"+i[3]
	print "call[cp,"+lib_path+","+out_path+"]"
	call(["cp",lib_path,out_path])

for i in lst:
	out_path = release_dir+"/"+i[3]
	print "Stat of "+out_path;
	try:
		st = os.stat(out_path);
		print "  Size: "+str(st.st_size)
	except: pass
	
