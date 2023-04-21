import os, sys, shutil

for d in next(os.walk('.'))[1]:

	if not os.path.isfile(os.path.join(d,"CMakeLists.txt")): continue

	print ("=======================================")
	print (d)
	print ("=======================================")

	os.chdir(d)

	if os.path.isdir('build'):
		shutil.rmtree('build');

	os.mkdir('build')
	os.chdir('build')

	print ("Configuring...")
	rc = os.system('cmake -A x64 ..')
	if rc != 0: sys.exit(rc)

	print ("Building...")
	rc = os.system('cmake --build . --config Release')
	if rc != 0: sys.exit(rc)

	print ("Done.")

	os.chdir('..')
	shutil.rmtree('build');
	os.chdir('..')


