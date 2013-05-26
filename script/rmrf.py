import sys
import os
import shutil

if len(sys.argv) != 2:
	print 'Must specify a path by parameter.\n'
	sys.exit()
	
folder = sys.argv[1]

for some_file in os.listdir(folder):
	file_path = os.path.join(folder, some_file)
	
	try:
		if os.path.isfile(file_path):
			os.unlink(file_path)
		elif os.path.isdir(file_path):
			shutil.rmtree(file_path)
	except Exception, e:
		print e
